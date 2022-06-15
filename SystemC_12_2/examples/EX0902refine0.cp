////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0902refine0.cpp                                            //
// Title       : Refining Hierarchical Channels                               //
// Project     : SystemC Language Fundamentals                                //
// Description : Initial unrefined channel                                    //
// Notes       : producer calls channel's interface method to write           //
//               consumer calls channel's interface method to read            //
//               channel acts directly upon embedded data array               //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef RAND_H
#define RAND_H

// For this algorithm "poly" is the reverse of the polynomial
// For 8 bits 0x163 is primitive polynomial so use 0xC6
// This (should) give us 255 unique numbers before recycling

  unsigned rand ( unsigned seed, unsigned poly )
  {
    if ( seed & 1 )
      return seed >> 1 ;
    else
      return seed >> 1 ^ poly ;
  }

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

#include "systemc.h"

template <class T> class interface
:
  virtual public sc_interface
{

public :

  virtual void clear ( ) = 0 ;
  virtual void read ( T& ) = 0 ;
  virtual void write ( const T& ) = 0 ;

} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef CHANNEL_H
#define CHANNEL_H

#include "systemc.h"
//#include "interface.h"

template <class TDATA, unsigned DEPTH> class channel
:
  public sc_channel ,
  public interface <TDATA>
{

public :

  SC_CTOR ( channel )
  {
    fifo = new TDATA[DEPTH] ;
    full       = false ;
    empty      = true  ;
    read_addr  = 0     ;
    write_addr = 0     ;
  }

  virtual ~channel ( ) { delete [] fifo ; }

  virtual void clear ( )
  {
    full       = false ;
    empty      = true  ;
    read_addr  = 0     ;
    write_addr = 0     ;
    wait ( 2, SC_NS )  ;
  }

  virtual void write ( const TDATA& data )
  {
    if ( full ) wait ( read_event ) ;
    fifo[write_addr]  = data ;
    write_addr = (write_addr+1)%DEPTH ;
    if ( write_addr == read_addr ) full = true ;
    empty = false ;
    write_event.notify() ;
    wait ( 2, SC_NS ) ; // s/b exponential distribution
  }

  virtual void read ( TDATA& data )
  {
    if ( empty ) wait ( write_event ) ;
    data              = fifo[read_addr] ;
    read_addr = (read_addr+1)%DEPTH ;
    if ( read_addr == write_addr ) empty = true ;
    full = false ;
    read_event.notify() ;
    wait ( 2, SC_NS ) ; // s/b normal distribution
  }

protected :

  TDATA    *fifo       ;
  bool     full        ;
  bool     empty       ;
  sc_event read_event  ;
  sc_event write_event ;
  unsigned read_addr   ;
  unsigned write_addr  ;

} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef PRODUCER_H
#define PRODUCER_H

#include "systemc.h"
//#include "interface.h"
//#include "rand.h"

template <class T> class producer
:
  public sc_module
{

public :

  sc_port <interface<T> > out_p ;

  SC_HAS_PROCESS ( producer ) ;

  producer ( sc_module_name name, unsigned seed=1, unsigned poly=0xC6 )
  :
    sc_module ( name    ) ,
    out_p     ( "out_p" ) ,
    seed      ( seed    ) ,
    poly      ( poly    )
  {
    SC_THREAD ( producer_thread ) ;
  }

  void producer_thread ( )
  {
    while ( true )
    {
      seed = rand ( seed, poly ) ;
      out_p->write( (T) seed ) ;
    }
  }

protected :

  unsigned seed ;
  unsigned poly ;

} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef CONSUMER_H
#define CONSUMER_H

#include "systemc.h"
//#include "interface.h"
//#include "rand.h"

template <class T> class consumer
:
  public sc_module
{

public :

  sc_port <interface<T> > in_p ;

  SC_HAS_PROCESS ( consumer ) ;

  consumer ( sc_module_name name, unsigned seed=1, unsigned poly=0xC6 )
  :
    sc_module ( name   ) ,
    in_p      ( "in_p" ) ,
    seed      ( seed   ) ,
    poly      ( poly   )
  {
    SC_THREAD ( consumer_thread ) ;
  }

  void consumer_thread ( )
  {
    T data ;
    while ( true )
    {
      in_p->read ( data );
      seed = rand ( seed, poly ) ;
      cout << "SystemC consumer got " << data
           << " at " << sc_simulation_time() ;
      if ( data == (T) seed )
        cout << endl ;
      else
      {
        cout << " s/b=" << (T) seed << endl ;
        cout << "SYSTEMC TEST FAILED" << endl ;
        sc_stop ( ) ;
      }
    }
  }

protected :

  unsigned seed ;
  unsigned poly ;

} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
//#include "producer.h"
//#include "channel.h"
//#include "consumer.h"

#define WIDTH 8
#define DEPTH 8
#define TDATA sc_lv <WIDTH>
#define TCTRL sc_logic

SC_MODULE ( testbench ) {

  producer <TDATA>        producer_i ;
  channel  <TDATA, DEPTH> channel_i  ;
  consumer <TDATA>        consumer_i ;

  void testbench_thread ( ) ;

  SC_CTOR ( testbench )
  :
    producer_i ( "producer_i" ) ,
    channel_i  ( "channel_i"  ) ,
    consumer_i ( "consumer_i" )  
  {
    producer_i ( channel_i ) ;
    consumer_i ( channel_i ) ;
    SC_THREAD ( testbench_thread ) ;
  }

} ;

#undef WIDTH
#undef DEPTH
#undef TDATA
#undef TCTRL

////////////////////////////////////////////////////////////////////////////////

//#include "testbench.h"

void testbench::testbench_thread ( )
{
  channel_i.clear ( ) ;
  wait ( 17, SC_NS ) ;
  cout << "SYSTEMC TEST PASSED" << endl ;
  sc_stop ( ) ;
}

int sc_main ( int argc, char **argv ) {
  testbench top ( "top" ) ;
  sc_start ( ) ;
  return ( 0 ) ;
}


// SystemC consumer got 00000000 at 2
// SystemC consumer got 11000110 at 4
// SystemC consumer got 10100101 at 6
// SystemC consumer got 01010010 at 8
// SystemC consumer got 11101111 at 10
// SystemC consumer got 01110111 at 12
// SystemC consumer got 00111011 at 14
// SystemC consumer got 00011101 at 16
// SystemC consumer got 00001110 at 18
// SYSTEMC TEST PASSED
// SystemC: simulation stopped by user.