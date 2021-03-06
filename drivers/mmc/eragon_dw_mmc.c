/*
 * (C) Copyright 2015 Linaro
 * peter.griffin <peter.griffin@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dwmmc.h>
#include <malloc.h>
#include <asm-generic/errno.h>

#define	DWMMC_MAX_CH_NUM		4

#define	DWMMC_MAX_FREQ			HSP_DEFAULT_FREQ
#define	DWMMC_MIN_FREQ			400000

/* Source clock is configured to 100MHz by ATF bl1*/
#define MMC0_DEFAULT_FREQ		HSP_DEFAULT_FREQ

static int eragon_dwmci_core_init(struct dwmci_host *host, int index)
{
	host->name = "ERAGON DWMMC";

	host->dev_index = index;

	/* Add the mmc channel to be registered with mmc core */
	if (add_dwmci(host, DWMMC_MAX_FREQ, DWMMC_MIN_FREQ)) {
		printf("DWMMC%d registration failed\n", index);
		return -1;
	}
	return 0;
}

/*
 * This function adds the mmc channel to be registered with mmc core.
 * index -	mmc channel number.
 * regbase -	register base address of mmc channel specified in 'index'.
 * bus_width -	operating bus width of mmc channel specified in 'index'.
 */
struct dwmci_host dw_host;
int eragon_dwmci_add_port(int index, u32 regbase, int bus_width)
{
	dw_host.ioaddr = (void *)(ulong)regbase;
	dw_host.buswidth = bus_width;
	dw_host.bus_hz = MMC0_DEFAULT_FREQ;

	return eragon_dwmci_core_init(&dw_host, index);
}
