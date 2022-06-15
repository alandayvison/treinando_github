////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1104assert.cpp                                             //
// Title       : Making Assertions                                            //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates SC_REPORT_FATAL(id,msg)                         //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// SC_DEFAULT_FATAL_ACTIONS = (SC_LOG | SC_DISPLAY | SC_CACHE_REPORT | SC_ABORT)

#include "systemc.h"

SC_MODULE ( top ) {
  void thread() {
    sc_uint<32> uint1(1) ;
    sc_uint<32> uint2(2) ;
    sc_assert ( uint1 == uint2 ) ;
  }
  SC_CTOR ( top ) { SC_THREAD(thread); }

} ;

int sc_main (int argc, char**argv) {
  top top1("top1");
  sc_start();
  return 0;
}


// Fatal: (F4) assertion failed: uint1 == uint2
// In file: /<etc>/EX1104assert.cpp::6
// SystemC: simulation stopped by user.
