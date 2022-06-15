////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_node.cpp                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET node                                                    //
// Notes       : A PNET node contains a PNET CPU and a PNET channel.          //
//               This node binds PNET CPU cpu data read/write ports to        //
//               FIFOs and thence to PNET channel cpu data read/write ports.  //
//               This node binds its net data read/write ports to             //
//               PNET channel net data read/write ports.                      //
//               The fifo depth of 1 forces close process synchronization.    //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Initialized p_net_read before p_net_write.  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_node.h"

pnet_node::pnet_node ( sc_module_name name, unsigned addr )
: sc_module      ( name               )
, p_net_read     ( "p_net_read"       )
, p_net_write    ( "p_net_write"      )
, f_cpu_tx_data  ( "f_cpu_tx_data", 1 )
, f_cpu_rx_data  ( "f_cpu_rx_data", 1 )
, cpu            ( "cpu",  addr       )
, chan           ( "chan", addr       )
{
  // Connect together the PNET CPU and PNET channel
  // cpu data read/write ports through local fifo channels
  cpu.p_cpu_read  ( f_cpu_rx_data ) ; chan.p_cpu_write ( f_cpu_rx_data ) ;
  cpu.p_cpu_write ( f_cpu_tx_data ) ; chan.p_cpu_read  ( f_cpu_tx_data ) ;

  // Connect the PNET channel net data read/write ports to local
  // read-write ports later connected to external fifo channels
  chan.p_net_read  ( p_net_read  ) ;
  chan.p_net_write ( p_net_write ) ;
}
