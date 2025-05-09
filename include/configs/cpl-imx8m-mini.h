/*
 * Copyright 2020 CompuLab
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CPL_IMX8M_MINI_H
#define __CPL_IMX8M_MINI_H

#include <linux/sizes.h>
#include <asm/arch/imx-regs.h>
#include "imx_env.h"

#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR	0x300
#define CONFIG_SYS_MMCSD_FS_BOOT_PARTITION	1
#define CONFIG_SYS_UBOOT_BASE		(QSPI0_AMBA_BASE + CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR * 512)

#ifdef CONFIG_SPL_BUILD
/*#define CONFIG_ENABLE_DDR_TRAINING_DEBUG*/
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT

#define CONFIG_SPL_STACK            0x920000
#define CONFIG_SPL_BSS_START_ADDR   0x910000
#define CONFIG_SYS_SPL_MALLOC_START 0x42200000
#define CONFIG_SYS_SPL_MALLOC_SIZE  SZ_512K

/* malloc f used before GD_FLG_FULL_MALLOC_INIT set */
#define CONFIG_MALLOC_F_ADDR        0x912000

#define CONFIG_SPL_ABORT_ON_RAW_IMAGE /* For RAW image gives a error info not panic */

#undef CONFIG_DM_MMC
#undef CONFIG_DM_PMIC
#undef CONFIG_DM_PMIC_PFUZE100

#define CONFIG_POWER_I2C
#define CONFIG_POWER_BD71837

#endif /*ifdef CONFIG_SPL_BUILD*/

#define CONFIG_SERIAL_TAG
#define CONFIG_FASTBOOT_USB_DEV 0

#define CONFIG_REMAKE_ELF

#define CONFIG_BOARD_POSTCLK_INIT

/* Flat Device Tree Definitions */
#define CONFIG_OF_BOARD_SETUP

#undef CONFIG_CMD_IMLS

#undef CONFIG_CMD_CRC32
#undef CONFIG_BOOTM_NETBSD

/* ENET Config */
/* ENET1 */
#if defined(CONFIG_CMD_NET)
#define CONFIG_ETHPRIME                 "FEC"

#define CONFIG_FEC_XCV_TYPE             RGMII
#define CONFIG_FEC_MXC_PHYADDR          0
#define FEC_QUIRK_ENET_MAC

#define IMX_FEC_BASE			0x30BE0000

#endif

#define CFG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=${console},${baudrate} " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
		"clk_ignore_unused "\
		"\0" \
	"initrd_addr=0x43800000\0" \
	"initrd_high=0xffffffff\0" \
	"emmc_dev=2\0" \
	"sd_dev=1\0" \
	"bootcmd_mfg=run mfgtool_args;  if iminfo ${initrd_addr}; then "\
					   "booti ${loadaddr} ${initrd_addr} ${fdt_addr};"\
					"else echo \"Run fastboot ...\"; fastboot 0; fi\0" \
/* Initial environment variables */
#define CFG_EXTRA_ENV_SETTINGS		\
	CFG_MFG_ENV_SETTINGS \
	"autoload=off\0" \
	"script=boot.scr\0" \
	"image=Image\0" \
	"console=ttymxc2,115200 earlycon=ec_imx6q,0x30880000,115200\0" \
	"fdt_addr=0x43000000\0"			\
	"fdt_high=0xffffffffffffffff\0"		\
	"boot_fdt=yes\0" \
	"fdt_file="CONFIG_DEFAULT_FDT_FILE"\0" \
	"initrd_addr=0x43800000\0"		\
	"initrd_high=0xffffffffffffffff\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcroot=" CONFIG_MMCROOT " rootwait rw\0" \
	"mmcautodetect=yes\0" \
	"root_opt=rootwait rw\0" \
	"emmc_ul=setenv iface mmc; setenv dev 2; setenv part 1;" \
	"setenv bootargs console=${console} root=/dev/mmcblk2p2 ${root_opt};\0" \
	"sd_ul=setenv iface mmc; setenv dev 1; setenv part 1;" \
	"setenv bootargs console=${console} root=/dev/mmcblk1p2 ${root_opt};\0" \
	"usb_ul=usb start; setenv iface usb; setenv dev 0; setenv part 1;" \
	"setenv bootargs console=${console} root=/dev/sda2 ${root_opt};\0" \
	"ulbootscript=load ${iface} ${dev}:${part} ${loadaddr} ${script};\0" \
	"ulimage=load ${iface} ${dev}:${part} ${loadaddr} ${image}\0" \
	"ulfdt=if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
		"load ${iface} ${dev}:${part} ${fdt_addr} ${fdt_file}; fi;\0" \
	"bootscript=echo Running bootscript from mmc ...; " \
		"source\0" \
	"netargs=setenv bootargs console=${console} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs;  " \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"${get_cmd} ${loadaddr} ${image}; " \
		"if test ${boot_fdt} = yes || test ${boot_fdt} = try; then " \
			"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
				"booti ${loadaddr} - ${fdt_addr}; " \
			"else " \
				"echo WARN: Cannot load the DT; " \
			"fi; " \
		"else " \
			"booti; " \
		"fi;\0"

#define CFG_SYS_INIT_RAM_ADDR        0x40000000
#define CFG_SYS_INIT_RAM_SIZE        0x80000
#define CFG_SYS_INIT_SP_OFFSET \
        (CFG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CFG_SYS_INIT_SP_ADDR \
        (CFG_SYS_INIT_RAM_ADDR + CFG_SYS_INIT_SP_OFFSET)

#define CFG_MXC_UART_BASE		UART_BASE_ADDR(3)

#define CONFIG_MMCROOT			"/dev/mmcblk1p2"  /* USDHC2 */

#define PHYS_SDRAM              0x40000000
#define PHYS_SDRAM_2            0x100000000
#define PHYS_SDRAM_SIZE   0 /* Memory chip autodetection */
#define PHYS_SDRAM_2_SIZE 0 /* Memory chip autodetection */
#define CFG_SYS_SDRAM_BASE   PHYS_SDRAM

#define MEMTEST_DIVIDER   2
#define MEMTEST_NUMERATOR 1

#define CONFIG_BAUDRATE			115200

#define CONFIG_MXC_UART_BASE		UART3_BASE_ADDR

/* Monitor Command Prompt */
#undef CONFIG_SYS_PROMPT
#define CONFIG_SYS_PROMPT		"u-boot=> "
#define CONFIG_SYS_PROMPT_HUSH_PS2     "> "
#define CONFIG_SYS_CBSIZE              2048
#define CONFIG_SYS_MAXARGS             64
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_FSL_ESDHC_ADDR       0

#ifndef CONFIG_DM_I2C
#define CONFIG_SYS_I2C
#endif
#define CONFIG_SYS_I2C_SPEED		100000

/* EEPROM */
#define CONFIG_ENV_EEPROM_IS_ON_I2C
#define CONFIG_SYS_I2C_EEPROM_BUS		1
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_EEPROM_SIZE			256
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4

/* USB configs */
#ifndef CONFIG_SPL_BUILD
#define CONFIG_USBD_HS

#define CONFIG_USB_GADGET_MASS_STORAGE

#endif

#define CONFIG_USB_GADGET_VBUS_DRAW 2

#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_USB_MAX_CONTROLLER_COUNT         2

#ifdef CONFIG_VIDEO
#define CONFIG_SPLASH_SCREEN 1
#define CONFIG_CMD_BMP 1
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IMX_VIDEO_SKIP
#define CONFIG_RM67191
#endif

#define CONFIG_BOARD_POSTCLK_INIT
#define CONFIG_OF_BOARD_SETUP

#endif
