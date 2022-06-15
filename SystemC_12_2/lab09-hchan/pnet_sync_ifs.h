////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_sync_ifs.h                                              //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET sync get interface                                      //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_SYNC_IF_H
#define PNET_SYNC_IF_H

#include "systemc.h"

template <class T> class pnet_sync_write_if
: virtual public sc_interface
{
public:
  virtual unsigned num_free ( ) const = 0 ;
  virtual const sc_event & data_read_event ( ) const = 0 ;
  virtual void write ( const T & ) = 0 ;
  virtual bool nb_write ( const T & ) = 0 ;
} ;

template <class T> class pnet_sync_read_if
: virtual public sc_interface
{
public:
  virtual unsigned num_available ( ) const = 0 ;
  virtual const sc_event & data_written_event ( ) const = 0 ;
  virtual void read ( T & ) = 0 ;
  virtual bool nb_read ( T & ) = 0 ;
} ;

#endif