/*
 * ZETALOG's Personal COPYRIGHT
 *
 * Copyright (c) 2019
 *    ZETALOG - "Lv ZHENG".  All rights reserved.
 *    Author: Lv "Zetalog" Zheng
 *    Internet: zhenglv@hotmail.com
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
 * @(#)pcc.h: PCC (Peripheral Clock Controller) definitions
 * $Id: pcc.h,v 1.279 2019-04-14 10:19:18 zhenglv Exp $
 */

#ifndef __PCC_QDF2400_H_INCLUDE__
#define __PCC_QDF2400_H_INCLUDE__

/* Accepts the clock outputs from GCCMW, generates the clocks
 * and the resets for the peripheral wrap hard macro.
 */
#define PCC_BASE			ULL(0x0FF7AC00000)

/* PCC CCs */
#define PCC_BLOCK_SHIFT			16
#define PCC_REG(blk, off)		\
	((caddr_t)PCC_BASE + ((blk) << PCC_BLOCK_SHIFT) + (off))

/* ============================================================
 * Non-BLSP
 * ============================================================ */
#define PCC_BLSP_REG(blsp, offset)	\
	PCC_REG(PCC_BLSP##blsp, (offset))

/* BLSP generic */
#define PCC_BLSP0			0x00
#define PCC_BLSP1			0x07
#define PCC_BLSP2			0x0C
#define PCC_BLSP3			0x11
#define PCC_BLSP0_BCR			PCC_BLSP_REG(0, 0x0000)
#define PCC_BLSP0_PFAB_FCLK_CBCR	PCC_BLSP_REG(0, 0x001C)
#define PCC_BLSP0_AHB_CBCR		PCC_BLSP_REG(0, 0x0020)
#define PCC_BLSP0_SLEEP_CBCR		PCC_BLSP_REG(0, 0x0024)
#define PCC_BLSP1_BCR			PCC_BLSP_REG(1, 0x0000)
#define PCC_BLSP1_PFAB_FCLK_CBCR	PCC_BLSP_REG(1, 0x0014)
#define PCC_BLSP1_AHB_CBCR		PCC_BLSP_REG(1, 0x0018)
#define PCC_BLSP1_SLEEP_CBCR		PCC_BLSP_REG(1, 0x0024)
#define PCC_BLSP2_BCR			PCC_BLSP_REG(2, 0x0000)
#define PCC_BLSP2_PFAB_FCLK_CBCR	PCC_BLSP_REG(2, 0x0014)
#define PCC_BLSP2_AHB_CBCR		PCC_BLSP_REG(2, 0x0018)
#define PCC_BLSP2_SLEEP_CBCR		PCC_BLSP_REG(2, 0x0024)
#define PCC_BLSP3_BCR			PCC_BLSP_REG(3, 0x0000)
#define PCC_BLSP3_PFAB_FCLK_CBCR	PCC_BLSP_REG(3, 0x001C)
#define PCC_BLSP3_AHB_CBCR		PCC_BLSP_REG(3, 0x0020)
#define PCC_BLSP3_SLEEP_CBCR		PCC_BLSP_REG(3, 0x0024)

/* UART */
#define PCC_BLSP0_UART0			0x03 /* UART */
#define PCC_BLSP0_UART1			0x04 /* UART */
#define PCC_BLSP0_UART2			0x05 /* UART */
#define PCC_BLSP0_UART3			0x06 /* UART */
#define PCC_BLSP3_UART0			0x14 /* UART */
#define PCC_BLSP3_UART1			0x15 /* UART */
#define PCC_BLSP3_UART2			0x16 /* UART */
#define PCC_BLSP3_UART3			0x17 /* UART */
#define PCC_UART_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_UART_CMD_RCGR(blk)		PCC_REG(blk, 0x0004) /* MND */
#define PCC_UART_MND_MASK		0xFFFF
#define PCC_UART_APPS_CBCR(blk)		PCC_REG(blk, 0x0018)

/* SPI */
#define PCC_BLSP0_QUP0			0x01 /* SPI */
#define PCC_BLSP0_QUP1			0x02 /* SPI */
#define PCC_BLSP3_QUP0			0x12 /* SPI */
#define PCC_BLSP3_QUP1			0x13 /* SPI */
#define PCC_SPI_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_SPI_CMD_RCGR(blk)		PCC_REG(blk, 0x0004) /* MND */
#define PCC_SPI_MND_MASK		0xFF
#define PCC_SPI_APPS_CBCR(blk)		PCC_REG(blk, 0x0018)

/* I2C */
#define PCC_BLSP1_QUP0			0x08 /* I2C */
#define PCC_BLSP1_QUP1			0x09 /* I2C */
#define PCC_BLSP1_QUP2			0x0A /* I2C */
#define PCC_BLSP1_QUP3			0x0B /* I2C */
#define PCC_BLSP2_QUP0			0x0D /* I2C */
#define PCC_BLSP2_QUP1			0x0E /* I2C */
#define PCC_BLSP2_QUP2			0x0F /* I2C */
#define PCC_BLSP2_QUP3			0x10 /* I2C */
/* NOTE: QUP0_I2C registers need a quirk */
#define PCC_I2C_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_I2C_CMD_RCGR(blk)		PCC_REG(blk, 0x0004)
#define PCC_I2C_APPS_CBCR(blk)		PCC_REG(blk, 0x000C)

/* ============================================================
 * Non-BLSP
 * ============================================================ */
/* I2C_SLAVE */
#define PCC_I2C_SLAVE			0x18
#define PCC_I2C_SLAVE_BCR		PCC_REG(PCC_I2C_SLAVE, 0x0000)
#define PCC_I2C0_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0004)
#define PCC_I2C1_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0008)
#define PCC_I2C2_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x000C)
#define PCC_I2C3_SLV_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x0010)
#define PCC_I2CSPI_PFAB_FCLK_CBCR	PCC_REG(PCC_I2C_SLAVE, 0x0014)
#define PCC_I2CSPI_S_AHB_CBCR		PCC_REG(PCC_I2C_SLAVE, 0x001C)

/* PDM */
#define PCC_PDM				0x1A
#define PCC_PDM_BCR			PCC_REG(PCC_PDM, 0x0000)
#define PCC_PDM2_CMD_RCGR		PCC_REG(PCC_PDM, 0x0004)
#define PCC_PDM2_CBCR			PCC_REG(PCC_PDM, 0x000C)
#define PCC_PDM_AHB_CBCR		PCC_REG(PCC_PDM, 0x0010)
#define PCC_PDM_XO4_CDIVR		PCC_REG(PCC_PDM, 0x0014)
#define PCC_PDM_XO4_CBCR		PCC_REG(PCC_PDM, 0x0018)

/* SPI_SLAVE */
#define PCC_SPI_PERIPH			0x1B
#define PCC_PERIPH_SPI_BCR		PCC_REG(PCC_SPI_PERIPH, 0x0000)

/* SPI_SLAVE */
#define PCC_SPI_SLAVE2			0x24
#define PCC_SPI_SLAVE_BCR		PCC_REG(PCC_SPI_SLAVE2, 0x0000)
#define PCC_PERIPH_SPI_CMD_RCGR		PCC_REG(PCC_SPI_SLAVE2, 0x0004)
#define PCC_PERIPH_SPI_CORE_CBCR	PCC_REG(PCC_SPI_SLAVE2, 0x000C)
#define PCC_SPI_AHB_M_CBCR		PCC_REG(PCC_SPI_SLAVE2, 0x0010)
#define PCC_SPI_SLV_AHB_CBCR		PCC_REG(PCC_SPI_SLAVE2, 0x0014)

/* PRNG */
#define PCC_PRNG0			0x1C
#define PCC_PRNG1			0x1D
#define PCC_PRNG0_BCR(blk)		PCC_REG(PCC_PRNG0, 0x0000)
#define PCC_PRNG0_AHB_CBCR(blk)		PCC_REG(PCC_PRNG0, 0x0004)
#define PCC_PRNG1_BCR(blk)		PCC_REG(PCC_PRNG1, 0x0000)
#define PCC_PRNG1_AHB_CBCR(blk)		PCC_REG(PCC_PRNG1, 0x0004)
#define PCC_PRNG_AHB_CBCR		PCC_REG(PCC_PRNG1, 0x0044)
#define PCC_PRNG_PFAB_FCLK_CBCR		PCC_REG(PCC_PRNG1, 0x0048)

/* PERIPH_FAB */
#define PCC_PFAB			0x1E
#define PCC_PFAB_BCR				PCC_REG(PCC_PFAB, 0x0000)
#define PCC_PFAB_CMD_RCGR			PCC_REG(PCC_PFAB, 0x0004)
#define PCC_PFAB_CORE_CBCR			PCC_REG(PCC_PFAB, 0x0010)
#define PCC_PFAB_SFAB_FCLK_CBCR			PCC_REG(PCC_PFAB, 0x0028)
#define PCC_PFAB_SFAB_M_AXI_CBCR		PCC_REG(PCC_PFAB, 0x002C)
#define PCC_PFAB_UPHY_XPU_AHB_FCLK_CBCR		PCC_REG(PCC_PFAB, 0x0030)
#define PCC_PFAB_CFG_AHB_CBCR			PCC_REG(PCC_PFAB, 0x0050)
#define PCC_SFAB_PFAB_QSMMUV3_CLIENT_CBCR	PCC_REG(PCC_PFAB, 0x0054)

/* SDCC */
#define PCC_SDCC0			0x1F
#define PCC_SDCC1			0x20
#define PCC_SDCC2			0x21
#define PCC_SDCC3			0x22
#define PCC_SDCC_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_SDCC_APPS_CMD_RCGR(blk)	PCC_REG(blk, 0x0004) /* MND */
#define PCC_SDCC_APPS_MND_MASK		0xFF
#define PCC_SDCC_AXI_CBCR(blk)		PCC_REG(blk, 0x0018)
#define PCC_SDCC_AHB_CBCR(blk)		PCC_REG(blk, 0x001C)
#define PCC_SDCC_APPS_CBCR(blk)		PCC_REG(blk, 0x0020)
#define PCC_SDCC_PFAB_FCLK_CBCR(blk)	PCC_REG(blk, 0x0030)

/* USB2 */
#define PCC_USB2_0			0x27
#define PCC_USB2_1			0x28
#define PCC_USB2_2			0x29
#define PCC_USB2_3			0x2A
#define PCC_USB2_BCR(blk)		PCC_REG(blk, 0x0000)
#define PCC_USB2_PHY_AHB_CBCR(blk)	PCC_REG(blk, 0x0008)
#define PCC_USB2_MSTR_CBCR(blk)		PCC_REG(blk, 0x000C)
#define PCC_USB2_SLEEP_CBCR(blk)	PCC_REG(blk, 0x0010)
#define PCC_USB2_MOCK_UTMI_CBCR(blk)	PCC_REG(blk, 0x0014)
#define PCC_USB2_PHY_RESET(blk)		PCC_REG(blk, 0x0100)
#define PCC_USB2_PHY_SLEEP_CBCR(blk)	PCC_REG(blk, 0x0104)

/* USB2 special */
#define PCC_USB2_MSTR			0x26
#define PCC_USB2_PFAB			0x2B
#define PCC_USB2_MSTR_CMD_RCGR		PCC_REG(PCC_USB2_MSTR, 0x0000)
#define PCC_USB2_MSTR_AHB_CBCR		PCC_REG(PCC_USB2_MSTR, 0x0008)
#define PCC_USB2_PFAB_FCLK_CBCR		PCC_REG(PCC_USB2_PFAB, 0x0000)

/* MISC */
#define PCC_MISC			0x3A
#define PCC_ABH2MSM_PFAB_CFG_AHB_CBCR	PCC_REG(PCC_MISC, 0x0008)
#define PCC_I2C_XO_CBCR			PCC_REG(PCC_MISC, 0x001C)
#define PCC_IM_SLEEP_CBCR		PCC_REG(PCC_MISC, 0x0020)
#define PCC_USB2_1_SLEEP_CBCR		PCC_REG(PCC_MISC, 0x0060)
#define PCC_XO_CBCR			PCC_REG(PCC_MISC, 0x0074)

#endif /* __PCC_QDF2400_H_INCLUDE__ */
