#ifndef __GPIO_AT8XC5122_H_INCLUDE__
#define __GPIO_AT8XC5122_H_INCLUDE__

#include <target/config.h>
#include <target/generic.h>

#include <asm/reg.h>
#include <asm/mach/irq.h>
#include <asm/mach/pm.h>
#include <asm/mach/clk.h>

#ifdef CONFIG_GPIO_AT8XC5122
#ifndef ARCH_HAVE_GPIO
#define ARCH_HAVE_GPIO		1
#else
#error "Multiple GPIO controller defined"
#endif
#endif

/* Ports */
Sfr(P0,		0x80);		/* Port 0 */
Sbit(P0_7,	0x80, 7);
Sbit(P0_6,	0x80, 6);
Sbit(P0_5,	0x80, 5);
Sbit(P0_4,	0x80, 4);
Sbit(P0_3,	0x80, 3);
Sbit(P0_2,	0x80, 2);
Sbit(P0_1,	0x80, 1);
Sbit(P0_0,	0x80, 0);

Sfr(P1,		0x90);		/* Port 1 */
Sbit(P1_7,	0x90, 7);
Sbit(P1_6,	0x90, 6);
Sbit(P1_5,	0x90, 5);
Sbit(P1_4,	0x90, 4);
Sbit(P1_3,	0x90, 3);
Sbit(P1_2,	0x90, 2);
Sbit(P1_1,	0x90, 1);
Sbit(P1_0,	0x90, 0);

Sfr(P2,		0xA0);		/* Port 2 */
Sbit(P2_7,	0xA0, 7);
Sbit(P2_6,	0xA0, 6);
Sbit(P2_5,	0xA0, 5);
Sbit(P2_4,	0xA0, 4);
Sbit(P2_3,	0xA0, 3);
Sbit(P2_2,	0xA0, 2);
Sbit(P2_1,	0xA0, 1);
Sbit(P2_0,	0xA0, 0);

Sfr(P3,	0xB0);			/* Port 3 */
Sbit(P3_7,	0xB0, 7);
Sbit(P3_6,	0xB0, 6);
Sbit(P3_5,	0xB0, 5);
Sbit(P3_4,	0xB0, 4);
Sbit(P3_3,	0xB0, 3);
Sbit(P3_2,	0xB0, 2);
Sbit(P3_1,	0xB0, 1);
Sbit(P3_0,	0xB0, 0);

Sfr(P4,		0xC0);		/* Port 4 */
Sbit(P4_7,	0xC0, 7);
Sbit(P4_6,	0xC0, 6);
Sbit(P4_5,	0xC0, 5);
Sbit(P4_4,	0xC0, 4);
Sbit(P4_3,	0xC0, 3);
Sbit(P4_2,	0xC0, 2);
Sbit(P4_1,	0xC0, 1);
Sbit(P4_0,	0xC0, 0);

Sfr(P5,		0xE8);		/* Port 5 */
Sbit(P5_7,	0xE8, 7);
Sbit(P5_6,	0xE8, 6);
Sbit(P5_5,	0xE8, 5);
Sbit(P5_4,	0xE8, 4);
Sbit(P5_3,	0xE8, 3);
Sbit(P5_2,	0xE8, 2);
Sbit(P5_1,	0xE8, 1);
Sbit(P5_0,	0xE8, 0);

/* Port Mode Register 0 */
Sfr(PMOD0,	0x91);
/* Port Mode Register 1 */
Sfr(PMOD1,	0x84);

/* PMOD0 */
#define P3C1			7
#define P3C0			6
#define	P2C1			5
#define P2C0			4
#define P0C1			2
#define P0C0			1
/* PMOD1 */
#define P5HC1			7
#define P5HC0			6
#define P5MC1			5
#define	P5MC0			4
#define P5LC1			3
#define P5LC0			2
#define P4C1			1
#define P4C0			0

#define GPIOA			0
#define GPIOB			1
#define GPIOC			2
#define GPIOD			3
#define GPIOE			4
#define GPIOF			5

uint8_t gpio_hw_read_pin(uint8_t port, uint8_t pin);
void gpio_hw_write_pin(uint8_t port, uint8_t pin, uint8_t val);
uint8_t gpio_hw_read_port(uint8_t port);
void gpio_hw_write_port(uint8_t port, uint8_t val);

#define gpio_hw_ctrl_init()

#endif /* __GPIO_AT8XC5122_H_INCLUDE__ */
