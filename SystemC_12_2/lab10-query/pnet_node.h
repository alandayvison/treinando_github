////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_node.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET node                                                    //
// Notes       : A PNET node contains a PNET CPU and a PNET channel.          //
//               This node binds PNET CPU cpu data read/write ports to        //
//               PNET channel cpu data read/write interfaces.                 //
//               This node binds its net data read/write ports to             //
//               PNET channel net data read/write interfaces.                 //
//               This node instantiates the wrapped refined channel.          //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Instantiated network write/read ports.      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_NODE_H
#define PNET_NODE_H

#include "systemc.h"
#include "pnet_ifs.h"
#include "pnet_frame.h"
#include "pnet_cpu.h"
#include "pnet_wrap.h"

SC_MODULE ( pnet_node )
{
  sc_port <pnet_net_read_if > p_net_read  ;
  sc_port <pnet_net_write_if> p_net_write ;
  pnet_cpu  cpu  ;
  pnet_wrap wrap ;

  pnet_node ( sc_module_name name, unsigned addr ) ;

} ;

#endif
