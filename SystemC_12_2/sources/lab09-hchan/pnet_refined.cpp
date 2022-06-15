////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_refined.cpp                                             //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel has processes acting through ports to read //
//               and write bytes from and to the cpu and net transactors.     //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_refined.h"
#include <iomanip>
using namespace std;

extern unsigned VERBOSITY ;

pnet_refined::pnet_refined ( sc_module_name name, unsigned addr )
: sc_module   ( name            )
, p_cpu_tx_data_value ( "p_cpu_tx_data_value" )
, p_cpu_tx_data_ready ( "p_cpu_tx_data_ready" )
, p_cpu_tx_data_done  ( "p_cpu_tx_data_done"  )

, p_cpu_rx_data_value ( "p_cpu_rx_data_value" )
, p_cpu_rx_data_ready ( "p_cpu_rx_data_ready" )
, p_cpu_rx_data_done  ( "p_cpu_rx_data_done"  )

, p_net_tx_data_value ( "p_net_tx_data_value" )
, p_net_tx_data_ready ( "p_net_tx_data_ready" )
, p_net_tx_data_done  ( "p_net_tx_data_done"  )

, p_net_rx_data_value ( "p_net_rx_data_value" )
, p_net_rx_data_ready ( "p_net_rx_data_ready" )
, p_net_rx_data_done  ( "p_net_rx_data_done"  )
, cpu_fifo    ( "cpu_fifo"      )
, net_fifo    ( "net_fifo"      )
, addr        ( (sc_lv<2>) addr )
{
  SC_HAS_PROCESS ( pnet_refined ) ;
  SC_THREAD ( cpu_read_process  ) ;
  SC_THREAD ( cpu_write_process ) ;
  SC_THREAD ( net_read_process  ) ;
  SC_THREAD ( net_write_process ) ;
}


// USE CPU READ PROTOCOL TO READ ADDR/DATA BYTES
// WRITE FRAME TO INTERNAL CPU/NET FIFOs

void pnet_refined::cpu_read_protocol ( sc_lv<8> & data )
{

  // STUDENT DEFINES THIS METHOD

}

void pnet_refined::cpu_read_process ( )
{

  // STUDENT DEFINES THIS METHOD

}


// READ FRAME FROM INTERNAL CPU FIFO
// USE CPU WRITE PROTOCOL TO WRITE DATA BYTE

void pnet_refined::cpu_write_process ( )
{

  // STUDENT DEFINES THIS METHOD

}

void pnet_refined::cpu_write_protocol ( const sc_lv<8> & data )
{

  // STUDENT DEFINES THIS METHOD

}


// USE NET READ PROTOCOL TO READ FRAME
// WRITE FRAME TO INTERNAL CPU/NET FIFOs

void pnet_refined::net_read_protocol ( pnet_frame & frame )
{

  // STUDENT DEFINES THIS METHOD

}

void pnet_refined::net_read_process ( )
{

  // STUDENT DEFINES THIS METHOD

}


// READ FRAME FROM INTERNAL NET FIFO
// USE NET WRITE PROTOCOL TO WRITE FRAME

void pnet_refined::net_write_process ( )
{

  // STUDENT DEFINES THIS METHOD

}

void pnet_refined::net_write_protocol ( const pnet_frame & frame )
{

  // STUDENT DEFINES THIS METHOD

}


void pnet_refined::encode (
  const sc_lv<2> & addr, // encode address/data
  const sc_lv<8> & data,
      pnet_frame & frame // to frame
)
{
  sc_logic parity  = SC_LOGIC_1 ; // not implemented
  sc_logic encrypt = data.xor_reduce() ;
  sc_lv<3> operand = data(4,2) ;
  sc_lv<8> temp    = data ;
  for ( unsigned i=0; i < operand.to_uint(); ++i )
    temp(6,0) = ( temp[6] ^ temp[0], temp(6,1) );
  if ( encrypt == SC_LOGIC_1 )
    temp(6,0) = temp(6,0).reverse() ;
  frame.high = ( SC_LOGIC_1, ( parity, addr, temp(3,0) ) ) ;
  frame.low  = ( SC_LOGIC_0, ( encrypt, operand, temp(6,4) ) ) ;
}


void pnet_refined::decode (
  const pnet_frame & frame, // decode frame
          sc_lv<2> & addr,  // to address/data
          sc_lv<8> & data
)
{
  addr = frame.high(5,4) ;
  sc_lv<4> data30  = frame.high(3,0) ;
  sc_logic encrypt = frame.low[6] ;
  sc_lv<3> operand = frame.low(5,3) ;
  sc_lv<3> data64  = frame.low(2,0) ;
  data = (SC_LOGIC_0, data64, data30) ;
  if ( encrypt == SC_LOGIC_1 )
    data(6,0) = data(6,0).reverse() ;
  for ( unsigned i=0; i < operand.to_uint(); ++i )
    data = ( data(5,0), data[6] ^ data[5] ) ;
}
