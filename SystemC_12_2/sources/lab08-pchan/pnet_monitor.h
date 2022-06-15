////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_monitor.h                                               //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET monitor                                                 //
// Notes       : PNET monitor is a "singleton" class in that you can          //
//               instantiate it only once. This is so that all components     //
//               know about it without needing to pass around a pointer.      //
//               Public methods are:                                          //
//               void insert(unsigned a, unsigned d) - store unit "a" data "d"//
//               void erase (unsigned a, unsigned d) - erase unit "a" data "d"//
//               void summarize() - Summarize the state of the monitor        //
//               You are expected to use the monitor as a "scoreboard", that  //
//               is, to store expected data and then delete it as it arrives. //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_MONITOR_H
#define PNET_MONITOR_H

#include <set>
using namespace std;

class pnet_monitor {
public:
  pnet_monitor ( ) ;
  virtual ~pnet_monitor ( ) ;
  void insert ( unsigned addr, unsigned data ) ;
  void erase  ( unsigned addr, unsigned data ) ;
  void summarize ( ) ;
  static pnet_monitor * monitor;
protected:
  unsigned            * m_counter ;
  multiset<unsigned> ** m_multiset ;
private:
  pnet_monitor ( const pnet_monitor& ) { }
} ;

#endif
