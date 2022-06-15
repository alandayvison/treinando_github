////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0801fifo.cpp                                               //
// Title       : Example Using an sc_fifo Channel                             //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates use of an sc_fifo channel                       //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( producer ) {
  sc_fifo_out <int> fifo_out_port ;
  void producer_thread () {
    int int_var ;
    srand(1);
    int_var=rand(); cout << int_var << endl; fifo_out_port->write(int_var);
    int_var=rand(); cout << int_var << endl; fifo_out_port.write(int_var);
    while (fifo_out_port.num_free()!=0) {
      int_var=rand(); cout << int_var << endl;
      fifo_out_port.write(int_var) ; }
    cout << fifo_out_port.nb_write(rand()) << endl;
  }
  SC_CTOR ( producer )
  : fifo_out_port ( "fifo_out_port" )
  { SC_THREAD ( producer_thread ) ; }
} ;

SC_MODULE ( consumer ) {
  sc_port<sc_fifo_in_if<int> > fifo_in_port;
  void consumer_thread () {
    int int_var ;
    cout << fifo_in_port->read() << endl;
    while (fifo_in_port->num_available()!=0) {
      fifo_in_port->read(int_var);
      cout << int_var << endl;
    }
    cout << fifo_in_port->nb_read(int_var) << endl;
  }
  SC_CTOR ( consumer )
  : fifo_in_port ( "fifo_in_port" )
  { SC_THREAD ( consumer_thread ) ; }
} ;
 
SC_MODULE ( fifo_test ) {
  producer      producer_inst ;
  sc_fifo <int> fifo_inst     ;
  consumer      consumer_inst ;
  SC_CTOR ( fifo_test )
  :
    producer_inst ("producer_inst"),
    fifo_inst     ("fifo_inst", 4 ),
    consumer_inst ("consumer_inst") 
  {
    producer_inst(fifo_inst);
    consumer_inst(fifo_inst);
  }
} ;

int sc_main ( int argc, char **argv ) {
  fifo_test fifo_test_inst ("fifo_test_inst");
  sc_start ( ) ;
  return ( 0 ) ;
}
