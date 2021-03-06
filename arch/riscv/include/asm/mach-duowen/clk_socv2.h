/*
 * ZETALOG's Personal COPYRIGHT
 *
 * Copyright (c) 2020
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
 * @(#)clk_socv2.h: DUOWEN SOCv2 clock controller definitions
 * $Id: clk_socv2.h,v 1.1 2020-10-26 17:06:00 zhenglv Exp $
 */

#ifndef __CLK_SOCv2_DUOWEN_H_INCLUDE__
#define __CLK_SOCV2_DUOWEN_H_INCLUDE__

#ifdef CONFIG_DUOWEN_ASIC
#define CLK_INPUT		((clk_cat_t)0)
#define CLK_VCO			((clk_cat_t)1)
#define CLK_PLL			((clk_cat_t)2)
#define CLK_SELECT		((clk_cat_t)3)
#define CLK_OUTPUT		((clk_cat_t)4)
#define CLK_DIV			((clk_cat_t)5)

/* CLK_INPUT */
#define XO_CLK			((clk_clk_t)0)
#define TIC_CLK			((clk_clk_t)1)
#define JTAG_CLK		((clk_clk_t)2)
#define NR_INPUT_CLKS		(JTAG_CLK + 1)
#define xo_clk			clkid(CLK_INPUT, XO_CLK)
#define tic_clk			clkid(CLK_INPUT, TIC_CLK)
#define jtag_clk		clkid(CLK_INPUT, JTAG_CLK)

/* CLK_VCO */
#define SOC_VCO			SOC_PLL
#define DDR_BUS_VCO		DDR_BUS_PLL
#define DDR_VCO			DDR_PLL
#define PCIE_VCO		PCIE_PLL
#define COHFAB_VCO		COHFAB_PLL
#define CL0_VCO			CL0_PLL
#define CL1_VCO			CL1_PLL
#define CL2_VCO			CL2_PLL
#define CL3_VCO			CL3_PLL
#define ETH_VCO			ETH_PLL
#define NR_VCO_CLKS		DUOWEN_MAX_PLLS
#define soc_vco			clkid(CLK_VCO, SOC_VCO)
#define ddr_bus_vco		clkid(CLK_VCO, DDR_BUS_VCO)
#define ddr_vco			clkid(CLK_VCO, DDR_VCO)
#define pcie_vco		clkid(CLK_VCO, PCIE_VCO)
#define cohfab_vco		clkid(CLK_VCO, COHFAB_VCO)
#define cl0_vco			clkid(CLK_VCO, CL0_VCO)
#define cl1_vco			clkid(CLK_VCO, CL1_VCO)
#define cl2_vco			clkid(CLK_VCO, CL2_VCO)
#define cl3_vco			clkid(CLK_VCO, CL3_VCO)
#define eth_vco			clkid(CLK_VCO, ETH_VCO)

/* CLK_PLL */
/* P PLL_OUT clocks use same name as PLLs, R PLL_OUT clocks are defined
 * here.
 */
#define SYSFAB_PLL		(DUOWEN_MAX_PLLS + SOC_PLL)
#define SGMII_PLL		(DUOWEN_MAX_PLLS + ETH_PLL)
#define NR_PLL_CLKS		(SGMII_PLL + 1)
#define soc_pll			clkid(CLK_PLL, SOC_PLL)
#define ddr_bus_pll		clkid(CLK_PLL, DDR_BUS_PLL)
#define ddr_pll			clkid(CLK_PLL, DDR_PLL)
#define pcie_pll		clkid(CLK_PLL, PCIE_PLL)
#define cohfab_pll		clkid(CLK_PLL, COHFAB_PLL)
#define cl0_pll			clkid(CLK_PLL, CL0_PLL)
#define cl1_pll			clkid(CLK_PLL, CL1_PLL)
#define cl2_pll			clkid(CLK_PLL, CL2_PLL)
#define cl3_pll			clkid(CLK_PLL, CL3_PLL)
#define eth_pll			clkid(CLK_PLL, ETH_PLL)
#define sysfab_pll		clkid(CLK_PLL, SYSFAB_PLL)
#define sgmii_pll		clkid(CLK_PLL, SGMII_PLL)

/* CLK_SELECT: CLK_SEL_CFG */
#define SOC_CLK_DIV2_SEL	((clk_clk_t)0) /* SOC_PLL P clock div2 */
#define SYSFAB_CLK_SEL		((clk_clk_t)1) /* SOC_PLL R clock */
#define DDR_BUS_CLK_SEL		((clk_clk_t)2)
#define DDR_CLK_SEL		((clk_clk_t)3)
#define PCIE_REF_CLK_SEL	((clk_clk_t)4)
#define SOC_CLK_SEL		((clk_clk_t)5) /* SOC_PLL P clock */
#define COHFAB_CLK_SEL		((clk_clk_t)7)
#define CL0_CLK_SEL		((clk_clk_t)8)
#define CL1_CLK_SEL		((clk_clk_t)9)
#define CL2_CLK_SEL		((clk_clk_t)10)
#define CL3_CLK_SEL		((clk_clk_t)11)
#define NR_SELECT_CLKS		(CL3_CLK_SEL + 1)
#define soc_clk_div2_sel	clkid(CLK_SELECT, SOC_CLK_DIV2_SEL)
#define sysfab_clk_sel		clkid(CLK_SELECT, SYSFAB_CLK_SEL)
#define soc_clk_sel		clkid(CLK_SELECT, SOC_CLK_SEL)
#define ddr_bus_clk_sel		clkid(CLK_SELECT, DDR_BUS_CLK_SEL)
#define ddr_clk_sel		clkid(CLK_SELECT, DDR_CLK_SEL)
#define pcie_ref_clk_sel	clkid(CLK_SELECT, PCIE_REF_CLK_SEL)
#define soc_clk_sel		clkid(CLK_SELECT, SOC_CLK_SEL)
#define cohfab_clk_sel		clkid(CLK_SELECT, COHFAB_CLK_SEL)
#define cl0_clk_sel		clkid(CLK_SELECT, CL0_CLK_SEL)
#define cl1_clk_sel		clkid(CLK_SELECT, CL1_CLK_SEL)
#define cl2_clk_sel		clkid(CLK_SELECT, CL2_CLK_SEL)
#define cl3_clk_sel		clkid(CLK_SELECT, CL3_CLK_SEL)
#endif

#ifdef CONFIG_DUOWEN_ZEBU
#define CLK_INPUT		((clk_cat_t)0)
#define CLK_SELECT		((clk_cat_t)1)
#define CLK_OUTPUT		((clk_cat_t)2)
#define CLK_DIV			((clk_cat_t)3)

/* CLK_INPUT */
#define CLK_PLL			CLK_INPUT
#define SYSFAB_PLL		((clk_clk_t)(DUOWEN_MAX_PLLS + 0))
#define SGMII_PLL		((clk_clk_t)(DUOWEN_MAX_PLLS + 1))
#define XO_CLK			((clk_clk_t)(DUOWEN_MAX_PLLS + 2))
#define TIC_CLK			((clk_clk_t)(DUOWEN_MAX_PLLS + 3))
#define JTAG_CLK		((clk_clk_t)(DUOWEN_MAX_PLLS + 4))
#define NR_INPUT_CLKS		(JTAG_CLK + 1)
#define soc_pll			clkid(CLK_PLL, SOC_PLL)
#define ddr_bus_pll		clkid(CLK_PLL, DDR_BUS_PLL)
#define ddr_pll			clkid(CLK_PLL, DDR_PLL)
#define pcie_pll		clkid(CLK_PLL, PCIE_PLL)
#define cohfab_pll		clkid(CLK_PLL, COHFAB_PLL)
#define cl0_pll			clkid(CLK_PLL, CL0_PLL)
#define cl1_pll			clkid(CLK_PLL, CL1_PLL)
#define cl2_pll			clkid(CLK_PLL, CL2_PLL)
#define cl3_pll			clkid(CLK_PLL, CL3_PLL)
#define eth_pll			clkid(CLK_PLL, ETH_PLL)
#define sysfab_pll		clkid(CLK_PLL, SYSFAB_PLL)
#define sgmii_pll		clkid(CLK_PLL, SGMII_PLL)
#define xo_clk			clkid(CLK_INPUT, XO_CLK)
#define tic_clk			clkid(CLK_INPUT, TIC_CLK)
#define jtag_clk		clkid(CLK_INPUT, JTAG_CLK)

/* CLK_SELECT: CLK_SEL_CFG */
#define SOC_CLK_DIV2_SEL	((clk_clk_t)0)
#define SYSFAB_CLK_SEL		((clk_clk_t)1)
#define DDR_BUS_CLK_SEL		((clk_clk_t)2)
#define DDR_CLK_SEL		((clk_clk_t)3)
#define PCIE_REF_CLK_SEL	((clk_clk_t)4)
#define SOC_CLK_SEL		((clk_clk_t)5)
#define COHFAB_CLK_SEL		((clk_clk_t)7)
#define CL0_CLK_SEL		((clk_clk_t)8)
#define CL1_CLK_SEL		((clk_clk_t)9)
#define CL2_CLK_SEL		((clk_clk_t)10)
#define CL3_CLK_SEL		((clk_clk_t)11)
#define NR_SELECT_CLKS		(CL3_CLK_SEL + 1)
#define soc_clk_div2_sel	clkid(CLK_SELECT, SOC_CLK_DIV2_SEL)
#define sysfab_clk_sel		clkid(CLK_SELECT, SYSFAB_CLK_SEL)
#define ddr_bus_clk_sel		clkid(CLK_SELECT, DDR_BUS_CLK_SEL)
#define ddr_clk_sel		clkid(CLK_SELECT, DDR_CLK_SEL)
#define pcie_ref_clk_sel	clkid(CLK_SELECT, PCIE_REF_CLK_SEL)
#define soc_clk_sel		clkid(CLK_SELECT, SOC_CLK_SEL)
#define cohfab_clk_sel		clkid(CLK_SELECT, COHFAB_CLK_SEL)
#define cl0_clk_sel		clkid(CLK_SELECT, CL0_CLK_SEL)
#define cl1_clk_sel		clkid(CLK_SELECT, CL1_CLK_SEL)
#define cl2_clk_sel		clkid(CLK_SELECT, CL2_CLK_SEL)
#define cl3_clk_sel		clkid(CLK_SELECT, CL3_CLK_SEL)
#endif

#ifdef CONFIG_DUOWEN_FPGA
#define CLK_INPUT		((clk_cat_t)0)
#define CLK_OUTPUT		((clk_cat_t)1)
#define CLK_DIV			((clk_cat_t)2)

/* CLK_INPUT */
#define CLK_PLL			CLK_INPUT
#define CLK_SELECT		CLK_INPUT
#define SYSFAB_PLL		((clk_clk_t)(DUOWEN_MAX_PLLS + 0))
#define SGMII_PLL		((clk_clk_t)(DUOWEN_MAX_PLLS + 1))
#define XO_CLK			((clk_clk_t)(DUOWEN_MAX_PLLS + 2))
#define TIC_CLK			((clk_clk_t)(DUOWEN_MAX_PLLS + 3))
#define JTAG_CLK		((clk_clk_t)(DUOWEN_MAX_PLLS + 4))
#define NR_INPUT_CLKS		(JTAG_CLK + 1)
#define soc_pll			clkid(CLK_PLL, SOC_PLL)
#define ddr_bus_pll		clkid(CLK_PLL, DDR_BUS_PLL)
#define ddr_pll			clkid(CLK_PLL, DDR_PLL)
#define pcie_pll		clkid(CLK_PLL, PCIE_PLL)
#define cohfab_pll		clkid(CLK_PLL, COHFAB_PLL)
#define cl0_pll			clkid(CLK_PLL, CL0_PLL)
#define cl1_pll			clkid(CLK_PLL, CL1_PLL)
#define cl2_pll			clkid(CLK_PLL, CL2_PLL)
#define cl3_pll			clkid(CLK_PLL, CL3_PLL)
#define eth_pll			clkid(CLK_PLL, ETH_PLL)
#define sysfab_pll		clkid(CLK_PLL, SYSFAB_PLL)
#define sgmii_pll		clkid(CLK_PLL, SGMII_PLL)
#define xo_clk			clkid(CLK_INPUT, XO_CLK)
#define tic_clk			clkid(CLK_INPUT, TIC_CLK)
#define jtag_clk		clkid(CLK_INPUT, JTAG_CLK)
#define soc_clk_div2_sel	soc_clk_div2
#define sysfab_clk_sel		sysfab_pll
#define ddr_bus_clk_sel		ddr_bus_pll
#define ddr_clk_sel		ddr_pll
#define pcie_ref_clk_sel	pcie_pll
#define soc_clk_sel		soc_pll
#define cohfab_clk_sel		cohfab_pll
#define cl0_clk_sel		cl0_pll
#define cl1_clk_sel		cl1_pll
#define cl2_clk_sel		cl2_pll
#define cl3_clk_sel		cl3_pll
#endif

/* Alias for select clocks */
#define pcie_axi_clk_sel	soc_clk_sel
#define sysfab_500m_clk_sel	soc_clk_div2_sel
#define sysfab_100m_clk_sel	sysfab_clk_sel
#define sysfab_100m_clk		sysfab_100m_clk_sel
#define sysfab_500m_clk		sysfab_500m_clk_sel
#define soc_clk			sysfab_500m_clk
#define sysfab_clk		sysfab_100m_clk
#define pcie_axi_clk		pcie_axi_clk_sel

/* CLK_OUTPUT: CLK_EN_CFG0 */
#define DMA_CLK			((clk_clk_t)0)
#define PCIE_POR		((clk_clk_t)1) /* SW_RST only */
#define PCIE_CLK		((clk_clk_t)2)
#define DDR_POR			((clk_clk_t)4) /* SW_RST only */
#define DDR_BYPASS_PCLK		((clk_clk_t)5) /* CLK_EN only */
#define DDR_PCLK		((clk_clk_t)6)
#define DDR_ACLK		((clk_clk_t)7)
#define DDR_CLK			((clk_clk_t)8)
#define DDR_RST			((clk_clk_t)9)
#define SYSFAB_DBG_CLK		((clk_clk_t)10)
#define SYSFAB_TIC_CLK		((clk_clk_t)11)
#define CLUSTER0_HCLK		((clk_clk_t)12)
#define CLUSTER1_HCLK		((clk_clk_t)13)
#define CLUSTER2_HCLK		((clk_clk_t)14)
#define CLUSTER3_HCLK		((clk_clk_t)15)
#define COHFAB_HCLK		((clk_clk_t)16)
#define SCSR_CLK		((clk_clk_t)19)
#define TLMM_CLK		((clk_clk_t)20)
#define PLIC_CLK		((clk_clk_t)21)
#define TIC_RST			((clk_clk_t)23) /* SW_RST only */
#define DBG_RST			((clk_clk_t)24) /* SW_RST only */
#define TMR0_CLK		((clk_clk_t)25)
#define TMR1_CLK		((clk_clk_t)26)
#define TMR2_CLK		((clk_clk_t)27)
#define TMR3_CLK		((clk_clk_t)28)
#define WDT0_CLK		((clk_clk_t)29)
#define WDT1_CLK		((clk_clk_t)30)

/* CLK_OUTPUT: CLK_EN_CFG1 */
#define GPIO0_CLK		((clk_clk_t)32)
#define GPIO1_CLK		((clk_clk_t)33)
#define GPIO2_CLK		((clk_clk_t)34)
#define UART0_CLK		((clk_clk_t)35)
#define UART1_CLK		((clk_clk_t)36)
#define UART2_CLK		((clk_clk_t)37)
#define UART3_CLK		((clk_clk_t)38)
#define I2C0_CLK		((clk_clk_t)39)
#define I2C1_CLK		((clk_clk_t)40)
#define I2C2_CLK		((clk_clk_t)41)
#define I2C3_CLK		((clk_clk_t)42)
#define I2C4_CLK		((clk_clk_t)43)
#define I2C5_CLK		((clk_clk_t)44)
#define I2C6_CLK		((clk_clk_t)45)
#define I2C7_CLK		((clk_clk_t)46)
#define I2C8_CLK		((clk_clk_t)47)
#define I2C9_CLK		((clk_clk_t)48)
#define I2C10_CLK		((clk_clk_t)49)
#define I2C11_CLK		((clk_clk_t)50)
#define SPI0_CLK		((clk_clk_t)51)
#define SPI1_CLK		((clk_clk_t)52)
#define SPI2_CLK		((clk_clk_t)53)
#define SPI3_CLK		((clk_clk_t)54)
#define SPI4_CLK		((clk_clk_t)55)
#define SPI_FLASH_CLK		((clk_clk_t)56)
#define SD_CLK			((clk_clk_t)57)
#define ETH_CLK			((clk_clk_t)58)
#define TSENSOR_CLK		((clk_clk_t)63)

/* CLK_OUTPUT: CLK_EN_CFG2 */

/* CLK_OUTPUT: CLK_EN_CFG3 */
#define IMC_CLK			((clk_clk_t)96)

/* Additional output clocks */
#define COHFAB_CFG_CLK		((clk_clk_t)97)
#define PCIE_PCLK		((clk_clk_t)98)
#define ETH_ALT_REF_CLK		((clk_clk_t)99)
#define SGMII_REF_CLK		((clk_clk_t)100)

/* CLK_OUTPUT: CLUSTER/COHFAB CLK_CFG */
#define COHFAB_CLK		((clk_clk_t)104)
#define CLUSTER0_CLK		((clk_clk_t)105)
#define CLUSTER1_CLK		((clk_clk_t)106)
#define CLUSTER2_CLK		((clk_clk_t)107)
#define CLUSTER3_CLK		((clk_clk_t)108)

/* CLK_OUTPUT: CLUSTER internal CLK_CG/RST_CTRL */
#define CLUSTER0_APC0_CPU0_CLK	((clk_clk_t)112)
#define CLUSTER0_APC0_CPU1_CLK	((clk_clk_t)113)
#define CLUSTER0_APC1_CPU0_CLK	((clk_clk_t)114)
#define CLUSTER0_APC1_CPU1_CLK	((clk_clk_t)115)
#define CLUSTER0_APC0_L2_CLK	((clk_clk_t)116)
#define CLUSTER0_APC1_L2_CLK	((clk_clk_t)117)
#define CLUSTER1_APC0_CPU0_CLK	((clk_clk_t)118)
#define CLUSTER1_APC0_CPU1_CLK	((clk_clk_t)119)
#define CLUSTER1_APC1_CPU0_CLK	((clk_clk_t)120)
#define CLUSTER1_APC1_CPU1_CLK	((clk_clk_t)121)
#define CLUSTER1_APC0_L2_CLK	((clk_clk_t)122)
#define CLUSTER1_APC1_L2_CLK	((clk_clk_t)123)
#define CLUSTER2_APC0_CPU0_CLK	((clk_clk_t)124)
#define CLUSTER2_APC0_CPU1_CLK	((clk_clk_t)125)
#define CLUSTER2_APC1_CPU0_CLK	((clk_clk_t)126)
#define CLUSTER2_APC1_CPU1_CLK	((clk_clk_t)127)
#define CLUSTER2_APC0_L2_CLK	((clk_clk_t)128)
#define CLUSTER2_APC1_L2_CLK	((clk_clk_t)129)
#define CLUSTER3_APC0_CPU0_CLK	((clk_clk_t)130)
#define CLUSTER3_APC0_CPU1_CLK	((clk_clk_t)131)
#define CLUSTER3_APC1_CPU0_CLK	((clk_clk_t)132)
#define CLUSTER3_APC1_CPU1_CLK	((clk_clk_t)133)
#define CLUSTER3_APC0_L2_CLK	((clk_clk_t)134)
#define CLUSTER3_APC1_L2_CLK	((clk_clk_t)135)
#define NR_OUTPUT_CLKS		(CLUSTER3_APC1_L2_CLK + 1)

/* CLK_OUTPUT: CLK_EN_CFG0 */
/* Integrated overall clocks */
#define dma_clk			clkid(CLK_OUTPUT, DMA_CLK)
#define ddr_por			clkid(CLK_OUTPUT, DDR_POR)
#define ddr_bypass_pclk		clkid(CLK_OUTPUT, DDR_BYPASS_PCLK)
#define ddr_pclk		clkid(CLK_OUTPUT, DDR_PCLK)
#define ddr_aclk		clkid(CLK_OUTPUT, DDR_ACLK)
#define ddr_clk			clkid(CLK_OUTPUT, DDR_CLK)
#define ddr_rst			clkid(CLK_OUTPUT, DDR_RST)
#define pcie_por		clkid(CLK_OUTPUT, PCIE_POR)
#define pcie_clk		clkid(CLK_OUTPUT, PCIE_CLK)
#define sysfab_dbg_clk		clkid(CLK_OUTPUT, SYSFAB_DBG_CLK)
#define sysfab_tic_clk		clkid(CLK_OUTPUT, SYSFAB_TIC_CLK)
/* Internal bus clocks */
#define cluster0_hclk		clkid(CLK_OUTPUT, CLUSTER0_HCLK)
#define cluster1_hclk		clkid(CLK_OUTPUT, CLUSTER1_HCLK)
#define cluster2_hclk		clkid(CLK_OUTPUT, CLUSTER2_HCLK)
#define cluster3_hclk		clkid(CLK_OUTPUT, CLUSTER3_HCLK)
#define cohfab_hclk		clkid(CLK_OUTPUT, COHFAB_HCLK)
#define scsr_clk		clkid(CLK_OUTPUT, SCSR_CLK)
#define tlmm_clk		clkid(CLK_OUTPUT, TLMM_CLK)
#define plic_clk		clkid(CLK_OUTPUT, PLIC_CLK)
#define tic_rst			clkid(CLK_OUTPUT, TIC_RST)
#define dbg_rst			clkid(CLK_OUTPUT, DBG_RST)
#define tmr0_clk		clkid(CLK_OUTPUT, TMR0_CLK)
#define tmr1_clk		clkid(CLK_OUTPUT, TMR1_CLK)
#define tmr2_clk		clkid(CLK_OUTPUT, TMR2_CLK)
#define tmr3_clk		clkid(CLK_OUTPUT, TMR3_CLK)
#define wdt0_clk		clkid(CLK_OUTPUT, WDT0_CLK)
#define wdt1_clk		clkid(CLK_OUTPUT, WDT1_CLK)
/* Additional clocks */
#define cohfab_cfg_clk		clkid(CLK_OUTPUT, COHFAB_CFG_CLK)
#define pcie_pclk		clkid(CLK_OUTPUT, PCIE_PCLK)
#define eth_alt_ref_clk		clkid(CLK_OUTPUT, ETH_ALT_REF_CLK)
#define sgmii_ref_clk		clkid(CLK_OUTPUT, SGMII_REF_CLK)
/* Alias for AO domain clocks */
#define ram_clk			soc_clk
#define rom_clk			soc_clk
/* clocke/reset alias required by DDR/PCIe drivers */
#define ddr_prst		ddr_pclk
#define ddr_arst		ddr_aclk
#define pcie_aux_clk		xo_clk
#define pcie_aclk		pcie_axi_clk
#define pcie_alt_ref_clk	pcie_clk
#define pcie_rst		pcie_alt_ref_clk

/* CLK_OUTPUT: CLK_EN_CFG1 */
/* Internal bus clocks */
#define gpio0_clk		clkid(CLK_OUTPUT, GPIO0_CLK)
#define gpio1_clk		clkid(CLK_OUTPUT, GPIO1_CLK)
#define gpio2_clk		clkid(CLK_OUTPUT, GPIO2_CLK)
/* Integrated overall clocks */
#define uart0_clk		clkid(CLK_OUTPUT, UART0_CLK)
#define uart1_clk		clkid(CLK_OUTPUT, UART1_CLK)
#define uart2_clk		clkid(CLK_OUTPUT, UART2_CLK)
#define uart3_clk		clkid(CLK_OUTPUT, UART3_CLK)
#define i2c0_clk		clkid(CLK_OUTPUT, I2C0_CLK)
#define i2c1_clk		clkid(CLK_OUTPUT, I2C1_CLK)
#define i2c2_clk		clkid(CLK_OUTPUT, I2C2_CLK)
#define i2c3_clk		clkid(CLK_OUTPUT, I2C3_CLK)
#define i2c4_clk		clkid(CLK_OUTPUT, I2C4_CLK)
#define i2c5_clk		clkid(CLK_OUTPUT, I2C5_CLK)
#define i2c6_clk		clkid(CLK_OUTPUT, I2C6_CLK)
#define i2c7_clk		clkid(CLK_OUTPUT, I2C7_CLK)
#define i2c8_clk		clkid(CLK_OUTPUT, I2C8_CLK)
#define i2c9_clk		clkid(CLK_OUTPUT, I2C9_CLK)
#define i2c10_clk		clkid(CLK_OUTPUT, I2C10_CLK)
#define i2c11_clk		clkid(CLK_OUTPUT, I2C11_CLK)
#define spi_flash_clk		clkid(CLK_OUTPUT, SPI_FLASH_CLK)
#define spi0_clk		clkid(CLK_OUTPUT, SPI0_CLK)
#define spi1_clk		clkid(CLK_OUTPUT, SPI1_CLK)
#define spi2_clk		clkid(CLK_OUTPUT, SPI2_CLK)
#define spi3_clk		clkid(CLK_OUTPUT, SPI3_CLK)
#define spi4_clk		clkid(CLK_OUTPUT, SPI4_CLK)
#define sd_clk			clkid(CLK_OUTPUT, SD_CLK)
#define eth_clk			clkid(CLK_OUTPUT, ETH_CLK)
#define tsensor_clk		clkid(CLK_OUTPUT, TSENSOR_CLK)
/* TODO: dependency clocks:
 * sd_tm_clk: depends sd_clk, sources soc_pll_div10/100
 */

/* CLK_OUTPUT: CLK_EN_CFG2 */

/* CLK_OUTPUT: CLK_EN_CFG3 */
/* Integrated overall clocks */
#define imc_clk			clkid(CLK_OUTPUT, IMC_CLK)

/* CLK_OUTPUT: COHFAB/CLUSTER CLK_CFG */
#define cohfab_clk		clkid(CLK_OUTPUT, COHFAB_CLK)
#define cluster0_clk		clkid(CLK_OUTPUT, CLUSTER0_CLK)
#define cluster1_clk		clkid(CLK_OUTPUT, CLUSTER1_CLK)
#define cluster2_clk		clkid(CLK_OUTPUT, CLUSTER2_CLK)
#define cluster3_clk		clkid(CLK_OUTPUT, CLUSTER3_CLK)

/* CLK_OUT: CLUSTER internal CLK_CG/RST_CTRL */
#define cluster0_apc0_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER0_APC0_CPU0_CLK)
#define cluster0_apc0_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER0_APC0_CPU1_CLK)
#define cluster0_apc1_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER0_APC1_CPU0_CLK)
#define cluster0_apc1_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER0_APC1_CPU1_CLK)
#define cluster0_apc0_l2_clk	clkid(CLK_OUTPUT, CLUSTER0_APC0_L2_CLK)
#define cluster0_apc1_l2_clk	clkid(CLK_OUTPUT, CLUSTER0_APC1_L2_CLK)
#define cluster1_apc0_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER1_APC0_CPU0_CLK)
#define cluster1_apc0_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER1_APC0_CPU1_CLK)
#define cluster1_apc1_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER1_APC1_CPU0_CLK)
#define cluster1_apc1_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER1_APC1_CPU1_CLK)
#define cluster1_apc0_l2_clk	clkid(CLK_OUTPUT, CLUSTER1_APC0_L2_CLK)
#define cluster1_apc1_l2_clk	clkid(CLK_OUTPUT, CLUSTER1_APC1_L2_CLK)
#define cluster2_apc0_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER2_APC0_CPU0_CLK)
#define cluster2_apc0_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER2_APC0_CPU1_CLK)
#define cluster2_apc1_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER2_APC1_CPU0_CLK)
#define cluster2_apc1_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER2_APC1_CPU1_CLK)
#define cluster2_apc0_l2_clk	clkid(CLK_OUTPUT, CLUSTER2_APC0_L2_CLK)
#define cluster2_apc1_l2_clk	clkid(CLK_OUTPUT, CLUSTER2_APC1_L2_CLK)
#define cluster3_apc0_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER3_APC0_CPU0_CLK)
#define cluster3_apc0_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER3_APC0_CPU1_CLK)
#define cluster3_apc1_cpu0_clk	clkid(CLK_OUTPUT, CLUSTER3_APC1_CPU0_CLK)
#define cluster3_apc1_cpu1_clk	clkid(CLK_OUTPUT, CLUSTER3_APC1_CPU1_CLK)
#define cluster3_apc0_l2_clk	clkid(CLK_OUTPUT, CLUSTER3_APC0_L2_CLK)
#define cluster3_apc1_l2_clk	clkid(CLK_OUTPUT, CLUSTER3_APC1_L2_CLK)

/* CLK_DIV */
#define SOC_CLK_DIV2		((clk_clk_t)0)
#define DDR_CLK_SEL_DIV4	((clk_clk_t)1)
#define XO_CLK_DIV4		((clk_clk_t)2)
#define ETH_CLK_DIV2		((clk_clk_t)3)
#define NR_DIV_CLKS		(ETH_CLK_DIV2 + 1)
#define soc_clk_div2		clkid(CLK_DIV, SOC_CLK_DIV2)
#define ddr_clk_sel_div4	clkid(CLK_DIV, DDR_CLK_SEL_DIV4)
#define xo_clk_div4		clkid(CLK_DIV, XO_CLK_DIV4)
#define eth_clk_div2		clkid(CLK_DIV, ETH_CLK_DIV2)

#endif /* __CLK_SOCv2_DUOWEN_H_INCLUDE__ */
