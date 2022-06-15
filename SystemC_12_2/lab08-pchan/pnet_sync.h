////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_sync.h                                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET sync primitive channel                                  //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef PNET_SYNC_H
#define PNET_SYNC_H

#include "systemc.h"
#include "pnet_sync_ifs.h"

template <class T> class pnet_sync
: public sc_prim_channel
, public pnet_sync_write_if<T>
, public pnet_sync_read_if<T>
{
public:
  pnet_sync ( ) ;                              // constructor (default)
  explicit pnet_sync ( const char * name ) ;   // constructor (initialization)
  virtual ~pnet_sync ( ) ;                     // destructor
  unsigned num_free ( ) const ;                // (write IF) number free
  const sc_event & data_read_event ( ) const ; // (write IF) data read event
  void write ( const T & ) ;                   // (write IF) write (blocking)
  bool nb_write ( const T & ) ;                // (write IF) write (nonblocking)
  unsigned num_available ( ) const ;              // (read IF) number available
  const sc_event & data_written_event ( ) const ; // (read IF) data written
  void read ( T & ) ;                             // (read IF) read (blocking)
  bool nb_read ( T & ) ;                          // (read IF) read (nonblock)
  const char * kind ( ) const ;                   // (sc_object) kind
protected:
  void update() ;
  sc_event m_data_read_event ;
  sc_event m_data_written_event ;
  T m_write_data ;
  T m_read_data ;
  bool m_write_pending ;
  bool m_read_pending ;
  unsigned m_num_free ;
  unsigned m_num_available ;
private: // disable copy/assignment
  pnet_sync ( const pnet_sync<T> & ) ;
  pnet_sync & operator= ( const pnet_sync<T> & ) ;
} ;

// constructor (default)
template <class T> pnet_sync<T>::pnet_sync ( )
: m_write_pending ( false )
, m_read_pending  ( false )
, m_num_free      ( 1 )
, m_num_available ( 0 )
{ }

// constructor (initialization)
template <class T> pnet_sync<T>::pnet_sync ( const char * name )
: sc_prim_channel ( name  )
, m_write_pending ( false )
, m_read_pending  ( false )
, m_num_free      ( 1 )
, m_num_available ( 0 )
{ }

// destructor
template <class T> pnet_sync<T>::~pnet_sync ( ) { }

// pnet_sync_write_if<T>::num_free()
template <class T> unsigned pnet_sync<T>::num_free ( ) const {
  return m_num_free ;
}

// pnet_sync_write_if<T>::data_read_event()
template <class T> const sc_event & pnet_sync<T>::data_read_event ( ) const {
  return m_data_read_event ;
}

// pnet_sync_write_if<T>::nb_write()
template <class T> bool pnet_sync<T>::nb_write ( const T & data ) {
  if ( m_num_free == 0 ) return false ;
  m_write_data    = data ;
  m_num_free      = 0    ;
  m_write_pending = true ;
  request_update() ;
  return true ;
}

// pnet_sync_write_if<T>::write()
template <class T> void pnet_sync<T>::write ( const T & data ) {
  while ( m_num_free == 0 ) wait ( m_data_read_event ) ;
  sc_assert ( nb_write(data) ) ;
}

// pnet_sync_read_if<T>::num_available()
template <class T> unsigned pnet_sync<T>::num_available ( ) const {
  return m_num_available ;
}

// pnet_sync_read_if<T>::data_written_event()
template <class T> const sc_event & pnet_sync<T>::data_written_event ( ) const {
  return m_data_written_event ;
}

// pnet_sync_read_if<T>::nb_read()
template <class T> bool pnet_sync<T>::nb_read ( T & data ) {
  if ( m_num_available == 0 ) return false ;
  data            = m_read_data ;
  m_num_available = 0 ;
  m_read_pending  = true ;
  request_update() ;
  return true ;
}

// pnet_sync_read_if<T>::read()
template <class T> void pnet_sync<T>::read ( T & data ) {
  while ( m_num_available == 0 ) wait ( m_data_written_event ) ;
  sc_assert ( nb_read(data) ) ;
}

template <class T> const char * pnet_sync<T>::kind ( ) const {
  return "pnet_sync" ;
}

// now modify sync state
template <class T> void pnet_sync<T>::update() {
  if ( m_read_pending ) {
    // do something about m_read_pending
    // do something about m_num_free
    // do something about m_data_read_event
  }
  if ( m_write_pending ) {
    // do something about m_read_data
    // do something about m_write_pending
    // do something about m_num_available
    // do something about m_data_written_event
  }
}

#endif
