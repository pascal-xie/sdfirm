/* ACR122U101 */
#include <driver/acr122.h>
#include <target/timer.h>

#define ACR122_POLL_TIMEOUT		0x10
#define ACR122_POLL_MAXIMUM		50

#define ACR122_BUF_SIZE			255

#define ACR122_XCHG_STATE_CMD		0x00
#define ACR122_XCHG_STATE_RESP		0x01

static scs_cmpl_cb acr122_complete = NULL;
static struct acr122_pseudo_apdu acr122_apdu;
static uint8_t acr122_buf[ACR122_BUF_SIZE];
static uint8_t acr122_state;
static uint8_t acr122_poll;

static tid_t acr122_tid = INVALID_TID;

static void acr122_write_ack(void);
static void acr122_write_cmd(void);

static void acr122_set_sw(uint8_t sw1, uint8_t sw2)
{
	acr122_apdu.ne = 0;
	acr122_apdu.sw1 = sw1;
	acr122_apdu.sw2 = sw2;
}
#define acr122_set_sw_default()		acr122_set_sw(0x90, 0x00)
#define acr122_set_sw_length(len)	acr122_set_sw(0x61, (len)+2)
#define acr122_set_sw_error(err)	acr122_set_sw(0x63, (err))

scs_err_t acr122_get_error(void)
{
	return SCS_ERR_SUCCESS;
}

static void acr122_set_error(scs_err_t err)
{
	switch (err) {
	case SCS_ERR_TIMEOUT:
		acr122_set_sw_error(ACR122_SW2_TIMEOUT);
		break;
	case SCS_ERR_PARITY_ERR:
		acr122_set_sw_error(ACR122_SW2_PARITY);
		break;
	default:
		if (err & SCS_ERR_SANITY)
			acr122_set_sw_error(ACR122_SW2_SANITY);
		break;
	}
}
#define acr122_set_sanity(i)		acr122_set_error(SCS_ERR_SANITY|(i))

static void acr122_set_state(uint8_t state, uint8_t poll)
{
	acr122_state = state;
	acr122_poll = poll;
}

void acr122_register_completion(scs_cmpl_cb completion)
{
	acr122_complete = completion;
}

scs_size_t acr122_xchg_avail(void)
{
	return acr122_apdu.ne + 2;
}

uint8_t acr122_read_byte(scs_off_t index)
{
	if (index < acr122_apdu.ne) {
		return acr122_buf[index];
	} else {
		if (acr122_apdu.p1 == 0x48) {
			if (index < 10)
				return acr122_buf[index];
		} else {
			if (index == acr122_apdu.ne)
				return acr122_apdu.sw1;
			else if (index == (acr122_apdu.ne+1))
				return acr122_apdu.sw2;
		}
	}
	return 0;
}

void acr122_write_byte(scs_off_t index, uint8_t value)
{
	if (index == 0) {
		acr122_apdu.nc = 0;
		acr122_set_sw_default();
	} else {
		if (acr122_apdu.sw1 != 0x90)
			return;
	}

	switch (index) {
	case 0:
		if (value != 0xFF)
			acr122_set_sanity(index);
		break;
	case 1:
		if (value == 0xC0) {
			if (acr122_state != ACR122_XCHG_STATE_RESP)
				acr122_set_sanity(index);
		} else if (value != 0x00) {
			acr122_set_sanity(index);
		}
		if (acr122_apdu.sw1 == 0x90)
			acr122_apdu.ins = value;
		break;
	case 2:
		if (acr122_apdu.ins == 0x00) {
			if ((value != 0x00) &&
			    (value != 0x40) && (value != 0x48))
				acr122_set_sanity(index);
		} else {
			if (value != 0x00)
				acr122_set_sanity(index);
		}
		if (acr122_apdu.sw1 == 0x90)
			acr122_apdu.p1 = value;
		break;
	case 3:
		if (value != 0x00)
			acr122_set_sanity(index);
		break;
	case 4:
		if (acr122_apdu.ins == 0x00) {
			acr122_apdu.nc = value;
			acr122_apdu.ne = 0;
		} else {
			acr122_apdu.nc = 0;
			acr122_apdu.ne = (value-2);
		}
		break;
	default:
		if ((index-ACR122_HEAD_SIZE) >= acr122_apdu.nc)
			acr122_set_sanity(index);
		else
			acr122_buf[index-ACR122_HEAD_SIZE] = value;
		break;
	}
}

static void __acr122_write_preamble(void)
{
	pn53x_xchg_write(0, 0x00);
	pn53x_xchg_write(1, 0x00);
	pn53x_xchg_write(2, 0xFF);
}

static void acr122_write_ack(void)
{
	__acr122_write_preamble();
	pn53x_xchg_write(PN53X_LEN, HIBYTE(PN53X_ACK));
	pn53x_xchg_write(PN53X_LCS, LOBYTE(PN53X_ACK));
	pn53x_xchg_write(5, 0x00);
	pn53x_write_cmpl(6);
}

static void acr122_write_cmd(void)
{
	uint8_t i;
	uint8_t dcs = 0;

	__acr122_write_preamble();
	pn53x_xchg_write(PN53X_LEN, acr122_apdu.nc);
	pn53x_xchg_write(PN53X_LCS, (uint8_t)(-acr122_apdu.nc));

	for (i = 0; i < acr122_apdu.nc; i++) {
		dcs += acr122_buf[i];
		pn53x_xchg_write(i+PN53X_HEAD_SIZE-1, acr122_buf[i]);
	}

	i += (PN53X_HEAD_SIZE-1);
	pn53x_xchg_write(i++, (uint8_t)(-dcs));
	pn53x_xchg_write(i++, 0);
	pn53x_write_cmpl(i);
}

static void acr122_xchg_end(uint8_t state)
{
	acr122_write_ack();
	acr122_set_state(state, 0);
	if (acr122_complete)
		acr122_complete();
}

static scs_err_t acr122_xchg_begin(void)
{
	acr122_write_cmd();
	acr122_set_state(ACR122_XCHG_STATE_CMD, 1);
	return SCS_ERR_PROGRESS;
}

scs_err_t acr122_xchg_block(scs_size_t nc, scs_size_t ne)
{
	if (acr122_apdu.sw1 != 0x90) {
		return SCS_ERR_SUCCESS;
	}

	switch (acr122_apdu.ins) {
	case 0x00:
		switch (acr122_apdu.p1) {
		case 0x00:
			return acr122_xchg_begin();
			break;
		case 0x40:
			break;
		case 0x48:
			acr122_buf[0x00] = 0x41;
			acr122_buf[0x01] = 0x43;
			acr122_buf[0x02] = 0x52;
			acr122_buf[0x03] = 0x31;
			acr122_buf[0x04] = 0x32;
			acr122_buf[0x05] = 0x32;
			acr122_buf[0x06] = 0x55;
			acr122_buf[0x07] = 0x31;
			acr122_buf[0x08] = 0x30;
			acr122_buf[0x09] = 0x31;
			acr122_apdu.ne = 8;
			break;
		default:
			BUG();
			break;
		}
		break;
	case 0xC0:
		BUG_ON(acr122_state != ACR122_XCHG_STATE_RESP);
		break;
	default:
		BUG();
		break;
	}
	return SCS_ERR_SUCCESS;
}

static void acr122_xchg_failure(scs_err_t err)
{
	acr122_set_error(err);
	acr122_xchg_end(ACR122_XCHG_STATE_CMD);
}

static void acr122_xchg_success(uint8_t len)
{
	acr122_set_sw_length(len);
	acr122_xchg_end(ACR122_XCHG_STATE_RESP);
}

static void acr122_read_completion(scs_off_t i)
{
	uint8_t val;
	val = pn53x_xchg_read(i++);
	pn53x_read_cmpl(i);
}

static void acr122_poll_completion(void)
{
	scs_off_t i;
	uint8_t head[PN53X_HEAD_SIZE-1];

	BUG_ON(acr122_poll == 0);

	for (i = 0; i < (PN53X_HEAD_SIZE-1); i++)
		head[i] = pn53x_xchg_read(i);

	if ((acr122_state == ACR122_XCHG_STATE_RESP) &&
	    ((uint8_t)(head[PN53X_LEN] + head[PN53X_LCS]) != 0)) {
		acr122_read_completion(PN53X_HEAD_SIZE-1);
		if (PN53X_EXTEND(head))
			acr122_xchg_failure(SCS_ERR_UNSUPPORT);
		else
			acr122_xchg_failure(SCS_ERR_PARITY_ERR);
		return;
	}

	if (!PN53X_NORMAL(head)) {
		acr122_read_completion(PN53X_HEAD_SIZE-1);
		if ((pn53x_type(head) == PN53X_ACK) &&
		    (acr122_state == ACR122_XCHG_STATE_CMD)) {
			acr122_set_state(ACR122_XCHG_STATE_RESP, 1);
			return;
		}
		acr122_xchg_failure(SCS_ERR_PARITY_ERR);
	} else {
		uint8_t dcs = 0;
		uint8_t value;
		uint8_t len = head[PN53X_LEN];

		for (i = 0; i < len; i++) {
			value = pn53x_xchg_read(i+PN53X_HEAD_SIZE-1);
			dcs += value;
			acr122_buf[i] = value;
		}
		i += (PN53X_HEAD_SIZE-1);
		dcs += pn53x_xchg_read(i++);
		acr122_read_completion(i);

		if (dcs != 0) {
			acr122_xchg_failure(SCS_ERR_PARITY_ERR);
		} else {
			acr122_xchg_success(len);
		}
	}
}

static void acr122_poll_ready(void)
{
	if (pn53x_poll_ready()) {
		acr122_poll_completion();
	} else {
		acr122_poll++;
		if (acr122_poll > ACR122_POLL_MAXIMUM) {
			acr122_xchg_failure(SCS_ERR_TIMEOUT);
		}
	}
}

static void acr122_timer_handler(void)
{
	if (acr122_poll > 0)
		acr122_poll_ready();
	timer_schedule_shot(acr122_tid, ACR122_POLL_TIMEOUT);
}

timer_desc_t acr122_timer = {
	TIMER_BH,
	acr122_timer_handler,
};

void acr122_init(void)
{
	pn53x_ctrl_init();
	acr122_set_state(ACR122_XCHG_STATE_CMD, 0);
	acr122_tid = timer_register(&acr122_timer);
	timer_schedule_shot(acr122_tid, ACR122_POLL_TIMEOUT);
}
