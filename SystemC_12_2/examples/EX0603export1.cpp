////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0603export1.cpp                                            //
// Title       : The sc_export Class                                          //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates normal connection to channel through ports      //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#ifndef MY_INTERFACE
#define MY_INTERFACE
class my_interface
: virtual public sc_interface
{
public:
  virtual const bool& read()=0;
  virtual void write(const bool&)=0;
};
#endif


#include "systemc.h"
//#include "interface.h"
class my_channel
: public sc_channel,
  public my_interface
{
public:
  SC_CTOR(my_channel){}
  virtual const bool& read() { return my_bool; }
  virtual void write(const bool&b) { my_bool = b; }
private:
  bool my_bool;
};


#include "systemc.h"
//#include "interface.h"
SC_MODULE(my_module) {
  sc_port<my_interface> p;
  SC_CTOR(my_module):p("p"){SC_THREAD(my_thread);}
  void my_thread() {
    p->write(false); wait(1,SC_NS); cout<<p->read()<<endl;
    p->write(true ); wait(1,SC_NS); cout<<p->read()<<endl;
    sc_stop();
  }
};


#include "systemc.h"
//#include "module.h"
//#include "channel.h"
SC_MODULE(top) {
  my_module m;
  my_channel c;
  SC_CTOR(top):m("m"),c("c"){m(c);}
};

int sc_main ( int argc, char **argv ) {
  top t("t");
  sc_start();
  return 0;
}
