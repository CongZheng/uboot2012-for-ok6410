/*
 * Copyright (C) 2012
 * Gabriel Huau <contact@huau-gabriel.fr>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
/* #define DEBUG */
#include <common.h>
#include <asm/arch/s3c6410.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <errno.h>

#define GPIO_INPUT  0x0
#define GPIO_OUTPUT 0x1

#define S3C_GPIO_CON	0x0
#define S3C_GPIO_DAT	0x4

static uint32_t s3c_gpio_get_bank_addr(unsigned gpio)
{
	/* There is up to 16 pins per bank, one bank is 0x10 big. */
	uint32_t addr = gpio & ~0xf;
	if(gpio == -1) return 0xffffffff;
	return addr | ELFIN_GPIO_BASE;
}

int gpio_set_value(unsigned gpio, int value)
{
	uint32_t addr = s3c_gpio_get_bank_addr(gpio);

	if (addr == 0xffffffff)
		return -EINVAL;
	/* GPH GPK GPL Port have 2 configuration*/
	addr |= S3C_GPIO_DAT;
	switch(addr-ELFIN_GPIO_BASE) {
		case GPH0:
		case GPK0:
		case GPL0:
			addr += S3C_GPIO_DAT;
			break;
		default:
			break;
	}
	
	debug("gpio: addr=%x offset=%d\n", addr,(gpio&0xf));
	if (value)
		setbits_le32(addr, 1 << (gpio & 0xf));
	else
		clrbits_le32(addr, 1 << (gpio & 0xf));

	return 0;
}

int gpio_get_value(unsigned gpio)
{
	uint32_t addr = s3c_gpio_get_bank_addr(gpio);

	if (addr == 0xffffffff)
		return -EINVAL;
	/* GPH GPK GPL Port have 2 configuration*/
	addr |= S3C_GPIO_DAT;
	switch(addr-ELFIN_GPIO_BASE) {
		case GPH0:
		case GPK0:
		case GPL0:
			addr += S3C_GPIO_DAT;
			break;
		default:
			break;
	}

	return !!(readl(addr) & (1 << (gpio & 0xf)));
}

int gpio_request(unsigned gpio, const char *label)
{
	return 0;
}

int gpio_free(unsigned gpio)
{
	return 0;
}

static int s3c_gpio_direction(unsigned gpio, uint8_t dir)
{
	uint32_t addr = s3c_gpio_get_bank_addr(gpio);
	uint32_t mask = 0xf << ((gpio & 0xf) << 2);
	uint32_t dirm = dir << ((gpio & 0xf) << 2);

	if (addr == 0xffffffff)
		return -EINVAL;

	/* GPH GPK GPL Port have 2 configuration*/
	addr |= S3C_GPIO_CON;
	switch(addr-ELFIN_GPIO_BASE) {
		case GPF0:
		case GPI0:
		case GPJ0:
		case GPN0:
		case GPO0:
		case GPP0:
		case GPQ0:
			mask = 0x3 << ((gpio & 0xf) << 1);
			dirm = dir << ((gpio & 0xf) << 1);
			break;
		default:
			if((gpio & 0xf) > 7) {
				addr += 4;
			}
			break;
	}
	debug("gpio: gpio=%x addr=%x mask=%x offset=%d\n",gpio,addr,mask,(gpio&0xf));
	clrsetbits_le32(addr, mask, dirm);
	return 0;
}

int gpio_direction_input(unsigned gpio)
{
	return s3c_gpio_direction(gpio, GPIO_INPUT);
}

int gpio_direction_output(unsigned gpio, int value)
{
	s3c_gpio_direction(gpio, GPIO_OUTPUT);
	return gpio_set_value(gpio, value);
}
