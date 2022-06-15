////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0402vector.cpp                                             //
// Title       : Example Vector Methods                                       //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrate vector methods                                   //
// Change Log  : 2019-11-14 mikep Added integer constructors                  //
//               2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

int sc_main ( int argc, char *argv[] ) {

  sc_bit   bit; sc_logic log;
  sc_bv<2> bv2; sc_lv<2> lv2;
  sc_bv<4> bv4; sc_lv<4> lv4;

  cout << ( bv4 = sc_bv<4>(10) ) << endl;            // 1010
  cout << ( lv4 = sc_lv<4>(10) ) << endl;            // 1010

  char unsigned c = '<';                             // 60 - 48
  cout << ( bv4 = sc_bv<4>(c) ) << endl;             // 1100
  cout << ( lv4 = sc_lv<4>(c) ) << endl;             // 1100

  cout << ( bv4 = "1010" ) << endl;                  // 1010
  cout << ( lv4 = "XZ10" ) << endl;                  // XZ10

  cout << ( bit = bv4.xor_reduce() ) << endl;        // 0
  cout << ( log = lv4.xor_reduce() ) << endl;        // X

  cout << ( bv2 = bv4(2,1) ) << endl;                // 01
  cout << ( lv2 = lv4(2,1) ) << endl;                // Z1

  cout << ( bv2 = bv4.range(2,1) ) << endl;          // 01
  cout << ( lv2 = lv4.range(2,1) ) << endl;          // Z1

  cout << ( bv2 = (bv4[2],bv4[1]) ) << endl;         // 01
  cout << ( lv2 = (lv4[2],lv4[1]) ) << endl;         // 01 [see note]

  cout << ( bv2 = (bv4.bit(2),bv4.bit(1)) ) << endl; // 01
  cout << ( lv2 = (lv4.bit(2),lv4.bit(1)) ) << endl; // 01 [see note]

  return 0 ;
}

