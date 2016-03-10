/*
 * Copyright (C) 2012 Samsung Electronics
 *
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

#include <common.h>
#include <linux/list.h>
#include <linux/fb.h>
#include <lcd.h>
#include <mipi_display.h>
#include <asm/arch/gpio.h>
#include <asm/gpio.h>
#include "ssd2828.h"


struct short_packet {
	unsigned char cmd;
	unsigned char par;
};

const struct short_packet data_to_send[] = {
	{0xFF,0xEE},//For LOW Temp. can't initial 
	{0x26,0x08},//                                       
	{0x26,0x00},//                                       
	{0xFF,0x00},//                                       
	{0xFF,0x01},//Command2 page0                         
	{0xFB,0x01},//Register                               
	{0x00,0x4A},//Set select panel application           
	{0x01,0x33},//Set Pump Freq                          
	{0x02,0x53},//                                       
	{0x03,0x55},//                                       
	{0x04,0x55},//                                       
	{0x05,0x33},//Set AVDD=6V/AVEE=-6V                   
	{0x06,0x22},//Set AVDD/AVEE output level             
	{0x08,0x56},//Set VGH level 2AVDD/VGL level 2VCL-AVDD
	{0x09,0x8F},//Set VGL -8V                            
	{0x0B,0xCF},//Set GVDDP=-4.7V                        
	{0x0C,0xCF},//Set GVDDP=+4.7V                        
	{0x0D,0x2F},//Set VCI1=3.05V                         
//	{0x0E,0x33},//Set VGHO=10V   
	{0x0E,0x29},
//	{0x11,0x7D},//Set VCOMDC3                            
//	{0x12,0x03},//                                       
	{0x36,0x73},//Enable gate EQ                         
	{0x0F,0x0A},//NVT ENGINEER COMMAND                   
	{0xFF,0xEE},//For Bonding too large , drop voltage   
	{0xFB,0x01},//                                       
	{0x12,0x50},//                                       
	{0x13,0x02},//                                       
	{0x6A,0x60},//    
	                                   
	//LTPS Timing
	{0xFF,0x05},
	{0xFB,0x01},
	{0x01,0x00},
	{0x02,0x82},//8D  82
	{0x03,0x82},//8D  82
	{0x04,0x82},//8D  82
	{0x06,0x33},
	{0x07,0x01},
	{0x08,0x00},
	{0x09,0x46},
	{0x0A,0x46},
	{0x0D,0x0B},
	{0x0E,0x1D},
	{0x0F,0x08},
	{0x10,0x53},
	{0x11,0x00},
	{0x12,0x00},
	{0x14,0x01},
	{0x15,0x00},
	{0x16,0x05},
	{0x17,0x00},
	{0x19,0x7F},
	{0x1A,0xFF},
	{0x1B,0x0F},
	{0x1C,0x00},
	{0x1D,0x00},
	{0x1E,0x00},
	{0x1F,0x07},
	{0x20,0x00},
	{0x21,0x00},
	{0x22,0x55},
//	{0x22,0x11},
	{0x23,0x4D},//4//4D
	{0x2D,0x02},
	{0x83,0x01},
	{0x9E,0x58},
	{0x9F,0x78},//6a
	{0xA0,0x01},
	{0xA2,0x10},
	{0xBB,0x0A},
	{0xBC,0x0A},
	{0x28,0x01},//01
	{0x2F,0x02},//02
	{0x32,0x08},
	{0x33,0xB8},
	{0x36,0x01},
	{0x37,0x00},
	{0x43,0x00},
	{0x4B,0x21},
	{0x4C,0x03},
	{0x50,0x21},
	{0x51,0x03},
	{0x58,0x21},
	{0x59,0x03},
	{0x5D,0x21},
	{0x5E,0x03},
	{0x6C,0x00},
	{0x6D,0x00}, 

	{0xFF,0x00},//UCS
	{0xFB,0x01},
	
	{0xBA,0x03},//1LANES	0x03 4-lanes	0x01:2lane
//	{0xC2,0x0B},//Video mode with Ram
	{0xC2,0x03},//Video mode without Ram
//	{0xC2,0x08},//command mode with Ram
	{0x36,0x01},
	{0x3A,0x55}, // 5:16bpp	6:18bpp 7:24bpp
	        
	{0x51,0xff}, //��������
	{0x53,0x24},
        
//	{0xFF,0x04},//Command2 page3                         
//	{0xFB,0x01},//Register
//	{0x00,0x08},//b3:ledpwm(output-hz)b?:force_cabc_pwm
//	{0x01,0x02},//b1:ledpwmpol b?:pwm_enh_oe
        
	//Gamma Red+ setting
	{0xFF,0x01},
	{0xFB,0x01},
	{0x75,0x00},
	{0x76,0x98},
	{0x77,0x00},
	{0x78,0xAF},
	{0x79,0x00},
	{0x7A,0xD1},
	{0x7B,0x00},
	{0x7C,0xE9},
	{0x7D,0x00},
	{0x7E,0xFE},
	{0x7F,0x01},
	{0x80,0x10},
	{0x81,0x01},
	{0x82,0x20},
	{0x83,0x01},
	{0x84,0x2E},
	{0x85,0x01},
	{0x86,0x3B},
	{0x87,0x01},
	{0x88,0x65},
	{0x89,0x01},
	{0x8A,0x88},
	{0x8B,0x01},
	{0x8C,0xBD},
	{0x8D,0x01},
	{0x8E,0xE7},
	{0x8F,0x02},
	{0x90,0x27},
	{0x91,0x02},
	{0x92,0x59},
	{0x93,0x02},
	{0x94,0x5B},
	{0x95,0x02},
	{0x96,0x87},
	{0x97,0x02},
	{0x98,0xB6},
	{0x99,0x02},
	{0x9A,0xD5},
	{0x9B,0x02},
	{0x9C,0xFD},
	{0x9D,0x03},
	{0x9E,0x19},
	{0x9F,0x03},
	{0xA0,0x40},
	{0xA2,0x03},
	{0xA3,0x4C},
	{0xA4,0x03},
	{0xA5,0x59},
	{0xA6,0x03},
	{0xA7,0x67},
	{0XA9,0x03},
	{0xAA,0x78},
	{0xAB,0x03},
	{0xAC,0x8A},
	{0xAD,0x03},
	{0xAE,0xA8},
	{0xAF,0x03},
	{0xB0,0xB8},
	{0xB1,0x03},
	{0xB2,0xBE},

	//Gamma Red- setting 
	{0xB3,0x00},
	{0xB4,0x98},
	{0xB5,0x00},
	{0xB6,0xAF},
	{0xB7,0x00},
	{0xB8,0xD1},
	{0xB9,0x00},
	{0xBA,0xE9},
	{0xBB,0x00},
	{0xBC,0xFE},
	{0xBD,0x01},
	{0xBE,0x10},
	{0xBF,0x01},
	{0xC0,0x20},
	{0xC1,0x01},
	{0xC2,0x2E},
	{0xC3,0x01},
	{0xC4,0x3B},
	{0xC5,0x01},
	{0xC6,0x65},
	{0xC7,0x01},
	{0xC8,0x88},
	{0xC9,0x01},
	{0xCA,0xBD},
	{0xCB,0x01},
	{0xCC,0xE7},
	{0xCD,0x02},
	{0xCE,0x27},
	{0xCF,0x02},
	{0xD0,0x59},
	{0xD1,0x02},
	{0xD2,0x5B},
	{0xD3,0x02},
	{0xD4,0x87},
	{0xD5,0x02},
	{0xD6,0xB6},
	{0xD7,0x02},
	{0xD8,0xD5},
	{0xD9,0x02},
	{0xDA,0xFD},
	{0xDB,0x03},
	{0xDC,0x19},
	{0xDD,0x03},
	{0xDE,0x40},
	{0xDF,0x03},
	{0xE0,0x4C},
	{0xE1,0x03},
	{0xE2,0x59},
	{0xE3,0x03},
	{0xE4,0x67},
	{0xE5,0x03},
	{0xE6,0x78},
	{0xE7,0x03},
	{0xE8,0x8A},
	{0xE9,0x03},
	{0xEA,0xA8},
	{0xEB,0x03},
	{0xEC,0xB8},
	{0xED,0x03},
	{0xEE,0xBE}, 

	//Gamma Green+ setting
	{0xEF,0x00},
	{0xF0,0x98},
	{0xF1,0x00},
	{0xF2,0xAF},
	{0xF3,0x00},
	{0xF4,0xD1},
	{0xF5,0x00},
	{0xF6,0xE9},
	{0xF7,0x00},
	{0xF8,0xFE},
	{0xF9,0x01},
	{0xFA,0x10},
	{0xFF,0x02},
	{0xFB,0x01},
	{0x00,0x01},
	{0x01,0x20},
	{0x02,0x01},
	{0x03,0x2E},
	{0x04,0x01},
	{0x05,0x3B},
	{0x06,0x01},
	{0x07,0x65},
	{0x08,0x01},
	{0x09,0x88},
	{0x0A,0x01},
	{0x0B,0xBD},
	{0x0C,0x01},
	{0x0D,0xE7},
	{0x0E,0x02},
	{0x0F,0x27},
	{0x10,0x02},
	{0x11,0x59},
	{0x12,0x02},
	{0x13,0x5B},
	{0x14,0x02},
	{0x15,0x87},
	{0x16,0x02},
	{0x17,0xB6},
	{0x18,0x02},
	{0x19,0xD5},
	{0x1A,0x02},
	{0x1B,0xFD},
	{0x1C,0x03},
	{0x1D,0x19},
	{0x1E,0x03},
	{0x1F,0x40},
	{0x20,0x03},
	{0x21,0x4C},
	{0x22,0x03},
	{0x23,0x59},
	{0x24,0x03},
	{0x25,0x67},
	{0x26,0x03},
	{0x27,0x78},
	{0x28,0x03},
	{0x29,0x8A},
	{0x2A,0x03},
	{0x2B,0xA8},
	{0x2D,0x03},
	{0x2F,0xB8},
	{0x30,0x03},
	{0x31,0xBE},  

	//Gamma Green- setting  
	{0x32,0x00},
	{0x33,0x98},
	{0x34,0x00},
	{0x35,0xAF},
	{0x36,0x00},
	{0x37,0xD1},
	{0x38,0x00},
	{0x39,0xE9},
	{0x3A,0x00},
	{0x3B,0xFE},
	{0x3D,0x01},
	{0x3F,0x10},
	{0x40,0x01},
	{0x41,0x20},
	{0x42,0x01},
	{0x43,0x2E},
	{0x44,0x01},
	{0x45,0x3B},
	{0x46,0x01},
	{0x47,0x65},
	{0x48,0x01},
	{0x49,0x88},
	{0x4A,0x01},
	{0x4B,0xBD},
	{0x4C,0x01},
	{0x4D,0xE7},
	{0x4E,0x02},
	{0x4F,0x27},
	{0x50,0x02},
	{0x51,0x59},
	{0x52,0x02},
	{0x53,0x5B},
	{0x54,0x02},
	{0x55,0x87},
	{0x56,0x02},
	{0x58,0xB6},
	{0x59,0x02},
	{0x5A,0xD5},
	{0x5B,0x02},
	{0x5C,0xFD},
	{0x5D,0x03},
	{0x5E,0x19},
	{0x5F,0x03},
	{0x60,0x40},
	{0x61,0x03},
	{0x62,0x4C},
	{0x63,0x03},
	{0x64,0x59},
	{0x65,0x03},
	{0x66,0x67},
	{0x67,0x03},
	{0x68,0x78},
	{0x69,0x03},
	{0x6A,0x8A},
	{0x6B,0x03},
	{0x6C,0xA8},
	{0x6D,0x03},
	{0x6E,0xB8},
	{0x6F,0x03},
	{0x70,0xBE}, 

	//Gamma Blue+ setting
	{0x71,0x00},
	{0x72,0x98},
	{0x73,0x00},
	{0x74,0xAF},
	{0x75,0x00},
	{0x76,0xD1},
	{0x77,0x00},
	{0x78,0xE9},
	{0x79,0x00},
	{0x7A,0xFE},
	{0x7B,0x01},
	{0x7C,0x10},
	{0x7D,0x01},
	{0x7E,0x20},
	{0x7F,0x01},
	{0x80,0x2E},
	{0x81,0x01},
	{0x82,0x3B},
	{0x83,0x01},
	{0x84,0x65},
	{0x85,0x01},
	{0x86,0x88},
	{0x87,0x01},
	{0x88,0xBD},
	{0x89,0x01},
	{0x8A,0xE7},
	{0x8B,0x02},
	{0x8C,0x27},
	{0x8D,0x02},
	{0x8E,0x59},
	{0x8F,0x02},
	{0x90,0x5B},
	{0x91,0x02},
	{0x92,0x87},
	{0x93,0x02},
	{0x94,0xB6},
	{0x95,0x02},
	{0x96,0xD5},
	{0x97,0x02},
	{0x98,0xFD},
	{0x99,0x03},
	{0x9A,0x19},
	{0x9B,0x03},
	{0x9C,0x40},
	{0x9D,0x03},
	{0x9E,0x4C},
	{0x9F,0x03},
	{0xA0,0x59},
	{0xA2,0x03},
	{0xA3,0x67},
	{0xA4,0x03},
	{0xA5,0x78},
	{0xA6,0x03},
	{0xA7,0x8A},
	{0XA9,0x03},
	{0xAA,0xA8},
	{0xAB,0x03},
	{0xAC,0xB8},
	{0xAD,0x03},
	{0xAE,0xBE},

	//Gamma Blue- setting
	{0xAF,0x00},
	{0xB0,0x98},
	{0xB1,0x00},
	{0xB2,0xAF},
	{0xB3,0x00},
	{0xB4,0xD1},
	{0xB5,0x00},
	{0xB6,0xE9},
	{0xB7,0x00},
	{0xB8,0xFE},
	{0xB9,0x01},
	{0xBA,0x10},
	{0xBB,0x01},
	{0xBC,0x20},
	{0xBD,0x01},
	{0xBE,0x2E},
	{0xBF,0x01},
	{0xC0,0x3B},
	{0xC1,0x01},
	{0xC2,0x65},
	{0xC3,0x01},
	{0xC4,0x88},
	{0xC5,0x01},
	{0xC6,0xBD},
	{0xC7,0x01},
	{0xC8,0xE7},
	{0xC9,0x02},
	{0xCA,0x27},
	{0xCB,0x02},
	{0xCC,0x59},
	{0xCD,0x02},
	{0xCE,0x5B},
	{0xCF,0x02},
	{0xD0,0x87},
	{0xD1,0x02},
	{0xD2,0xB6},
	{0xD3,0x02},
	{0xD4,0xD5},
	{0xD5,0x02},
	{0xD6,0xFD},
	{0xD7,0x03},
	{0xD8,0x19},
	{0xD9,0x03},
	{0xDA,0x40},
	{0xDB,0x03},
	{0xDC,0x4C},
	{0xDD,0x03},
	{0xDE,0x59},
	{0xDF,0x03},
	{0xE0,0x67},
	{0xE1,0x03},
	{0xE2,0x78},
	{0xE3,0x03},
	{0xE4,0x8A},
	{0xE5,0x03},
	{0xE6,0xA8},
	{0xE7,0x03},
	{0xE8,0xB8},
	{0xE9,0x03},
	{0xEA,0xBE},
	{0xFF,0x00},
};

vidinfo_t panel_info = {
	.vl_freq	= 60,
	.vl_col		= 720,
	.vl_row		= 1280,
	.vl_width	= 720,
	.vl_height	= 1280,
	.vl_clkp	= CONFIG_SYS_HIGH,
	.vl_hsp		= CONFIG_SYS_HIGH,
	.vl_vsp		= CONFIG_SYS_HIGH,
	.vl_dp		= CONFIG_SYS_LOW,
 	.vl_bpix	= 4,	/* Bits per pixel, 2^5 = 32 */

	/* Panel infomation */
	.vl_hspw	= 2,
	.vl_hbpd	= 6,
	.vl_hfpd	= 6,

	.vl_vspw	= 1,
	.vl_vbpd	= 1,
	.vl_vfpd	= 1,

	.win_id		= 0,
	.cfg_gpio	= NULL,
	.backlight_on	= NULL,
	.lcd_power_on	= NULL,	/* lcd_power_on in mipi dsi driver */
	.reset_lcd	= NULL,

	.init_delay	= 0,
	.power_on_delay = 0,
	.reset_delay	= 0,
	.interface_mode = FIMD_RGB_INTERFACE,
	.mipi_enabled	= 1,
};

static void nt35590_panel_init(const struct ssd2828_config *cfg)
{
	unsigned int i,data;
	
	for(i = 0;i < ARRAY_SIZE(data_to_send);i++) {
		data = data_to_send[i].cmd|(data_to_send[i].par << 8);
		send_mipi_dcs_command(cfg, data, 2);
	}
}

static void convert_to_fb_videomode(struct fb_videomode *mode1,vidinfo_t *mode2)
{
	mode1->xres = mode2->vl_width;
	mode1->yres = mode2->vl_height;
	mode1->upper_margin = mode2->vl_vfpd;
	mode1->lower_margin = mode2->vl_vbpd;
	mode1->left_margin = mode2->vl_hfpd;
	mode1->right_margin = mode2->vl_hbpd;
	mode1->vsync_len = mode2->vl_vspw;
	mode1->hsync_len = mode2->vl_hspw;
}

void init_panel_info(vidinfo_t *vid)
{
	
	vid->logo_on	= 0;
	vid->rgb_mode	= MODE_RGB_P;
	
	setenv("lcdinfo", "lcd_mipi_dsi_nt35590");
}

void mipi_dsi_init(void)
{
	struct fb_videomode lcd_dev;
	struct ssd2828_config cfg = {
/*
		.csx_pin	= GPC3,
		.sck_pin	= GPC1,
		.sdi_pin	= GPC2,
		.sdo_pin	= GPC0,
		.reset_pin	= GPP1,
*/
		.csx_pin	= GPI9,	//VD9
		.sck_pin	= GPJ2, //VD18
		.sdi_pin	= GPJ1, //VD17
		.sdo_pin	= GPJ0, //VD16
		.reset_pin	= GPI8, //VD8

		.ssd2828_tx_clk_khz = 12000, 
		.ssd2828_color_depth = 16,
		.mipi_dsi_number_of_data_lanes	= 4,
		.mipi_dsi_bitrate_per_data_lane_mbps	= 500,
		.mipi_dsi_loosely_packed_pixel_format	= 0,
	
		.mipi_dsi_delay_after_exit_sleep_mode_ms = 100,
		.mipi_dsi_delay_after_set_display_on_ms	= 100,
		.lcd_lp_init	= nt35590_panel_init,
	};
	convert_to_fb_videomode(&lcd_dev, &panel_info);
	ssd2828_init(&cfg, &lcd_dev);
}

