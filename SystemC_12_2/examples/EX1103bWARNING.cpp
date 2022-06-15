////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1103bWARNING.cpp                                           //
// Title       : Reporting Messages                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates SC_REPORT_WARNING(id,msg)                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// SC_DEFAULT_WARNING_ACTIONS = (SC_LOG | SC_DISPLAY)

#include "systemc.h"

SC_MODULE ( top ) {
  void thread() {
    sc_report_handler::add_msg_type("My message type");
    SC_REPORT_WARNING("My message type","My error message");
  }
  SC_CTOR ( top ) { SC_THREAD(thread); }

} ;

int sc_main (int argc, char**argv) {
  top top1("top1");
  sc_start();
  return 0;
}

// Warning: My message type: My error message
// In file: /<etc>/EX1103bWARNING.cpp:20
// In process: top1.thread @ 0 s
