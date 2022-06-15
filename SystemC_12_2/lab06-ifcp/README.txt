////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011_2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 6 - "Interfaces, Channels, and Ports"               //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2012-09-23 <mikep> Changed PNET node from channel to module. //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 6-1	Hierarchical Channels 

Objective:	Convert a module to a channel. 

Do this lab in the lab6-ifcp directory. 

This directory provides the completed (and partially modified) PNET system of the previous lab. 

For this lab, you replace the PNET channel’s processes and ports with interface methods, thus converting the PNET channel to a true SystemC channel. 

	Examine the New and Modified PNET Source Files 
	==============================================

	- pnet_ifs.h 

This file declares the cpu and network write and read interfaces. 

	- pnet_cpu.h,cpp 

The PNET CPU is modified to replace the input and output ports with generic SystemC ports specialized for the cpu write and read interfaces. To access the interface methods implemented in the channel, the generic port utilizes the pointer operator. The cpu read process now assumes that only data meant for it is provided to it, so no longer reads the address to verify it. 

	- pnet_node.h,cpp 

The PNET node is modified to remove the internal cpu FIFOs and instead connect the CPU ports directly to the PNET channel. It also replaces its own network fifo input and output ports with SystemC ports it connects to the channel and through which the system accesses the network write and read methods implemented by the channel. 

	- pnet_system.h,cpp 

The PNET system is modified to replace the FIFO-based node interconnect with a process between each node pair that endlessly reads a frame from the previous node and writes it to the next node. 

	Modify, Test, and Debug the PNET Channel 
	========================================

1.	Modify files pnet_chan.h and pnet_chan.cpp to convert the module to a channel, inherit the cpu and network write and read interfaces, remove the ports, and replace the cpu and network read and write processes with the cpu and network write and read interface methods. 

Tip:	The algorithms will not significantly change, but instead of, for example, an internal process to read cpu data through a port from an external fifo, the algorithm is a method called by an external process to write cpu data. Remember that the cpu read method now returns to the cpu only the data byte and not the address byte. 

2.	Test your PNET channel modifications (and debug as needed), enter: 

xrun –f xrun_args.txt –sysc 

DIFFERENCES FROM LAB 5
======================
pnet_ifs.h         Author  created
pnet_chan.h,cpp   *Student modifies starting with lab 5 solutions
pnet_cpu.h,cpp     Author  modified starting with lab 5 sources
pnet_node.h,cpp    Author  modified starting with lab 5 sources
pnet_system.h,cpp  Author  modified starting with lab 5 sources

LAB 6 SOURCES IDENTICAL TO LAB 5 SOURCES
========================================
pnet_frame.cpp
pnet_frame.h
pnet_monitor.cpp
pnet_monitor.h
sc_main.cpp
xrun_args.txt
