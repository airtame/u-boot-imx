/*
 * Copyright 2014 Broadcom Corporation.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <fb_mmc.h>
#include <part.h>
#include <aboot.h>
#include <sparse_format.h>

/* The 64 defined bytes plus the '\0' */
#define RESPONSE_LEN	(64 + 1)

static char *response_str;

void fastboot_fail(const char *s)
{
	strncpy(response_str, "FAIL", 4);
	strncat(response_str, s, RESPONSE_LEN - 4 - 1);
}

void fastboot_okay(const char *s)
{
	strncpy(response_str, "OKAY", 4);
	strncat(response_str, s, RESPONSE_LEN - 4 - 1);
}

static void write_raw_image(block_dev_desc_t *dev_desc,
		lbaint_t block_offset, void *buffer,
		unsigned int download_bytes)
{
	lbaint_t blkcnt;
	lbaint_t blks;

	/* determine number of blocks to write */
	blkcnt = ((download_bytes + (dev_desc->blksz - 1)) & ~(dev_desc->blksz - 1));
	blkcnt = blkcnt / dev_desc->blksz;

	if ((blkcnt + block_offset) > dev_desc->lba) {
		error("too large for disk\n");
		fastboot_fail("too large for disk");
		return;
	}

	puts("Flashing Raw Image\n");

	blks = dev_desc->block_write(dev_desc->dev, block_offset, blkcnt,
				     buffer);
	if (blks != blkcnt) {
		error("failed writing to device %d\n", dev_desc->dev);
		fastboot_fail("failed writing to device");
		return;
	}

	printf("........ wrote " LBAFU " bytes\n", blkcnt * dev_desc->blksz);
	fastboot_okay("");
}

void fb_mmc_flash_write(const char *cmd, void *download_buffer,
			unsigned int download_bytes, char *response)
{
	block_dev_desc_t *dev_desc;
	lbaint_t offset = 0;
	char *tmpcmd = (char *)cmd;

	/* initialize the response buffer */
	response_str = response;

	dev_desc = get_dev("mmc", CONFIG_FASTBOOT_FLASH_MMC_DEV);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		error("invalid mmc device\n");
		fastboot_fail("invalid mmc device");
		return;
	}

	strsep(&tmpcmd, ":");
	offset = simple_strtoul(tmpcmd, NULL, 0);

	write_raw_image(dev_desc, offset, download_buffer,
				download_bytes);
}
