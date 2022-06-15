////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1102waves.cpp                                              //
// Title       : Tracing Signal Waveforms                                     //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates tracing various types                           //
// Change Log  : 2019-11-13 mikep Changed VCD time unit from 1ns to 500ps     //
//               2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#define SC_INCLUDE_FX
#include "systemc.h"
#include <climits>
#include <cfloat>

SC_MODULE ( top ) {
  sc_trace_file *vcd_tf_pntr;
  bool            pbool         ; //  1
  char            pchar         ; //  8
  short           pshort        ; // 16
  int             pint          ; // 16
  long            plong         ; // 32
  long long       plongl        ; // 64
  float           pfloat        ; // 1E+37 1E-5
  double          pdouble       ; // 1E+37 1E-9
  long double     pldouble      ; // 1E+37 1E-9
  sc_bit          bit           ;
  sc_logic        logic         ;
  sc_bv       <4> bv4           ;
  sc_lv       <4> lv4           ;
  sc_int     <64> int64         ;
  sc_uint    <64> uint64        ;
  sc_bigint  <65> bigint65      ;
  sc_biguint <65> biguint65     ;
  sc_fixed  <5,3> fixed53       ;
  sc_ufixed <4,2> ufixed42      ;
  sc_fix          fix53         ;
  sc_ufix         ufix42        ;
  sc_clock        clock1        ;
  sc_fifo<int>    fifo1         ;
  sc_out<int>     out_p1        ;
  sc_signal<int>  signal1       ;
  sc_time         time          ;
  SC_CTOR ( top )
:
  pbool    (false),
  pchar    (0),
  pshort   (0),
  pint     (0),
  plong    (0),
  plongl   (0),
  pfloat   (0.0),
  pdouble  (0.0),
  pldouble (0.0),
  fix53   (sc_fix(5,3)), 
  ufix42  (sc_ufix(4,2)) ,
  clock1  ("clock1" ) ,
  fifo1   ("fifo1"   ) ,
  out_p1  ("out_p1"  ) ,
  signal1 ("signal1" )  
  {
    SC_THREAD ( top_thread ) ;
    out_p1 ( signal1 ) ;

    vcd_tf_pntr = sc_create_vcd_trace_file ( "EX1102waves" ) ;
    vcd_tf_pntr -> set_time_unit( 100, SC_PS );
    sc_trace ( vcd_tf_pntr, pbool    , "pbool"     ) ;
    sc_trace ( vcd_tf_pntr, pchar    , "pchar"     ) ;
    sc_trace ( vcd_tf_pntr, pshort   , "pshort"    ) ;
    sc_trace ( vcd_tf_pntr, pint     , "pint"      ) ;
    sc_trace ( vcd_tf_pntr, plong    , "plong"     ) ;
    sc_trace ( vcd_tf_pntr, pfloat   , "pfloat"    ) ;
    sc_trace ( vcd_tf_pntr, pdouble  , "pdouble"   ) ;
//  sc_trace ( vcd_tf_pntr, pldouble , "pldouble"  ) ; // no function match
    sc_trace ( vcd_tf_pntr, bit      , "bit"       ) ;
    sc_trace ( vcd_tf_pntr, logic    , "logic"     ) ;
    sc_trace ( vcd_tf_pntr, bv4      , "bv4"       ) ;
    sc_trace ( vcd_tf_pntr, lv4      , "lv4"       ) ;
    sc_trace ( vcd_tf_pntr, int64    , "int64"     ) ;
    sc_trace ( vcd_tf_pntr, uint64   , "uint64"    ) ;
    sc_trace ( vcd_tf_pntr, bigint65 , "bigint65"  ) ;
    sc_trace ( vcd_tf_pntr, biguint65, "biguint65" ) ;
    sc_trace ( vcd_tf_pntr, fixed53  , "fixed53"   ) ;
    sc_trace ( vcd_tf_pntr, ufixed42 , "ufixed42"  ) ;
    sc_trace ( vcd_tf_pntr, fix53    , "fix53"     ) ;
    sc_trace ( vcd_tf_pntr, ufix42   , "ufix42"    ) ;
    sc_trace ( vcd_tf_pntr, clock1   , "clock1"    ) ;
//  Error: (E519) wait() is only allowed in SC_THREADs and SC_CTHREADs:
//  sc_trace ( vcd_tf_pntr, fifo1    , "fifo1"     ) ; // 2.1 error
    sc_trace ( vcd_tf_pntr, signal1  , "signal1"   ) ;
    sc_trace ( vcd_tf_pntr, out_p1   , "out_p1"    ) ; //
//  sc_trace ( vcd_tf_pntr, time     , "time"      ) ; // no function match

  }

  void top_thread ( ) {

    wait ( 10, SC_NS ) ;
    vcd_tf_pntr -> write_comment ( "Now at 10 NS" ) ;

    pbool     = true      ;
    pchar     = SCHAR_MAX ;
    pshort    = SHRT_MAX  ;
    pint      = INT_MAX   ;
    plong     = LONG_MAX  ;
    plongl    = LLONG_MAX ;
    pfloat    = FLT_MAX   ;
    pdouble   = DBL_MAX   ;
    pldouble  = LDBL_MAX  ;
    bit       = 1         ;
    logic     = 'X'       ;
    bv4       = "0101"    ;
    lv4       = "01ZX"    ;
    int64     = LLONG_MAX ;
    uint64    = LLONG_MAX ;
    bigint65  = +1        ;
    biguint65 = +1        ;
    fixed53   = 0.75      ;
    ufixed42  = 0.75      ;
    fix53     = 0.75      ;
    ufix42    = 0.75      ;
    fifo1.write(INT_MAX)  ;
    signal1.write(INT_MAX)  ;
    time      = sc_time(DBL_MAX, SC_FS) ;

    wait ( 10, SC_NS ) ;
    vcd_tf_pntr -> write_comment ( "Now at 20 NS do delta cycles" ) ;
    pbool = false ;
    wait ( 0, SC_NS ) ;
    pbool = true  ;
    wait ( 0, SC_NS ) ;

    wait ( 10.5, SC_NS ) ;
    vcd_tf_pntr -> write_comment ( "Now at 30.5 NS check resolution" ) ;

    pbool    = false        ;
    pchar    = SCHAR_MIN    ;
    pshort   = SHRT_MIN     ;
    pint     = INT_MIN      ;
    plong    = LONG_MIN     ;
    plongl   = LLONG_MIN    ;
    pfloat   = FLT_EPSILON  ;
    pdouble  = DBL_EPSILON  ;
    pldouble = LDBL_EPSILON ;
    bit       = 0           ;
    logic     = 'Z'         ;
    bv4       = "1010"      ;
    lv4       = "XZ10"      ;
    int64     = LLONG_MIN   ;
    uint64    = LLONG_MIN   ;
    bigint65  = -1          ;
    biguint65 = -1          ;
    fixed53   = -1.0        ;
    ufixed42  = -1.0        ;
    fix53     = -1.0        ;
    ufix42    = -1.0        ;
    fifo1.write(INT_MIN)    ;
    signal1.write(INT_MIN)  ;
    time      = sc_time(DBL_EPSILON, SC_FS) ;


    wait ( 10, SC_NS ) ;
    sc_stop();
  }
} ;

int sc_main(int c, char **v) {
  top top1 ("top1") ;
  sc_start();
  return 0;
}

