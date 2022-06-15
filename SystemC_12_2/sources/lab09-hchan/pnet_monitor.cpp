////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_monitor.cpp                                             //
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

#include "pnet_monitor.h"
#include <cassert>
#include <iostream>

extern unsigned NODES ;

pnet_monitor * pnet_monitor::monitor = 0;

pnet_monitor::pnet_monitor ( )
{
  assert ( monitor == 0 ) ;
  m_counter = new unsigned [NODES] ;
  m_multiset = new multiset<unsigned> * [NODES] ;
  for ( unsigned i=0; i < NODES; ++i ) {
    m_multiset[i] = new multiset<unsigned> ;
    m_counter[i] = 0 ;
  }
  monitor = this ;
}

pnet_monitor::~pnet_monitor ( ) {
  for ( unsigned i=0; i < NODES; ++i )
    delete m_multiset[i] ;
  delete [] m_multiset ;
  delete [] m_counter ;
} 

void pnet_monitor::insert ( unsigned addr, unsigned data ) {
  m_multiset[addr] -> insert ( data ) ;
  ++m_counter[addr] ;
}

void pnet_monitor::erase  ( unsigned addr, unsigned data ) {
  multiset<unsigned>::iterator iter = m_multiset[addr] -> find ( data ) ;
  if ( iter == m_multiset[addr]->end() )
    cout << "MONITOR ERROR: Unit " << addr
         << " received data " << data
         << " not sent!" << endl ;
  else
    m_multiset[addr] -> erase ( iter ) ;
}

void pnet_monitor::summarize ( ) {
  for ( unsigned i=0; i < NODES; ++i ) {
    cout << "To unit: "      << i
         << ", trans sent: " << dec << m_counter[i]
         << ", trans rcvd: " << dec << m_counter[i] - m_multiset[i]->size() ;
    if ( !m_multiset[i]->empty() ) {
      cout << ", Missing data:" ;
      multiset<unsigned>::iterator iter = m_multiset[i]->begin();
      while (iter != m_multiset[i]->end() ) {
        cout << " " << *iter << flush ;
        ++iter ;
      }
    }
    cout << endl ;
  }
}
