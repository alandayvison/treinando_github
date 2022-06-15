////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 8 - "Building and Using Primitive Channels"         //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 8-1	Primitive Channels 

Objective:	Construct and use a primitive channel. 

Do this lab in the lab08-pchan directory. 

This directory provides the most recently completed (and partially modified) PNET system, a set of interfaces for a primitive channel that you will complete, and a test of that channel. 

For this lab, you create a primitive channel and use it in your PNET channel. 

	Examine the Interfaces 
	======================

	- pnet_sync_ifs.h

This file declares the pnet_sync_write_if and pnet_sync_read_if interfaces. The interfaces are deliberately similar to the SystemC FIFO interfaces. 

	Implement and Test the Interfaces 
	=================================

1.	Implement the interfaces. 

The pnet_sync class template located in the pnet_sync.h file is a SystemC primitive channel that inherits and implements the interfaces. To simplify the channel, it stores at most one element. Complete this class template by defining the update() method that the kernel calls during the update phase of the delta cycle to update the primitive channel. 

	- If a write is pending, the update() method must do something with the m_write_pending flag, the m_num_available variable, and the m_data_written_event event. It must also make the written value available for reading. 

	- If a read is pending, the update() method must do something with the m_read_pending flag, the m_num_free variable, and the m_data_read_event event. 

2.	Test your primitive channel description. 

a.	Compile and simulate, enter: 

xrun pnet_sync_test.cpp –sysc 

Correct as required until the test indicates completion with no error. 

	Modify, Test, and Debug the PNET Channel 
	========================================

1.	Modify files pnet_chan.h and pnet_chan.cpp to utilize your pnet_sync primitive channel instead of the SystemC FIFO for the cpu and network data FIFOs. 

2.	Test your PNET channel modifications (and debug as needed), enter: 

xrun –f xrun_args.txt –sysc 
 	
DIFFERENCES FROM LAB 6
===================================
pnet_sync_ifs.h     Author  created
pnet_sync.h        *Student modifies starting with author creation
pnet_sync_test.cpp  Author  created
pnet_chan.h,cpp    *Student modifies starting with lab 6 solutions

LAB 8 SOURCES IDENTICAL TO LAB 6 SOURCES
========================================
pnet_cpu.cpp
pnet_cpu.h
pnet_frame.cpp
pnet_frame.h
pnet_ifs.h
pnet_monitor.cpp
pnet_monitor.h
pnet_node.cpp
pnet_node.h
pnet_system.cpp
pnet_system.h
sc_main.cpp
xrun_args.txt
