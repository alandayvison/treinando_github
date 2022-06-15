////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_node.cpp                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET node                                                    //
// Notes       : A PNET node contains a PNET CPU and a PNET channel.          //
//               This node binds PNET CPU cpu data read/write ports to        //
//               PNET channel cpu data read/write interfaces.                 //
//               This node binds its net data read/write ports to             //
//               PNET channel net data read/write interfaces.                 //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Instantiated network write/read ports.      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_node.h"

pnet_node::pnet_node ( sc_module_name name, unsigned addr )
: sc_module      ( name               )
, p_net_read     ( "p_net_read"       )
, p_net_write    ( "p_net_write"      )
, cpu            ( "cpu",  addr       )
, chan           ( "chan", addr       )
{
  // bind cpu ports to channel
  cpu.p_cpu_read  ( chan ) ;
  cpu.p_cpu_write ( chan ) ;
  // bind node ports to channel
  p_net_read  ( chan ) ;
  p_net_write ( chan ) ;
}
