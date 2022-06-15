////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0503dynthread.cpp                                          //
// Title       : Example Dynamic Sensitivity: SC_THREAD                       //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates dynamic sensitivity with thread process         //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( algorithm ) {
  sc_in     <int> a,b,c,d;
  sc_out    <int> result;
  SC_CTOR ( algorithm ) {
    SC_THREAD ( addDiv ) ;
      sensitive << a << b << c << d ;
      dont_initialize();
    SC_THREAD ( multiply ) ;
      sensitive << do_mult ;
      dont_initialize();
  }
  void addDiv ( ) {
    while (true) {
      sum = a + b ;
      do_mult.notify(SC_ZERO_TIME);
      wait(mult.default_event());
      result = mult / d ;
      wait(); // static
    }
  }
  void multiply ( ) {
    while (true) {
      mult = sum * c ;
      wait(); // static
    }
  }
private:
  sc_signal <int> sum;
  sc_buffer <int> mult;
  sc_event do_mult ;
};

SC_MODULE ( test ) {
  sc_signal <int> a,b,c,d,result;
  algorithm algo;
  SC_CTOR ( test ) :
    algo("algo") {
    algo(a,b,c,d,result);
    SC_THREAD ( thread ) ;
  }
  void thread ( ) {
    wait(10,SC_NS);
    a=1;b=2;c=3;d=4;
    wait(10,SC_NS);
    cout<<"result="<<result<<endl; // result=2
    a=4;b=3;c=2;d=1;
    wait(10,SC_NS);
    cout<<"result="<<result<<endl; // result=14
  }
};

int sc_main ( int argc, char **argv ) {
  test top ( "top" ) ;
  sc_start ( ) ;
  return ( 0 ) ;
}
