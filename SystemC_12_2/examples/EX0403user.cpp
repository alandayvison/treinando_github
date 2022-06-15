////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0403user.cpp                                               //
// Title       : Defining Your Own Data Type                                  //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate a user data type                                 //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

// make it easy on ourself
typedef int my_data_t;

typedef struct my_frame_t {
  my_data_t hi, lo ;
  my_frame_t& operator=(const my_frame_t& frame)
    { hi=frame.hi; lo=frame.lo; return *this; }
  bool operator==(const my_frame_t& frame)
    { return hi==frame.hi && lo==frame.lo ; }
} my_frame_s, *my_frame_p ;

ostream& operator<<(ostream& o, const my_frame_s& frame)
  { return o << frame.hi << '/' << frame.lo; }

void sc_trace ( sc_trace_file* tf, const my_frame_s& frame, const std::string& name )
  { sc_trace(tf,frame.hi,name+"_hi"); sc_trace(tf,frame.lo,name+"_lo"); }

SC_MODULE ( test ) {
  sc_out <my_frame_s> p_out ;
  sc_in  <my_frame_s> p_in  ;
  sc_signal <my_frame_s> signal ;
  SC_CTOR  ( test )
  : p_out  ( "p_out"  )
  , p_in   ( "p_in"   )
  , signal ( "signal" )
  { SC_THREAD ( produce ) ;
    SC_THREAD ( consume ) ;
    (*this)(signal,signal);
  }
  my_frame_s frame ;
  void produce() {
     frame.hi =  5 ;
     frame.lo = -3 ;
    p_out -> write ( frame ) ;
  }
  void consume() {
    my_frame_s frame ;
    wait(1,SC_NS);
    frame = p_in -> read() ;
    cout << "member frame = " << this->frame << endl ; // 5/-3
    cout << "local  frame = " <<       frame << endl ; // 5/-3
    if ( this->frame == frame )
      cout << "They are same." << endl ;
    else
      cout << "They are diff." << endl ;
  }
};


int sc_main ( int srgc, char ** argv )
{
  test test1 ( "test1" ) ;
  sc_start() ;
  return 0 ;
}

