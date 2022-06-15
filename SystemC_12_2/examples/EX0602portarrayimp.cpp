////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0602portarrayimp.cpp                                       //
// Title       : The sc_port Class Template                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates use of port array with implicit binding         //
// Change Log  : 2011-03-30 mikep Created.                                    //
//               2012-09-23 mikep Split into two test cases.                  //
//               2019-11-24 mikep Added test case for implicit binding.       //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include <systemc.h>

SC_MODULE ( producer ) {

  sc_port<sc_signal_out_if<sc_bv<8> >  > p_out[2] ;

  SC_CTOR ( producer )

//: p_out ( "p_out" ) // cannot initialize arrays

  {
    SC_THREAD ( producer_thread ) ;
  }

  void producer_thread ( ) {
    wait ( 1, SC_NS ) ;
    p_out[1]->write( (sc_bv<8>) "10101010" ) ;
    wait ( 1, SC_NS ) ;
    p_out[0]->write( (sc_bv<8>) "11001100" ) ;
    wait ( 1, SC_NS ) ;
    p_out[1]->write( (sc_bv<8>) "00110011" ) ;
    wait ( 1, SC_NS ) ;
    p_out[0]->write( (sc_bv<8>) "01010101" ) ;
    wait ( 1, SC_NS ) ;
    sc_stop ( ) ;
  }

} ;


SC_MODULE ( consumer ) {

  sc_port<sc_signal_in_if<sc_bv<8> >  > p_in[2] ;

  SC_CTOR ( consumer )

//: p_in ( "p_in" ) // cannot initialize arrays

  {
    SC_METHOD ( consumer_method ) ;
      dont_initialize();
      sensitive << p_in[1] << p_in[0] ;

  }

  void consumer_method ( ) {
    cout
      << " at simtime = " << sc_time_stamp()
      << " p_in[0] = " << (sc_bv<8>) p_in[0]->read()
      << " p_in[1] = " << (sc_bv<8>) p_in[1]->read()
      << " p_in[1][0] = " << (sc_bit) p_in[1]->read()[0]
      << endl ;
  }

} ;


SC_MODULE ( top ) {

  producer producer_inst ;
  sc_signal<sc_bv<8> > signal0 ;
  sc_signal<sc_bv<8> > signal1 ;
  consumer consumer_inst ;

  SC_CTOR ( top )
  :
    producer_inst ( "producer_inst" ) ,
    signal0       ( "signal0"       ) ,
    signal1       ( "signal1"       ) ,
    consumer_inst ( "consumer_inst" )
  {

    producer_inst ( signal0, signal1) ;
    consumer_inst ( signal0, signal1) ;

  }
} ;


int sc_main ( int argc, char **argv ) {
  top top1 ( "top1" ) ;
  sc_start ( ) ;
  return ( 0 ) ;
}

// at simtime = 1 ns p_in[0] = 00000000 p_in[1] = 10101010 p_in[1][0] = 0
// at simtime = 2 ns p_in[0] = 11001100 p_in[1] = 10101010 p_in[1][0] = 0
// at simtime = 3 ns p_in[0] = 11001100 p_in[1] = 00110011 p_in[1][0] = 1
// at simtime = 4 ns p_in[0] = 01010101 p_in[1] = 00110011 p_in[1][0] = 1
