////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0502sensitive.cpp                                          //
// Title       : Example Statically Setting Sensitivity                       //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates statically setting sensitivity                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( dut ) {
  sc_event           e1, e2 ;
  sc_fifo_in  <bool> fi ;
  sc_fifo_out <bool> fo ;
  sc_in       <bool> i1, i2 ;
  sc_signal   <bool> s1, s2 ;
  SC_CTOR ( dut )
  :
    fi("fi"),fo("fo"),
    i1("i1"),i2("i2"),
    s1("s1"),s2("s2") 
  {
    SC_METHOD ( method ) ;
      sensitive << e1 << i1 << s1  << fi.data_written() ;
    SC_THREAD ( thread ) ;
      sensitive   (e2)  (i2)  (s2)   (fo.data_read())   ;
  }
  void method ( ) {
    cout << sc_time_stamp() << " : method triggered" << endl;
  }
  void thread ( ) {
    while ( true ) {
      cout << sc_time_stamp() << " : thread triggered" << endl;
      wait ( ) ;
    }
  }
} ;

SC_MODULE ( test ) {
  sc_signal <bool> s1, s2 ;
  sc_fifo   <bool> f1 ;
  dut              sub ;
  SC_CTOR ( test )
  :
    s1("s1"),s2("s2"),
    f1("f1",1),sub("sub") 
  {
    sub(f1,f1,s1,s2);
    SC_THREAD ( thread ) ;
  }
  void thread ( ) {
    wait ( 10, SC_NS ); sub.e1.notify() ; // 10 : method triggered (event)
    wait ( 10, SC_NS ); sub.s1.write(1) ; // 20 : method triggered (channel)
    wait ( 10, SC_NS ); s1.write(1) ;     // 30 : method triggered (signal port)
    wait ( 10, SC_NS ); f1.write(1) ;     // 40 : method triggered (fifo write)

    wait ( 10, SC_NS ); sub.e2.notify() ; // 50 : thread triggered (event)
    wait ( 10, SC_NS ); sub.s2.write(1) ; // 60 : thread triggered (channel)
    wait ( 10, SC_NS ); s2.write(1) ;     // 70 : thread triggered (signal port)
    wait ( 10, SC_NS ); f1.read() ;       // 80 : thread triggered (fifo read)

    wait ( 10, SC_NS );
  }
} ;

int sc_main ( int argc, char **argv ) {
  test top ( "top" ) ;
  sc_start ( ) ;
  return ( 0 ) ;
}
