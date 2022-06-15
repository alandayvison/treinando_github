////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_chan.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel implements methods that external processes //
//               use to read and write cpu and net data directly or through   //
//               ports connected to the channel.                              //
//               Thus this PNET channel is now a true SystemC channel.        //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_CHAN_H
#define PNET_CHAN_H

#include "systemc.h"
#include "pnet_ifs.h"
#include "pnet_sync.h"
#include "pnet_frame.h"

class pnet_chan
: public sc_module
, public pnet_cpu_write_if
, public pnet_cpu_read_if
, public pnet_net_write_if
, public pnet_net_read_if
{
public:
  pnet_sync   <pnet_frame> cpu_fifo    ; // Collect cpu write frames
  pnet_sync   <pnet_frame> net_fifo    ; // Collect net write frames

  pnet_chan ( sc_module_name name, unsigned addr ) ;

  void cpu_write_function ( const sc_lv<8> & data ) ; // External process writes cpu data
  void cpu_read_function  (       sc_lv<8> & data ) ; // External process reads  cpu data
  void net_write_function ( const pnet_frame & frame ) ; // External process writes net frames
  void net_read_function  (       pnet_frame & frame ) ; // External process reads net frames

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
