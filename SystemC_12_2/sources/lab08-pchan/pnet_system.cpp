////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2012 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_system.cpp                                              //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET system                                                  //
// Notes       : The PNET system is a number of interconnected nodes.         //
//               This system connects the nodes using processes.              //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2012-09-23 mikep Processes accesses interfaces through ports.//
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_DYNAMIC_PROCESSES
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

  // spawn node interconnect processes
  for ( unsigned i = 0; i < NODES; ++i )
    (void) sc_spawn ( sc_bind(&pnet_system::connect,this,i,(i+1)%NODES),
                      sc_gen_unique_name("connect_proc") ) ;
}

void pnet_system::connect ( unsigned prev, unsigned next ) {
  pnet_frame frame ;
  while ( true ) {
    node[prev] -> p_net_read  -> net_read_function  ( frame ) ;
    node[next] -> p_net_write -> net_write_function ( frame ) ;
  }
}
