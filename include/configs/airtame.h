/*
 * Copyright (C) 2014 AIRTAME ApS
 *
 * Configuration settings for the AIRTAME v1 dongle
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "mx6_common.h"
#include <asm/arch/imx-regs.h>
#include <asm/imx-common/gpio.h>
#include <linux/sizes.h>

#define CONFIG_MX6
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define MACH_TYPE_AIRTAME   4412 // ???
#define CONFIG_MACH_TYPE    MACH_TYPE_AIRTAME

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG

#define CONFIG_SYS_GENERIC_BOARD

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN           (10 * SZ_1M)

#define CONFIG_DEBUG_EARLY_SERIAL

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_MXC_GPIO
#define CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_DUALSPEED
#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_CDC
#define CONFIG_NETCONSOLE

/* USB Configs */
#define CONFIG_CMD_USB
#define CONFIG_CMD_FAT
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_MCS7830
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET    /* For OTG port */
#define CONFIG_MXC_USB_PORTSC   (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS    0
#define CONFIG_USB_KEYBOARD
#define CONFIG_SYS_USB_EVENT_POLL_VIA_CONTROL_EP


#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE            UART1_BASE

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX               1
#define CONFIG_BAUDRATE                 115200

/* Command definition */
#include <config_cmd_default.h>

#undef CONFIG_CMD_IMLS

#define CONFIG_CMD_BMODE
#define CONFIG_CMD_SETEXPR
#define CONFIG_CMD_GETTIME

/* Enable IMX6 fuses */
#define CONFIG_MXC_OCOTP
#define CONFIG_CMD_FUSE
#define CONFIG_CMD_IMXMAC


#define CONFIG_BOOTDELAY                 3

#define CONFIG_SYS_MEMTEST_START        0x10000000
#define CONFIG_SYS_MEMTEST_END          (CONFIG_SYS_MEMTEST_START + 500 * SZ_1M)
#define CONFIG_LOADADDR                 0x12000000
#define CONFIG_SYS_TEXT_BASE            0x17800000

/* MMC Configuration */

#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_USDHC_NUM        1
#define CONFIG_SYS_FSL_ESDHC_ADDR       0

#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION

/* LED */
#define CONFIG_STATUS_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define CONFIG_CMD_LED

#define STATUS_LED_BIT 1
#define STATUS_LED_BOOT 0
#define STATUS_LED_STATE STATUS_LED_ON
#define STATUS_LED_PERIOD (CONFIG_SYS_HZ / 1)

/* Memory test */
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_ALT_MEMTEST /* more elaborate test */

/* USB Configs */
#define CONFIG_CMD_USB
#define CONFIG_CMD_FAT
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_USB_ETHER_MCS7830
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET    /* For OTG port */
#define CONFIG_MXC_USB_PORTSC   (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS    0

/* Framebuffer */
#define CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_SYS_CONSOLE_IS_IN_ENV
#define CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IPUV3_CLK 260000000
#define CONFIG_CMD_HDMIDETECT
#define CONFIG_IMX_HDMI
#define CONFIG_IMX_VIDEO_SKIP
#define CONFIG_CMD_BMP

/* I2C Configs */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED        100000
#define CONFIG_I2C_EDID

/* Device tree file for the kernel */
#define CONFIG_DEFAULT_FDT_FILE         "airtame1.dtb"
#define CONFIG_DEFAULT_KERNEL_FILE  "airtame1.img"

/* Default environmental vars */
#define CONFIG_PREBOOT                 ""
#define CONFIG_EXTRA_ENV_SETTINGS \
        "console=ttymxc0\0" \
        "splashpos=m,m\0" \
        "rootfs1_ok=1\0" \
        "rootfs2_ok=0\0" \
        "mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
        "mmcpart=2\0" \
        "environment=/boot/uEnv.txt\0" \
        "devicetree=/boot/" CONFIG_DEFAULT_FDT_FILE "\0" \
        "linux=/boot/" CONFIG_DEFAULT_KERNEL_FILE "\0" \
        "bootargs=console=${console},115200n8 ro rootwait ath6kl_core.mac=${wifimac}\0" \
        "fdt_addr=0x18000000\0" \
        "fdt_high=0xffffffff\0"   \
        "initrd_addr=0x19000000\0" \
        "initrd_high=0xffffffff\0" \
        "load=ext2load\0" \
        "fixenv=" \
                "if test -n ${options};then " \
                        "setenv bootargs ${options} ath6kl_core.mac=${wifimac};" \
                "fi;" \
                "setenv bootargs ${bootargs} root=/dev/mmcblk0p${mmcpart};" \
                "if test -n ${name};then " \
                        "setenv devicetree /boot/${name}.dtb;" \
                        "setenv linux /boot/${name}.img;" \
                        "if test -n ${initrd};then " \
                                "setenv initrd /boot/${name}.ird;" \
                        "fi;" \
                "fi;\0" \
        "redundroot=" \
            "if test \"${mmcpart}\" = 2; then " \
                "if test \"${rootfs1_ok}\" != 1; then " \
                    "echo \"Wrong rootfs selected. Falling back to rootfs2\";" \
                    "setenv mmcpart 3;" \
                    "saveenv;" \
                "fi;" \
            "fi;" \
            "if test \"${mmcpart}\" = 3; then " \
                "if test \"${rootfs2_ok}\" != 1; then " \
                    "echo \"Wrong rootfs selected. Falling back to rootfs1\";" \
                    "setenv mmcpart 2;" \
                    "saveenv;" \
                "fi;" \
            "fi;\0" \
        "mmcinit=" \
            "imxmac get;" \
            "led 0 toggle;" \
            "mmc dev ${mmcdev};" \
            "if mmc rescan;then " \
                "setenv bootcmd run mmcboot;" \
                "led 0 toggle;" \
                "if ${load} mmc ${mmcdev}:${mmcpart} ${loadaddr} ${environment};then " \
                    "echo Loading ${environment}..;" \
                    "env import -t ${loadaddr} ${filesize};" \
                "else " \
                    "false;" \
                "fi;" \
            "else " \
                "false;" \
            "fi\0" \
        "mmcboot=" \
            "led 0 toggle;" \
            "run fixenv;" \
            "if ${load} mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${devicetree};then " \
                "led 0 toggle;" \
                "if ${load} mmc ${mmcdev}:${mmcpart} ${loadaddr} ${linux};then " \
                    "led 0 toggle;" \
                    "if test -n ${initrd};then " \
                        "if ${load} mmc ${mmcdev}:${mmcpart} ${initrd_addr} ${initrd};then " \
                            "bootz ${loadaddr} ${initrd_addr}:${filesize} ${fdt_addr};" \
                        "else " \
                            "false;" \
                        "fi;" \
                    "else " \
                        "bootz ${loadaddr} - ${fdt_addr};" \
                    "fi;" \
                "else " \
                    "false;" \
                "fi;" \
            "else " \
                "false;" \
            "fi\0"

#define CONFIG_BOOTCOMMAND \
    "if kbd; then " \
        "echo \"Recovery mode on.\";" \
        "fastboot;" \
    "else " \
        "run redundroot;" \
        "if run mmcinit; then " \
            "run bootcmd;" \
        "else " \
            "fastboot;" \
        "fi;" \
    "fi"

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE               256

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS             16
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_SYS_LOAD_ADDR            CONFIG_LOADADDR

#define CONFIG_CMDLINE_EDITING

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS            1
#define PHYS_SDRAM                      MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE           PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR        IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE        IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
        (CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
        (CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE         (1024 * 1024)
#define CONFIG_ENV_SIZE_REDUND  (1024 * 1024)

#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV          0

#define CONFIG_ENV_OFFSET           (16384*512)
#define CONFIG_ENV_OFFSET_REDUND    (2*16384*512)


#define CONFIG_OF_LIBFDT
#define CONFIG_CMD_BOOTZ

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif

#define CONFIG_CMD_ELF

#define CONFIG_USB_GADGET
#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_GADGET_MASS_STORAGE
#define CONFIG_USBDOWNLOAD_GADGET
#define CONFIG_USB_GADGET_VBUS_DRAW 2

/* Netchip IDs */
#define CONFIG_G_DNL_VENDOR_NUM 0x0451
#define CONFIG_G_DNL_PRODUCT_NUM 0xd022
#define CONFIG_G_DNL_MANUFACTURER "Boundary"

#define CONFIG_CMD_FASTBOOT
#define CONFIG_USB_FASTBOOT_BUF_ADDR   CONFIG_SYS_LOAD_ADDR
#define CONFIG_USB_FASTBOOT_BUF_SIZE   0x10000000
#define CONFIG_FASTBOOT_FLASH
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 0

/* Partition handling */
#define CONFIG_CMD_PART
#define CONFIG_PARTITION_UUIDS
#define CONFIG_EFI_PARTITION

#endif                         /* __CONFIG_H * */
