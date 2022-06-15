////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0902refine2a.cpp                                           //
// Title       : Refining Hierarchical Channels                               //
// Project     : SystemC Language Fundamentals                                //
// Description : User channel hierarchy flattened                             //
// Notes       : producer calls adapters's interface method to write          //
//               consumer calls adapters's interface method to read           //
//               adapters adapt to signals connected to external FIFO         //
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

#ifndef FIFO_H
#define FIFO_H

#include "systemc.h"

template <class TDATA, unsigned DEPTH, class TCTRL> class fifo :
  public sc_module
{

public :

  sc_out <TDATA> p_datao ;
  sc_out <TCTRL> p_full  ;
  sc_out <TCTRL> p_empty ;
  sc_in  <TDATA> p_datai ;
  sc_in  <TCTRL> p_write ;
  sc_in  <TCTRL> p_read  ;
  sc_in  <TCTRL> p_clear ;

  SC_CTOR ( fifo ) :
    p_datao   ( "p_datao"  ) ,
    p_full    ( "p_full"   ) ,
    p_empty   ( "p_empty"  ) ,
    p_datai   ( "p_datai"  ) ,
    p_write   ( "p_write"  ) ,
    p_read    ( "p_read"   ) ,
    p_clear   ( "p_clear"  )  
  {
    SC_METHOD ( clear ) ;
      sensitive << p_clear.pos() ;
      dont_initialize() ;
    SC_METHOD ( write ) ;
      sensitive << p_write.pos() ;
      dont_initialize() ;
    SC_METHOD ( read ) ;
      sensitive << p_read.pos() ;
      dont_initialize() ;
    mem = new TDATA[DEPTH] ;
    read_addr  = 0     ; 
    write_addr = 0     ;
  }

  ~fifo ( )
  {
    delete [] mem ;
  }

  void clear ( )
  {
    p_full     = (TCTRL) 0 ;
    p_empty    = (TCTRL) 1 ;
    read_addr  = 0     ; 
    write_addr = 0     ;
  }

  void write ( )
  {
    if ( p_full == (TCTRL) 0 )
    {
      mem[write_addr]   = p_datai ;
      write_addr = (write_addr+1)%DEPTH ;
      if ( write_addr == read_addr ) p_full = (TCTRL) 1 ;
      p_empty = (TCTRL) 0 ;
    }
  }

  void read ( )
  {
    if ( p_empty == (TCTRL) 0 )
    {
      p_datao           = mem[read_addr] ;
      read_addr = (read_addr+1)%DEPTH ;
      if ( read_addr == write_addr ) p_full = (TCTRL) 1 ;
      p_full = (TCTRL) 0 ;
    }
  }

protected :

  TDATA *mem ;
  unsigned read_addr   ;
  unsigned write_addr  ;

} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef INTERFACE_H
#define INTERFACE_H

#include "systemc.h"

template <class T> class interface_w
  : virtual public sc_interface
{
public :
  virtual void write ( const T& ) = 0 ;
} ;

template <class T> class interface_r
  : virtual public sc_interface
{
public :
  virtual void read ( T& ) = 0 ;
} ;

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef CHANNEL_H
#define CHANNEL_H

#include "systemc.h"
//#include "interface.h"

template <class TDATA, class TCTRL> class channel_w :
  public sc_channel ,
  public interface_w <TDATA>
{
public :
  sc_in  <TCTRL> full_p  ;
  sc_out <TDATA> datai_p ;
  sc_out <TCTRL> write_p ;
  SC_CTOR ( channel_w ) :
    full_p  ( "full_p"  ) ,
    datai_p ( "datai_p" ) ,
    write_p ( "write_p" )  
  { }
  virtual void clear ( ) {
    write_p = (TCTRL) 0 ;
  }
  virtual void write ( const TDATA& data ) {
    if ( full_p != (TCTRL) 0 ) wait ( full_p.negedge_event() ) ;
    datai_p = data ;
    write_p = (TCTRL) 1 ; wait ( 1, SC_NS ) ;
    write_p = (TCTRL) 0 ; wait ( 1, SC_NS ) ;
  }
} ;

template <class TDATA, class TCTRL> class channel_r :
  public sc_channel ,
  public interface_r <TDATA>
{
public :
  sc_in  <TDATA> datao_p ;
  sc_in  <TCTRL> empty_p ;
  sc_out <TCTRL> read_p  ;
  SC_CTOR ( channel_r ) :
    datao_p  ( "datao_p" ) ,
    empty_p  ( "empty_p" ) ,
    read_p   ( "read_p"  )  
  { }
  virtual void clear ( ) {
    read_p = (TCTRL) 0 ;
  }
  virtual void read ( TDATA& data ) {
    if ( empty_p != (TCTRL) 0 ) wait ( empty_p.negedge_event() ) ;
    read_p = (TCTRL) 1 ; wait ( 1, SC_NS ) ;
    read_p = (TCTRL) 0 ; wait ( 1, SC_NS ) ;
    data   = datao_p ;
  }
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

  sc_port <interface_w<T> > out_p ;

  SC_HAS_PROCESS ( producer ) ;

  producer ( sc_module_name name, unsigned seed=1, unsigned poly=0xC6)
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
      seed = rand(seed,poly);
      out_p->write((T)seed);
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

  sc_port <interface_r<T> > in_p ;

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
//#include "fifo.h"

#define WIDTH 8
#define DEPTH 8
#define TDATA sc_lv <WIDTH>
#define TCTRL sc_logic

SC_MODULE ( testbench ) {

  producer  <TDATA>               producer_i ;
  channel_w <TDATA, TCTRL>        channel_w_i  ;
  fifo      <TDATA, DEPTH, TCTRL> fifo_i ;
  channel_r <TDATA, TCTRL>        channel_r_i  ;
  consumer  <TDATA>               consumer_i ;

  sc_signal <TDATA> datao_s ;
  sc_signal <TCTRL> full_s  ;
  sc_signal <TCTRL> empty_s ;
  sc_signal <TDATA> datai_s ;
  sc_signal <TCTRL> write_s ;
  sc_signal <TCTRL> read_s  ;
  sc_signal <TCTRL> clear_s ;

  void testbench_thread ( ) ;

 SC_CTOR ( testbench )
  :
    producer_i   ( "producer_i"  ) ,
    channel_w_i  ( "channel_w_i" ) ,
    fifo_i       ( "fifo_i"      ) ,
    channel_r_i  ( "channel_r_i" ) ,  
    consumer_i   ( "consumer_i"  ) ,
    datao_s      ( "datao_s" ) ,
    full_s       ( "full_s"  ) ,
    empty_s      ( "empty_s" ) ,
    datai_s      ( "datai_s" ) ,
    write_s      ( "write_s" ) ,
    read_s       ( "read_s"  ) ,
    clear_s      ( "clear_s" )
  {
    producer_i  ( channel_w_i ) ;
    channel_w_i ( full_s, datai_s, write_s ) ;
    fifo_i      ( datao_s, full_s, empty_s, datai_s, write_s, read_s, clear_s ) ;
    channel_r_i ( datao_s, empty_s, read_s ) ;
    consumer_i  ( channel_r_i ) ;
    SC_THREAD ( testbench_thread ) ;
  }

} ;

void testbench::testbench_thread ( )
{
  channel_w_i.clear ( ) ;
  channel_r_i.clear ( ) ;
  clear_s = (TCTRL) 1 ;
  wait ( 1, SC_NS) ;
  clear_s = (TCTRL) 0 ;
  wait ( 1, SC_NS) ;
  wait ( 17, SC_NS ) ;
  cout << "SYSTEMC TEST PASSED" << endl ;
  sc_stop ( ) ;
}

#undef WIDTH
#undef DEPTH
#undef TDATA
#undef TCTRL

////////////////////////////////////////////////////////////////////////////////

//#include "testbench.h"

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