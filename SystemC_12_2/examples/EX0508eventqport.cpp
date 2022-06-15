////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0508eventqport.cpp                                         //
// Title       : Example Queuing Events Through a Port                        //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates external event queue channel                    //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE(mod) {
  sc_port <sc_event_queue_if> p;
  SC_CTOR(mod)
  {
    SC_THREAD(m_thread);
  //SC_METHOD(m_method);
  //  sensitive << p->default_event(); // not yet bound and no
  //  dont_initialize();               // event finder exists
    SC_THREAD(r_thread);
  }
  void m_thread() {
    p->notify(2,SC_NS);      // my_method runs at time 2 ns
    p->notify(4,SC_NS);      // my_method runs at time 4 ns
    p->cancel_all();         // cancel all notifications
    p->notify(SC_ZERO_TIME); // my_method runs at time 0 ns
    p->notify(1,SC_NS);      // my_method runs at time 1 ns
    p->notify(3,SC_NS);      // my_method runs at time 2 ns
  }
//void m_method() {
//  cout << "Notified at " << sc_time_stamp() << endl;
//}
  void r_thread() {
    while (true) {
      wait(p->default_event());
      cout << "Notified at " << sc_time_stamp() << endl;
    }
  }
};

SC_MODULE(top) {
  mod m;
  sc_event_queue q;
  SC_CTOR(top):m("m"),q("q") {
    m.p(q);
  }
};

int sc_main ( int argc, char **argv ) {
  top top1("top1");
  sc_start();
  return 0;
}

// Notified at 0 s
// Notified at 1 ns
// Notified at 3 ns
