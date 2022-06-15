////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0506spawn.cpp                                              //
// Title       : Example Dynamically Spawning Processes                       //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates dynamically spawning processes                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include "systemc.h"

SC_MODULE(test) {
  int r; sc_event e1, e2;
  int spawned_thread(sc_event& e_rcv, sc_event& e_xmt) {
    wait(e_rcv);
    cout << sc_get_current_process_handle().name() << " rcv event at " << sc_time_stamp() << " with r = " << r << endl;
    e_xmt.notify(10, SC_NS);
    return r+1;
  }
  void test_thread() {
    sc_spawn_options opt;
      opt.set_stack_size(0x10000); // 64K
    r=0; e1.notify(10, SC_NS);
    SC_FORK
      sc_spawn(&r,
        sc_bind(&test::spawned_thread,this,sc_ref(e1),sc_ref(e2)),
        "process1", &opt), // Comma-separated list
      sc_spawn(&r,
        sc_bind(&test::spawned_thread,this,sc_ref(e2),sc_ref(e1)),
        "process2", &opt)  // No comma at end
    SC_JOIN
    cout << sc_get_current_process_handle().name() << " join at " << sc_time_stamp
() << " with r = " << r << endl;
  }
  SC_CTOR(test) {
    SC_THREAD(test_thread);
  }
};

  int sc_main ( int argc, char **argv )
  {
    test t1("t1");
    sc_start(50, SC_NS);
    return 0;
  }

// t1.test_thread.process1 rcv event at 10 ns with r = 0
// t1.test_thread.process2 rcv event at 20 ns with r = 1
// t1.test_thread join at 20 ns with r = 2
