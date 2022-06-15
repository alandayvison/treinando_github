////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1002proc.cpp                                               //
// Title       : Getting Process Information                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstration of getting process information                 //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

#include "systemc.h"

struct interface : virtual sc_interface {
  virtual bool read ( ) = 0 ;
  virtual void write ( bool ) = 0 ;
  virtual const sc_event& default_event ( ) = 0 ;
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef CHANNEL_H
#define CHANNEL_H

#include "systemc.h"
//#include "interface.h"

struct channel : sc_module, interface {
  sc_signal <bool> bool_sig ;
  SC_CTOR ( channel )
#ifndef NONAMES
  : bool_sig ( "bool_sig" )
#endif
    { }
  virtual void write ( bool data )
    { bool_sig.write ( data ) ; }
  virtual bool read ( )
    { return bool_sig.read() ; }
  virtual const sc_event& default_event ( )
    { return bool_sig.default_event() ; }
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef PRODUCER_H
#define PRODUCER_H

#include "systemc.h"
//#include "interface.h"

SC_MODULE ( producer ) {
  sc_port <interface> out_port ;
  SC_CTOR ( producer )
  : out_port ( "out_port" )
  {
    SC_THREAD ( producer_thread ) ;
  }
  void producer_thread ( ) {
    out_port->write(true) ;
    wait ( 1, SC_NS ) ;
    out_port->write(false) ;
    wait ( 1, SC_NS ) ;
  }
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef CONSUMER_H
#define CONSUMER_H

#include "systemc.h"
//#include "interface.h"

SC_MODULE ( consumer ) {
  sc_port <interface> in_port ;
  SC_CTOR ( consumer ) :
    in_port ( "in_port" )
  {
    SC_THREAD ( consumer_thread ) ;
  }
  void consumer_thread ( ) {
    sc_process_handle handle = sc_get_current_process_handle();
    cout << "name = " << handle.name()      << endl;
    cout << "kind = " << handle.proc_kind() << endl;
    while (true) {
      wait ( in_port->default_event() ) ;
      cout
        << "in_port is " << in_port->read()
        << " @ " << sc_time_stamp()
        << endl ;
    }
  }
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

//#include "producer.h"
//#include "channel.h"
//#include "consumer.h"

SC_MODULE ( top ) {
  producer producer_inst ;
  channel  channel_inst  ;
  consumer consumer_inst ;
  SC_CTOR ( top ) :
    producer_inst ( "producer_inst" ) ,
    channel_inst  ( "channel_inst"  ) ,
    consumer_inst ( "consumer_inst" )  
  {
    producer_inst ( channel_inst ) ;
    consumer_inst ( channel_inst ) ;
  }
} ;

int sc_main ( int argc, char **argv ) {
  top top_inst ( "top_inst" ) ;
  sc_start ( ) ;
  return 0 ;
}


// name = top_inst.consumer_inst.consumer_thread
// kind = 2
