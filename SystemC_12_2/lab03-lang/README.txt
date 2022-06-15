////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 3 - "SystemC Language Basics"                       //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 3-1	SystemC Module Construction 

Objective:	Construct a SystemC module. 

Do this lab in the lab03-lang directory. 

This lab directory provides the PNET system described below. 

For this lab, you complete the pnet_chan.cpp file defining the PNET channel. 

	Preview the PNET System 
	=======================

	Examine the PNET Source Files 
	=============================

	- pnet_chan.h,cpp 

The PNET channel is a SystemC module with four ports for cpu and network read and write data, two internal FIFOs to collect cpu and network data, four processes to read and write cpu and network data, an address attribute, and encode and decode functions. The cpu read process reads address / data byte pairs through ports from an external FIFO, encodes them, and depending upon the address, writes them to either the local cpu data FIFO or the local network data FIFO. The cpu write process reads address / data byte pairs from the internal cpu FIFO, decodes them, and writes them through a port to the external cpu FIFO.  The counterpart network read and write processes act similarly, but of course do not encode or decode the bytes. 

	- pnet_cpu.h,cpp 

The PNET CPU is a SystemC module with two ports for cpu read and write data, two processes to write and read cpu data, and an address attribute. The CPU write process generates random address / data byte pairs, writes them through a port to an external FIFO, and inserts them into a monitor for later checking. The CPU read process reads address / data byte pairs through a port from an external FIFO, and erases them from the monitor. 

	- pnet_node.h,cpp 

The PNET node is a SystemC module with two ports for network read and write data, two local FIFOs for cpu read and write data, a cpu instance, and a channel instance. The node connects cpu instance ports and channel instance ports through the local FIFOs for cpu read and write data, and connects channel instance ports to node ports for network read and write data. 

	- pnet_system.h,cpp 

The PNET system is a SystemC module with a parameterizable number of node instances and FIFOs. The FIFOs communicate net data between the nodes. The system dynamically allocates nodes and FIFOs, and connects node network data write and read ports through the FIFOs. 

	- pnet_monitor.h,cpp 

The PNET monitor keeps a counter and a data multiset for each node. Its insert() method inserts a data value and increments the counter. Its erase() method erases a data value. Its summarize() method displays the number stored and the number erased and any remaining data values. 

	- sc_main.cpp

This file sets SEED, NODES, VERBOSITY, and TRANSACTIONS global constants. Its sc_main() function instantiates the PNET system and monitor, sets the random seed, and starts the simulation. 

	Complete the PNET Channel Description 
	=====================================

1.	Complete the PNET channel description. 

Modify the pnet_chan.cpp file to enter the network read and write methods. 

Tip:	These methods will be very similar to the cpu read and write methods. 

2.	Test your PNET channel description. 

a.	Compile and simulate, enter: 

xrun –f xrun_args.txt –sysc 

Correct as required until simulation succeeds with all transmitted data received. 

Note:	Set the VERBOSITY constant in sc_main.cpp to 2 to produce more verbose diagnostic messages. 

b.	More thoroughly test the PNET system. 

Set the TRANSACTIONS constant in sc_main.cpp to a larger number (1000) and again compile and simulate. This will more likely detect any clashes or deadlocks between the nodes. 
