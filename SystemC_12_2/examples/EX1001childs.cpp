////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1001childs.cpp                                             //
// Title       : Example Traversing the Design Hierarchy                      //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstration of listing child objects                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

#include "systemc.h"

struct interface : virtual sc_interface {
  virtual bool read ( ) = 0 ;
  virtual void write ( bool ) = 0 ;
  virtual const sc_event& default_event ( ) const = 0 ;
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
  virtual const sc_event& default_event ( ) const
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
#ifndef NONAMES
  : out_port ( "out_port" )
#endif
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
      // port interface must have: const sc_event& default_event() const
      sensitive << in_port ;
  }
  void consumer_thread ( ) {
    while (true) {
      wait ( ) ;
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
  void start_of_simulation ( ) {
    cout << "Listing the object named \"top_inst.channel_inst\"" << endl;
    listThisObject ( "top_inst.channel_inst" ) ;
    cout << "Listing the entire design hierarchy " << endl;
    listChildObjects ( sc_get_top_level_objects() ) ;
    cout << "Listing the hierarchy under current object " << name() << endl;
    listChildObjects ( get_child_objects() ) ;
  }
protected :

  void listThisObject ( const char *name ) {
    const sc_object *object_pointer = sc_find_object(name) ;
    if (object_pointer != 0)
      cout << object_pointer->name() << " : "
           << object_pointer->kind() << endl ;
  }

  typedef std::vector<sc_object*> vector_t;
  void listChildObjects (const vector_t& childList ) {
    vector_t::const_iterator object_iterator = childList.begin() ;
    while ( object_iterator != childList.end() ) {
      sc_object *child_pointer = *object_iterator ;
      cout << child_pointer->name() << " : "
           << child_pointer->kind() << endl ;
    //if ( strcmp(child_pointer->kind(),"sc_module") == 0 )
        listChildObjects ( (            child_pointer)->get_child_objects() ) ;
      ++object_iterator ;
    }
  }

} ;


int sc_main ( int argc, char **argv ) {
  top top_inst ( "top_inst" ) ;
  sc_start ( ) ;
  return 0 ;
}


// Listing the object named "top_inst.channel_inst"
// top_inst.channel_inst : sc_module
// Listing the entire design hierarchy 
// top_inst : sc_module
// top_inst.producer_inst : sc_module
// top_inst.producer_inst.out_port : sc_port
// top_inst.producer_inst.producer_thread : sc_thread_process
// top_inst.channel_inst : sc_module
// top_inst.channel_inst.bool_sig : sc_signal
// top_inst.consumer_inst : sc_module
// top_inst.consumer_inst.in_port : sc_port
// top_inst.consumer_inst.consumer_thread : sc_thread_process
// Listing the hierarchy under current object top_inst
// top_inst.producer_inst : sc_module
// top_inst.producer_inst.out_port : sc_port
// top_inst.producer_inst.producer_thread : sc_thread_process
// top_inst.channel_inst : sc_module
// top_inst.channel_inst.bool_sig : sc_signal
// top_inst.consumer_inst : sc_module
// top_inst.consumer_inst.in_port : sc_port
// top_inst.consumer_inst.consumer_thread : sc_thread_process