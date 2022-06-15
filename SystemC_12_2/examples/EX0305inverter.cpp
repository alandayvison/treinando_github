////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0305inverter.cpp                                           //
// Title       : The Cadence SimVision C Debug Layout                         //
// Project     : SystemC Language Fundamentals                                //
// Description : Model for demonstrating C debug layout                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef INV_H
#define INV_H
#include "systemc.h"
SC_MODULE ( Inv ) {
  sc_in  <bool> p_in  ;
  sc_out <bool> p_out ;
  SC_CTOR ( Inv )
  :
    p_in  ( "p_in"  ) ,
    p_out ( "p_out" ) 
  {
    SC_METHOD ( inv_method ) ;
      sensitive << p_in ;
  }
  void inv_method() {
    p_out = ! p_in ;
  }
} ;
#endif

#ifndef INV_TEST_H
#define INV_TEST_H
#include "systemc.h"
//#include "Inv.h"
SC_MODULE ( InvTest ) {
  sc_signal <bool> s_in  ;
  sc_signal <bool> s_out ;
  Inv Inv_inst;
  SC_CTOR ( InvTest )
  :
    s_in      ( "s_in"     ) ,
    s_out     ( "s_out"    ) ,
    Inv_inst  ( "Inv_inst" ) 
  {
    Inv_inst.p_in  ( s_in  ) ;
    Inv_inst.p_out ( s_out ) ;
    SC_THREAD ( test_thread ) ;
  }
  void test_thread() {
    s_in = 0 ;
    wait ( 1, SC_NS ) ;
    s_in = 1 ;
    wait ( 1, SC_NS ) ;
    sc_stop() ;
  }
} ;
#endif

#include "systemc.h"
//#include "InvTest.h"
int sc_main ( int argc, char **argv ) {
  InvTest InvTest_inst ( "InvTest_inst" ) ;
  sc_start() ;
  return 0 ;
}