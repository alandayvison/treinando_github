////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_walker.h                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : Hierarchy walker                                             //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_WALKER_H
#define PNET_WALKER_H

#include "systemc.h"
#include <vector>
using namespace std;

struct pnet_walker : sc_module {
  pnet_walker ( sc_module_name name ) ;
  void start_of_simulation ( ) ;
protected:
  void listChildObjects ( const vector<sc_object*> & childList,
                          unsigned indent=0 ) ;
  vector<bool> last ; // helps indentation
} ;

#endif
