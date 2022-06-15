////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_trans.cpp                                               //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET transactors                                             //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_trans.h"
#include "pnet_frame.h"


// CPU WRITE TRANSACTOR

pnet_cpu_write_trans::pnet_cpu_write_trans ( sc_module_name name )
: sc_module    ( name           )
, p_cpu_tx_data_value ( "p_cpu_tx_data_value" )
, p_cpu_tx_data_ready ( "p_cpu_tx_data_ready" )
, p_cpu_tx_data_done  ( "p_cpu_tx_data_done"  )
{ }

void pnet_cpu_write_trans::cpu_write_function ( const sc_lv<8> & data ) {
  p_cpu_tx_data_value = data ;
  p_cpu_tx_data_ready = SC_LOGIC_1 ;
  if ( p_cpu_tx_data_done != SC_LOGIC_1 )
    wait ( p_cpu_tx_data_done->posedge_event() ) ;
  if ( p_cpu_tx_data_done != SC_LOGIC_0 )
    wait ( p_cpu_tx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_cpu_tx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
}


// CPU READ TRANSACTOR

pnet_cpu_read_trans::pnet_cpu_read_trans ( sc_module_name name )
: sc_module    ( name           )
, p_cpu_rx_data_value ( "p_cpu_rx_data_value" )
, p_cpu_rx_data_ready ( "p_cpu_rx_data_ready" )
, p_cpu_rx_data_done  ( "p_cpu_rx_data_done"  )
{ }

void pnet_cpu_read_trans::cpu_read_function ( sc_lv<8> & data ) {
  p_cpu_rx_data_done = SC_LOGIC_0 ;
  if ( p_cpu_rx_data_ready != SC_LOGIC_1 )
    wait ( p_cpu_rx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_cpu_rx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  data = p_cpu_rx_data_value ;
  p_cpu_rx_data_done = SC_LOGIC_0 ;
  if ( p_cpu_rx_data_ready != SC_LOGIC_0 )
    wait ( p_cpu_rx_data_ready->negedge_event() ) ;
}


// NET WRITE TRANSACTOR

pnet_net_write_trans::pnet_net_write_trans ( sc_module_name name )
: sc_module    ( name           )
, p_net_tx_data_value ( "p_net_tx_data_value" )
, p_net_tx_data_ready ( "p_net_tx_data_ready" )
, p_net_tx_data_done  ( "p_net_tx_data_done"  )
{ }

void pnet_net_write_trans::net_write_function ( const pnet_frame & frame ) {
  p_net_tx_data_value = frame.high ;
  p_net_tx_data_ready = SC_LOGIC_1 ;
  if ( p_net_tx_data_done != SC_LOGIC_1 )
    wait ( p_net_tx_data_done->posedge_event() ) ;
  if ( p_net_tx_data_done != SC_LOGIC_0 )
    wait ( p_net_tx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_tx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
  p_net_tx_data_value = frame.low ;
  p_net_tx_data_ready = SC_LOGIC_1 ;
  if ( p_net_tx_data_done != SC_LOGIC_1 )
    wait ( p_net_tx_data_done->posedge_event() ) ;
  if ( p_net_tx_data_done != SC_LOGIC_0 )
    wait ( p_net_tx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_tx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
}


// NET READ TRANSACTOR

pnet_net_read_trans::pnet_net_read_trans ( sc_module_name name )
: sc_module    ( name           )
, p_net_rx_data_value ( "p_net_rx_data_value" )
, p_net_rx_data_ready ( "p_net_rx_data_ready" )
, p_net_rx_data_done  ( "p_net_rx_data_done"  )
{ }

void pnet_net_read_trans::net_read_function ( pnet_frame & frame ) {
  p_net_rx_data_done = SC_LOGIC_0 ;
  if ( p_net_rx_data_ready != SC_LOGIC_1 )
    wait ( p_net_rx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_rx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  frame.high = p_net_rx_data_value ;
  p_net_rx_data_done = SC_LOGIC_0 ;
  if ( p_net_rx_data_ready != SC_LOGIC_0 )
    wait ( p_net_rx_data_ready->negedge_event() ) ;
  if ( p_net_rx_data_ready != SC_LOGIC_1 )
    wait ( p_net_rx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_rx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  frame.low = p_net_rx_data_value ;
  p_net_rx_data_done = SC_LOGIC_0 ;
  if ( p_net_rx_data_ready != SC_LOGIC_0 )
    wait ( p_net_rx_data_ready->negedge_event() ) ;
}
