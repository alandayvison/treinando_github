////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0701time.cpp                                               //
// Title       : Simulation Time Resolution                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates time resolution                                 //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( top ) {
  SC_CTOR ( top ) {
    SC_THREAD ( top_thread ) ;
  }
  void top_thread ( ) {
    sc_time delay1 ( 10, SC_NS ) ;
    sc_time delay2 = sc_time ( 20.1, SC_NS ) ; // rounded
    sc_time delay3 = delay2 - delay1 ;
    wait ( delay3 ) ;
    cout << "simulation time is " << sc_time_stamp()      << endl ;
    wait(100, SC_NS);
  }
};

int sc_main ( int c, char** v ) {
  sc_set_time_resolution ( 1, SC_NS ) ;
  cout << "time resolution is " << sc_get_time_resolution() << endl;
  top top1 ( "top1" ) ;
  sc_start ( 30001, SC_PS ) ; // rounded
  cout << "simulation time is " << sc_time_stamp()      << endl ;
  return 0 ;
}

// time resolution is 1 ns
// simulation time is 10 ns
// simulation time is 30 ns