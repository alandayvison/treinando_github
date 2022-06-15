////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 4 - "Data Types and Operators"                      //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 4-1	User-Defined Data Structures 

Objective:	Define and use a data structure. 

Do this lab in the lab4-data directory. 

This directory provides the completed (and partially modified) PNET system of the previous lab and an additional test file for the data structure you will define. 

For this lab, you define and test a data structure representing the network high / low data bytes, and then modify the PNET channel to use this structure for all network communication between nodes. 

	Examine the New and Modified PNET Source Files 
	==============================================

	- pnet_frame.h 

The PNET frame is a structure of high / low data bytes that also defines the minimum operators and methods required of any user data type used with SystemC. You will later create the corresponding pnet_frame.cpp file. 

	- pnet_frame_test.cpp 

This is a separate test for just the PNET frame. 

	- pnet_node.h, pnet_system.h,cpp 

Modified to replace the network high / low data bytes with the PNET frame type. 

	Describe, Test, and Debug the PNET Frame Structure 
	==================================================

1.	Create the pnet_frame.cpp file defining the operators and methods declared in the provided  pnet_frame.h file. 

2.	Test just your PNET frame definition by itself (and debug as needed), enter: 

xrun pnet_frame.cpp pnet_frame_test.cpp –sysc 

	Modify, Test, and Debug the PNET Channel 
	========================================

1.	Modify files pnet_chan.h and pnet_chan.cpp to replace the network high / low data bytes with the PNET frame type. 

Tip:	Compare the previous lab’s pnet_node.h and pnet_system.h/cpp with the provided modified counterparts in this lab. 

2.	Test your PNET channel modifications (and debug as needed), enter: 

xrun –f xrun_args.txt –sysc 

DIFFERENCES FROM LAB 3
======================================
xrun_files.txt       Author  modified starting with lab 3 sources
pnet_frame.h         Author  modified starting with lab 3 sources
pnet_frame.cpp      *Student creates
pnet_frame_test.cpp  Author  created
pnet_chan.h         *Student modifies starting with modified Lab 3 source  
pnet_chan.cpp       *Student modifies starting with modified Lab 3 solution
pnet_node.h          Author  modified starting with lab 3 sources
pnet_system.h,cpp    Author  modified starting with lab 3 sources

LAB 4 SOURCES IDENTICAL TO LAB 3 SOURCES
========================================
pnet_cpu.cpp
pnet_cpu.h
pnet_monitor.cpp
pnet_monitor.h
pnet_node.cpp
sc_main.cpp

