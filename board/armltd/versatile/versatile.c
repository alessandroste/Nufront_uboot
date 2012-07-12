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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <command.h>

DECLARE_GLOBAL_DATA_PTR;

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
int board_init (void)
{
	/*
	 * set clock frequency:
	 *	VERSATILE_REFCLK is 32KHz
	 *	VERSATILE_TIMCLK is 1MHz
	 */
	*(volatile unsigned int *)(VERSATILE_SCTL_BASE) |=
	  ((VERSATILE_TIMCLK << VERSATILE_TIMER1_EnSel) | (VERSATILE_TIMCLK << VERSATILE_TIMER2_EnSel) |
	   (VERSATILE_TIMCLK << VERSATILE_TIMER3_EnSel) | (VERSATILE_TIMCLK << VERSATILE_TIMER4_EnSel));

#ifdef CONFIG_ARCH_VERSATILE_AB
	gd->bd->bi_arch_number = MACH_TYPE_VERSATILE_AB;
#else
 	gd->bd->bi_arch_number = MACH_TYPE_VERSATILE_PB;
#endif

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x00000100;

	gd->flags = 0;

	icache_enable ();

	return 0;
}


int misc_init_r (void)
{
	setenv("verify", "n");
	return (0);
}

/******************************
 Routine:
 Description:
******************************/
int dram_init (void)
{
	return 0;
}

int interrupt_init (void){
	return 0;
}

/*
 * Write the system control status register to cause reset
 */
void reset_cpu(ulong addr){
	*(volatile unsigned int *)(VERSATILE_SCTL_BASE + SP810_OS_SCSYSSTAT) = 0x00000000;
}
/*
 *  u32 get_board_rev() for ARM supplied development boards
 */
ARM_SUPPLIED_GET_BOARD_REV

#ifdef CONFIG_REVISION_TAG
#if (CONFIG_COMMANDS & CFG_CMD_REV)


int do_show_rev(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	u32 * rev_reg = (u32*)ARM_SUPPLIED_REVISION_REGISTER; 
	u32 info = *rev_reg;				



	/* Versatile specific 
	 * perhaps we can generalize
	 *	[31:24] Read MAN , manufacturer 		: 0x41 = ARM
	 *	[23:16] Read ARCH, architecture		: 0x00 = ARM926
	 *	[15:12] Read FPGA type			: 0x7 = XC2V2000
	 *	[11:04] Read Build value (ARM internal use)
	 *	[03:00] Read REV , Major revision 	: 0x4 = multilayer AHB
	 */
	 printf("===================================================\n");
	 printf("Versatile board info register indicates:-          \n");
	 printf("Manufacturer   0x%08x (0x00000041 == ARM)   \n"		, ((info & 0xFF000000)/0x1000000));
	 printf("Architecture   0x%08x (0x00000000 == ARM926)\n"		, ((info & 0x00FF0000)/0x10000));
#ifdef CONFIG_ARCH_VERSATILE_AB	/* Versatile AB */
	 printf("FPGA type      0x%04x     (0x0008 == XC2S300E)\n"     		, ((info & 0x0000F000)/0x1000));
#else
	 printf("FPGA type      0x%04x     (0x0007 == XC2V2000)\n"     		, ((info & 0x0000F000)/0x1000));
#endif	 
	 printf("Build number   0x%08x\n"					, ((info & 0x00000FF0)/0x10));
	 printf("Major Revision 0x%04x     (0x0004 == Multi-layer AHB) \n"	,  (info & 0x0000000F));
	 printf("===================================================\n");
	 return 1;
}
/***************************************************/

U_BOOT_CMD(
	show_rev,	1,	1,	do_show_rev,
	"show_rev - Parse the board revision info\n",
	NULL
);

#endif	/* CFG_CMD_REV */
#endif /* CONFIG_REVISION_TAG */




