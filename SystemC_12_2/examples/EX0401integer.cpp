////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0401integer.cpp                                            //
// Title       : Example Integer Methods                                      //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate integer methods                                  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

int sc_main ( int argc, char *argv[] ) {

  sc_int<8> a = sc_int<8>(10) ; // constructor [00001010]
  sc_int<8> b = (sc_int<8>)9 ;  // converter   [00001001]
  sc_int<2> c = -1 ;            // operator=         [11]

  cout << "a = " << a.to_string(SC_OCT) << endl ; // 0o012
  cout << "b = " << b.to_string(SC_HEX) << endl ; // 0x09
  cout << "c = " << c.to_string(SC_DEC) << endl ; // -1

  cout << "a&b = " << (a&b) << endl ; // 8  ( 8 bits)
  cout << "a+b = " << (a+b) << endl ; // 19 ( 9 bits)
  cout << "a*b = " << (a*b) << endl ; // 90 (16 bits)

  cout << "a.length() = " << a.length() << endl ;                   // 8
  cout << "(a.bit(1),a.bit(0)) = " << (a.bit(1),a.bit(0)) << endl ; // 2
  cout << "(a[1],a[0]) = " << (a[1],a[0]) << endl ;                 // 2
  cout << "a.range(1,0) = " << a.range(1,0) << endl ;               // 2
  cout << "a(1,0) = " << a(1,0) << endl ;                           // 2

  c = sc_int<2>(a); cout << "c = " << c << endl ; // -2
  a = (sc_int<8>)c; cout << "a = " << a << endl ; // -2

  return 0 ;
}
