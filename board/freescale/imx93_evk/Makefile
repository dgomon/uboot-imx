#
# Copyright 2022 NXP
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += imx93_evk.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
ifdef CONFIG_IMX9_DRAM_INLINE_ECC
obj-$(CONFIG_IMX93_EVK_LPDDR4X) += lpddr4x_timing_ecc.o lpddr4x_timing_1866mts_ecc.o
else
obj-$(CONFIG_IMX93_EVK_LPDDR4X) += lpddr4x_timing.o lpddr4x_timing_1866mts.o
endif
endif
