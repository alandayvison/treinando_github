////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1103dFATAL.cpp                                             //
// Title       : Reporting Messages                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates SC_REPORT_FATAL(id,msg)                         //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// SC_DEFAULT_FATAL_ACTIONS = (SC_LOG | SC_DISPLAY | SC_CACHE_REPORT | SC_ABORT)

#include "systemc.h"

SC_MODULE ( top ) {
  void thread() {
    sc_report_handler::add_msg_type("My message type");
    sc_report_handler::set_log_file_name("fatal.log");
    SC_REPORT_FATAL("My message type","My fatal message");
  }
  SC_CTOR ( top ) { SC_THREAD(thread); }

} ;

int sc_main (int argc, char**argv) {
  top top1("top1");
  sc_start();
  return 0;
}

// Fatal: My message type: My fatal message
// In file: /<etc>/EX1103dFATAL.cpp:21
// In process: top1.thread @ 0 s

