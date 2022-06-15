////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_cpu.h                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET CPU                                                     //
// Notes       : A PNET CPU writes address/data bytes to the PNET channel     //
//               and reads data bytes from the PNET channel.                  //
//               The CPU utilizes the PNET monitor as a "scoreboard".         //
//               This CPU communicates with the PNET channel though ports     //
//               connected to external fifo channels.                         //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_CPU_H
#define PNET_CPU_H

#include "systemc.h"

SC_MODULE ( pnet_cpu )
{
  sc_fifo_out <sc_lv<8> > p_cpu_write ; // Port to write cpu data
  sc_fifo_in  <sc_lv<8> > p_cpu_read  ; // Port to read  cpu data

  pnet_cpu ( sc_module_name name, unsigned addr ) ;

  void cpu_write_process ( ) ; // Write bytes to cpu data output port
  void cpu_read_process  ( ) ; // Read bytes from cpu data input port

protected:
  unsigned addr ;

} ;

#endif
