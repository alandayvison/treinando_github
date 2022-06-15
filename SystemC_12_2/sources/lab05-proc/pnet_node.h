////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_node.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET node                                                    //
// Notes       : A PNET node contains a PNET CPU and a PNET channel.          //
//               This node binds PNET CPU cpu data read/write ports to        //
//               FIFOs and thence to PNET channel cpu data read/write ports.  //
//               This node binds its net data read/write ports to             //
//               PNET channel net data read/write ports.                      //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_NODE_H
#define PNET_NODE_H

#include "systemc.h"
#include "pnet_cpu.h"
#include "pnet_chan.h"
#include "pnet_frame.h"

SC_MODULE ( pnet_node )
{
  sc_fifo_in  <pnet_frame> p_net_read    ; // port to read  net data
  sc_fifo_out <pnet_frame> p_net_write   ; // port to write net data
  sc_fifo     <sc_lv<8> >  f_cpu_tx_data ; // fifo for cpu tx data
  sc_fifo     <sc_lv<8> >  f_cpu_rx_data ; // fifo for cpu rx data
  pnet_cpu  cpu  ;
  pnet_chan chan ;

  pnet_node ( sc_module_name name, unsigned addr ) ;

} ;

#endif
