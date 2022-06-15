////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0703scheduler.cpp                                          //
// Title       : Example Notifying Events                                     //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates evaluation and update phases                    //
// Change Log  : 2019-11-14 mikep Added dont_initialize and p3, p4            //
//               2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
SC_MODULE ( top )
{
  sc_signal <bool> a,b,c,d;
  void p1 ( ) ;
  void p2 ( ) ;
  void p3 ( ) ;
  void p4 ( ) ;
  void tb ( ) ;
  SC_CTOR ( top )
  {
    SC_METHOD ( p1 ) ;
      sensitive << a << b ;
      dont_initialize();
    SC_METHOD ( p2 ) ;
      sensitive << b ;
      dont_initialize();
    SC_METHOD ( p3 ) ;
      sensitive << c ;
      dont_initialize();
    SC_METHOD ( p4 ) ;
      sensitive << d ;
      dont_initialize();
    SC_THREAD ( tb ) ;
  }
private:
  void print(const char*);
} ;

void top::print ( const char* m ) {
  cout
    << "At " << sc_time_stamp()
    << " : " << sc_delta_count()
    << " : " << m
    << " : " << a << b << c << d
    << endl ;
}

void top::p1() // (a b)
{
  print ( "p1" ) ;
  b = a ;
  c = b ;
}

void top::p2() // (b)
{
  print ( "p2" ) ;
  d = b ;
}

void top::p3() // (c)
{
  print ( "p3" ) ;
}

void top::p4() // (d)
{
  print ( "p4" ) ;
}

void top::tb()
{
  print ( "tb" ) ;
  a = 1 ;
}

int sc_main ( int c, char** v ) {
  top top1 ( "top1" ) ;
//sc_start ( 1001 ) ;
  sc_start (      ) ;
  return 0 ;
}

// At 0 s : 0 : tb : 0000
// At 0 s : 1 : p1 : 1000
// At 0 s : 2 : p2 : 1100
// At 0 s : 2 : p1 : 1100
// At 0 s : 3 : p4 : 1111
// At 0 s : 3 : p3 : 1111
