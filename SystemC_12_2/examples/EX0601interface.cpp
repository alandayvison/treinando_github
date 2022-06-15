////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0601interface.cpp                                          //
// Title       : Interface, Channels, and Ports                               //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates definition and use of interface, channel, port  //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

// my_interface.h
#include "systemc.h"
template <class T> class my_interface
: virtual public sc_interface {
public:
  virtual void write ( const T& ) = 0; // write new value
  virtual const T& read() const = 0; // read current value
};

// my_channel.h
#include "systemc.h"
//#include "my_interface.h"
template <class T> class my_channel
: public sc_channel,
  public my_interface<T> {
public:
  SC_CTOR (my_channel) {}
  void write ( const T& value ) { my_value = value; } // write new value
  const T& read() const { return my_value; } // read current value
protected:
  T my_value;
};

// my_port.h
#include "systemc.h"
//#include "my_interface.h"
template <class T> class my_port
: public sc_port<my_interface<T> > {
public:
  my_port<T>& operator= (const T& d)     // assignment operator
  { (*this) -> write(d); return *this; } // to write new value
  operator const T& () const    // cast operator to
  { return (*this) -> read(); } // read current value
};

// my_module.h
#include "systemc.h"
//#include "my_port.h"
SC_MODULE (my_module) {
  my_port<int> port ;
  SC_CTOR (my_module)
  { SC_THREAD(my_process); }
  void my_process () {
    data = 42;
    port = data ;
    data = 86;
    data = port ;
    cout << "data is " << data << endl; // 42
  }
protected:
  int data ;
};

// top.h
#include "systemc.h"
//#include "my_module.h"
//#include "my_channel.h"
SC_MODULE (top) {
  my_module module;
  my_channel<int> channel;
  SC_CTOR (top)
  : module  ("module"),
    channel ("channel")
  {
    module.port(channel);
  }
};

int sc_main(int argc, char **argv) {
  top top1("top1");
  sc_start();
  return 0;
}
