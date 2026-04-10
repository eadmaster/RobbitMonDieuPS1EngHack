#!/bin/bash

INPUT_ROM="Robbit mon Dieu (Japan).bin"
OUTPUT_ROM="Robbit mon Dieu (English).bin"

# extract -> creates "Robbit mon Dieu (Japan).xml"
# dumpsxiso "$INPUT_ROM"

# compile main exe with https://github.com/C0mposer/C-Game-Modding-Utility/wiki/Command-Line-Interface
#  -> writes  mod_utility_prj/build/patched_SCPS_101.03
# TODO: call compiler directly
wine $HOME/opt/C0mpose_mod_utility/mod_utility.exe build RobbitMonDieuPS1Eng3

# rebuild with https://github.com/Lameguy64/mkpsxiso
mkpsxiso -y "Robbit mon Dieu (English).xml" --output "$OUTPUT_ROM" --cuefile "Robbit mon Dieu (English).cue"

# build xdelta patch
xdelta3 -S none -f -e -s "$INPUT_ROM" "$OUTPUT_ROM"  "Robbit.mon.Dieu.English.xdelta"

