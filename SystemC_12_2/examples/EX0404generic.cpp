////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0404generic.cpp                                            //
// Title       : Inheriting the sc_generic_base Class                         //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates sc_generic_base inheritance                     //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

typedef struct my_data_t : sc_dt::sc_generic_base<my_data_t> {
  int m_val;
  my_data_t& operator=(const my_data_t& r) {m_val = r.m_val; return *this;}
  my_data_t& operator=(const int      & r) {m_val = r      ; return *this;}
  bool operator==(const my_data_t& r) {return m_val == r.m_val;}
  int length() const {return 8*sizeof(m_val);}
  uint64 to_uint64() const {return (uint64) m_val;}
  int64  to_int64() const {return (int64) m_val;}
  void to_sc_unsigned (sc_unsigned& u) const {u = m_val;}
  void to_sc_signed (sc_signed& s) const {s = m_val;}
} my_data_s, *my_data_p;

ostream& operator<<(ostream& o, const my_data_t& d)
{ return o << d.m_val; }
void sc_trace(sc_trace_file* tf,const my_data_t& d, const std::string& name )
  { sc_trace(tf,d.m_val,name); }

typedef struct my_frame_t : sc_dt::sc_generic_base<my_frame_t> {
  my_data_s hi,lo;
  my_frame_t& operator=(const my_frame_t& frame)
    {hi=frame.hi; lo=frame.lo; return *this;}
  bool operator==(const my_frame_t& frame)
    {return hi==frame.hi && lo==frame.lo;}
  int length() const {return hi.length()+lo.length();}
  uint64 to_uint64() const
  {return (hi.to_uint64()<<lo.length())+lo.to_uint64();}
  int64  to_int64() const
  {return (hi.to_int64()<<lo.length())+lo.to_int64();}
  void to_sc_unsigned (sc_unsigned& u) const
  {u=(hi.to_uint64()<<lo.length())+lo.to_uint64();}
  void to_sc_signed (sc_signed& s) const
  {s=(hi.to_int64()<<lo.length())+lo.to_int64();}
} my_frame_s, *my_frame_p ;

ostream& operator<<(ostream& o, const my_frame_s& f)
  { return o << f.hi << '/' << f.lo; }

void sc_trace ( sc_trace_file* tf, const my_frame_s& f, const std::string& name )
  { sc_trace(tf,f.hi,name+"_hi"); sc_trace(tf,f.lo,name+"_lo"); }

int sc_main ( int argc, char ** argv )
{
  my_frame_s my_frame1, my_frame2 ;
  my_frame1.hi=5;
  my_frame1.lo=-3;
  my_frame2=my_frame1;
  cout << "my_frame1 = " << my_frame1 << endl ; // my_frame1 = 5/-3
  cout << "my_frame2 = " << my_frame2 << endl ; // my_frame2 = 5/-3
  if (my_frame1==my_frame2)
    cout << "They are same." << endl ; // They are same.
  else
    cout << "They are diff." << endl ;
  sc_uint<64> uint64(my_frame1);
  sc_bv<64> bv64(uint64);
  cout << "bv64 = " << bv64 << endl; // bv64 = 0000000000000000000000000000010011111111111111111111111111111101
  return 0 ;
}


