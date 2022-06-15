////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX1003attr.cpp                                               //
// Title       : Managing Attributes                                          //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstration setting/getting attributes, getting collection //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"

SC_MODULE ( top ) {

  SC_CTOR ( top ) { }

  void end_of_elaboration ( ) {
    setAttributeBool   ("myBool"   , true  ) ;
    setAttributeInt    ("myInt"    , 1     ) ;
    setAttributeFloat  ("myFloat"  , 1.1   ) ;
    setAttributeString ("myString" , "one" ) ;
    getAttributeBool   ("myBool"   ) ;
    getAttributeInt    ("myInt"    ) ;
    getAttributeFloat  ("myFloat"  ) ;
    getAttributeString ("myString" ) ;
    getAttributeCltn ( ) ;
  }

  void setAttributeBool (const char *name, bool value) {
    sc_attribute <bool> *attrPointerBool =
      new sc_attribute <bool> ( name, value ) ;
    add_attribute ( *attrPointerBool ) ; // automatic upcast to sc_attr_base
  }

  void setAttributeInt (const char *name, int value) {
    sc_attribute <int> *attrPointerInt =
      new sc_attribute <int> ( name, value ) ;
    add_attribute ( *attrPointerInt ) ;
  }

  void setAttributeFloat (const char *name, float value) {
    sc_attribute <float> *attrPointerFloat =
      new sc_attribute <float> ( name, value ) ;
    add_attribute ( *attrPointerFloat ) ;
  }

  void setAttributeString (const char *name, const char *value) {
    sc_attribute <std::string> *attrPointerString =
      new sc_attribute <std::string> ( name, (std::string) value ) ;
    add_attribute ( *attrPointerString ) ;
  }

  void getAttributeBool (const char *name) {
    sc_attr_base *attrPointerBase = get_attribute ( name ) ;
    // manually downcast to templated version
    sc_attribute <bool> *attrPointerBool =
      DCAST <sc_attribute<bool> *> ( attrPointerBase ) ; 
    cout << attrPointerBase -> name() << " = "  // name() is func
         << attrPointerBool -> value  << endl ; // value NOT func
  }

  void getAttributeInt (const char *name) {
    sc_attr_base *attrPointerBase = get_attribute ( name ) ;
    sc_attribute <int> *attrPointerInt =
      DCAST <sc_attribute<int> *> ( attrPointerBase ) ; 
    cout << attrPointerBase -> name() << " = "
         << attrPointerInt  -> value  << endl ;
  }

  void getAttributeFloat (const char *name) {
    sc_attr_base *attrPointerBase = get_attribute ( name ) ;
    sc_attribute <float> *attrPointerFloat =
      DCAST <sc_attribute<float> *> ( attrPointerBase ) ; 
    cout << attrPointerBase  -> name() << " = "
         << attrPointerFloat -> value  << endl ;
  }

  void getAttributeString (const char *name) {
    sc_attr_base *attrPointerBase = get_attribute ( name ) ;
    sc_attribute <std::string> *attrPointerString =
      DCAST <sc_attribute<std::string> *> ( attrPointerBase ) ; 
    cout << attrPointerBase   -> name() << " = "
         << attrPointerString -> value  << endl ;
  }

  void getAttributeCltn () {
    sc_attr_cltn &attrCltn = attr_cltn() ;
    if ( attrCltn.size() ) {
      sc_attr_base **attrIterator = attrCltn.begin() ;
      while ( attrIterator != attrCltn.end() ) {
      //cout << (*attrIterator) -> name() << endl ;
        if ( sc_attribute <bool> *attrPointerBool =
          DCAST <sc_attribute<bool> *> (*attrIterator) ) 
          cout << (*attrIterator) -> name() << " = "
               << attrPointerBool -> value  << endl;
        else
        if ( sc_attribute <int> *attrPointerInt =
          DCAST <sc_attribute<int> *> (*attrIterator) ) 
          cout << (*attrIterator) -> name() << " = "
               <<  attrPointerInt -> value  << endl;
        else
        if ( sc_attribute <float> *attrPointerFloat =
          DCAST <sc_attribute<float> *> (*attrIterator) ) 
          cout << (*attrIterator)  -> name() << " = "
               << attrPointerFloat -> value  << endl;
        else
        if ( sc_attribute <std::string> *attrPointerString =
          DCAST <sc_attribute<std::string> *> (*attrIterator) ) 
          cout << (*attrIterator)   -> name() << " = "
               << attrPointerString -> value  << endl;
        else
          cout << "Unknown attribute type" << endl;
        ++attrIterator ;
      }
    }
  }

} ;

int sc_main ( int argc, char **argv ) {
  top top_inst ( "top_inst" ) ;
  sc_start ( ) ;
  return 0 ;
}


// myBool = 1
// myInt = 1
// myFloat = 1.1
// myString = one
// myBool = 1
// myInt = 1
// myFloat = 1.1
// myString = one
