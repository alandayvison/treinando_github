////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0901channel.cpp                                            //
// Title       : Building Hierarchical Channels                               //
// Project     : SystemC Language Fundamentals                                //
// Description : ...                                    //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

// my_interface.h
#ifndef INTERFACE_H
#define INTERFACE_H

#include "systemc.h"

template <class T> class my_interface
: virtual public sc_interface
{
public :
  virtual void write ( const T& ) = 0 ;
  virtual const T& read ( ) const = 0 ;
  // other public interface methods
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

// my_channel.h
#ifndef CHANNEL_H
#define CHANNEL_H

#include "systemc.h"
// #include "my_interface.h"

template <class T> class my_channel
: public sc_channel
, public my_interface<T>
{
public :
  void write ( const T& ) ;
  const T& read ( ) const ;
  SC_CTOR ( my_channel ) { }
protected:
  T data ;
} ;

#endif


// my_channel.cpp
//#include "my_channel.h"

template <class T> void my_channel<T>::write ( const T& data )
{ this->data = data ; }

template <class T> const T& my_channel<T>::read ( ) const
{ return data ; }

////////////////////////////////////////////////////////////////////////////////

// producer.h
#ifndef PRODUCER_H
#define PRODUCER_H

#include "systemc.h"
// #include "interface.h"

template <class T> class producer
: public sc_module
{
public :
  sc_port<my_interface<T> > p_out ;
  void producer_thread() ;
  SC_CTOR ( producer ) : p_out("p_out")
  { SC_THREAD ( producer_thread ) ; }
} ;

#endif

#include "systemc.h"
// producer.cpp
//#include "producer.h"

template <class T> void producer<T>::producer_thread() {
  while ( true ) {
    wait(2,SC_NS);   // control timing
    T data = rand(); // generate data
    p_out->write ( data ) ;
  }
}

////////////////////////////////////////////////////////////////////////////////

// consumer.h
#ifndef CONSUMER_H
#define CONSUMER_H

#include "systemc.h"
// #include "interface.h"

template <class T> class consumer
: public sc_module
{
public :
  sc_port<my_interface<T> > p_in ;
  void consumer_thread() ;
  SC_CTOR ( consumer ) : p_in("p_in")
  { SC_THREAD ( consumer_thread ) ; }
} ;

#endif

#include "systemc.h"
// consumer.cpp
//#include "consumer.h"

template <class T> void consumer<T>::consumer_thread() {
  wait(1,SC_NS);
  while ( true ) {
    wait ( 2, SC_NS ) ;
    T data = p_in->read ( ) ;
    cout << "data=" << data << endl;
  }
}

////////////////////////////////////////////////////////////////////////////////

// testbench.h
#ifndef TESTBENCH_H
#define TESTBENCH_H

#include "systemc.h"
//#include "producer.h"
//#include "consumer.h"
//#include "my_channel.h"

#define WIDTH 8
#define TDATA sc_lv<WIDTH>

SC_MODULE ( testbench ) {
  producer   <TDATA> producer_inst ;
  consumer   <TDATA> consumer_inst ;
  my_channel <TDATA> channel_inst  ;
  void testbench_thread ( ) ;
  SC_CTOR ( testbench )
  : producer_inst ( "producer_inst" )
  , consumer_inst ( "consumer_inst" )
  , channel_inst  ( "channel_inst"  ) 
  {
    producer_inst.p_out ( channel_inst ) ;
    consumer_inst.p_in  ( channel_inst ) ;
    SC_THREAD ( testbench_thread ) ;
  }
} ;

#undef WIDTH
#undef TDATA

#endif

// testbench.cpp
#include "systemc.h"
//#include "testbench.h"

void testbench::testbench_thread ( ) { }

////////////////////////////////////////////////////////////////////////////////

// sc_main.cpp

#include "systemc.h"
//#include "testbench.h"

int sc_main ( int argc, char **argv ) {
  testbench testbench1 ( "testbench" ) ;
  sc_start ( 6, SC_NS ) ;
  return 0 ;
}