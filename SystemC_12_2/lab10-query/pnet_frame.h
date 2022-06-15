////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_frame.h                                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET transaction frame                                       //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_FRAME_H
#define PNET_FRAME_H

#include "systemc.h"

struct pnet_frame {
  sc_lv<8> low  ;
  sc_lv<8> high ;
  pnet_frame& operator= ( const pnet_frame& other ) ;
  bool operator== ( const pnet_frame& other ) ;
} ;

ostream& operator<< ( ostream& os, const pnet_frame& frame ) ;

void sc_trace ( sc_trace_file* tf, const pnet_frame& frame, const std::string name ) ;

#endif
