/*
 * Copyright (C) 2012-2016 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX6QSABRESD_CONFIG_H
#define __MX6QSABRESD_CONFIG_H

#ifdef CONFIG_SPL
#include "imx6_spl.h"
#endif

#define CONFIG_MACH_TYPE	3980
#define CONFIG_MXC_UART_BASE	UART1_BASE
#define CONSOLE_DEV		"ttymxc0"

#if defined(CONFIG_MX6QP)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6Q)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6DL)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6SOLO)
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#endif

#include "mx6sabre_common.h"

/* The following all refer to the same MMC device (SDHC3 = SD card) */
#define CONFIG_MMCROOT "/dev/mmcblk2" /* MMC block device in Linux */
#define CONFIG_SYS_MMC_ENV_DEV		1	  /* MMC device ID in U-Boot */
#define CONFIG_SYS_FSL_USDHC_NUM	3   /* Freescale MMC device ID (SDHC3) */

#define CONFIG_EXTRA_ENV_SETTINGS                                              \
  CONFIG_MFG_ENV_SETTINGS                                                      \
  /* New environment variables from the i.MX6QP SABRE SD board config */       \
  "loadbootscript="                                                            \
      "${load} mmc ${mmcdev}:${mmcpart} ${loadaddr} ${script};\0"              \
      "bootscript=echo Running bootscript from mmc ...; "                      \
      "source\0"                                                               \
  "script=/boot/boot.scr\0"                                                    \
  /* Environment variables analogous to AT-DG1 U-Boot */                       \
  "console=" CONSOLE_DEV "\0"                                                  \
  "splashpos=m,m\0"                                                            \
  "rootfs1_ok=1\0"                                                             \
  "rootfs2_ok=0\0"                                                             \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0"                           \
  "mmcpart=2\0" /* default to 2, but we will swap to 3 if marked redundant */  \
  "environment=/boot/uEnv.txt\0"                                               \
  "devicetree=/boot/airtame-dg2.dtb\0"                                         \
  "linux=/boot/airtame-dg2.img\0"                                              \
  "bootargs=console=${console},115200n8 rootwait ro\0"                         \
  "fdt_addr=0x18000000\0"                                                      \
  "fdt_high=0xffffffff\0"                                                      \
  "initrd_addr=0x19000000\0"                                                   \
  "initrd_high=0xffffffff\0"                                                   \
  "load=ext2load\0"                                                            \
  "redundroot=" /* select correct partition based on redundancy flags */       \
      "if test \"${mmcpart}\" = 2; then "                                      \
          "if test \"${rootfs1_ok}\" != 1; then "                              \
              "echo \"Wrong rootfs selected. Falling back to rootfs2\";"       \
              "setenv mmcpart 3;"                                              \
              "saveenv;"                                                       \
          "fi;"                                                                \
      "fi;"                                                                    \
      "if test \"${mmcpart}\" = 3; then "                                      \
          "if test \"${rootfs2_ok}\" != 1; then "                              \
              "echo \"Wrong rootfs selected. Falling back to rootfs1\";"       \
              "setenv mmcpart 2;"                                              \
              "saveenv;"                                                       \
          "fi;"                                                                \
      "fi;\0"                                                                  \
  "mmcinit=" /* load environment file from selected MMC device/partition */    \
      "led 0 toggle;"                                                          \
      "mmc dev ${mmcdev};"                                                     \
      "if mmc rescan;then "                                                    \
          "setenv bootcmd run mmcboot;" /* set boot target to MMC */           \
          "led 0 toggle;"                                                      \
          "if ${load} mmc ${mmcdev}:${mmcpart} ${loadaddr} ${environment};then " \
              "echo Loading ${environment}..;"                                 \
              "env import -t ${loadaddr} ${filesize};"                         \
          "else "                                                              \
              "echo Failed to load ${environment}!;"                           \
              "false;"                                                         \
          "fi;"                                                                \
      "else "                                                                  \
          "false;"                                                             \
      "fi\0"                                                                   \
  "fixenv=" /* update environment based on loaded environment */               \
      "if test -n ${options};then "                                            \
          "setenv bootargs ${options};"                                        \
      "fi;"                                                                    \
      "setenv bootargs ${bootargs} root=" CONFIG_MMCROOT "p${mmcpart};"        \
      "if test -n ${name};then "                                               \
          "setenv devicetree /boot/${name}.dtb;"                               \
          "setenv linux /boot/${name}.img;"                                    \
          "if test -n ${initrd};then "                                         \
              "setenv initrd /boot/${name}.ird;"                               \
          "fi;"                                                                \
      "fi;\0"                                                                  \
  "mmcboot=" /* apply loaded environment, load DT/kernel, and boot */          \
      "led 0 toggle;"                                                          \
      "run fixenv;"                                                            \
      "if ${load} mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${devicetree};then "    \
          "led 0 toggle;"                                                      \
          "if ${load} mmc ${mmcdev}:${mmcpart} ${loadaddr} ${linux};then "     \
              "led 0 toggle;"                                                  \
              "if test -n ${initrd};then "                                     \
                  "if ${load} mmc ${mmcdev}:${mmcpart} ${initrd_addr} ${initrd};then " \
                      "bootz ${loadaddr} ${initrd_addr}:${filesize} ${fdt_addr};" \
                  "else "                                                      \
                      "false;"                                                 \
                  "fi;"                                                        \
              "else "                                                          \
                  "bootz ${loadaddr} - ${fdt_addr};"                           \
              "fi;"                                                            \
          "else "                                                              \
              "false;"                                                         \
          "fi;"                                                                \
      "else "                                                                  \
          "false;"                                                             \
      "fi\0"

#define CONFIG_BOOTCOMMAND                                                     \
  "if kbd; then "                                                              \
      "echo \"Recovery mode on.\";"                                            \
      "fastboot;"                                                              \
  "else "                                                                      \
      "run redundroot;"                                                        \
      "if run mmcinit; then "                                                  \
          "run bootcmd;"                                                       \
      "else "                                                                  \
          "fastboot;" /* failed to load environment, fallback to fastboot */   \
      "fi;"                                                                    \
  "fi"

/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
#ifdef CONFIG_PCI
#define CONFIG_CMD_PCI
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(3, 19)
#endif

/* USB Configs */
#ifdef CONFIG_CMD_USB

#ifdef CONFIG_USB_FUNCTION_FASTBOOT
/* enable BCB support - it's not available in the menuconfig */
#define CONFIG_BCB_SUPPORT
#define CONFIG_CMD_READ
#endif /* CONFIG_USB_FUNCTION_FASTBOOT */

#if !defined(CONFIG_USB_EHCI)
#define CONFIG_USB_EHCI
#endif /* CONFIG_USB_EHCI */
#if !defined(CONFIG_USB_EHCI_MX6)
#define CONFIG_USB_EHCI_MX6
#endif /* CONFIG_USB_EHCI_MX6 */

#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1 /* Enabled USB controller number */

#endif /* CONFIG_CMD_USB */

/*#define CONFIG_SPLASH_SCREEN*/
/*#define CONFIG_MXC_EPDC*/

/*
 * SPLASH SCREEN Configs
 */
#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_MXC_EPDC)
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_CMD_BMP
	#undef LCD_TEST_PATTERN
	/* #define CONFIG_SPLASH_IS_IN_MMC			1 */
	#define LCD_BPP					LCD_MONOCHROME
	/* #define CONFIG_SPLASH_SCREEN_ALIGN		1 */

	#define CONFIG_WAVEFORM_BUF_SIZE		0x200000
#endif /* CONFIG_SPLASH_SCREEN && CONFIG_MXC_EPDC */

#endif                         /* __MX6QSABRESD_CONFIG_H */
