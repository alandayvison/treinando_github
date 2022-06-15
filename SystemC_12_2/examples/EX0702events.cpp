////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0702events.cpp                                             //
// Title       : Example Notifying Events                                     //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates event notification                              //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( top ) {
  void immediate_method   ( ) ;
  void delta_delay_method ( ) ;
  void time_delay_method  ( ) ;
  void testbench_thread   ( ) ;
  SC_CTOR ( top ) {
    SC_METHOD ( immediate_method   ) ;
      sensitive << immediate_event   ;
      dont_initialize ( ) ;
    SC_METHOD ( delta_delay_method ) ;
      sensitive << delta_delay_event ;
      dont_initialize ( ) ;
    SC_METHOD ( time_delay_method  ) ;
      sensitive << time_delay_event  ;
      dont_initialize ( ) ;
    SC_THREAD ( testbench_thread   ) ;
  }
private:
  sc_event immediate_event   ;
  sc_event delta_delay_event ;
  sc_event time_delay_event  ;
  void print ( const char* ) ;
} ;

void top::print ( const char* m ) {
  cout
//  << "At " << sc_simulation_time() // deprecated 2.1
    << "At " << sc_time_stamp()
//  << " : " << simcontext()->delta_count() // deprecated 2.1
    << " : " << sc_delta_count()
    << m << endl ;
}


void top::immediate_method   ( )
  {print(" Entered immediate_method"  );}
void top::delta_delay_method ( )
  {print(" Entered delta_delay_method");}
void top::time_delay_method  ( )
  {print(" Entered time_delay_method" );}

void top::testbench_thread ( )
{
  print(" Entered testbench_thread" ) ;
  immediate_event.notify ( ) ;
  delta_delay_event.notify (0, SC_NS ) ;
  time_delay_event.notify ( 1, SC_NS ) ;
//for ( unsigned t=0;t<=1;++t ) {
//  for ( unsigned d=1;d<=2;++d ) {
//    print ( "" ) ;
//    wait ( 0, SC_NS ) ;
//  }
//  wait ( 1, SC_NS ) ;
//}
}

int sc_main ( int c, char** v ) {
  top top1 ( "top1" ) ;
  sc_start ( ) ;
  return 0 ;
}

// At 0 s : 1 Entered testbench_thread
// At 0 s : 1 Entered immediate_method
// At 0 s : 2 Entered delta_delay_method
// At 1 ns : 4 Entered time_delay_method
