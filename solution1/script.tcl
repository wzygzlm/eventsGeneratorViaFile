############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project eventsGeneratorViaFile
set_top eventsGeneratorViaFile
add_files eventsGeneratorViaFile/src/main.cpp
open_solution "solution1"
set_part {xc7z045ffg900-1} -tool vivado
create_clock -period 10 -name default
#source "./eventsGeneratorViaFile/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -rtl verilog -format ip_catalog
