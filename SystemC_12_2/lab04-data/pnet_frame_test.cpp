////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_frame_test.cpp                                          //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET transaction frame test                                  //
// Notes       : View the waveform display using binary radix.                //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_frame.h"

SC_MODULE ( pnet_frame_test ) {
  pnet_frame frame1, frame2 ;
  SC_CTOR ( pnet_frame_test )
  { SC_THREAD ( test_thread ) ; }
  void test_thread ( ) {
    frame1.high = "01ZX01ZX" ;
    frame1.low  = "XZ10XZ10" ;
    frame2 = frame1 ;
    cout << "frame1 = " << frame1 << " frame2 = " << frame2 << endl ;
    sc_assert ( frame2 == frame1 ) ;
    wait ( 10, SC_NS ) ;
    frame1.high = 0xBE ;
    frame1.low  = 0xAD ;
    frame2.high = 0xFE ;
    frame2.low  = 0xED ;
    cout << "frame1 = " << frame1 << " frame2 = " << frame2 << endl ;
    wait ( 10, SC_NS ) ;
  }
} ;

int sc_main ( int argc, char **argv ) {
  pnet_frame_test test ( "test" ) ;
  sc_trace_file * tf = sc_create_vcd_trace_file ( "pnet_frame_test" ) ;
  sc_trace ( tf, test.frame1, std::string("frame1") ) ;
  sc_trace ( tf, test.frame2, std::string("frame2") ) ;
  sc_start ( ) ;
  sc_close_vcd_trace_file ( tf ) ;
  cout << "Now view the waveform file \"pnet_frame_test.vcd\"." << endl ;
  return 0 ;
}
