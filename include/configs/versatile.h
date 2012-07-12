/*
 * (C) Copyright 2003
 * Texas Instruments.
 * Kshitij Gupta <kshitij@ti.com>
 * Configuation settings for the TI OMAP Innovator board.
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
 * Configuration for Versatile PB.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 *  Code, etc. common to all ARM supplied development boards
 */
#include <armsupplied.h>
/*
 * Board info register
 */
#define SYS_ID  (0x10000000)
#define ARM_SUPPLIED_REVISION_REGISTER SYS_ID

/*
 * High Level Configuration Options
 * (easy to change)
 */
#define CONFIG_ARM926EJS	1	/* This is an arm926ejs CPU core */
#define CONFIG_VERSATILE	1	/* in Versatile Platform Board	*/
#define CONFIG_ARCH_VERSATILE	1	/* Specifically, a Versatile	*/

#ifndef CONFIG_ARCH_VERSATILE_AB	/* AB				*/
#	define CONFIG_ARCH_VERSATILE_PB	/* Versatile PB is default	*/
#endif

#define CONFIG_SYS_MEMTEST_START	0x100000
#define CONFIG_SYS_MEMTEST_END		0x10000000
#define CONFIG_SYS_HZ			(1000)
#define CONFIG_SYS_TIMERBASE		0x101E2000	/* SP804 Timer 0 and 1 base */

#define CONFIG_SYS_TIMER_RELOAD	0xFFFFFFFF
#define READ_TIMER		(*(volatile ulong *)(CONFIG_SYS_TIMERBASE+4))
#define TIMER_LOAD_VAL		CONFIG_SYS_TIMER_RELOAD

/*
 * control registers
 */
#define VERSATILE_SCTL_BASE	0x101E0000	/* System controller */
#define SP810_OS_SCSYSSTAT	(0x00000004)	/* System status register */

/*
 * System controller bit assignment
 */
#define VERSATILE_REFCLK	0
#define VERSATILE_TIMCLK	1

#define VERSATILE_TIMER1_EnSel	15
#define VERSATILE_TIMER2_EnSel	17
#define VERSATILE_TIMER3_EnSel	19
#define VERSATILE_TIMER4_EnSel	21

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
#define CONFIG_MISC_INIT_R		1	/* call misc_init_r during start up */ 
/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 128 * 1024)
/* 
 * Number of bytes reserved for initial data 
 */
#define CONFIG_SYS_GBL_DATA_SIZE	128

/*
 * Hardware drivers
 */

#define CONFIG_DRIVER_SMC91111
#define CONFIG_SMC_USE_32_BIT
#define CONFIG_SMC91111_BASE	0x10010000
#undef CONFIG_SMC91111_EXT_PHY

/*
 * NS16550 Configuration
 */
#define CONFIG_PL011_SERIAL
#define CONFIG_PL011_CLOCK	24000000
#define CONFIG_PL01x_PORTS				\
			{(void *)CONFIG_SYS_SERIAL0,	\
			 (void *)CONFIG_SYS_SERIAL1 }
#define CONFIG_CONS_INDEX	0

#define CONFIG_BAUDRATE		38400
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }
#define CONFIG_SYS_SERIAL0		0x101F1000
#define CONFIG_SYS_SERIAL1		0x101F2000

/*
 * Command line configuration.
 */
#define CONFIG_CMD_BDI
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ENV
#define CONFIG_CMD_FLASH
#define CONFIG_CMD_IMI
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_NET
#define CONFIG_CMD_PING
#define CONFIG_CMD_SAVEENV

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_SUBNETMASK

#define CONFIG_BOOTDELAY	2

/* #define CONFIG_BOOTARGS "root=/dev/nfs mem=128M ip=dhcp netdev=25,0,0xf1010000,0xf1010010,eth0" */
/*
The kernel command line & boot command below are for a VersatilePB board flashed using Boot_Monitor.axf:-
0x34000000	u-boot
0x34040000	u-linux
0x34380000	mtdroot

Name: mtdroot
Flash Address: 0x34380000
Load Address : 0x00000000
Entry Point	: 0x00000000
Size				 : 5012K
Blocks Used	: 20

and a VersatileAB board flashed using Boot_monitor.axf:-

0x34000000	u-boot
0x34020000	EMPTY_IMAGE
0x34040000	u-linux
0x34380000	mtdroot

Name: mtdroot
Flash Address: 0x34380000
Load Address : 0x00000000
Entry Point	: 0x00000000
Size				 : 5012K
Blocks Used	: 40

i.e despite the difference in flash block size the same command may be used.

*/

#define CONFIG_BOOTARGS "root=/dev/mtdblock0 mtdparts=armflash.0:7268k@0x02680000(cramfs) ip=dhcp mem=128M console=ttyAMA0 video=vc:1-2clcdfb:"
#define CONFIG_BOOTCOMMAND "cp 0x36000000 0x7fc0 0x00200000 ; bootm"

/*
 * Static configuration when assigning fixed address
 */
/*#define CONFIG_NETMASK	255.255.255.0	/--* talk on MY local net */
/*#define CONFIG_IPADDR		xx.xx.xx.xx	/--* static IP I currently own */
/*#define CONFIG_SERVERIP	xx.xx.xx.xx	/--* current IP of my dev pc */
#define CONFIG_BOOTFILE		"/tftpboot/uImage" /* file to load */
/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP	/* undef to save memory */
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size */
/* Monitor Command Prompt	 */
#ifdef CONFIG_ARCH_VERSATILE_AB
# define CONFIG_SYS_PROMPT	"VersatileAB # "
#else
# define CONFIG_SYS_PROMPT	"VersatilePB # "
#endif
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE /* Boot Argument Buffer Size */

#define CONFIG_SYS_LOAD_ADDR	0x7fc0	/* default load address */

/*-----------------------------------------------------------------------
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE	(128 * 1024)	/* regular stack */
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 * 1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4 * 1024)	/* FIQ stack */
#endif

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1	/* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x00000000	/* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x08000000	/* 128 MB */
#define PHYS_FLASH_SIZE		0x04000000	/* 64MB */

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */
/*
 * Use the CFI flash driver for ease of use
 */
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_ENV_IS_IN_FLASH	1
/* 
 *	System control register
 */
#define VERSATILE_SYS_BASE		0x10000000
#define VERSATILE_SYS_FLASH_OFFSET	0x4C
#define VERSATILE_FLASHCTRL		\
		(VERSATILE_SYS_BASE + VERSATILE_SYS_FLASH_OFFSET)
/* 
 * Enable writing to flash
 */
#define VERSATILE_FLASHPROG_FLVPPEN	(1 << 0)

/* Timeout values are in ticks */
/* Lengthened for bad boards */
#define CONFIG_SYS_FLASH_ERASE_TOUT	(20 * CONFIG_SYS_HZ) /* Erase Timeout */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(20 * CONFIG_SYS_HZ) /* Write Timeout */

// #define PHYS_FLASH_1		(CONFIG_SYS_FLASH_BASE)

/*
 * Note that CONFIG_SYS_MAX_FLASH_SECT allows for a parameter block 
 * i.e. the bottom "sector" (bottom boot), or top "sector" 
 *      (top boot), is a seperate erase region divided into 
 *      4 (equal) smaller sectors. This, notionally, allows
 *      quicker erase/rewrire of the most frequently changed
 *      area......
 *      CONFIG_SYS_MAX_FLASH_SECT is padded up to a multiple of 4
 */

#ifdef CONFIG_ARCH_VERSATILE_AB	/* AB				*/
# define FLASH_SECTOR_SIZE	0x00020000	/* 128 KB sectors */
# define QUANTUM		(2 * FLASH_SECTOR_SIZE)
#define CONFIG_SYS_MAX_FLASH_SECT	(520)
#endif

#ifdef CONFIG_ARCH_VERSATILE_PB	/* Versatile PB is default	*/
# define FLASH_SECTOR_SIZE	0x00040000	/* 256 KB sectors */
# define QUANTUM		FLASH_SECTOR_SIZE
#define CONFIG_SYS_MAX_FLASH_SECT	(260)
#endif

#define CONFIG_SYS_FLASH_BASE		0x34000000
#define CONFIG_SYS_MAX_FLASH_BANKS	1		/* max number of memory banks */

#define CONFIG_ENV_SECT_SIZE	QUANTUM
#define CONFIG_SYS_MONITOR_LEN	(4 * QUANTUM)

/* The ARM Boot Monitor is shipped in the lowest sector of flash
 * These values place U-Boot & its environment at the top of flash */
#define ARM_BM_START		(CONFIG_SYS_FLASH_BASE)       

#define FLASH_TOP		(CONFIG_SYS_FLASH_BASE + PHYS_FLASH_SIZE)

#define CONFIG_ENV_SIZE		8192	
#define CONFIG_ENV_ADDR		(FLASH_TOP - (2 * CONFIG_ENV_SECT_SIZE))
#define CONFIG_ENV_OFFSET	(CONFIG_ENV_ADDR - CONFIG_SYS_FLASH_BASE)          
#define CONFIG_SYS_MONITOR_BASE	(CONFIG_ENV_ADDR - CONFIG_SYS_MONITOR_LEN)

#define CONFIG_SYS_FLASH_PROTECTION	/* The devices have real protection */
#define CONFIG_SYS_FLASH_EMPTY_INFO	/* flinfo indicates empty blocks */

#endif	/* __CONFIG_H */
