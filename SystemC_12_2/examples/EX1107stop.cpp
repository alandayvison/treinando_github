////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1107stop.cpp                                               //
// Title       : Debugging C++ Code                                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates sc_stop_here()                                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
// Notes       : Run simulator inside gdb and enter commands from cmd file    //
//               Commands do not work for implementations that hide symbols   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

int sc_main (int argc, char**argv) {
  sc_report_handler::add_msg_type("My message type");
  sc_report_handler::set_actions("My message type",SC_DEFAULT_WARNING_ACTIONS | SC_STOP);
  SC_REPORT_WARNING("My message type", "My warning message");
  return 0;
}

