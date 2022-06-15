#include "systemc.h"


SC_MODULE ( inv )
{
  sc_in  <bool> a ;
  sc_out <bool> z ;
  SC_CTOR ( inv )
  :
    a ( "a" ) ,
    z ( "z" )
  {
    SC_METHOD ( run ) ;
      sensitive << a ;
  }
  void run ( )
  {
   z = ! a ;
  }
} ;


SC_MODULE ( top ) {
  sc_signal <bool> a ;
  sc_signal <bool> z ;
  inv inv1 ;
  void test_thread ( ) ;
  SC_CTOR ( top )
  :
    a  ( "a"  ) ,
    z  ( "z"  ) ,
    inv1 ( "inv1" )
  {
    inv1.a ( a ) ;
    inv1.z ( z ) ;
    SC_THREAD ( test_thread ) ;
  }
} ;

void top::test_thread ( )
{
  cout << "SystemC says Hello!\n" ;
  a = 0 ; wait ( 10, SC_NS ) ;
  cout << "At " << sc_time_stamp() << ", a = " << a << ", z = " << z << endl;
  a = 1 ; wait ( 10, SC_NS ) ;
  cout << "At " << sc_time_stamp() << ", a = " << a << ", z = " << z << endl;
  a = 0 ; wait ( 10, SC_NS ) ;
  cout << "At " << sc_time_stamp() << ", a = " << a << ", z = " << z << endl;
}

int sc_main ( int argc, char ** argv ) {
  top top_i ( "top_i" ) ;
  sc_start() ;
  return 0 ;
}
