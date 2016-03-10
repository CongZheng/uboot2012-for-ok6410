/*
 * (C) Copyright 2012 Samsung Electronics
 * Donghwa Lee <dh09.lee@samsung.com>
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
 * aint with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#ifndef __ASM_ARM_ARCH_FB_H_
#define __ASM_ARM_ARCH_FB_H_

#ifndef __ASSEMBLY__
struct s3c6410_fb {
	unsigned int vidcon0;
	unsigned int vidcon1;
	unsigned int vidcon2;
	unsigned int vidcon3;
	
	unsigned int vidtcon0;
	unsigned int vidtcon1;
	unsigned int vidtcon2;
	unsigned int vidtcon3;
	
	unsigned int wincon0;
	unsigned int wincon1;
	unsigned int wincon2;
	unsigned int wincon3;
	
	unsigned int wincon4;
	unsigned int res1[3];
	
	unsigned int vidosd0a;
	unsigned int vidosd0b;
	unsigned int vidosd0c;
	unsigned int res2;

	unsigned int vidosd1a;
	unsigned int vidosd1b;
	unsigned int vidosd1c;
	unsigned int vidosd1d;

	unsigned int vidosd2a;
	unsigned int vidosd2b;
	unsigned int vidosd2c;
	unsigned int vidosd2d;

	unsigned int vidosd3a;
	unsigned int vidosd3b;
	unsigned int vidosd3c;
	unsigned int res3;

	unsigned int vidosd4a;
	unsigned int vidosd4b;
	unsigned int vidosd4c;
	unsigned int res4[5];

	unsigned int vidw00add0b0;
	unsigned int vidw00add0b1;
	unsigned int vidw01add0b0;
	unsigned int vidw01add0b1;

	unsigned int vidw02add0b0;
	unsigned int vidw02add0b1;
	unsigned int vidw03add0b0;
	unsigned int vidw03add0b1;
	
	unsigned int vidw04add0b0;
	unsigned int vidw04add0b1;
	unsigned int res5[2];

	unsigned int vidw00add1b0;
	unsigned int vidw00add1b1;
	unsigned int vidw01add1b0;
	unsigned int vidw01add1b1;

	unsigned int vidw02add1b0;
	unsigned int vidw02add1b1;
	unsigned int vidw03add1b0;
	unsigned int vidw03add1b1;

	unsigned int vidw04add1b0;
	unsigned int vidw04add1b1;
	unsigned int res6[2];

	unsigned int vidw00add2;
	unsigned int vidw01add2;
	unsigned int vidw02add2;
	unsigned int vidw03add2;
	unsigned int vidw04add2;
	unsigned int res7[7];

	unsigned int vidintcon0;
	unsigned int vidintcon1;
	unsigned int res8[2];

	unsigned int w1keycon0;
	unsigned int w1keycon1;
	unsigned int w2keycon0;
	unsigned int w2keycon1;
	unsigned int w3keycon0;
	unsigned int w3keycon1;
	unsigned int w4keycon0;
	unsigned int w4keycon1;

	unsigned int dithmode;
	unsigned int res9[3];

	unsigned int win0map;
	unsigned int win1map;
	unsigned int win2map;
	unsigned int win3map;
	unsigned int win4map;
	unsigned int res10[3];

	unsigned int wpalcon;
	unsigned int trigcon;
	unsigned int ituifcon0;
	unsigned int res11[1];

	unsigned int i80ifcona0;
	unsigned int i80ifcona1;
	unsigned int i80ifconb0;
	unsigned int i80ifconb1;

	unsigned int ldi_cmdcon0;
	unsigned int ldi_cmdcon1;
	unsigned int res12[2];

	unsigned int sifccon0;
	unsigned int sifccon1;
	unsigned int sifccon2;
	unsigned int res13[37];
	
	unsigned int ldi_com[12];
	
};
#endif

#define S3C6410_FIMD_BASE			0x77100000

static inline unsigned int s3c6410_get_base_fimd(void)
{
		return S3C6410_FIMD_BASE;
}

/*
 *  Register offsets
*/
#define S3C6410_WINCON(x)				(x * 0x04)
#define S3C6410_VIDOSD(x)				(x * 0x10)
#define S3C6410_BUFFER_OFFSET(x)				(x * 0x08)
#define S3C6410_BUFFER_SIZE(x)				(x * 0x04)

/*
 * Bit Definitions
*/

/* VIDCON0 */
#define S3C6410_VIDCON0_SCAN_PROGRESSIVE			(0 << 29)
#define S3C6410_VIDCON0_SCAN_INTERLACE			(1 << 29)
#define S3C6410_VIDCON0_SCAN_MASK			(1 << 29)
#define S3C6410_VIDCON0_VIDOUT_RGB			(0 << 26)
#define S3C6410_VIDCON0_VIDOUT_ITU			(1 << 26)
#define S3C6410_VIDCON0_VIDOUT_I80LDI0			(2 << 26)
#define S3C6410_VIDCON0_VIDOUT_I80LDI1			(3 << 26)
#define S3C6410_VIDCON0_VIDOUT_MASK			(3 << 26)
#define S3C6410_VIDCON0_PNRMODE_RGB_P			(0 << 17)
#define S3C6410_VIDCON0_PNRMODE_BGR_P			(1 << 17)
#define S3C6410_VIDCON0_PNRMODE_RGB_S			(2 << 17)
#define S3C6410_VIDCON0_PNRMODE_BGR_S			(3 << 17)
#define S3C6410_VIDCON0_PNRMODE_MASK			(3 << 17)
#define S3C6410_VIDCON0_PNRMODE_SHIFT			(17)
#define S3C6410_VIDCON0_CLKVALUP_ALWAYS			(0 << 16)
#define S3C6410_VIDCON0_CLKVALUP_START_FRAME		(1 << 16)
#define S3C6410_VIDCON0_CLKVALUP_MASK			(1 << 16)
#define S3C6410_VIDCON0_CLKVAL_F(x)			(((x) & 0xff) << 6)
#define S3C6410_VIDCON0_VCLKEN_NORMAL			(0 << 5)
#define S3C6410_VIDCON0_VCLKEN_FREERUN			(1 << 5)
#define S3C6410_VIDCON0_VCLKEN_MASK			(1 << 5)
#define S3C6410_VIDCON0_CLKDIR_DIRECTED			(0 << 4)
#define S3C6410_VIDCON0_CLKDIR_DIVIDED			(1 << 4)
#define S3C6410_VIDCON0_CLKDIR_MASK			(1 << 4)
#define S3C6410_VIDCON0_CLKSEL_HCLK			(0 << 2)
#define S3C6410_VIDCON0_CLKSEL_SCLK			(1 << 2)
#define S3C6410_VIDCON0_CLKSEL_MASK			(3 << 2)
#define S3C6410_VIDCON0_ENVID_ENABLE			(1 << 1)
#define S3C6410_VIDCON0_ENVID_DISABLE			(0 << 1)
#define S3C6410_VIDCON0_ENVID_F_ENABLE			(1 << 0)
#define S3C6410_VIDCON0_ENVID_F_DISABLE			(0 << 0)

/* VIDCON1 */
#define S3C6410_VIDCON1_IVCLK_FALLING_EDGE		(0 << 7)
#define S3C6410_VIDCON1_IVCLK_RISING_EDGE		(1 << 7)
#define S3C6410_VIDCON1_IHSYNC_NORMAL			(0 << 6)
#define S3C6410_VIDCON1_IHSYNC_INVERT			(1 << 6)
#define S3C6410_VIDCON1_IVSYNC_NORMAL			(0 << 5)
#define S3C6410_VIDCON1_IVSYNC_INVERT			(1 << 5)
#define S3C6410_VIDCON1_IVDEN_NORMAL			(0 << 4)
#define S3C6410_VIDCON1_IVDEN_INVERT			(1 << 4)

/* VIDCON2 */
#define S3C6410_VIDCON2_EN601_DISABLE			(0 << 23)
#define S3C6410_VIDCON2_EN601_ENABLE			(1 << 23)
#define S3C6410_VIDCON2_EN601_MASK			(1 << 23)
#define S3C6410_VIDCON2_WB_DISABLE			(0 << 15)
#define S3C6410_VIDCON2_WB_ENABLE			(1 << 15)
#define S3C6410_VIDCON2_WB_MASK				(1 << 15)
#define S3C6410_VIDCON2_TVFORMATSEL_HW			(0 << 14)
#define S3C6410_VIDCON2_TVFORMATSEL_SW			(1 << 14)
#define S3C6410_VIDCON2_TVFORMATSEL_MASK			(1 << 14)
#define S3C6410_VIDCON2_TVFORMATSEL_RGB			(0 << 12)
#define S3C6410_VIDCON2_TVFORMATSEL_YUV422		(1 << 12)
#define S3C6410_VIDCON2_TVFORMATSEL_YUV444		(2 << 12)
#define S3C6410_VIDCON2_TVFORMATSEL_YUV_MASK		(3 << 12)
#define S3C6410_VIDCON2_ORGYUV_YCBCR			(0 << 8)
#define S3C6410_VIDCON2_ORGYUV_CBCRY			(1 << 8)
#define S3C6410_VIDCON2_ORGYUV_MASK			(1 << 8)
#define S3C6410_VIDCON2_YUVORD_CBCR			(0 << 7)
#define S3C6410_VIDCON2_YUVORD_CRCB			(1 << 7)
#define S3C6410_VIDCON2_YUVORD_MASK			(1 << 7)

/* VIDTCON0 */
#define S3C6410_VIDTCON0_VBPDE(x)			(((x) & 0xff) << 24)
#define S3C6410_VIDTCON0_VBPD(x)				(((x) & 0xff) << 16)
#define S3C6410_VIDTCON0_VFPD(x)				(((x) & 0xff) << 8)
#define S3C6410_VIDTCON0_VSPW(x)				(((x) & 0xff) << 0)

/* VIDTCON1 */
#define S3C6410_VIDTCON1_VFPDE(x)			(((x) & 0xff) << 24)
#define S3C6410_VIDTCON1_HBPD(x)				(((x) & 0xff) << 16)
#define S3C6410_VIDTCON1_HFPD(x)				(((x) & 0xff) << 8)
#define S3C6410_VIDTCON1_HSPW(x)				(((x) & 0xff) << 0)

/* VIDTCON2 */
#define S3C6410_VIDTCON2_LINEVAL(x)			(((x) & 0x7ff) << 11)
#define S3C6410_VIDTCON2_HOZVAL(x)			(((x) & 0x7ff) << 0)

/* Window 0~4 Control - WINCONx */
#define S3C6410_WINCON_DATAPATH_DMA			(0 << 22)
#define S3C6410_WINCON_DATAPATH_LOCAL			(1 << 22)
#define S3C6410_WINCON_DATAPATH_MASK			(1 << 22)
#define S3C6410_WINCON_BUFSEL_0				(0 << 20)
#define S3C6410_WINCON_BUFSEL_1				(1 << 20)
#define S3C6410_WINCON_BUFSEL_MASK			(1 << 20)
#define S3C6410_WINCON_BUFSEL_SHIFT			(20)
#define S3C6410_WINCON_BUFAUTO_DISABLE			(0 << 19)
#define S3C6410_WINCON_BUFAUTO_ENABLE			(1 << 19)
#define S3C6410_WINCON_BUFAUTO_MASK			(1 << 19)
#define S3C6410_WINCON_BITSWP_DISABLE			(0 << 18)
#define S3C6410_WINCON_BITSWP_ENABLE			(1 << 18)
#define S3C6410_WINCON_BITSWP_SHIFT			(18)
#define S3C6410_WINCON_BYTESWP_DISABLE			(0 << 17)
#define S3C6410_WINCON_BYTESWP_ENABLE			(1 << 17)
#define S3C6410_WINCON_BYTESWP_SHIFT			(17)
#define S3C6410_WINCON_HAWSWP_DISABLE			(0 << 16)
#define S3C6410_WINCON_HAWSWP_ENABLE			(1 << 16)
#define S3C6410_WINCON_HAWSWP_SHIFT			(16)
#define S3C6410_WINCON_INRGB_RGB				(0 << 13)
#define S3C6410_WINCON_INRGB_YUV				(1 << 13)
#define S3C6410_WINCON_INRGB_MASK			(1 << 13)
#define S3C6410_WINCON_BURSTLEN_16WORD			(0 << 9)
#define S3C6410_WINCON_BURSTLEN_8WORD			(1 << 9)
#define S3C6410_WINCON_BURSTLEN_4WORD			(2 << 9)
#define S3C6410_WINCON_BURSTLEN_MASK			(3 << 9)
#define S3C6410_WINCON_BLD_PLANE				(0 << 6)
#define S3C6410_WINCON_BLD_PIXEL				(1 << 6)
#define S3C6410_WINCON_BLD_MASK				(1 << 6)
#define S3C6410_WINCON_BPPMODE_1BPP			(0 << 2)
#define S3C6410_WINCON_BPPMODE_2BPP			(1 << 2)
#define S3C6410_WINCON_BPPMODE_4BPP			(2 << 2)
#define S3C6410_WINCON_BPPMODE_8BPP_PAL			(3 << 2)
#define S3C6410_WINCON_BPPMODE_8BPP			(4 << 2)
#define S3C6410_WINCON_BPPMODE_16BPP_565			(5 << 2)
#define S3C6410_WINCON_BPPMODE_16BPP_A555		(6 << 2)
#define S3C6410_WINCON_BPPMODE_16BPP_I555		(7 << 2)
#define S3C6410_WINCON_BPPMODE_18BPP_666			(8 << 2)
#define S3C6410_WINCON_BPPMODE_18BPP_A665		(9 << 2)
#define S3C6410_WINCON_BPPMODE_19BPP_A666		(0xa << 2)
#define S3C6410_WINCON_BPPMODE_24BPP_888			(0xb << 2)
#define S3C6410_WINCON_BPPMODE_24BPP_A887		(0xc << 2)
#define S3C6410_WINCON_BPPMODE_25BPP			(0xd << 2)
#define S3C6410_WINCON_BPPMODE_MASK			(0xf << 2)
#define S3C6410_WINCON_BPPMODE_SHIFT			(2)
#define S3C6410_WINCON_ALPHA0_SEL			(0 << 1)
#define S3C6410_WINCON_ALPHA1_SEL			(1 << 1)
#define S3C6410_WINCON_ALPHA_SEL_MASK			(1 << 1)
#define S3C6410_WINCON_ENWIN_DISABLE			(0 << 0)
#define S3C6410_WINCON_ENWIN_ENABLE			(1 << 0)

/* WINCON1 special */
#define S3C6410_WINCON1_LOCALSEL_FIMC1			(0 << 23)
#define S3C6410_WINCON1_LOCALSEL_VP			(1 << 23)
#define S3C6410_WINCON1_LOCALSEL_MASK			(1 << 23)

/* VIDOSDxA, VIDOSDxB */
#define S3C6410_VIDOSD_LEFT_X(x)				(((x) & 0x7ff) << 11)
#define S3C6410_VIDOSD_TOP_Y(x)				(((x) & 0x7ff) << 0)
#define S3C6410_VIDOSD_RIGHT_X(x)			(((x) & 0x7ff) << 11)
#define S3C6410_VIDOSD_BOTTOM_Y(x)			(((x) & 0x7ff) << 0)

/* VIDOSD0C, VIDOSDxD */
#define S3C6410_VIDOSD_SIZE(x)				(((x) & 0xffffff) << 0)

/* VIDOSDxC (1~4) */
#define S3C6410_VIDOSD_ALPHA0_R(x)			(((x) & 0xf) << 20)
#define S3C6410_VIDOSD_ALPHA0_G(x)			(((x) & 0xf) << 16)
#define S3C6410_VIDOSD_ALPHA0_B(x)			(((x) & 0xf) << 12)
#define S3C6410_VIDOSD_ALPHA1_R(x)			(((x) & 0xf) << 8)
#define S3C6410_VIDOSD_ALPHA1_G(x)			(((x) & 0xf) << 4)
#define S3C6410_VIDOSD_ALPHA1_B(x)			(((x) & 0xf) << 0)
#define S3C6410_VIDOSD_ALPHA0_SHIFT			(12)
#define S3C6410_VIDOSD_ALPHA1_SHIFT			(0)

/* Start Address */
#define S3C6410_VIDADDR_START_VBANK(x)			(((x) & 0xff) << 24)
#define S3C6410_VIDADDR_START_VBASEU(x)			(((x) & 0xffffff) << 0)

/* End Address */
#define S3C6410_VIDADDR_END_VBASEL(x)			(((x) & 0xffffff) << 0)

/* Buffer Size */
#define S3C6410_VIDADDR_OFFSIZE(x)			(((x) & 0x1fff) << 13)
#define S3C6410_VIDADDR_PAGEWIDTH(x)			(((x) & 0x1fff) << 0)

/* WIN Color Map */
#define S3C6410_WINMAP_COLOR(x)				((x) & 0xffffff)

/* VIDINTCON0 */
#define S3C6410_VIDINTCON0_SYSMAINCON_DISABLE		(0 << 19)
#define S3C6410_VIDINTCON0_SYSMAINCON_ENABLE		(1 << 19)
#define S3C6410_VIDINTCON0_SYSSUBCON_DISABLE		(0 << 18)
#define S3C6410_VIDINTCON0_SYSSUBCON_ENABLE		(1 << 18)
#define S3C6410_VIDINTCON0_SYSIFDONE_DISABLE		(0 << 17)
#define S3C6410_VIDINTCON0_SYSIFDONE_ENABLE		(1 << 17)
#define S3C6410_VIDINTCON0_FRAMESEL0_BACK		(0 << 15)
#define S3C6410_VIDINTCON0_FRAMESEL0_VSYNC		(1 << 15)
#define S3C6410_VIDINTCON0_FRAMESEL0_ACTIVE		(2 << 15)
#define S3C6410_VIDINTCON0_FRAMESEL0_FRONT		(3 << 15)
#define S3C6410_VIDINTCON0_FRAMESEL0_MASK		(3 << 15)
#define S3C6410_VIDINTCON0_FRAMESEL1_NONE		(0 << 13)
#define S3C6410_VIDINTCON0_FRAMESEL1_BACK		(1 << 13)
#define S3C6410_VIDINTCON0_FRAMESEL1_VSYNC		(2 << 13)
#define S3C6410_VIDINTCON0_FRAMESEL1_FRONT		(3 << 13)
#define S3C6410_VIDINTCON0_INTFRMEN_DISABLE		(0 << 12)
#define S3C6410_VIDINTCON0_INTFRMEN_ENABLE		(1 << 12)
#define S3C6410_VIDINTCON0_FIFOSEL_WIN4			(1 << 11)
#define S3C6410_VIDINTCON0_FIFOSEL_WIN3			(1 << 10)
#define S3C6410_VIDINTCON0_FIFOSEL_WIN2			(1 << 9)
#define S3C6410_VIDINTCON0_FIFOSEL_WIN1			(1 << 6)
#define S3C6410_VIDINTCON0_FIFOSEL_WIN0			(1 << 5)
#define S3C6410_VIDINTCON0_FIFOSEL_ALL			(0x73 << 5)
#define S3C6410_VIDINTCON0_FIFOSEL_MASK			(0x73 << 5)
#define S3C6410_VIDINTCON0_FIFOLEVEL_25			(0 << 2)
#define S3C6410_VIDINTCON0_FIFOLEVEL_50			(1 << 2)
#define S3C6410_VIDINTCON0_FIFOLEVEL_75			(2 << 2)
#define S3C6410_VIDINTCON0_FIFOLEVEL_EMPTY		(3 << 2)
#define S3C6410_VIDINTCON0_FIFOLEVEL_FULL		(4 << 2)
#define S3C6410_VIDINTCON0_FIFOLEVEL_MASK		(7 << 2)
#define S3C6410_VIDINTCON0_INTFIFO_DISABLE		(0 << 1)
#define S3C6410_VIDINTCON0_INTFIFO_ENABLE		(1 << 1)
#define S3C6410_VIDINTCON0_INT_DISABLE			(0 << 0)
#define S3C6410_VIDINTCON0_INT_ENABLE			(1 << 0)
#define S3C6410_VIDINTCON0_INT_MASK			(1 << 0)

/* VIDINTCON1 */
#define S3C6410_VIDINTCON1_INTI80PEND			(1 << 2)
#define S3C6410_VIDINTCON1_INTFRMPEND			(1 << 1)
#define S3C6410_VIDINTCON1_INTFIFOPEND			(1 << 0)

/* WINMAP */
#define S3C6410_WINMAP_ENABLE				(1 << 24)

/* WxKEYCON0 (1~4) */
#define S3C6410_KEYCON0_KEYBLEN_DISABLE			(0 << 26)
#define S3C6410_KEYCON0_KEYBLEN_ENABLE			(1 << 26)
#define S3C6410_KEYCON0_KEY_DISABLE			(0 << 25)
#define S3C6410_KEYCON0_KEY_ENABLE			(1 << 25)
#define S3C6410_KEYCON0_DIRCON_MATCH_FG			(0 << 24)
#define S3C6410_KEYCON0_DIRCON_MATCH_BG			(1 << 24)
#define S3C6410_KEYCON0_COMPKEY(x)			(((x) & 0xffffff) << 0)

/* WxKEYCON1 (1~4) */
#define S3C6410_KEYCON1_COLVAL(x)			(((x) & 0xffffff) << 0)

/* I80IFCONA0 and I80IFCONA1 */
#define S3C6410_LCD_CS_SETUP(x)				(((x) & 0xf) << 16)
#define S3C6410_LCD_WR_SETUP(x)				(((x) & 0xf) << 12)
#define S3C6410_LCD_WR_ACT(x)				(((x) & 0xf) << 8)
#define S3C6410_LCD_WR_HOLD(x)				(((x) & 0xf) << 4)
#define S3C6410_RSPOL_LOW				(0 << 2)
#define S3C6410_RSPOL_HIGH				(1 << 2)
#define S3C6410_I80IFEN_DISABLE				(0 << 0)
#define S3C6410_I80IFEN_ENABLE				(1 << 0)

/* TRIGCON */
#define S3C6410_I80SOFT_TRIG_EN				(1 << 0)
#define S3C6410_I80START_TRIG				(1 << 1)
#define S3C6410_I80STATUS_TRIG_DONE			(1 << 2)

#endif /* _REGS_FB_H */
