////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_frame.cpp                                               //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET transaction frame                                       //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_frame.h"

pnet_frame& pnet_frame::operator= ( const pnet_frame& other )
{ high = other.high; low = other.low; return *this; }

bool pnet_frame::operator== ( const pnet_frame& other )
{ return low==other.low && high==other.high; }

ostream& operator<< ( ostream& os, const pnet_frame& frame )
{ os << frame.high << " " << frame.low; return os; }

void sc_trace ( sc_trace_file* tf, const pnet_frame& frame, const std::string name ) {
  sc_trace ( tf, frame.high, name+".high" ) ;
  sc_trace ( tf, frame.low,  name+".low"  ) ;
}

