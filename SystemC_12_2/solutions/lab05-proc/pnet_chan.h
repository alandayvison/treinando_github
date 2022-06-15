////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_chan.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel implements processes to read and write cpu //
//               and net data through ports connected to external channels.   //
//               Thus this PNET channel is not yet a true SystemC channel.    //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_CHAN_H
#define PNET_CHAN_H

#include "systemc.h"
#include "pnet_frame.h"

SC_MODULE ( pnet_chan )
{
  sc_fifo_in  <sc_lv<8> >  p_cpu_read  ; // Port to read  cpu data
  sc_fifo_out <sc_lv<8> >  p_cpu_write ; // Port to write cpu data
  sc_fifo_in  <pnet_frame> p_net_read  ; // Port to read  net data
  sc_fifo_out <pnet_frame> p_net_write ; // Port to write net data
  sc_fifo     <pnet_frame> cpu_fifo    ; // Collect cpu write frames
  sc_fifo     <pnet_frame> net_fifo    ; // Collect net write frames

  pnet_chan ( sc_module_name name, unsigned addr ) ;

  void cpu_read_process  ( ) ; // Read  bytes  from cpu data input  port
  void cpu_write_process ( ) ; // Write bytes  to   cpu data output port
  void net_read_process  ( ) ; // Read  frames from net data input  port
  void net_write_process ( ) ; // Write frames to   net data output port

protected:
  sc_lv<2> addr ; // my address
  sc_lv<2> cpu_read_proc_addr ;

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
