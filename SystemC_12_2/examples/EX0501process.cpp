////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0501process.cpp                                            //
// Title       : Statically Registering Processes                             //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates statically registering processes                //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( mux ) {
  sc_in  <bool> sel, ina, inb ;
  sc_out <bool> out ;
  SC_CTOR ( mux )
  {
    SC_METHOD ( mux_method ) ;
      sensitive<<sel<<ina<<inb;
  }
  void mux_method()
    { out = sel ? inb : ina ; }
} ;

SC_MODULE ( mux_test ) {
  sc_signal<bool> sel,ina,inb,out;
  mux mux_inst ;
  SC_CTOR ( mux_test ) :
    mux_inst ( "mux_inst" )
  {
    mux_inst(sel,ina,inb,out);
    SC_THREAD(test_thread);
  }
  void test_thread() {
    sel=0;ina=0;inb=1;
    wait ( 10, SC_NS ) ;
    cout << "out=" << out << endl; // 0
    sel=0;ina=1;inb=1;
    wait ( 10, SC_NS ) ;
    cout << "out=" << out << endl; // 1
    sel=1;ina=1;inb=1;
    wait ( 10, SC_NS ) ;
    cout << "out=" << out << endl; // 1
    sel=1;ina=1;inb=0;
    wait ( 10, SC_NS ) ;
    cout << "out=" << out << endl; // 0
  }
} ;

int sc_main ( int argc, char **argv ) {
  mux_test top ( "top" ) ;
  sc_start ( ) ;
  return ( 0 ) ;
}
