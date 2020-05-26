#
# Copyright 2018 CompuLab
#
# SPDX-License-Identifier:      GPL-2.0+
#

obj-y += ucm-imx8m-mini.o

ifdef CONFIG_SPL_BUILD
obj-y += spl.o
obj-y += ddr/ddr.o
obj-y += ddr/lpddr4_timing_ff020008.o
obj-y += ddr/lpddr4_timing_ff000110.o
obj-y += ddr/lpddr4_timing_01061010.o
obj-y += ddr/lpddr4_timing_01050008.o
obj-y += eeprom_spl.o
else
obj-y += ucm-imx8m-mini.o eeprom.o
endif
