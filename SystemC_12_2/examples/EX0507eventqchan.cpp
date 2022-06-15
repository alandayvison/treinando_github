////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0507eventqchan.cpp                                         //
// Title       : Example Queuing Events to Local Channel                      //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates local event queue channel                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE(my_module) {
  sc_event_queue my_event_q;
  SC_CTOR(my_module)
  :
    my_event_q ( "my_event_q" )
  {
    SC_THREAD(my_thread);
    SC_METHOD(my_method);
      sensitive << my_event_q;
      dont_initialize();
  }
  void my_thread() {
    my_event_q.notify(2,SC_NS);      // my_method runs at time 2 ns
    my_event_q.notify(4,SC_NS);      // my_method runs at time 4 ns
    my_event_q.cancel_all();         // cancel all notifications
    my_event_q.notify(SC_ZERO_TIME); // my_method runs at time 0 ns
    my_event_q.notify(1,SC_NS);      // my_method runs at time 1 ns
    my_event_q.notify(3,SC_NS);      // my_method runs at time 2 ns
  }
  void my_method() {
    cout << "In my_method at " << sc_time_stamp() << endl;
  }
};

int sc_main ( int argc, char **argv ) {
  my_module t1("t1");
  sc_start();
  return 0;
}

// In my_method at 0 s
// In my_method at 1 ns
// In my_method at 3 ns