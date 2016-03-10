/*
 * Copyright (C) 2012 Samsung Electronics
 *
 * Author: InKi Dae <inki.dae@samsung.com>
 * Author: Donghwa Lee <dh09.lee@samsung.com>
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

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <lcd.h>
#include <div64.h>
#include <asm/arch/s3c6410.h>
#include "s3c6410_fb.h"

static unsigned long *lcd_base_addr;
static vidinfo_t *pvid;

void s3c6410_fimd_lcd_init_mem(u_long screen_base, u_long fb_size,
		u_long palette_size)
{
	lcd_base_addr = (unsigned long *)screen_base;
}

static void s3c6410_fimd_set_par(unsigned int win_id)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	/* set window control */
	cfg = readl((unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));

	cfg &= ~(S3C6410_WINCON_BITSWP_ENABLE | S3C6410_WINCON_BYTESWP_ENABLE |
		S3C6410_WINCON_HAWSWP_ENABLE |S3C6410_WINCON_BURSTLEN_MASK |
		S3C6410_WINCON_BPPMODE_MASK |S3C6410_WINCON_INRGB_MASK | 
		S3C6410_WINCON_DATAPATH_MASK);

	/* DATAPATH is DMA */
	cfg |= S3C6410_WINCON_DATAPATH_DMA;

	/* bpp is 32 */
	cfg |= S3C6410_WINCON_HAWSWP_ENABLE;

	/* dma burst is 16 */
	cfg |= S3C6410_WINCON_BURSTLEN_16WORD;

	/* pixel format is unpacked RGB888 */
	cfg |= S3C6410_WINCON_BPPMODE_16BPP_565;

	writel(cfg, (unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));

	/* set window position to x=0, y=0*/
	cfg = S3C6410_VIDOSD_LEFT_X(0) | S3C6410_VIDOSD_TOP_Y(0);
	writel(cfg, (unsigned int)&fimd_ctrl->vidosd0a +
			S3C6410_VIDOSD(win_id));

	cfg = S3C6410_VIDOSD_RIGHT_X(pvid->vl_col - 1) |
		S3C6410_VIDOSD_BOTTOM_Y(pvid->vl_row - 1);

	writel(cfg, (unsigned int)&fimd_ctrl->vidosd0b +
			S3C6410_VIDOSD(win_id));

	/* set window size for window0*/
	cfg = S3C6410_VIDOSD_SIZE(pvid->vl_col * pvid->vl_row);
	writel(cfg, (unsigned int)&fimd_ctrl->vidosd0c +
			S3C6410_VIDOSD(win_id));
}

static void s3c6410_fimd_set_buffer_address(unsigned int win_id)
{
	unsigned long start_addr, end_addr;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	start_addr = (unsigned long)lcd_base_addr;
	end_addr = start_addr + ((pvid->vl_col * (NBITS(pvid->vl_bpix) / 8)) *
				pvid->vl_row);

	writel(start_addr, (unsigned int)&fimd_ctrl->vidw00add0b0 +
			S3C6410_BUFFER_OFFSET(win_id));
	writel(end_addr, (unsigned int)&fimd_ctrl->vidw00add1b0 +
			S3C6410_BUFFER_OFFSET(win_id));
}

static void s3c6410_fimd_set_clock(vidinfo_t *pvid)
{
	unsigned int cfg = 0, div = 0, remainder, remainder_div;
	unsigned long pixel_clock;
	unsigned long long src_clock;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	if (pvid->interface_mode == FIMD_CPU_INTERFACE) {
		pixel_clock = pvid->vl_freq *
				pvid->vl_width * pvid->vl_height *
				(pvid->cs_setup + pvid->wr_setup +
				 pvid->wr_act + pvid->wr_hold + 1);
	} else {
		pixel_clock = pvid->vl_freq *
				(pvid->vl_hspw + pvid->vl_hfpd +
				 pvid->vl_hbpd + pvid->vl_col) *
				(pvid->vl_vspw + pvid->vl_vfpd +
				 pvid->vl_vbpd + pvid->vl_row);
	}

	cfg = readl(&fimd_ctrl->vidcon0);
	cfg &= ~(S3C6410_VIDCON0_CLKSEL_MASK | S3C6410_VIDCON0_CLKVALUP_MASK |
		S3C6410_VIDCON0_CLKVAL_F(0xFF) | S3C6410_VIDCON0_VCLKEN_MASK |
		S3C6410_VIDCON0_CLKDIR_MASK);
	cfg |= (S3C6410_VIDCON0_CLKSEL_HCLK | S3C6410_VIDCON0_CLKVALUP_ALWAYS |
		S3C6410_VIDCON0_VCLKEN_NORMAL | S3C6410_VIDCON0_CLKDIR_DIVIDED);

	src_clock = (unsigned long long) get_HCLK();

	/* get quotient and remainder. */
	remainder = do_div(src_clock, pixel_clock);
	div = src_clock;

	remainder *= 10;
	remainder_div = remainder / pixel_clock;

	/* round about one places of decimals. */
	if (remainder_div >= 5)
		div++;

	cfg |= S3C6410_VIDCON0_CLKVAL_F(div - 1);
	writel(cfg, &fimd_ctrl->vidcon0);
}

void s3c6410_set_trigger(void)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	cfg = readl(&fimd_ctrl->trigcon);

	cfg |= (S3C6410_I80SOFT_TRIG_EN | S3C6410_I80START_TRIG);

	writel(cfg, &fimd_ctrl->trigcon);
}

int s3c6410_is_i80_frame_done(void)
{
	unsigned int cfg = 0;
	int status;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	cfg = readl(&fimd_ctrl->trigcon);

	/* frame done func is valid only when TRIMODE[0] is set to 1. */
	status = (cfg & S3C6410_I80STATUS_TRIG_DONE) ==
			S3C6410_I80STATUS_TRIG_DONE;

	return status;
}

static void s3c6410_fimd_lcd_on(void)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	/* display on */
	cfg = readl(&fimd_ctrl->vidcon0);
	cfg |= (S3C6410_VIDCON0_ENVID_ENABLE | S3C6410_VIDCON0_ENVID_F_ENABLE);
	writel(cfg, &fimd_ctrl->vidcon0);
}

static void s3c6410_fimd_window_on(unsigned int win_id)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	/* enable window */
	cfg = readl((unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));
	cfg |= S3C6410_WINCON_ENWIN_ENABLE;
	writel(cfg, (unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));
}

void s3c6410_fimd_lcd_off(void)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	cfg = readl(&fimd_ctrl->vidcon0);
	cfg &= (S3C6410_VIDCON0_ENVID_DISABLE | S3C6410_VIDCON0_ENVID_F_DISABLE);
	writel(cfg, &fimd_ctrl->vidcon0);
}

void s3c6410_fimd_window_off(unsigned int win_id)
{
	unsigned int cfg = 0;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	cfg = readl((unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));
	cfg &= S3C6410_WINCON_ENWIN_DISABLE;
	writel(cfg, (unsigned int)&fimd_ctrl->wincon0 +
			S3C6410_WINCON(win_id));
}


void s3c6410_fimd_lcd_init(vidinfo_t *vid)
{
	unsigned int cfg = 0, rgb_mode;
	unsigned int offset;
	struct s3c6410_fb *fimd_ctrl =
		(struct s3c6410_fb *)s3c6410_get_base_fimd();

	offset = 0;

	/* store panel info to global variable */
	pvid = vid;

	rgb_mode = vid->rgb_mode;

	if (vid->interface_mode == FIMD_RGB_INTERFACE) {
		cfg |= S3C6410_VIDCON0_VIDOUT_RGB;
		writel(cfg, &fimd_ctrl->vidcon0);

		cfg = readl(&fimd_ctrl->vidcon2);
		cfg &= ~(S3C6410_VIDCON2_WB_MASK |
			S3C6410_VIDCON2_TVFORMATSEL_MASK |
			S3C6410_VIDCON2_TVFORMATSEL_YUV_MASK);
		cfg |= S3C6410_VIDCON2_WB_DISABLE;
		writel(cfg, &fimd_ctrl->vidcon2);

		/* set polarity */
		cfg = 0;
		if (!pvid->vl_clkp)
			cfg |= S3C6410_VIDCON1_IVCLK_RISING_EDGE;
		if (!pvid->vl_hsp)
			cfg |= S3C6410_VIDCON1_IHSYNC_INVERT;
		if (!pvid->vl_vsp)
			cfg |= S3C6410_VIDCON1_IVSYNC_INVERT;
		if (!pvid->vl_dp)
			cfg |= S3C6410_VIDCON1_IVDEN_INVERT;

		writel(cfg, (unsigned int)&fimd_ctrl->vidcon1 + offset);

		/* set timing */
		cfg = S3C6410_VIDTCON0_VFPD(pvid->vl_vfpd - 1);
		cfg |= S3C6410_VIDTCON0_VBPD(pvid->vl_vbpd - 1);
		cfg |= S3C6410_VIDTCON0_VSPW(pvid->vl_vspw - 1);
		writel(cfg, (unsigned int)&fimd_ctrl->vidtcon0 + offset);

		cfg = S3C6410_VIDTCON1_HFPD(pvid->vl_hfpd - 1);
		cfg |= S3C6410_VIDTCON1_HBPD(pvid->vl_hbpd - 1);
		cfg |= S3C6410_VIDTCON1_HSPW(pvid->vl_hspw - 1);

		writel(cfg, (unsigned int)&fimd_ctrl->vidtcon1 + offset);

		/* set lcd size */
		cfg = S3C6410_VIDTCON2_HOZVAL(pvid->vl_col - 1) |
			S3C6410_VIDTCON2_LINEVAL(pvid->vl_row - 1);

		writel(cfg, (unsigned int)&fimd_ctrl->vidtcon2 + offset);
	}

	/* set display mode */
	cfg = readl(&fimd_ctrl->vidcon0);
	cfg &= ~S3C6410_VIDCON0_PNRMODE_MASK;
	cfg |= (rgb_mode << S3C6410_VIDCON0_PNRMODE_SHIFT);
	writel(cfg, &fimd_ctrl->vidcon0);

	/* set par */
	s3c6410_fimd_set_par(pvid->win_id);

	/* set memory address */
	s3c6410_fimd_set_buffer_address(pvid->win_id);

	/* set buffer size */
	cfg = S3C6410_VIDADDR_PAGEWIDTH(pvid->vl_col * NBITS(pvid->vl_bpix) / 8) |
		S3C6410_VIDADDR_OFFSIZE(0);

	writel(cfg, (unsigned int)&fimd_ctrl->vidw00add2 +
					S3C6410_BUFFER_SIZE(pvid->win_id));

	/* set clock */
	s3c6410_fimd_set_clock(pvid);

	/* display on */
	s3c6410_fimd_lcd_on();

	/* window on */
	s3c6410_fimd_window_on(pvid->win_id);
}

unsigned long s3c6410_fimd_calc_fbsize(void)
{
	return pvid->vl_col * pvid->vl_row * (NBITS(pvid->vl_bpix) / 8);
}
