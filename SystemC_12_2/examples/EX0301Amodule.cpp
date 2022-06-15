////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0301Amodule.cpp                                            //
// Title       : Assembling a SystemC Module                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate module assembly using instances                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PRODUCER_H
#define PRODUCER_H
#include "systemc.h"
SC_MODULE ( producer )
{
  sc_in  <bool> full ;
  sc_out <bool> wrt  ;
  void produce() {
    // ...
  }
  SC_CTOR ( producer )
  : full ( "full" )
  , wrt  ( "wrt"  )  
  {
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
  sc_out <bool> full ;
  sc_in  <bool> wrt  ;
  SC_CTOR ( consumer )
  :
    full ( "full" ) ,
    wrt  ( "wrt"  )  
  {
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
  sc_signal<bool> f, w ;
  producer p ;
  consumer c ;
  // Constructor
  SC_CTOR ( top )
  : f ( "f" )
  , w ( "w" )
  , p ( "p" )
  , c ( "c" )
  {
    p.full ( f ) ;
    p.wrt  ( w ) ;
    c.full ( f ) ;
    c.wrt  ( w ) ;
  }
  // Destructor
} ;
#endif

#include "systemc.h"
//#include "top.h"
int sc_main ( int argc, char **argv ) {
  top top_inst ( "top_inst" ) ;
  sc_start() ;
  return 0 ;
}
