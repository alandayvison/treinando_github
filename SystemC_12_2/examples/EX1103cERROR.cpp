////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1103cERROR.cpp                                             //
// Title       : Reporting Messages                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates SC_REPORT_ERROR(id,msg)                         //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// SC_DEFAULT_ERROR_ACTIONS = (SC_LOG | SC_CACHE_REPORT | SC_THROW)

#include "systemc.h"

SC_MODULE ( top ) {
  void thread() {
    sc_report_handler::add_msg_type("My message type");
    sc_report_handler::set_log_file_name("EX1103cERROR.log");
    try { SC_REPORT_ERROR("My message type","My error message"); }
    catch(const sc_report &report) {cout << "Caught: " << report.what() << endl;}
    sc_report *report_p = sc_report_handler::get_cached_report();
    cout << "msg_type  :\t" << report_p->get_msg_type () << endl;
    cout << "msg       :\t" << report_p->get_msg () << endl;
    cout << "severity  :\t" << report_p->get_severity() << endl;
    cout << "file      :\t" << report_p->get_file_name() << endl;
    cout << "line      :\t" << report_p->get_line_number() << endl;
    cout << "timestamp :\t" << report_p->get_time() << endl;
  }
  SC_CTOR ( top ) { SC_THREAD(thread); }

} ;

int sc_main (int argc, char**argv) {
  top top1("top1");
  sc_start();
  return 0;
}

// Caught: Error: My message type: My error message
// In file: /<etc>/EX1103cERROR.cpp:20
// In process: top1.thread @ 0 s
// msg_type  :     My message type
// msg       :     My error message
// severity  :     2
// file      :     /<etc>/EX1103cERROR.cpp
// line      :     20
// timestamp :     0 s
