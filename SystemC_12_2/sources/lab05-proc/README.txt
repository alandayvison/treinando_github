////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 5 - "Processes and Events"                          //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 5-1	Method and Thread Processes 

Objective:	Convert thread processes to method processes. 

Do this lab in the lab5-proc directory. 

This directory provides the completed (and partially modified) PNET system of the previous lab. 

For this lab, you replace the PNET channel’s SC_THREAD processes with SC_METHOD processes to the extent practical, thus demonstrating your understanding how these process types differ. 

	Examine the Modified PNET Source Files 
	======================================

	- pnet_node.cpp 

The cpu FIFO size is increased from 1 to 4. Later discussion explains why. 

	Discussion Concerning PNET Channel Process Modifications
	========================================================

	- CPU Read Process 

You can make the cpu_read_process() an SC_METHOD process statically sensitive to the data_written() event finder of the “p_cpu_read” fifo input port (don’t initialize). Only some pre-specialized ports have event finders. A port needs event “finders” because at the point the process is made statically sensitive, the port might not yet be bound to a channel. Local process variables exist only during the process activation, and as an SC_METHOD process cannot block and thus cannot “step” its execution, it no longer can verify the address/data sequence, but instead must trust that data[7] accurately specifies whether an address or data byte. The process likewise cannot store the address locally, as it cannot then “wait” for the data. It must instead store the address in a class member variable. Question - why can we not resolve this by making the address variable “static”? Answer - because a static variable belongs to all instances of the class, and the PNET system has four nodes that would thus all “own” the variable. The SC_METHOD cpu_read_process() can safely continue to use a blocking read on the input fifo, as the process is triggered by a write to the input fifo, which ensures that data is available when the process activates. The process should now use non-blocking writes (nb_write()) to the local cpu fifo and net fifo, and wrap those writes within sc_assert(expression) macros to provide a more useful error indication if the write fails. You must increase the size of these local fifos from 1 to 2, as two processes write to them, and the cpu_read_process() process now cannot wait if another process has already filled a fifo. 
 
	- CPU Write Process 

You can with a bit more challenge make the cpu_write_process() an SC_METHOD process statically sensitive to the data_written_event() of the local cpu fifo (don’t initialize). You need to resolve issues with both the process input fifo and the process output fifo. The SC_METHOD cpu_write_process() can safely continue to use a blocking read on the input fifo, as the process is triggered by a write to the input fifo, which ensures that data is available when the process activates. The process should now use non-blocking writes to the output fifo, and wrap those writes within sc_assert() macros to provide a more useful error indication if the write fails. 

	-- The first issue is with the local cpu fifo. The cpu_read_process() and net_read_process() processes both write to the local cpu fifo. Both processes can write the fifo in the same evaluate phase, but the cpu_write_process() can be notified only once per evaluate phase, thus backing up transactions in the fifo. You can resolve this issue by looping the cpu_write_process() process while the cpu fifo num_available() method indicates that the fifo still has data available. 

	-- The second issue is with the output fifo located in the parent node. As the SC_METHOD cpu_write_process() process cannot consume time, it must write both the address and the data bytes to the output fifo without potentially waiting for a full fifo, thus the fifo size must be increased to 4 (already done) to accommodate the address and data from two frames. 

	- Net Read Process 

You can make the net_read_process() an SC_METHOD process statically sensitive to the data_written() event finder of the “p_net_read” fifo input port. The SC_METHOD net_read_process() can safely continue to use a blocking read on the input fifo, as the process is triggered by a write to the input fifo, which ensures that data is available when the process activates. The process should now use non-blocking writes to the local “cpu_fifo” and “net_fifo”, and wrap those writes within sc_assert() macros to provide a more useful error indication if the write fails. At this point, no other issues with fifos should exist. The input fifo is written by only one process (in the cpu unit) and the cpu fifo and net fifo that two processes write can now each accommodate two frames. 

	- Net Write Process 

The net_write_process() process has the two fifo-related issues similar to those you resolved for the cpu_write_process() process. However, the output fifo for the network interconnect is located at the system level. As you would learn little more by making this modification, let’s pretend that the project manager has declined to allow you to modify the system to increase the system network fifo size from 1 to 2. You can leave this process as a thread process. 

	Modify, Test, and Debug the PNET Channel 
	========================================

1.	Modify files pnet_chan.h and pnet_chan.cpp to replace the SC_THREAD processes with SC_METHOD processes to the extent practical. 

Tip:	Do this iteratively, one process at a time, and test each new process. 

2.	Test your PNET channel modifications (and debug as needed), enter: 

xrun –f xrun_args.txt –sysc 

DIFFERENCES FROM LAB 4
=================================
pnet_chan.h,cpp *Student modifies starting with lab 4 solutions
pnet_node.cpp    Author  modified starting with lab 4 sources

LAB 5 SOURCES IDENTICAL TO LAB 4 SOURCES
========================================
pnet_cpu.cpp
pnet_cpu.h
pnet_frame.h
pnet_monitor.cpp
pnet_monitor.h
pnet_node.h
pnet_system.cpp
pnet_system.h
sc_main.cpp
xrun_args.txt
