////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_wrap.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel wrapper                                         //
// Notes       : The PNET channel wrapper instantiates the refined PNET       //
//               channel and four transactors (with signal channels) to       //
//               transact between wrapper interfaces and the refined channel. //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_WRAP_H
#define PNET_WRAP_H

#include "systemc.h"
#include "pnet_ifs.h"
#include "pnet_trans.h"
#include "pnet_refined.h"

class pnet_wrap
: public sc_module
, public pnet_cpu_write_if
, public pnet_cpu_read_if
, public pnet_net_write_if
, public pnet_net_read_if
{
public:

  // CPU WRITE

  void cpu_write_function ( const sc_lv<8> & data )    ; // INTERFACE
  pnet_cpu_write_trans  cpu_write_trans       ; // TRANSACTOR
  sc_signal <sc_lv<8> > cpu_tx_data_value     ; // SIGNALS
  sc_signal <sc_logic>  cpu_tx_data_ready     ;
  sc_signal <sc_logic>  cpu_tx_data_done      ;

  // CPU READ

  void cpu_read_function  ( sc_lv<8> & data )          ; // INTERFACE
  pnet_cpu_read_trans   cpu_read_trans                 ; // TRANSACTOR
  sc_signal <sc_lv<8> > cpu_rx_data_value              ; // SIGNALS
  sc_signal <sc_logic>  cpu_rx_data_ready              ;
  sc_signal <sc_logic>  cpu_rx_data_done               ;

  // NET WRITE

  void net_write_function ( const pnet_frame & frame ) ; // INTERFACE
  pnet_net_write_trans  net_write_trans                ; // TRANSACTOR
  sc_signal <sc_lv<8> > net_tx_data_value              ; // SIGNALS
  sc_signal <sc_logic>  net_tx_data_ready              ;
  sc_signal <sc_logic>  net_tx_data_done               ;

  // NET READ

  void net_read_function  ( pnet_frame & frame )       ; // INTERFACE
  pnet_net_read_trans   net_read_trans                 ; // TRANSACTOR
  sc_signal <sc_lv<8> > net_rx_data_value              ; // SIGNALS
  sc_signal <sc_logic>  net_rx_data_ready              ;
  sc_signal <sc_logic>  net_rx_data_done               ;

  pnet_refined refined ;                        // REFINED CHANNEL

  pnet_wrap ( sc_module_name name, unsigned addr ) ;

} ;

#endif
