/*
 * Copyright (c) 2012.
 *
 * Gabriel Huau <contact@huau-gabriel.fr>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _S3C64X0_GPIO_H_
#define _S3C64X0_GPIO_H_

enum s3c2440_gpio {
	GPA0,
	GPA1,
	GPA2,
	GPA3,
	GPA4,
	GPA5,
	GPA6,
	GPA7,

	GPB0 = 32,
	GPB1,
	GPB2,
	GPB3,
	GPB4,
	GPB5,
	GPB6,

	GPC0 = 64,
	GPC1,
	GPC2,
	GPC3,
	GPC4,
	GPC5,
	GPC6,
	GPC7,

	GPD0 = 96,
	GPD1,
	GPD2,
	GPD3,
	GPD4,

	GPE0 = 128,
	GPE1,
	GPE2,
	GPE3,
	GPE4,

	GPF0 = 160,
	GPF1,
	GPF2,
	GPF3,
	GPF4,
	GPF5,
	GPF6,
	GPF7,
	GPF8,
	GPF9,
	GPF10,
	GPF11,
	GPF12,
	GPF13,
	GPF14,
	GPF15,

	GPG0 = 192,
	GPG1,
	GPG2,
	GPG3,
	GPG4,
	GPG5,
	GPG6,

	GPH0 = 224,
	GPH1,
	GPH2,
	GPH3,
	GPH4,
	GPH5,
	GPH6,
	GPH7,
	GPH8,
	GPH9,

	GPI0 = 256,
	GPI1,
	GPI2,
	GPI3,
	GPI4,
	GPI5,
	GPI6,
	GPI7,
	GPI8,
	GPI9,
	GPI10,
	GPI11,
	GPI12,
	GPI13,
	GPI14,
	GPI15,

	GPJ0 = 288,
	GPJ1,
	GPJ2,
	GPJ3,
	GPJ4,
	GPJ5,
	GPJ6,
	GPJ7,
	GPJ8,
	GPJ9,
	GPJ10,
	GPJ11,

	GPO0 = 320,
	GPO1,
	GPO2,
	GPO3,
	GPO4,
	GPO5,
	GPO6,
	GPO7,
	GPO8,
	GPO9,
	GPO10,
	GPO11,
	GPO12,
	GPO13,
	GPO14,
	GPO15,

	GPP0 = 352,
	GPP1,
	GPP2,
	GPP3,
	GPP4,
	GPP5,
	GPP6,
	GPP7,
	GPP8,
	GPP9,
	GPP10,
	GPP11,
	GPP12,
	GPP13,
	GPP14,

	GPQ0 = 384,
	GPQ1,
	GPQ2,
	GPQ3,
	GPQ4,
	GPQ5,
	GPQ6,
	GPQ7,
	GPQ8,

	GPK0 = 2048,
	GPK1,
	GPK2,
	GPK3,
	GPK4,
	GPK5,
	GPK6,
	GPK7,
	GPK8,
	GPK9,
	GPK10,
	GPK11,
	GPK12,
	GPK13,
	GPK14,
	GPK15,

	GPL0 = 2064,
	GPL1,
	GPL2,
	GPL3,
	GPL4,
	GPL5,
	GPL6,
	GPL7,
	GPL8,
	GPL9,
	GPL10,
	GPL11,
	GPL12,
	GPL13,
	GPL14,

	GPM0 = 2080,
	GPM1,
	GPM2,
	GPM3,
	GPM4,
	GPM5,

	GPN0 = 2096,
	GPN1,
	GPN2,
	GPN3,
	GPN4,
	GPN5,
	GPN6,
	GPN7,
	GPN8,
	GPN9,
	GPN10,
	GPN11,
	GPN12,
	GPN13,
	GPN14,
	GPN15,
};

#endif