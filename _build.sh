#!/bin/bash

INPUT_ROM="Robbit mon Dieu (Japan).bin"
OUTPUT_ROM="Robbit mon Dieu (English).bin"

# https://github.com/C0mposer/C-Game-Modding-Utility/wiki/Command-Line-Interface
#wine $HOME/opt/C0mpose_mod_utility/mod_utility.exe build RobbitMonDieuPS1Eng2
cp "mod_utility_prj/build/ModdedGame_DEFAULT.bin" "$OUTPUT_ROM"

# https://github.com/cebix/psximager
psxinject "$OUTPUT_ROM" SCPS_101.03 mod_utility_prj/build/patched_SCPS_101.03
psxinject "$OUTPUT_ROM" MAP.CSV mod_utility_prj/src/map.csv
psxinject "$OUTPUT_ROM" INGAME.CSV mod_utility_prj/src/ingame.csv

# build xdelta patch
xdelta3 -S none -f -e -s "$INPUT_ROM" "$OUTPUT_ROM"  "Robbit.mon.Dieu.English.xdelta"

