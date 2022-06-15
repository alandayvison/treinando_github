////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_wrap.cpp                                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel wrapper                                         //
// Notes       : The PNET channel wrapper instantiates the refined PNET       //
//               channel and four transactors (with signal channels) to       //
//               transact between wrapper interfaces and the refined channel. //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_wrap.h"
#include "pnet_frame.h"

pnet_wrap::pnet_wrap ( sc_module_name name, unsigned addr )
: sc_module ( name )

  // INITIALIZE CPU WRITE ELEMENTS
, cpu_write_trans   ( "cpu_write_trans"   ) // transactor
, cpu_tx_data_value ( "cpu_tx_data_value" ) // signals
, cpu_tx_data_ready ( "cpu_tx_data_ready" )
, cpu_tx_data_done  ( "cpu_tx_data_done"  )

  // INITIALIZE CPU READ ELEMENTS
, cpu_read_trans    ( "cpu_read_trans"    ) // transactor
, cpu_rx_data_value ( "cpu_rx_data_value" ) // signals
, cpu_rx_data_ready ( "cpu_rx_data_ready" )
, cpu_rx_data_done  ( "cpu_rx_data_done"  )

  // INITIALIZE NET WRITE ELEMENTS
, net_write_trans   ( "net_write_trans"   ) // transactor
, net_tx_data_value ( "net_tx_data_value" ) // signals
, net_tx_data_ready ( "net_tx_data_ready" )
, net_tx_data_done  ( "net_tx_data_done"  )

  // INITIALIZE NET READ ELEMENTS
, net_read_trans    ( "net_read_trans"    ) // transactor
, net_rx_data_value ( "net_rx_data_value" ) // signals
, net_rx_data_ready ( "net_rx_data_ready" )
, net_rx_data_done  ( "net_rx_data_done"  )

// INITIALIZE REFINED CHANNEL
, refined           ( "refined", addr     )

{
  // BIND CPU WRITE SIGNALS
  cpu_write_trans.p_cpu_tx_data_value ( cpu_tx_data_value ) ;
  cpu_write_trans.p_cpu_tx_data_ready ( cpu_tx_data_ready ) ;
  cpu_write_trans.p_cpu_tx_data_done  ( cpu_tx_data_done  ) ;
  refined.p_cpu_tx_data_value  ( cpu_tx_data_value ) ;
  refined.p_cpu_tx_data_ready  ( cpu_tx_data_ready ) ;
  refined.p_cpu_tx_data_done   ( cpu_tx_data_done  ) ;

  // BIND CPU READ SIGNALS
  cpu_read_trans.p_cpu_rx_data_value  ( cpu_rx_data_value ) ;
  cpu_read_trans.p_cpu_rx_data_ready  ( cpu_rx_data_ready ) ;
  cpu_read_trans.p_cpu_rx_data_done   ( cpu_rx_data_done  ) ;
  refined.p_cpu_rx_data_value  ( cpu_rx_data_value ) ;
  refined.p_cpu_rx_data_ready  ( cpu_rx_data_ready ) ;
  refined.p_cpu_rx_data_done   ( cpu_rx_data_done  ) ;

  // BIND NET WRITE SIGNALS
  net_write_trans.p_net_tx_data_value ( net_tx_data_value ) ;
  net_write_trans.p_net_tx_data_ready ( net_tx_data_ready ) ;
  net_write_trans.p_net_tx_data_done  ( net_tx_data_done  ) ;
  refined.p_net_tx_data_value  ( net_tx_data_value ) ;
  refined.p_net_tx_data_ready  ( net_tx_data_ready ) ;
  refined.p_net_tx_data_done   ( net_tx_data_done  ) ;

  // BIND NET READ SIGNALS
  net_read_trans.p_net_rx_data_value  ( net_rx_data_value ) ;
  net_read_trans.p_net_rx_data_ready  ( net_rx_data_ready ) ;
  net_read_trans.p_net_rx_data_done   ( net_rx_data_done  ) ;
  refined.p_net_rx_data_value  ( net_rx_data_value ) ;
  refined.p_net_rx_data_ready  ( net_rx_data_ready ) ;
  refined.p_net_rx_data_done   ( net_rx_data_done  ) ;

}

void pnet_wrap::cpu_write_function ( const sc_lv<8> & data )
{ cpu_write_trans.cpu_write_function ( data ) ; }

void pnet_wrap::cpu_read_function ( sc_lv<8> & data )
{ cpu_read_trans.cpu_read_function ( data ) ; }

void pnet_wrap::net_write_function ( const pnet_frame & frame )
{ net_write_trans.net_write_function ( frame ) ; }

void pnet_wrap::net_read_function ( pnet_frame & frame )
{ net_read_trans.net_read_function ( frame ) ; }

