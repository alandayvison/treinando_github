////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0802mutex.cpp                                              //
// Title       : Example Using an sc_mutex Channel                            //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates use of an sc_mutex channel                      //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( user1 ) {
  sc_port <sc_mutex_if> mutex_port ;
  void user_thread () {
    wait (10, SC_NS);
    (void) mutex_port->lock();
    cout << "1 locked  okay at " << sc_time_stamp() << endl;
    wait (40, SC_NS);
      if (mutex_port->unlock()==0)
        cout << "1 unlock  okay at " << sc_time_stamp() << endl;
      else
        cout << "1 unlock  fail at " << sc_time_stamp() << endl;
  }
  SC_CTOR ( user1 )
  : mutex_port ("mutex_port")
  { SC_THREAD ( user_thread ) ; }
} ;

SC_MODULE ( user2 ) {
  sc_port <sc_mutex_if> mutex_port ;
  void user_thread () {
    do {
      wait (20, SC_NS);
      (void) mutex_port->unlock();
      if (mutex_port->unlock()==0)
        cout << "2 unlock  okay at " << sc_time_stamp() << endl;
      else
        cout << "2 unlock  fail at " << sc_time_stamp() << endl;
    }
    while (mutex_port->trylock()!=0);
    cout << "2 trylock okay at " << sc_time_stamp() << endl;
    wait (40, SC_NS);
    if (mutex_port->unlock()==0)
      cout << "2 unlock  okay at " << sc_time_stamp() << endl;
    else
      cout << "2 unlock  fail at " << sc_time_stamp() << endl;
    }
  SC_CTOR ( user2 )
  : mutex_port ("mutex_port")
  { SC_THREAD ( user_thread ) ; }
} ;


SC_MODULE ( mutex_test ) {
  user1    user1_inst;
  user2    user2_inst;
  sc_mutex mutex_inst;
  SC_CTOR ( mutex_test ) :
    user1_inst("user1_inst"),
    user2_inst("user2_inst"),
    mutex_inst("mutex_inst") 
  {
    user1_inst(mutex_inst);
    user2_inst(mutex_inst);
  }
} ;

int sc_main ( int argc, char **argv ) {
  mutex_test mutex_test_inst("mutex_test_inst");
  sc_start ( ) ;
  return ( 0 ) ;
}

// 1 locked  okay at 10 ns
// 2 unlock  fail at 20 ns
// 2 unlock  fail at 40 ns
// 1 unlock  okay at 50 ns
// 2 unlock  fail at 60 ns
// 2 trylock okay at 60 ns
// 2 unlock  okay at 100 ns
