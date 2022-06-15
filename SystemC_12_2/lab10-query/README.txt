////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 10 - "Querying the Simulator"                       //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 10-1	Hierarchy Walker Application 

Objective:	Describe the SystemC design object hierarchy. 

Do this lab in the lab10-query directory. 

This directory provides the completed and unmodified PNET system of the previous lab. 

For this lab, you define the hierarchy walker application presented in the training materials. 

	Examine the New and Modified Files 
	==================================

	- pnet_walker.h 

The PNET hierarchy walker is a SystemC module. It implements a listChildObjects() method to describe the objects in a passed reference to a vector of SystemC objects. It implements its inherited start_of_simulation() callback to pass a vector of top-level SystemC objects to the listChildObjects() method. 

	- sc_main.cpp 

The sc_main() function is modified to instantiate the hierarchy walker. 

	Define and Test the Hierarchy Walker 
	====================================

1.	In a new pnet_walker.cpp file, define the hierarchy walker methods. Indent each object report two additional spaces for each additional level below the top-level objects. Optionally display vectors between parent and child objects. The first few lines of the display could look something like this: 

system : sc_module
|_system.node_0 : sc_module
| |_system.node_0.cpu : sc_module
| | |_system.node_0.cpu.p_cpu_write : sc_port
| | |_system.node_0.cpu.p_cpu_read : sc_port
| | |_system.node_0.cpu.cpu_write_proc : sc_thread_process
| | |_system.node_0.cpu.cpu_read_proc : sc_thread_process
| |_system.node_0.wrap : sc_module
|   |_system.node_0.wrap.cpu_write_trans : sc_module
|   | |_system.node_0.wrap.cpu_write_trans.p_cpu_tx_data_value : sc_out
|   | |_system.node_0.wrap.cpu_write_trans.p_cpu_tx_data_ready : sc_out
...

Note:	To assist with the parent-child vector display, the solution uses a vector of bool to track whether it has displayed the last element at each level. 

2.	Test your hierarchy walker, enter: 

xrun -f xrun_args.txt -sysc 
 	
DIFFERENCES FROM LAB 9
================================
xrun_args.txt    Author  modified starting with lab 9 source
pnet_walker.h    Author  created
pnet_walker.cpp *Student creates
sc_main.cpp      Author  modified starting with lab 9 source

LAB 10 SOURCES IDENTICAL TO LAB 9 SOURCES
=========================================
pnet_cpu.cpp
pnet_cpu.h
pnet_frame.cpp
pnet_frame.h
pnet_ifs.h
pnet_monitor.cpp
pnet_monitor.h
pnet_node.cpp
pnet_node.h
pnet_refined.cpp
pnet_refined.h
pnet_sync.h
pnet_sync_ifs.h
pnet_system.cpp
pnet_system.h
pnet_trans.cpp
pnet_trans.h
pnet_wrap.h
