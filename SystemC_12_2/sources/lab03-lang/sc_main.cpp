////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : sc_main.cpp                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET SC main                                                 //
// Notes       : The PNET simulation consists of a PNET system and a PNET     //
//               monitor. After simulation it displays the monitor results.   //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Added sc_stop() call for SimVision.         //
//               2019-11-12 mikep Removed call to srand()                     //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_system.h"
#include "pnet_monitor.h"

extern unsigned SEED = 1 ;
extern unsigned NODES = 4 ;
extern unsigned VERBOSITY = 0 ;
extern unsigned TRANSACTIONS = 8 ;

int sc_main ( int argc, char **argv ) {
  pnet_system system ( "system" ) ;
  pnet_monitor monitor ;
  sc_start ( ) ;
  sc_stop ( ) ;
  monitor.summarize ( ) ;
  return 0 ;
}
