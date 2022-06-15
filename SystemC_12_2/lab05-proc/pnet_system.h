////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_system.h                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET system                                                  //
// Notes       : The PNET system is a number of interconnected nodes.         //
//               This system connects the nodes using fifo channels.          //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_SYSTEM_H
#define PNET_SYSTEM_H

#include "systemc.h"
#include "pnet_node.h"
#include "pnet_frame.h"

SC_MODULE ( pnet_system )
{
  pnet_node ** node ;            // node iterators
  sc_fifo <pnet_frame> ** fifo ; // fifo iterators

  pnet_system ( sc_module_name name ) ;

} ;

#endif
