////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 9 - "Hierarchical Channels"                         //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 9-1	Channel Refinement 

Objective:	Refine a hierarchical channel. 

Do this lab in the lab09-hchan directory. 

This directory provides the completed (and partially modified) PNET system of the previous lab. 

For this lab, you replace the PNET channel’s interface methods with processes acting through ports upon external signal-level channels, thus converting the PNET channel’s transaction-level interface to a signal-level interface. 

	Examine the New and Modified PNET Source Files 
	==============================================

	- pnet_refined.h 

The refined PNET channel is a SystemC module with processes that act through ports upon external signal channels connected to transactors. To simplify the processes, they call helper functions to perform the transaction bus protocols. You will complete the refined channel definition. 

	- pnet_trans.h,cpp 

These files declare and define transactor channels that implement the cpu and network write and read interfaces to convert between transaction-level interfaces and signal-level-level interfaces. 

	- pnet_wrap.h,cpp 

These files declare and define a wrapper channel that implements the cpu and network write and read interfaces. The wrapper instantiates the refined PNET channel (with signal-level interfaces), a transactor for each of the cpu and network write and read interfaces, and signal channels between the transactors and the refined channel. The wrapper presents to the interfaces that the node expects, so can easily replace the previous unrefined PNET channel. 

	- pnet_cpu.cpp 

The PNET CPU is modified to greatly reduce the rate at which transactions are generated. Now that transactions consume simulation time, the PNET network ring topology has an inherent potential to become deadlocked. You can reduce the deadlock potential to zero by maintaining an impractically miniscule mean FIFO usage. You can reduce the deadlock potential to acceptable limits by maintaining a reasonable FIFO usage. The mean FIFO usage can increase with FIFO size. The pnet_sync channel is size one. A reasonable FIFO usage for a FIFO of size one is perhaps 50%, that is, the cpu should insert new frames at about half the mean rate that the system can clear them. 

	- pnet_node.h,cpp 

The PNET node is modified to instantiate the wrapper channel instead of the unrefined channel. 

	Modify, Test, and Debug the Refined PNET Channel 
	================================================

1.	Complete the pnet_refined.cpp file by defining the cpu and network read and write processes and their helper functions. 

Tip:	The four processes can be very similar to those of the PNET channel of lab 4, but replace read and write calls to ports with calls to the helper functions. Remember that the cpu is now expecting only data bytes and no address bytes. The helper function protocols can be very similar to those of the provided transactors. Be sure to use correct port names, i.e. the refined channel reads “tx” data and writes “rx” data. 

2.	Test your PNET refined channel modifications (and debug as needed), enter: 

xrun –f xrun_args.txt –sysc 

DIFFERENCES FROM LAB 8
======================
xrun_args.txt     Author  modified starting with lab 8 source
pnet_trans.h,cpp  Author  created
pnet_refined.h    Author  created
pnet_refined.cpp *Student modifies starting with author creation
pnet_wrap.h,cpp   Author  created
pnet_cpu.cpp      Author  modified starting with lab 8 source
pnet_node.h,cpp   Author  modified starting with lab 8 source

LAB 9 SOURCES IDENTICAL TO LAB 8 SOURCES
========================================
pnet_cpu.h
pnet_frame.cpp
pnet_frame.h
pnet_ifs.h
pnet_monitor.cpp
pnet_monitor.h
pnet_sync.h
pnet_sync_ifs.h
pnet_system.cpp
pnet_system.h
sc_main.cpp
