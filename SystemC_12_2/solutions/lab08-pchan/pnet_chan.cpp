////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_chan.cpp                                                //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET channel                                                 //
// Notes       : The PNET channel takes data from its cpu and from the net,   //
//               and forwards it appropriately to either its cpu or the net.  //
//               This PNET channel implements methods that external processes //
//               use to read and write cpu and net data directly or through   //
//               ports connected to the channel.                              //
//               Thus this PNET channel is now a true SystemC channel.        //
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
, cpu_fifo    ( "cpu_fifo"      )
, net_fifo    ( "net_fifo"      )
, addr        ( (sc_lv<2>) addr )
{ }


// - EXTERNAL PROCESS WRITES CPU ADDR/DATA BYTES TO METHOD
// - METHOD WRITES FRAME TO INTERNAL CPU/NET FIFOs

void pnet_chan::cpu_write_function ( const sc_lv<8> & data )
{ 
  pnet_frame frame ;
  if ( data[7] == SC_LOGIC_1 )
  { // ADDRESS BYTE
    cpu_read_proc_addr = data(1,0) ;
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
             << " - " << name() << " rcvd cpu addr " << dec << cpu_read_proc_addr.to_uint()
             << endl;
  }
  else
  { // DATA BYTE
    if ( VERBOSITY > 1 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
             << " - " << name() << " rcvd cpu data " << dec << data.to_uint()
             << endl;
    encode ( cpu_read_proc_addr, data, frame ) ;
    if ( cpu_read_proc_addr == this->addr )
    { // UPLOAD TO CPU
      cpu_fifo.write ( frame ) ;
    }
    else
    { // FORWARD TO NET
      net_fifo.write ( frame ) ;
    }
  }
}


// - EXTERNAL PROCESS READS CPU DATA THROUGH METHOD
// - METHOD READS FRAME FROM INTERNAL CPU FIFO

void pnet_chan::cpu_read_function ( sc_lv<8> & data )
{
  sc_lv<2> addr ; // not used
  pnet_frame frame ;
  cpu_fifo.read ( frame ) ;
  decode ( frame, addr, data ) ;
  if ( VERBOSITY > 1 )
    cout << "time: "   << setw(5) << sc_simulation_time()
         << " cycle: " << setw(5) << sc_delta_count()
         << " - " << name() << " send cpu data " << dec << data.to_uint()
         << endl;
}


// - EXTERNAL PROCESS WRITES NET FRAME TO METHOD
// - METHOD WRITES FRAME TO INTERNAL CPU/NET FIFOs

void pnet_chan::net_write_function ( const pnet_frame & frame )
{
  sc_lv<2> addr ;
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


// - EXTERNAL PROCESS READS NET FRAME THROUGH METHOD
// - METHOD READS FRAME FROM INTERNAL NET FIFO

void pnet_chan::net_read_function ( pnet_frame & frame )
{
  net_fifo.read ( frame ) ;
  if ( VERBOSITY > 1 )
    cout << "time: "   << setw(5) << sc_simulation_time()
         << " cycle: " << setw(5) << sc_delta_count()
         << " - " << name() << " send net frame " << frame
         << endl;
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
