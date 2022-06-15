////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_chan.cpp                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel implements processes to read and write cpu //
//               and net data through ports connected to external channels.   //
//               Thus this PNET channel is not yet a true SystemC channel.    //
//               This PNET channel uses SC_THREAD processes.                  //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_chan.h"
#include <iomanip>
using namespace std;

extern unsigned VERBOSITY ;

pnet_chan::pnet_chan ( sc_module_name name, unsigned addr )
: sc_module   ( name            )
, p_cpu_read  ( "p_cpu_read"    )
, p_cpu_write ( "p_cpu_write"   )
, p_net_read  ( "p_net_read"    )
, p_net_write ( "p_net_write"   )
, cpu_fifo    ( "cpu_fifo", 1   )
, net_fifo    ( "net_fifo", 1   )
, addr        ( (sc_lv<2>) addr )
{
  SC_HAS_PROCESS ( pnet_chan ) ;
  SC_THREAD ( cpu_read_process  ) ; // read bytes from cpu data input port
  SC_THREAD ( cpu_write_process ) ; // write bytes to cpu data output port 
  SC_THREAD ( net_read_process  ) ; // read bytes from net data input port
  SC_THREAD ( net_write_process ) ; // write bytes to net data output port
}


// READ ADDR/DATA BYTES FROM EXTERNAL CPU FIFO THROUGH INPUT PORT
// WRITE FRAME TO INTERNAL CPU/NET FIFOs

void pnet_chan::cpu_read_process ( )
{
  sc_lv<2> addr ;
  sc_lv<8> data ;
  pnet_frame frame ;
  while ( true )
  {
    p_cpu_read.read ( data ) ;
    if ( data[7] != SC_LOGIC_1 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU ADDRESS" << endl ;
      sc_assert ( false ) ;
    }
    addr = data(1,0) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << " rcvd cpu addr " << dec << addr.to_uint()
           << endl;
    p_cpu_read.read ( data ) ;
    if ( data[7] != SC_LOGIC_0 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU DATA" << endl ;
      sc_assert ( false ) ;
    }
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
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
// WRITE ADDR/DATA BYTES TO EXTERNAL CPU FIFO THROUGH OUTPUT PORT

void pnet_chan::cpu_write_process ( )
{
  pnet_frame frame ;
  sc_lv<2> addr ;
  sc_lv<8> data ;
  while ( true )
  {
    cpu_fifo.read ( frame ) ;
    decode ( frame, addr, data ) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << " send cpu addr " << dec << addr.to_uint()
           << endl;
    p_cpu_write.write ( (sc_lv<6>(32), addr) ) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << " send cpu data " << dec << data.to_uint()
           << endl;
    p_cpu_write.write ( data ) ;
  }
}


// READ FRAME FROM EXTERNAL NET FIFO THROUGH INPUT PORT
// WRITE FRAME TO INTERNAL CPU/NET FIFOs

void pnet_chan::net_read_process ( )
{
  pnet_frame frame ;
  sc_lv<2> addr ;
  while ( true )
  {
    p_net_read.read ( frame ) ;
    addr = frame.high(5,4) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
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
// WRITE FRAME TO EXTERNAL NET FIFO THROUGH OUTPUT PORT

void pnet_chan::net_write_process ( )
{
  pnet_frame frame ;
  while ( true )
  {
    net_fifo.read ( frame ) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << " send net frame " << frame
           << endl;
    p_net_write.write ( frame ) ;
  }
}


void pnet_chan::encode (
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


void pnet_chan::decode (
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
