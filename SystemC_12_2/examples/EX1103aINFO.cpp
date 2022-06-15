////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1103aINFO.cpp                                              //
// Title       : Reporting Messages                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates SC_REPORT_INFO(id,msg)                          //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// SC_DEFAULT_INFO_ACTIONS = (SC_LOG | SC_DISPLAY)

#include "systemc.h"

SC_MODULE ( top ) {
  void thread() {
    sc_report_handler::add_msg_type("My message type");
    SC_REPORT_INFO ( "My message type", "My info message 1" ) ;
    // off by severity
    sc_report_handler::set_actions ( SC_INFO, SC_DO_NOTHING ) ;
    SC_REPORT_INFO ( "My message type", "My info message 2" ) ;
    // on by message type
    sc_report_handler::set_actions("My message type",SC_DEFAULT_INFO_ACTIONS);
    SC_REPORT_INFO ( "My message type", "My info message 3" ) ;
    // off by message type
    sc_report_handler::set_actions("My message type",SC_DO_NOTHING);
    // on by message type & severity
    sc_report_handler::set_actions("My message type",SC_INFO,SC_DEFAULT_INFO_ACTIONS);
    SC_REPORT_INFO ( "My message type", "My info message 4" ) ;
    }
  SC_CTOR ( top ) { SC_THREAD(thread); }

} ;

int sc_main (int c, char **v) {
  top top1("top1");
  sc_start();
  return 0;
}

// Info: My message type: My info message 1

// Info: My message type: My info message 3

// Info: My message type: My info message 4
