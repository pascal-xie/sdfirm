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
 * @(#)dma.h: direct memory access (DMA) definitions
 * $Id: dma.h,v 1.0 2020-12-1 23:38:00 zhenglv Exp $
 */

#ifndef __DMA_H_INCLUDE__
#define __DMA_H_INCLUDE__

#include <target/generic.h>
#include <target/irq.h>
#include <asm/dma.h>

/* dma_dir_t */
#define DMA_BIDIRECTIONAL	0
#define DMA_TO_DEVICE		1
#define DMA_FROM_DEVICE		2
#define DMA_NONE		3

#ifndef __ASSEMBLY__
/* DMA channel ID */
#if NR_DMAS <= 256
typedef uint8_t dma_t;
#elif NR_DMAS <= 65536
typedef uint16_t dma_t;
#endif

/* SoC specific DMA offset, should be defined in asm/mach/dma.h */
#ifdef DMA_HW_PHYS_OFFSET
#define DMA_PHYS_OFFSET		DMA_HW_PHYS_OFFSET
#else
#define DMA_PHYS_OFFSET		0
#endif

#ifndef CONFIG_MAX_CHANNELS
#define MAX_CHANNELS		0
#else
#define MAX_CHANNELS		CONFIG_MAX_CHANNELS
#endif

typedef uint8_t dma_dir_t;

struct dma_channel {
	bool coherent;
	bool indirect;
	bool has_range;
	phys_addr_t phys_base;
	dma_addr_t dma_base;
};

#include <driver/dmac.h>

#if NR_DMAS > 1
extern dma_t dma_sdma;
extern struct dma_channel dma_channels[NR_DMAS];
#define dma_channel_ctrl		dma_channels[dma_sdma]

void dma_channel_restore(dma_t dma);
dma_t dma_channel_save(dma_t dma);
#else
#define dma_sdma			0
struct dma_channel dma_channel_ctrl;

#define dma_channel_restore(dma)	do { } while (0)
#define dma_channel_save(dma)		dma_sdma
#endif

#define __phys_to_dma(phys_addr)	((phys_addr) - DMA_PHYS_OFFSET)
#define __dma_to_phys(dma_addr)		((dma_addr) + DMA_PHYS_OFFSET)

void dma_register_channel(dma_t dma, irq_handler cmpl);

/* DMA direct */
dma_addr_t dma_direct_map(dma_t dma, void *phys, size_t size, dma_dir_t dir);
void dma_direct_unmap(dma_t dma, dma_addr_t addr, size_t size, dma_dir_t dir);
void dma_direct_sync_cpu(dma_t dma, dma_addr_t addr, size_t size,
			 dma_dir_t dir);
void dma_direct_sync_dev(dma_t dma, dma_addr_t addr, size_t size,
			 dma_dir_t dir);

dma_addr_t dma_map_single(dma_t dma, void *ptr, size_t size, dma_dir_t dir);
void dma_unmap_single(dma_t dma, dma_addr_t addr, size_t size, dma_dir_t dir);
void dma_sync_cpu(dma_t dma, dma_addr_t addr, size_t size, dma_dir_t dir);
void dma_sync_dev(dma_t dma, dma_addr_t addr, size_t size, dma_dir_t dir);
#endif /* __ASSEMBLY__ */

#endif /* __DMA_H_INCLUDE__ */
