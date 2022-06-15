////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_system.cpp                                              //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET system                                                  //
// Notes       : The PNET system is a number of interconnected nodes.         //
//               This system connects the nodes using fifo channels.          //
//               The fifo depth of 1 enforces close synchronization.          //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_system.h"
#include "pnet_frame.h"

extern unsigned NODES ;

pnet_system::pnet_system ( sc_module_name name )
: sc_module ( name  )
{
  // allocate array of node pointers
  node = new pnet_node * [NODES] ;

  // allocate nodes
  for ( unsigned i=0; i < NODES; ++i )
    node[i] = new pnet_node ( sc_gen_unique_name("node"), i ) ;

  // allocate array of fifo pointers
  fifo = new sc_fifo <pnet_frame> * [NODES] ;

  // allocate fifos
  for ( unsigned i=0; i < NODES; ++i )
    fifo[i] = new sc_fifo <pnet_frame> ( sc_gen_unique_name("fifo"), 1 ) ;

  // bind node ports to fifos
  for ( unsigned i=0; i < NODES; ++i ) {
    node[i]->p_net_read  ( *fifo[i] ) ;
    node[i]->p_net_write ( *fifo[(i+1)%NODES] ) ;
  }
}
