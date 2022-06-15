////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 7 - "SystemC Event Scheduler"                       //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 7-1	SystemC Event Scheduling 

Objective:	Examine simulation event scheduling. 

Do this lab in the lab07-schd directory. 

This directory provides the fifo_test.cpp file that instantiates and tests a SystemC FIFO. 

For this lab, you examine the behavior of a FIFO channel. 

	Examine the Test Case 
	=====================

	- fifo_test.cpp

The test instantiates a SystemC FIFO of size 2 and spawns write and read processes to write and read 3 elements. It spawns the processes twice, in different order, separated by 1 ns, to detect any process ordering issues. The writes and reads use blocking semantics. 

	Execute the Test Case 
	=====================

1.	Execute the FIFO test, enter: 

xrun fifo_test.cpp –sysc 

	Examine the Test Case Output 
	============================

1.	Examine the diagnostic output in the log file: 

Writing to a not full FIFO requires how many cycles? ___

Notifying the reader that data has been written requires how many cycles? ___

Reading from a not empty FIFO requires how many cycles? ___

Notifying the writer that data has been read requires how many cycles? ___
