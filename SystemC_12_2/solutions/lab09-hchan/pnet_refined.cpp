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
  p_cpu_tx_data_done = SC_LOGIC_0 ;
  if ( p_cpu_tx_data_ready != SC_LOGIC_1 )
    wait ( p_cpu_tx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_cpu_tx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  data = p_cpu_tx_data_value ;
  p_cpu_tx_data_done = SC_LOGIC_0 ;
  if ( p_cpu_tx_data_ready != SC_LOGIC_0 )
    wait ( p_cpu_tx_data_ready->negedge_event() ) ;
}

void pnet_refined::cpu_read_process ( )
{
  sc_lv<2> addr ;
  sc_lv<8> data ;
  pnet_frame frame ;
  while ( true )
  {
    cpu_read_protocol ( data ) ;
    if ( data[7] != SC_LOGIC_1 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU ADDRESS" << endl ;
      sc_assert ( false ) ;
    }
    addr = data(1,0) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(6) << sc_simulation_time()
           << " cycle: " << setw(6) << sc_delta_count()
           << " - " << name() << " rcvd cpu addr " << dec << addr.to_uint()
           << endl;
    cpu_read_protocol ( data ) ;
    if ( data[7] != SC_LOGIC_0 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU DATA" << endl ;
      sc_assert ( false ) ;
    }
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(6) << sc_simulation_time()
           << " cycle: " << setw(6) << sc_delta_count()
           << " - " << name() << " rcvd cpu data " << dec << data.to_uint()
           << endl;
    encode ( addr, data, frame ) ;
    if ( addr == this->addr )
    { // UPLOAD TO CPU
      cpu_fifo.write ( frame ) ;
    }
    else
    { // FORWARD TO NET
      net_fifo.write ( frame ) ;
    }
  }
}


// READ FRAME FROM INTERNAL CPU FIFO
// USE CPU WRITE PROTOCOL TO WRITE DATA BYTE

void pnet_refined::cpu_write_process ( )
{
  pnet_frame frame ;
  sc_lv<2> addr ; // not used
  sc_lv<8> data ;
  while ( true )
  {
    cpu_fifo.read ( frame ) ;
    decode ( frame, addr, data ) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(6) << sc_simulation_time()
           << " cycle: " << setw(6) << sc_delta_count()
           << " - " << name() << " send cpu data " << dec << data.to_uint()
           << endl;
    cpu_write_protocol ( data ) ;
  }
}

void pnet_refined::cpu_write_protocol ( const sc_lv<8> & data )
{
  p_cpu_rx_data_value = data ;
  p_cpu_rx_data_ready = SC_LOGIC_1 ;
  if ( p_cpu_rx_data_done != SC_LOGIC_1 )
    wait ( p_cpu_rx_data_done->posedge_event() ) ;
  if ( p_cpu_rx_data_done != SC_LOGIC_0 )
    wait ( p_cpu_rx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_cpu_rx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
}


// USE NET READ PROTOCOL TO READ FRAME
// WRITE FRAME TO INTERNAL CPU/NET FIFOs

void pnet_refined::net_read_protocol ( pnet_frame & frame )
{
  p_net_tx_data_done = SC_LOGIC_0 ;
  if ( p_net_tx_data_ready != SC_LOGIC_1 )
    wait ( p_net_tx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_tx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  frame.high = p_net_tx_data_value ;
  p_net_tx_data_done = SC_LOGIC_0 ;
  if ( p_net_tx_data_ready != SC_LOGIC_0 )
    wait ( p_net_tx_data_ready->negedge_event() ) ;
  if ( p_net_tx_data_ready != SC_LOGIC_1 )
    wait ( p_net_tx_data_ready->posedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_tx_data_done = SC_LOGIC_1 ;
  wait ( 10, SC_NS ) ;
  frame.low = p_net_tx_data_value ;
  p_net_tx_data_done = SC_LOGIC_0 ;
  if ( p_net_tx_data_ready != SC_LOGIC_0 )
    wait ( p_net_tx_data_ready->negedge_event() ) ;
}

void pnet_refined::net_read_process ( )
{
  pnet_frame frame ;
  sc_lv<2> addr ;
  while ( true )
  {
    net_read_protocol ( frame ) ;
    addr = frame.high(5,4) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(6) << sc_simulation_time()
           << " cycle: " << setw(6) << sc_delta_count()
           << " - " << name() << " rcvd net frame " << frame
           << endl;
    if ( addr == this->addr )
    { // UPLOAD TO CPU
      cpu_fifo.write ( frame ) ;
    }
    else
    { // FORWARD TO NET
      net_fifo.write ( frame ) ;
    }
  }
}


// READ FRAME FROM INTERNAL NET FIFO
// USE NET WRITE PROTOCOL TO WRITE FRAME

void pnet_refined::net_write_process ( )
{
  pnet_frame frame ;
  while ( true )
  {
    net_fifo.read ( frame ) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(6) << sc_simulation_time()
           << " cycle: " << setw(6) << sc_delta_count()
           << " - " << name() << " send net frame " << frame
           << endl;
    net_write_protocol ( frame ) ;
  }
}

void pnet_refined::net_write_protocol ( const pnet_frame & frame )
{
  p_net_rx_data_value = frame.high ;
  p_net_rx_data_ready = SC_LOGIC_1 ;
  if ( p_net_rx_data_done != SC_LOGIC_1 )
    wait ( p_net_rx_data_done->posedge_event() ) ;
  if ( p_net_rx_data_done != SC_LOGIC_0 )
    wait ( p_net_rx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_rx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
  p_net_rx_data_value = frame.low ;
  p_net_rx_data_ready = SC_LOGIC_1 ;
  if ( p_net_rx_data_done != SC_LOGIC_1 )
    wait ( p_net_rx_data_done->posedge_event() ) ;
  if ( p_net_rx_data_done != SC_LOGIC_0 )
    wait ( p_net_rx_data_done->negedge_event() ) ;
  wait ( 10, SC_NS ) ;
  p_net_rx_data_ready = SC_LOGIC_0 ;
  wait ( 10, SC_NS ) ;
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
