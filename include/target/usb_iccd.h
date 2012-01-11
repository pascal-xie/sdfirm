/*
 * ZETALOG's Personal COPYRIGHT
 *
 * Copyright (c) 2009
 *    ZETALOG - "Lv ZHENG".  All rights reserved.
 *    Author: Lv "Zetalog" Zheng
 *    Internet: zetalog@gmail.com
 *
 * This COPYRIGHT used to protect Personal Intelligence Rights.
 * Redistribution and use in source and binary forms with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the Lv "Zetalog" ZHENG.
 * 3. Neither the name of this software nor the names of its developers may
 *    be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 * 4. Permission of redistribution and/or reuse of souce code partially only
 *    granted to the developer(s) in the companies ZETALOG worked.
 * 5. Any modification of this software should be published to ZETALOG unless
 *    the above copyright notice is no longer declaimed.
 *
 * THIS SOFTWARE IS PROVIDED BY THE ZETALOG AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE ZETALOG OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * @(#)usb_iccd.h: integrated circuit card devices (ICCD) interfaces
 * $Id: usb_iccd.h,v 1.32 2011-11-10 07:02:37 zhenglv Exp $
 */

#ifndef __USB_ICCD_H_INCLUDE__
#define __USB_ICCD_H_INCLUDE__

#include <target/scd.h>

#if NR_SCD_DEVICES == 0
#error "SCD device is not defined"
#endif

#define USB_INTERFACE_CLASS_ICCD	11

#define USB_PROTOCOL_ICCD_BULK		0x00
#define USB_PROTOCOL_ICCD_A		0x01
#define USB_PROTOCOL_ICCD_B		0x02

#ifdef CONFIG_ICCD_PROTO_BULK
 #define USB_PROTOCOL_ICCD	USB_PROTOCOL_ICCD_BULK
#elif defined(CONFIG_ICCD_PROTO_A)
 #define USB_PROTOCOL_ICCD	USB_PROTOCOL_ICCD_A
#elif defined(CONFIG_ICCD_PROTO_B)
 #define USB_PROTOCOL_ICCD	USB_PROTOCOL_ICCD_B
#endif

#define ICCD_RDR2PC_NOTIFYSLOTCHANGE	0x50

struct iccd_cmd {
	uint8_t  bMessageType;
	scs_size_t dwLength;
	uint8_t  bSlot;
	uint8_t  bSeq;
	uint8_t  abRFU[3];
};

struct iccd_resp {
	uint8_t  bMessageType;
	scs_size_t dwLength;
	/* Slot Status Register */
	uint8_t bStatus;
	/* Slot Error Register */
	uint8_t bError;
	uint8_t abRFU3;
};

struct iccd_t0_param {
	uint8_t bmFindexDindex;
	uint8_t bmTCCKST0;
	uint8_t bGuardTimeT0;
	uint8_t bWaitingIntegerT0;
	uint8_t bClockStop;
};

struct iccd_t1_param {
	uint8_t bmFindexDindex;
	uint8_t bmTCCKST1;
	uint8_t bGuardTimeT1;
	uint8_t bWaitingIntegerT1;
	uint8_t bClockStop;
	uint8_t bIFSC;
	uint8_t bNadValue;
};

#ifdef CONFIG_ICCD_PROTO_BULK
#define ICCD_HEADER_SIZE		10
#else
#define ICCD_HEADER_SIZE		0
#endif
#define ICCD_BUF_SIZE			261
#define ICCD_MESSAGE_SIZE		(ICCD_BUF_SIZE + ICCD_HEADER_SIZE)

struct iccd_dev {
	uint8_t state;
#define ICCD_SLOT_STATE_PC2RDR		0x00
#define ICCD_SLOT_STATE_ISO7816		0x01
#define ICCD_SLOT_STATE_RDR2PC		0x02
#define ICCD_SLOT_STATE_SANITY		0x03
};

struct iccd_hwerr {
	/* hwerr interrupt is pending */
	uint8_t bState;
#define ICCD_HWERR_PENDING	0x01
#define ICCD_HWERR_RUNNING	0x02
	uint8_t bSeq;
#define ICCD_HWERR_OVERCURRENT	0x01
	uint8_t bHardwareErrorCode;
	uint8_t bPendingSeq;
	uint8_t bPendingCode;
};
#define CCID_IRQ_HWERR_SIZE	0x04

#define ICCD_INVALID_SLOT		NR_SCD_DEVICES
#define ICCD_SINGLE_SLOT_IDX	(ICCD_MAX_BUSY_SLOT-1)

/* TODO:
 * Each intfc has the same endpoint number (NR_ICCD_ENDPS). 
 * How to improve this case?
 */
#ifdef CONFIG_ICCD_PROTO_BULK
 #ifdef CONFIG_ICCD_INTERRUPT_IN
  #define NR_ICCD_ENDPS		3
 #else
  #define NR_ICCD_ENDPS		2
 #endif
#elif defined(CONFIG_ICCD_PROTO_B)
 #ifdef CONFIG_ICCD_INTERRUPT_IN
  #define NR_ICCD_ENDPS		1
 #endif
#else
  #define NR_ICCD_ENDPS		0
#endif

#ifdef CONFIG_ICCD_PROTO_BULK
 #define ICCD_ENDP_BULK_IN		0x00
 #define ICCD_ENDP_BULK_OUT		0x01
 #define ICCD_ENDP_INTR_IN		0x02
#else
 #define ICCD_ENDP_BULK_IN		0x00	/* for compiler */
 #define ICCD_ENDP_BULK_OUT		0x00	/* for compiler */
 #define ICCD_ENDP_INTR_IN		0x00	
#endif

#define ICCD_INTR_RUNNING_SET		0x00
#define ICCD_INTR_RUNNING_UNSET		0x01
#define ICCD_INTR_PENDING_SET		0x02
#define ICCD_INTR_PENDING_UNSET		0x03
#define ICCD_INTR_ICC_PRESENT		0x04
#define ICCD_INTR_ICC_NOTPRESENT	0x05

#define ICCD_ERROR_ICC_MUTE			0xFE
#define ICCD_ERROR_XFR_OVERRUN			0xFC
#define ICCD_ERROR_HW_ERROR			0xFB
#define ICCD_ERROR_USER_DEFINED			0xC0
#define ICCD_ERROR_USER(e)			(ICCD_ERROR_USER_DEFINED-e)
#define ICCD_ERROR_RESERVED			0x80
#define ICCD_ERROR_CMD_UNSUPPORT		0x00

#define ICCD_CMD_STATUS_SUCC		(0x00 << 6)
#define ICCD_CMD_STATUS_FAIL		(0x01 << 6)
#define ICCD_CMD_STATUS_TIME_EXT	(0x02 << 6)
#define ICCD_CMD_STATUS_MASK		(0xc0)

#define ICCD_PC2RDR_ICCPOWERON		0x62
#define ICCD_PC2RDR_ICCPOWEROFF		0x63
#define ICCD_PC2RDR_XFRBLOCK		0x6F
#define ICCD_PC2RDR_GETPARAMETERS	0x6C

#define ICCD_RDR2PC_DATABLOCK		0x80
#define ICCD_RDR2PC_SLOTSTATUS		0x81

void iccd_CmdResponse_cmp(void);
void iccd_ScsSequence_cmp(scs_err_t err);
void iccd_XfrBlock_cmp(void);

void iccd_CmdOffset_cmp(uint8_t offset);
void iccd_SlotNotExist_cmp(void);
void iccd_DataBlock_cmp(scs_err_t err);

void iccd_SlotStatus_in(void);
void iccd_DataBlock_in(void);

#endif /* __USB_ICCD_H_INCLUDE__ */