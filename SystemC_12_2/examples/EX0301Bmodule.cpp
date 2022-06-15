////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0301Bmodule.cpp                                            //
// Title       : Assembling a SystemC Module                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate module assembly using pointers                   //
// Change Log  : 2019-11-14 mikep Added implicit binding examples             //
//               2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PRODUCER_H
#define PRODUCER_H
#include "systemc.h"
SC_MODULE ( producer )
{
  sc_in  <bool> *full ;
  sc_out <bool> *wrt  ;
  void produce() {
    // ...
  }
  SC_CTOR ( producer )
  {
    full = new sc_in  <bool> ( "full" ) ;
    wrt  = new sc_out <bool> ( "wrt"  ) ;
    SC_THREAD ( produce ) ;
    // sensitive << ...
    // dont_initialize() ;
  }
} ;
#endif

#ifndef CONSUMER_H
#define CONSUMER_H
#include "systemc.h"
SC_MODULE ( consumer )
{
  sc_out <bool> *full ;
  sc_in  <bool> *wrt  ;
  SC_CTOR ( consumer )
  {
    full = new sc_out <bool> ( "full" ) ;
    wrt  = new sc_in  <bool> ( "wrt"  ) ;
  }
} ;
#endif

#ifndef TOP_H
#define TOP_H
// Include files
#include "systemc.h"
//#include "producer.h"
//#include "consumer.h"
SC_MODULE ( top ) {
  // Declarations
  sc_signal<bool> *f, *w ;
  producer *p ;
  consumer *c ;
  // Constructor
  SC_CTOR ( top )
  {
    f = new sc_signal<bool> ( "f" ) ;
    w = new sc_signal<bool> ( "w" ) ;
    p = new producer ( "p" ) ;
    c = new consumer ( "c" ) ;
    (*p)            ( *f ) ; // implicitly bind 1st port
    (*p->wrt)       ( *w ) ; // explicitly bind 2nd port
//  c ->            ( *f ) ; // Cannot have adjacent binary operators
    c -> operator() ( *f ) ; // implicitly bind 1st port
    (*c->wrt)       ( *w ) ; // explicitly bind 2nd port
  }
  // Destructor
} ;
#endif

#include "systemc.h"
//#include "top.h"
int sc_main ( int argc, char **argv ) {
  top *top_ptr ;
  top_ptr = new top ( "top_inst" ) ;
  sc_start() ;
  return 0 ;
}
