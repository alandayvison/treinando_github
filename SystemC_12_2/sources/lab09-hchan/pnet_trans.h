////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_trans.h                                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET transactors                                             //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_TRANS_H
#define PNET_TRANS_H

#include "systemc.h"
#include "pnet_ifs.h"
#include "pnet_frame.h"

class pnet_cpu_write_trans
: public sc_module
, public pnet_cpu_write_if
{
public:
  sc_out <sc_lv<8> > p_cpu_tx_data_value ; // data value
  sc_out <sc_logic>  p_cpu_tx_data_ready ; // data ready
  sc_in  <sc_logic>  p_cpu_tx_data_done  ; // data done
  pnet_cpu_write_trans ( sc_module_name name ) ;
  void cpu_write_function ( const sc_lv<8> & data ) ;
} ;

class pnet_cpu_read_trans
: public sc_module
, public pnet_cpu_read_if
{
public:
  sc_in  <sc_lv<8> > p_cpu_rx_data_value ; // data value
  sc_in  <sc_logic>  p_cpu_rx_data_ready ; // data ready
  sc_out <sc_logic>  p_cpu_rx_data_done  ; // data done
  pnet_cpu_read_trans ( sc_module_name name ) ;
  void cpu_read_function ( sc_lv<8> & data ) ;
} ;


class pnet_net_write_trans
: public sc_module
, public pnet_net_write_if
{
public:
  sc_out <sc_lv<8> > p_net_tx_data_value ; // data value
  sc_out <sc_logic>  p_net_tx_data_ready ; // data ready
  sc_in  <sc_logic>  p_net_tx_data_done  ; // data done
  pnet_net_write_trans ( sc_module_name name ) ;
  void net_write_function ( const pnet_frame & frame ) ;
} ;

class pnet_net_read_trans
: public sc_module
, public pnet_net_read_if
{
public:
  sc_in  <sc_lv<8> > p_net_rx_data_value ; // data value
  sc_in  <sc_logic>  p_net_rx_data_ready ; // data ready
  sc_out <sc_logic>  p_net_rx_data_done  ; // data done
  pnet_net_read_trans ( sc_module_name name ) ;
  void net_read_function ( pnet_frame & frame ) ;
} ;

#endif
