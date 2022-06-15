////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1105exception.cpp                                          //
// Title       : Example Reporting Exceptions                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates catching exception report                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
int sc_main(int argc, char **argv){

  const char *msg_type_p = "My message type";
  const char *msg_add_p  = "My add message";

  sc_msg_def *msg_def_p = sc_report_handler::add_msg_type(msg_type_p);
  sc_actions actions = sc_report_handler::set_actions(msg_type_p,SC_INFO,SC_THROW|SC_LOG|SC_DISPLAY|SC_CACHE_REPORT); 
  bool success = sc_report_handler::set_log_file_name("EX1105exception.log");
  try {
    sc_report_handler::report(SC_INFO,msg_type_p,msg_add_p,__FILE__,__LINE__);
  }
  catch (const sc_report &report_obj) {
    cout << "Caught: " << report_obj.what() << endl;
  }
  sc_report *report_p = sc_report_handler::get_cached_report();
  cout << "msg_type  :\t" << report_p->get_msg_type () << endl;
  cout << "msg       :\t" << report_p->get_msg () << endl;
  cout << "severity  :\t" << report_p->get_severity() << endl;
  cout << "file      :\t" << report_p->get_file_name() << endl;
  cout << "line      :\t" << report_p->get_line_number() << endl;
  cout << "timestamp :\t" << report_p->get_time() << endl;
  cout << "name      :\t" << (report_p->get_process_name()?report_p->get_process_name():"null") << endl;
  cout << "id        :\t" << report_p->get_id() << endl;

  return 0;
}


// Info: My message type: My add message
// Caught: Info: My message type: My add message
// msg_type  :     My message type
// msg       :     My add message
// severity  :     0
// file      :     /<etc>/EX1105exception.cpp
// line      :     23
// timestamp :     0 s
// name      :     null
// id        :     -1
