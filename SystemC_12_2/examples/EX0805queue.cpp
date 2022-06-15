////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// (c) Copyright 2011 Cadence Design Systems, Inc. All Rights Reserved.       //
//                                                                            //
// File name   : EX0805queue.cpp                                              //
// Title       : Example Building Primitive Channels                          //
// Project     : SystemC Language Fundamentals                                //
// Description : Demonstrates a user-defined primitive channel                //
// Change Log  : 2011-03-30 mikep Created.                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "systemc.h"
template <class T> class my_queue_put_if : virtual public sc_interface {
public:
  virtual bool is_ok_to_put() const = 0 ;
  virtual const sc_event & ok_to_put() const = 0 ;
  virtual void put(const T &) = 0 ;
  virtual bool nb_put(const T &) = 0 ;
} ;

#include "systemc.h"
template <class T> class my_queue_get_if : virtual public sc_interface {
public:
  virtual bool is_ok_to_get() const = 0 ;
  virtual const sc_event & ok_to_get() const = 0 ;
  virtual T get() = 0 ;
  virtual bool nb_get(T &) = 0 ;
} ;

typedef enum {FIFO, LIFO} my_policy_t;

#include "systemc.h"
// #include "my_queue_put_if.h"
// #include "my_queue_get_if.h"
#include <deque>
using namespace std;
template <class T> class my_queue
: public my_queue_put_if<T>,
  public my_queue_get_if<T>,
  public sc_prim_channel
{
public: // interface
  explicit my_queue ( my_policy_t policy=FIFO )
  : sc_prim_channel(sc_gen_unique_name("my_queue")) { init ( 16, policy ); }
  explicit my_queue ( unsigned size, my_policy_t policy=FIFO )
  : sc_prim_channel(sc_gen_unique_name("my_queue")) { init ( size, policy ); }
  explicit my_queue ( char *name, unsigned size=16, my_policy_t policy=FIFO )
  : sc_prim_channel(name) { init ( size, policy ); }
  virtual ~my_queue() {}
  bool is_ok_to_put() const { return m_queue.size() < m_size; }
  const sc_event& ok_to_put() const { return m_ok_to_put; }
  void put(const T &);
  bool nb_put(const T &);
  bool is_ok_to_get() const { return m_queue.size() != 0; }
  const sc_event &  ok_to_get() const  { return m_ok_to_get; }
  T get ();
  bool nb_get(T &);
  const char* kind() const { return "my_queue"; }
  void register_port(sc_port_base&, const char*) ;
  operator T() { return get(); }
  my_queue<T>& operator= ( const T& a ) { put(a); return *this; }
  unsigned size() const { return m_size; }
  unsigned used() const { return m_queue.size(); }
protected:
  void init ( unsigned, my_policy_t ) ;
  void update() ;
  deque<T> m_queue ;
  unsigned m_size ;
  my_policy_t m_policy;
  sc_event m_ok_to_put ;
  sc_event m_ok_to_get ;
  T m_put_data, m_get_data;
  bool m_need_to_put, m_need_to_get;
  sc_port_base *m_put_port, *m_get_port;
private: // disable
  my_queue ( const my_queue<T>& ) ;
  my_queue& operator= ( const my_queue<T>& ) ;
} ;

// nonblocking put
template <class T> bool my_queue<T>::nb_put ( const T & data ) {
  if ( !is_ok_to_put() ) return false ;
  m_put_data = data ;
  if ( !m_need_to_put ) {
    m_need_to_put = true ;
    request_update() ;
  }
  return true ;
}

// blocking put
template <class T> void my_queue<T>::put ( const T & data ) {
  while ( !is_ok_to_put() ) wait ( ok_to_put() ) ;
  sc_assert ( nb_put(data) ) ;
}

// nonblocking get
template <class T> bool my_queue<T>::nb_get ( T & data ) {
  if ( !is_ok_to_get() ) return false ;
  if ( !m_need_to_get ) {
    if ( m_policy == FIFO ) m_get_data = m_queue.front() ;
    if ( m_policy == LIFO ) m_get_data = m_queue.back() ;
    m_need_to_get = true ;
    request_update() ;
  }
  data = m_get_data ;
  return true ;
}

// blocking get
template <class T> T my_queue<T>::get () {
  while ( !is_ok_to_get() ) wait ( ok_to_get() ) ;
  T data ;
  sc_assert ( nb_get(data) ) ;
  return data ;
}

// now modify queue state
template <class T> void my_queue<T>::update() {
  if ( m_need_to_put ) {
    m_queue.push_back ( m_put_data ) ;
    m_need_to_put = false ;
    m_ok_to_get.notify(SC_ZERO_TIME) ;
  }
  if ( m_need_to_get ) {
    if ( m_policy == FIFO ) m_queue.pop_front() ;
    if ( m_policy == LIFO ) m_queue.pop_back() ;
    m_need_to_get = false ;
    m_ok_to_put.notify(SC_ZERO_TIME) ;
  }
}

// enforce single-writer / single-reader policy
template <class T> void my_queue<T>::register_port ( sc_port_base &port, const char *if_typename ) {
  if ( string(if_typename) == typeid(my_queue_put_if<T>).name() ) {
    sc_assert ( m_put_port = 0 ) ;
    m_put_port = &port ;
  }
  if ( string(if_typename) == typeid(my_queue_get_if<T>).name() ) {
    sc_assert ( m_get_port = 0 ) ;
    m_get_port = &port ;
  }
}

// offload initialization duties from constructors
template <class T> void my_queue<T>::init ( unsigned size, my_policy_t policy ) {
  m_size        = size   ;
  m_policy      = policy ;
  m_need_to_put = false  ;
  m_need_to_get = false  ;
  m_put_port    = 0      ;
  m_get_port    = 0      ; 
}


#include "systemc.h"
// #include "my_queue.h"
SC_MODULE ( top ) {
  my_queue<int> q;
  void process() ;
  SC_CTOR ( top )
  : q("q",4,FIFO)
  { SC_THREAD(process); }
};

void top::process() {
  for (unsigned i=1; i<=4; ++i) {
    q.put(i);
    wait ( SC_ZERO_TIME ) ;
    cout << "data is " << i << " used " << q.used() << endl;
  }
  cout << "success is " << boolalpha << q.nb_put(5) << endl;
  int data;
  for (unsigned i=1; i<=4; ++i) {
    data = q.get();
    wait ( SC_ZERO_TIME ) ;
    cout << "data is " << data << " used " << q.used() << endl;
  }
  cout << "success is " << boolalpha << q.nb_get(data) << endl;
}

int sc_main(int argc, char **argv) {
  top top1("top1");
  sc_start();
  return 0;
}
