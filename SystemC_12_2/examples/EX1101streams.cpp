////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1101streams.cpp                                            //
// Title       : Debugging SystemC with I/O Streams                           //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates interactively poking/peeking variables          //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_FX
#include "systemc.h"

SC_MODULE ( top ) {
  SC_CTOR ( top )
  {
    SC_THREAD ( top_thread ) ;
  }
  void top_thread ( ) {
    wait ( 10, SC_NS ) ;
    cout << endl ;
    cout << "name     : " << this->name         ( ) << endl ;
    cout << "basename : " << this->basename     ( ) << endl ;
    cout << "kind     : " << this->kind         ( ) << endl ;
    cout << "stamp    : " << sc_time_stamp      ( ) << endl ;
    cout << endl ;
    ifstream inp("EX1101streams.txt");
//  No 2.0.1 istream overload for sc_time
//  sc_time         time          ; cout << "Enter time      : " ; inp >> time      ; cout << "      time      = " << time      << endl ;
    sc_logic        logic         ; cout << "Enter logic     : " ; inp >> logic     ; cout << "      logic     = " << logic     << endl ;
    sc_bv       <4> bv4           ; cout << "Enter bv4       : " ; inp >> bv4       ; cout << "      bv4       = " << bv4       << endl ;
    sc_lv       <4> lv4           ; cout << "Enter lv4       : " ; inp >> lv4       ; cout << "      lv4       = " << lv4       << endl ;
    sc_int     <64> int64         ; cout << "Enter int64     : " ; inp >> int64     ; cout << "      int64     = " << int64     << endl ;
    sc_uint    <64> uint64        ; cout << "Enter uint64    : " ; inp >> uint64    ; cout << "      uint64    = " << uint64    << endl ;
    sc_bigint  <65> bigint65      ; cout << "Enter bigint65  : " ; inp >> bigint65  ; cout << "      bigint65  = " << bigint65  << endl ;
    sc_biguint <65> biguint65     ; cout << "Enter biguint65 : " ; inp >> biguint65 ; cout << "      biguint65 = " << biguint65 << endl ;
    sc_fixed  <5,3> fixed53       ; cout << "Enter fixed53   : " ; inp >> fixed53   ; cout << "      fixed53   = " << fixed53   << endl ;
    sc_ufixed <4,2> ufixed42      ; cout << "Enter ufixed42  : " ; inp >> ufixed42  ; cout << "      ufixed42  = " << ufixed42  << endl ;
    sc_fix  fix53  = sc_fix(5,3)  ; cout << "Enter fix53     : " ; inp >> fix53     ; cout << "      fix53     = " << fix53     << endl ;
    sc_ufix ufix42 = sc_ufix(4,2) ; cout << "Enter ufix42    : " ; inp >> ufix42    ; cout << "      ufix42    = " << ufix42    << endl ;
    cout << endl ;
    sc_stop();
  }
} ;

int sc_main(int c, char **v) {
  top top1 ("top1") ;
  sc_start();
  return 0;
}


// name     : top1
// basename : top1
// kind     : sc_module
// stamp    : 10 ns

// Enter logic     :       logic     = X
// Enter bv4       :       bv4       = 0101
// Enter lv4       :       lv4       = 01ZX
// Enter int64     :       int64     = -9223372036854775808
// Enter uint64    :       uint64    = 18446744073709551615
// Enter bigint65  :       bigint65  = -18446744073709551616
// Enter biguint65 :       biguint65 = 36893488147419103231
// Enter fixed53   :       fixed53   = -3.75
// Enter ufixed42  :       ufixed42  = 3.75
// Enter fix53     :       fix53     = -1.25
// Enter ufix42    :       ufix42    = 1.25

// SystemC: simulation stopped by user.


// SC simulation stopped by user.

// SystemC : SystemC stopped at time 10

// Some types use a base type stream overload
//  sc_logic
//  sc_bv      sc_proxy
//  sc_lv      sc_proxy
//  sc_int
//  sc_uint
//  sc_bigint  sc_signed
//  sc_biguint sc_unsigned
//  sc_fixed   sc_fxnum
//  sc_ufixed  sc_fxnum
