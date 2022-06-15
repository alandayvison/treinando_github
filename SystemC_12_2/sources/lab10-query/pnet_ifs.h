////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_ifs.h                                                   //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET cpu and net write and read interfaces                   //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_IFS_H
#define PNET_IFS_H

#include "systemc.h"
#include "pnet_frame.h"

struct pnet_cpu_write_if : virtual sc_interface
{ virtual void cpu_write_function ( const sc_lv<8> & data ) = 0 ; } ;

struct pnet_cpu_read_if  : virtual sc_interface
{ virtual void cpu_read_function  (       sc_lv<8> & data ) = 0 ; } ;

struct pnet_net_write_if : virtual sc_interface
{ virtual void net_write_function ( const pnet_frame & frame ) = 0 ; } ;

struct pnet_net_read_if  : virtual sc_interface
{ virtual void net_read_function  (       pnet_frame & frame ) = 0 ; } ;

#endif
