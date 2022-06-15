////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0803semaphore.cpp                                          //
// Title       : Example Using an sc_semaphore Channel                        //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates use of an sc_semaphore channel                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( user1 ) {
  sc_port <sc_semaphore_if> semaphore_port ;
  void user_thread () {
    wait (10, SC_NS);
    (void) semaphore_port->wait();
    cout << "1 wait okay at " << sc_time_stamp() << endl;
    wait (40, SC_NS);
      if (semaphore_port->post()==0)
        cout << "1 post okay at " << sc_time_stamp() << endl;
      else
        cout << "1 post fail at " << sc_time_stamp() << endl;
  }
  SC_CTOR ( user1 )
  : semaphore_port ("semaphore_port")
  { SC_THREAD ( user_thread ) ; }
} ;

SC_MODULE ( user2 ) {
  sc_port <sc_semaphore_if> semaphore_port ;
  void user_thread () {
    do {
      wait (20, SC_NS);
      if (semaphore_port->post()==0)
        cout << "2 post okay at " << sc_time_stamp() << endl;
      else
        cout << "2 post fail at " << sc_time_stamp() << endl;
    }
    while (semaphore_port->trywait()!=0);
    cout << "2 trywait okay at " << sc_time_stamp() << endl;
    wait (40, SC_NS);
    if (semaphore_port->post()==0)
      cout << "2 post okay at " << sc_time_stamp() << endl;
    else
      cout << "2 post fail at " << sc_time_stamp() << endl;
    }
  SC_CTOR ( user2 )
  : semaphore_port ("semaphore_port")
  { SC_THREAD ( user_thread ) ; }
} ;

  
SC_MODULE ( semaphore_test ) {
  user1    user1_inst;
  user2    user2_inst;
  sc_semaphore  semaphore_inst;
  SC_CTOR ( semaphore_test ) :
    user1_inst("user1_inst"),
    user2_inst("user2_inst"),
    semaphore_inst("semaphore_inst", 1) 
  {
    user1_inst(semaphore_inst);
    user2_inst(semaphore_inst);
  }
} ;

int sc_main ( int argc, char **argv ) {
  semaphore_test semaphore_test_inst("semaphore_test_inst");
  sc_start ( ) ;
  return ( 0 ) ;
}

// 1 wait okay at 10 ns
// 2 post okay at 20 ns
// 2 trywait okay at 20 ns
// 1 post okay at 50 ns
// 2 post okay at 60 ns
