////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : pnet_walker.cpp                                              //
// Project     : SystemC Language Fundamentals                                //
// Description : Hierarchy walker                                             //
// Change Log  : 2011-04-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
#include "pnet_walker.h"
#include <vector>
using namespace std;

pnet_walker::pnet_walker ( sc_module_name name )
: sc_module ( name )
{ }

void pnet_walker::start_of_simulation ( ) {
  listChildObjects ( sc_get_top_level_objects() ) ;
}

void pnet_walker::listChildObjects ( const vector<sc_object*> & childList,
                                     unsigned indent ) {
  if ( indent >= last.size() ) last.resize ( indent + 1 ) ;
  vector<sc_object*>::const_iterator object_iterator = childList.begin() ;
  while ( object_iterator != childList.end() ) {
    sc_object * child_pointer = *object_iterator ;
    for ( unsigned i = 1; i <= indent ; ++i )
      if ( last[i] )       cout << "  " ; else
      if ( i != indent )   cout << "| " ; else
                           cout << "|_" ;
    cout << child_pointer->name() << " : "
         << child_pointer->kind() << endl ;
    last[indent] = ( ( childList.end() - object_iterator )  == 1 ) ;
    if ( strcmp(child_pointer->kind(),"sc_module") == 0 )
      listChildObjects ( child_pointer->get_child_objects(), indent+1 ) ;
    ++object_iterator ;
  }
  last[indent] = false ;
}
