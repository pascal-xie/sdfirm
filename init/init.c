#include <target/config.h>
#include <target/io.h>

/* This could be optimized on gcc by calling init functions from a link
 * stage array.  As SDCC can not support this and firmware may not include
 * so many modules, we decide to list all of the functions here after.
 */
/* prior subsystems */
#ifdef CONFIG_UART
void uart_init(void);
#else
#define uart_init()
#endif

#ifdef CONFIG_TIMER
void timer_init(void);
#else
#define timer_init()
#endif

#ifdef CONFIG_HEAP
extern void heap_init(void);
#else
#define heap_init()
#endif

#ifdef CONFIG_TASK
void task_init(void);
#else
#define task_init()
#endif

/* normal subsystems */
#ifdef CONFIG_I2C
void i2c_init(void);
#else
#define i2c_init()
#endif

#ifdef CONFIG_SPI
void spi_init(void);
#else
#define spi_init()
#endif

#ifdef CONFIG_MTD
void mtd_init(void);
#else
#define mtd_init()
#endif

#ifdef CONFIG_SCSI
void scsi_init(void);
#else
#define scsi_init()
#endif

#ifdef CONFIG_USB
void usb_init(void);
#else
#define usb_init()
#endif

#ifdef CONFIG_LCD
void lcd_init(void);
#else
#define lcd_init()
#endif

#ifdef CONFIG_LED
void led_init(void);
#else
#define led_init()
#endif

#ifdef CONFIG_KBD
void kbd_init(void);
#else
#define kbd_init()
#endif

#ifdef CONFIG_IFD
void ifd_init(void);
#else
#define ifd_init()
#endif

#ifdef CONFIG_SCD
void scd_init(void);
#else
#define scd_init()
#endif

#ifdef CONFIG_ICC
void icc_init(void);
#else
#define icc_init()
#endif

/* modules */
#ifdef CONFIG_MTD_FLASH
void flash_init(void);
#else
#define flash_init()
#endif

#ifdef CONFIG_MTD_DATAFLASH
void dataflash_init(void);
#else
#define dataflash_init()
#endif

#ifdef CONFIG_USB_HID
void hid_init(void);
#else
#define hid_init()
#endif

#ifdef CONFIG_USB_DFU
void dfu_init(void);
#else
#define dfu_init()
#endif

#ifdef CONFIG_USB_MSD
void msd_init(void);
#else
#define msd_init()
#endif

#ifdef CONFIG_USB_CCID
void ccid_init(void);
#else
#define ccid_init()
#endif

#ifdef CONFIG_USB_ICCD
void iccd_init(void);
#else
#define iccd_init()
#endif

#ifdef CONFIG_COS
void cos_init(void);
#else
#define cos_init()
#endif

#ifdef CONFIG_NET
void net_init(void);
#else
#define net_init()
#endif

void modules_init(void)
{
	/* prior subsys */
	uart_init();
	heap_init();
	timer_init();

	/* normal subsys */
	net_init();
	mtd_init();
	led_init();
	usb_init();
	scsi_init();
	kbd_init();
	i2c_init();
	lcd_init();
	spi_init();
	scd_init();
	ifd_init();
	icc_init();

	/* modules */
	flash_init();
	dataflash_init();
	hid_init();
	msd_init();
	ccid_init();
	iccd_init();
	cos_init();
	dfu_init();

	task_init();
}