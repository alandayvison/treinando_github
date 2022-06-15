////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011-2019 Cadence Design Systems, Inc. All Rights Reserved.  //
//                                                                            //
// File name   : README.txt                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET lab 2 - "SystemC Introduction"                          //
// Change Log  : 2019-11-04 <mikep> Updated for Xcelium 19.09                 //
//               2012-09-23 <mikep> Updated for Incisive 12.2                 //
//               2011-04-30 <mikep> Created.                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

Lab 2-1	The SystemC Installation 

Objective:	Examine and test the SystemC installation. 

Do this lab in the lab02-intro directory.

This directory is initially empty.

For this lab, you examine and test the SystemC installation, and optionally do the SystemC Simulation Tutorial. 

	Verify Your Environment Variables 
	=================================

The Cadence execution wrapper xrun sets most variables as needed. The user must set two environment variables. 

1.	Verify the values of two environment variables that the scripts cannot set: 

a.	Enter:	echo $CDS_LIC_FILE 

5280@licence-server 

b.	Enter:	echo $PATH 

Must include:	install­dir/tools/bin 

	Examine the Documentation Library 
	=================================

You use the Cadence Help documentation browser to view documentation. 

1.	Launch the Cadence Help facility; enter in a terminal window:  

cdnshelp& 

2.	Select to search Local Documents for “SystemC” and Filter to “Manuals”. 

3.	Locate and very briefly examine the following documents. 
	- SystemC Simulation User Guide
	- SystemC Simulation Reference
	- SystemC Simulation Tutorial
	- SystemC Advanced Debugging Tutorial
	- SystemC Simulation Quick Reference

	Examine the SystemC Examples 
	============================

The installation provides several SystemC examples. Most provided examples demonstrate proprietary extensions specific to Cadence SystemC simulation. You can download more vendor-independent examples from the OSCI web site. 

1.	Locate the example directory, enter:

ls `cds_root xrun`/tools/systemc/examples/ 

2.	Briefly examine the examples README file. 

	Execute a SystemC Example 
	=========================

1.	Copy the systemc_only example directory to the lab02-intro lab directory. 

2.	Run your local copy of the systemc_only example; enter: 

run_xrun

3.	Compare the “golden” results to your results; enter:  

diff xmsim.au xmsim.log 

You should see no differences. 

	Optionally do the SystemC Simulation Tutorial 
	=============================================

For this section, you do the SystemC Simulation Tutorial. The tutorial model is a drink machine design (that distributes drinks), and a testbench that controls and tests the drink machine. You follow the tutorial instructions to debug the design while experiencing the native debugging capabilities of the Cadence SimVision simulation analysis environment. 

1.	Locate and open the tutorial instructions (that you just now briefly examined). 

2.	Follow the tutorial instructions. 
