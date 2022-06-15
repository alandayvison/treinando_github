////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_refined.h                                               //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel has processes acting through ports to read //
//               and write bytes from and to the cpu and net transactors.     //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_REFINED_H
#define PNET_REFINED_H

#include "systemc.h"
#include "pnet_sync.h"
#include "pnet_frame.h"

SC_MODULE ( pnet_refined ) {

  // READ BYTES FROM CPU TX DATA TRANSACTOR
  sc_in  <sc_lv<8> > p_cpu_tx_data_value ; // data value
  sc_in  <sc_logic>  p_cpu_tx_data_ready ; // data ready
  sc_out <sc_logic>  p_cpu_tx_data_done  ; // data done


  // WRITE BYTES to CPU RX DATA TRANSACTOR
  sc_out <sc_lv<8> > p_cpu_rx_data_value ; // data value
  sc_out <sc_logic>  p_cpu_rx_data_ready ; // data ready
  sc_in  <sc_logic>  p_cpu_rx_data_done  ; // data done


  // READ FRAMES FROM NET TX DATA TRANSACTOR
  sc_in  <sc_lv<8> > p_net_tx_data_value ; // data value
  sc_in  <sc_logic>  p_net_tx_data_ready ; // data ready
  sc_out <sc_logic>  p_net_tx_data_done  ; // data done


  // WRITE FRAMES TO NET TX DATA TRANSACTOR
  sc_out <sc_lv<8> > p_net_rx_data_value ; // data value
  sc_out <sc_logic>  p_net_rx_data_ready ; // data ready
  sc_in  <sc_logic>  p_net_rx_data_done  ; // data done

  pnet_sync <pnet_frame> cpu_fifo    ; // Collect cpu write frames
  pnet_sync <pnet_frame> net_fifo    ; // Collect net write frames

  pnet_refined ( sc_module_name name, unsigned addr ) ;

  void cpu_read_process  ( ) ; // Read  bytes  from cpu tx data transactor
  void cpu_write_process ( ) ; // Write bytes  to   cpu rx data transactor
  void net_read_process  ( ) ; // Read  frames from net tx data transactor
  void net_write_process ( ) ; // Write frames to   net rx data transactor

protected:
  sc_lv<2> addr ; // my address

  void cpu_read_protocol  (       sc_lv<8>   & data  ) ;
  void cpu_write_protocol ( const sc_lv<8>   & data  ) ;
  void net_read_protocol  (       pnet_frame & frame ) ;
  void net_write_protocol ( const pnet_frame & frame ) ;

  void encode (
    const sc_lv<2> & addr, // encode address/data
    const sc_lv<8> & data,
        pnet_frame & frame // to frame
  ) ;

  void decode (
    const pnet_frame & frame, // decode frame
            sc_lv<2> & addr,  // to address/data
            sc_lv<8> & data
  ) ;

} ;

#endif
