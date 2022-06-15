////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2019 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_cpu.cpp                                                 //
// Project     : SystemC Language Fundamentals                                //
// Description : PNET CPU                                                     //
// Notes       : A PNET CPU writes address/data bytes to the PNET channel     //
//               and reads data bytes from the PNET channel.                  //
//               The CPU utilizes the PNET monitor as a "scoreboard".         //
//               This CPU communicates with the PNET channel though ports     //
//               connected to external fifo channels.                         //
// Change Log  : 2011-04-30 mikep Created.                                    //
//               2019-11-12 mikep Added local stable RNG                      //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_cpu.h"
#include "pnet_monitor.h"
#include <iomanip>
using namespace std;

extern unsigned SEED ;
extern unsigned VERBOSITY ;
extern unsigned TRANSACTIONS ;

static unsigned long int seed = SEED ;
int my_rand () { // RAND_MAX assumed to be 32767
  seed = seed * 1103515245 + 12345 ;
  return (unsigned int) (seed/65536) % 32768 ;
}

pnet_cpu::pnet_cpu ( sc_module_name name, unsigned addr )
: sc_module   ( name          )
, p_cpu_write ( "p_cpu_write" )
, p_cpu_read  ( "p_cpu_read"  )
, addr        ( addr          )
{
  SC_HAS_PROCESS ( pnet_cpu ) ;
  SC_THREAD ( cpu_write_process ) ; // Write bytes to cpu data output port
  SC_THREAD ( cpu_read_process  ) ; // Read bytes from cpu data input port
}
  
void pnet_cpu::cpu_write_process ( ) {
  unsigned addr ;
  unsigned data ;
  for ( unsigned i=0; i < TRANSACTIONS; ++i ) {
    addr = my_rand() & 0x3 ;
    data = my_rand() & 0x7F ;
    wait ( my_rand()%5, SC_NS ) ;
    if ( VERBOSITY > 0 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << "  send cpu addr " << dec << addr
           << endl;
    p_cpu_write.write ( (sc_lv<8>) (addr+128) ) ;
    wait ( my_rand()%5, SC_NS ) ;
    if ( VERBOSITY > 0 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << "  send cpu data " << dec << data
           << endl;
    p_cpu_write.write ( (sc_lv<8>) data ) ;
    pnet_monitor::monitor -> insert ( addr, data ) ;
  }
}

void pnet_cpu::cpu_read_process  ( ) {
  unsigned addr ;
  unsigned data ;
  sc_lv<8> temp ;
  while ( true ) {
    temp = p_cpu_read.read ( ) ;
    if ( temp[7] != SC_LOGIC_1 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU ADDRESS" << endl ;
      sc_assert ( false ) ;
    }
    addr = temp(1,0).to_uint() ;
    if ( VERBOSITY > 0 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << "  rcvd cpu addr " << dec << addr
           << endl;
    if ( addr != this->addr ) {
      cout << "ERROR: CPU RECEIVED INCORRECT ADDRESS" << endl ;
      sc_assert ( false ) ;
    }
    temp = p_cpu_read.read ( ) ;
    if ( temp[7] != SC_LOGIC_0 ) {
      cout << "ERROR: BYTES OUT OF ORDER - EXPECTED CPU DATA" << endl ;
      sc_assert ( false ) ;
    }
    data = temp.to_uint() ;
    if ( VERBOSITY > 0 )
      cout << "time: "   << setw(5) << sc_simulation_time()
           << " cycle: " << setw(5) << sc_delta_count()
           << " - " << name() << "  rcvd cpu data " << dec << data
           << endl;
    pnet_monitor::monitor -> erase ( addr, data ) ;
  }
}
