/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * (C) Copyright 2003
 * Texas Instruments, <www.ti.com>
 * Kshitij Gupta <Kshitij@ti.com>
 *
 * (C) Copyright 2004
 * ARM Ltd.
 * Philippe Robin, <philippe.robin@arm.com>
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

#include <common.h>
#ifdef CONFIG_PCI
#include <netdev.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

void peripheral_power_enable (void);

#if defined(CONFIG_SHOW_BOOT_PROGRESS)
void show_boot_progress(int progress)
{
	printf("Boot reached stage %d\n", progress);
}
#endif

#define COMP_MODE_ENABLE ((unsigned int)0x0000EAEF)

/*
 * Miscellaneous platform dependent initialisations
 */
#ifdef CONFIG_ARCH_CINTEGRATOR
 /******************************
  Routine:
 Description: The Integrator/CP uses CFI flash.
 In order for the CFI commands to work we must ensure that
 the flash is accessible.
 Also sets up the number of banks for a later check against
 include/configs/integratorcp.h
******************************/
int nbanks	= 0xDEADBABE;
int sizeIndex	= 0xCAFEBABE;
void flash__init (void)
{
	vu_long *cpcr = (vu_long *)CPCR_BASE;

	/* Check if there is an extra bank of flash */
	if (cpcr[1] & CPMASK_EXTRABANK)
		nbanks = 2;
	else
		nbanks = 1;

	/* Check if there is an extra bank of flash */
	if (cpcr[1] & CPMASK_FLASHSIZE)
		sizeIndex = 1;
	else
		sizeIndex = 0;

	/* Enable flash write */
	cpcr[1] |= 3;
}
/******************************
 Routine:
 Description: Check Integrator/CP control
							register settings against
				configs header.
******************************/
void flash_check(void) {
	unsigned int sizes[] =	{0x01000000, 0x02000000};
	if(nbanks != CONFIG_SYS_MAX_FLASH_BANKS){
		printf(	"The board control register indicates %d flash banks, "
			"<U-Boot root>/include/configs/integratorcp.h::"
			"CONFIG_SYS_MAX_FLASH_BANKS is set to %d\n" \
			,nbanks, CONFIG_SYS_MAX_FLASH_BANKS);
	}

	if(PHYS_FLASH_SIZE != sizes[sizeIndex]){
		printf(	"The board control register indicates 0x%08x bytes of "
			"flash, <U-Boot root>/include/configs/integratorcp.h"
			"::PHYS_FLASH_SIZE is set to 0x%08x\n" \
			,sizes[sizeIndex], PHYS_FLASH_SIZE);
	}
 }
#endif

int board_init (void)
{
	/* arch number of Integrator Board */
#ifdef CONFIG_ARCH_CINTEGRATOR
	gd->bd->bi_arch_number = MACH_TYPE_CINTEGRATOR;
#else
	gd->bd->bi_arch_number = MACH_TYPE_INTEGRATOR;
#endif

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x00000100;

	gd->flags = 0;

#ifdef CONFIG_CM_REMAP
extern void cm_remap(void);
	cm_remap();	/* remaps writeable memory to 0x00000000 */
#endif

	icache_enable ();

#ifdef CONFIG_ARCH_CINTEGRATOR
	flash__init ();
#endif


	return 0;
}

int misc_init_r (void)
{
#ifdef CONFIG_PCI
	pci_init();
#endif
	setenv("verify", "n");
	return (0);
}

/******************************
 Routine:
 Description:
******************************/
int dram_init (void)
{
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;
	gd->bd->bi_dram[0].size	 = PHYS_SDRAM_1_SIZE;

#ifdef CONFIG_CM_SPD_DETECT
	{
extern void dram_query(void);
	unsigned long cm_reg_sdram;
	unsigned long sdram_shift;

	dram_query();	/* Assembler accesses to CM registers */
			/* Queries the SPD values	      */

	/* Obtain the SDRAM size from the CM SDRAM register */

	cm_reg_sdram = *(volatile ulong *)(CM_BASE + OS_SDRAM);
	/*   Register	      SDRAM size
	 *
	 *   0xXXXXXXbbb000bb	 16 MB
	 *   0xXXXXXXbbb001bb	 32 MB
	 *   0xXXXXXXbbb010bb	 64 MB
	 *   0xXXXXXXbbb011bb	128 MB
	 *   0xXXXXXXbbb100bb	256 MB
	 *
	 */
	sdram_shift		 = ((cm_reg_sdram & 0x0000001C)/4)%4;
	gd->bd->bi_dram[0].size	 = 0x01000000 << sdram_shift;

	}
#endif /* CM_SPD_DETECT */

	return 0;
}

#ifdef CONFIG_PCI
int board_eth_init(bd_t *bis)
{
	return pci_eth_init(bis);
}
#endif

/*
 *  u32 get_board_rev() for ARM supplied development boards
 */
ARM_SUPPLIED_GET_BOARD_REV

