////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0804clock.cpp                                              //
// Title       : Choosing the Clock Constructor                               //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates use of an sc_clock channel                      //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( top ) {
  sc_in <bool> clk1 ;
  sc_in <bool> clk2 ;
  sc_in <bool> clk3 ;
  sc_in <bool> clk4 ;
  sc_in <bool> clk5 ;

  SC_CTOR ( top )
  :
    clk1 ( "clk1" ) ,
    clk2 ( "clk2" ) ,
    clk3 ( "clk3" ) ,
    clk4 ( "clk4" ) ,
    clk5 ( "clk5" )
  {
    SC_THREAD ( monitor_clk1 ) ;
    SC_THREAD ( monitor_clk2 ) ;
    SC_THREAD ( monitor_clk3 ) ;
    SC_THREAD ( monitor_clk4 ) ;
    SC_THREAD ( monitor_clk5 ) ;
  }

  void monitor_clk1 ( ) {
    for (unsigned i=4; i!=0; --i) {
      wait ( clk1.default_event() ) ;
      cout << "  clk1 = " << clk1 << "  time = " << sc_time_stamp() << endl ;
    }
  }

  void monitor_clk2 ( ) {
    for (unsigned i=4; i!=0; --i) {
      wait ( clk2.default_event() ) ;
      cout << "  clk2 = " << clk2 << "  time = " << sc_time_stamp() << endl ;
    }
  }

  void monitor_clk3 ( ) {
    for (unsigned i=4; i!=0; --i) {
      wait ( clk3.default_event() ) ;
      cout << "  clk3 = " << clk3 << "  time = " << sc_time_stamp() << endl ;
    }
  }

  void monitor_clk4 ( ) {
    for (unsigned i=4; i!=0; --i) {
      wait ( clk4.default_event() ) ;
      cout << "  clk4 = " << clk4 << "  time = " << sc_time_stamp() << endl ;
    }
  }

  void monitor_clk5 ( ) {
    for (unsigned i=4; i!=0; --i) {
      wait ( clk5.default_event() ) ;
      cout << "  clk5 = " << clk5 << "  time = " << sc_time_stamp() << endl ;
    }
  }

} ;

int sc_main ( int argc, char **argv ) {
  sc_set_default_time_unit ( 1, SC_US ) ;
  sc_clock clk1 ( "clk1" ) ;
  sc_clock clk2 ( "clk2", 2.0, 0.7, 1.0, false ) ;
  sc_clock clk3 ( "clk3", 2.0, SC_NS, 0.7 ) ;
  sc_clock clk4 ( "clk4", 2.0, SC_NS, 0.7, 1.0, SC_NS, false ) ;
  sc_time period ( 2, SC_NS ) ;
  sc_time start  ( 1, SC_NS ) ;
  sc_clock clk5 ( "clk5", period, 0.7, start, false ) ;
  top top_inst ( "top_inst" ) ;
  top_inst ( clk1, clk2, clk3, clk4, clk5 ) ;
  sc_start ( 5, SC_US ) ;
  return 0 ;
}

