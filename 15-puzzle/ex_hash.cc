// Hash table for 15-puzzle
// Universidad Simon Bolivar, 2008.
// Author: Blai Bonet
// Last Revision: 05/19/08
// Modified by:

#include <iostream>
#include <iomanip>
#include <ext/hash_map>

#define HSTEP 1
#define VSTEP 4
#define LEFT   "L"
#define RIGHT  "R"
#define UP     "U"
#define DOWN   "D"


// bit representation for movements: LRUD
static unsigned m1_ = 3758005178, m2_ = 1467408382; // m1_ = 0101 1101 1101 1001 0111 1111 1111 1011
                                                    // m2_ = 0111 1111 1111 1011 0110 1110 1110 1010

struct state15_t {
  unsigned p1_, p2_;
  state15_t() : p1_(0), p2_(0) { for( int i = 7; i >= 0; --i ) { p1_ = p1_<<4; p1_ += i; p2_ = p2_<<4; p2_ += i+8; } }
  bool operator==( const state15_t &s ) const { return((p1_==s.p1_)&&(p2_==s.p2_)); }
  unsigned bpos() const
  {
    unsigned p = p1_;
    for( int i = 0; i < 8; ++i, p = p>>4 ) if( (p&0xF) == 0 ) return(i);
    p = p2_;
    for( int i = 0; i < 8; ++i, p = p>>4 ) if( (p&0xF) == 0 ) return(8+i);
    return((unsigned)-1);
  }
  // Helpers
  unsigned cont( unsigned p ) const { return( (p<8?(p1_>>(p<<2)):(p2_>>((p-8)<<2))) & 0xF ); }
  short allowed_steps() { unsigned bp = bpos(); return ( (bp<8?(m1_>>(bp<<2)):(m2_>>((bp-8)<<2))) & 0xF ); }
  void set( unsigned p, unsigned t ) { if( p < 8 ) p1_ = (p1_&~(0xF<<(p<<2)))|(t<<(p<<2)); else p2_ = (p2_&~(0xF<<((p-8)<<2)))|(t<<((p-8)<<2)); }

  // Movements
  void left() { unsigned bp = bpos(), t = cont(bp-HSTEP); set(bp-HSTEP, 0); set(bp, t); }
  void right() { unsigned bp = bpos(), t = cont(HSTEP+bp); set(HSTEP+bp,0); set(bp,t); }
  void up() { unsigned bp = bpos(), t = cont(bp-VSTEP); set(bp-VSTEP,0); set(bp,t); }
  void down() { unsigned bp = bpos(), t = cont(VSTEP+bp); set(VSTEP+bp,0); set(bp,t); }

  // Problem methods
  void successors() {}

  void print( std::ostream &os ) const
  {
    unsigned p = p1_;
    for( int i = 0; i < 16; ++i ) {
      os << std::setw(2) << (p&0xF) << ' ';
      p = p>>4;
      if( i%4 == 3 ) os << std::endl;
      if( i == 7 ) p = p2_;
    }
  }
};

inline std::ostream& operator<<( std::ostream &os, const state15_t &s ) { s.print(os); return(os); }

struct value_t;

class node_t {
public:
  char g_, h_;
  bool open_;
  value_t *prev_, *next_;  // to be used in the priority queue

  node_t( unsigned g = 0, unsigned h = 0, bool open = true ) : g_(g), h_(h), open_(open), prev_(0), next_(0) { }
  unsigned g() const { return(g_); }
  unsigned h() const { return(h_); }
  unsigned f() const { return(g_+h_); }
  bool open() const { return(open_); }
  bool closed() const { return(!open()); }
  value_t* prev() const { return(prev_); }
  value_t* next() const { return(next_); }
  void set_g( unsigned g ) { g_ = g; }
  void set_h( unsigned h ) { h_ = h; }
  void set_open( bool open = false ) { open_ = open; }
  void set_prev( value_t *prev ) { prev_ = prev; }
  void set_next( value_t *next ) { next_ = next; }
  void print( std::ostream &os ) const { os << "g=" << g() << ", h=" << h() << ", open=" << (open()?"true":"false"); }

protected:
};

inline std::ostream& operator<<( std::ostream &os, const node_t &n ) { n.print(os); return(os); }

struct value_t : public std::pair<const state15_t,node_t> {
  void link( value_t *n ) { n->second.next_ = second.next_; if( second.next_ ) second.next_->second.prev_ = n; second.next_ = n; n->second.prev_ = this; }
  void unlink() { if( second.next_ ) second.next_->second.prev_ = second.prev_; if( second.prev_ ) second.prev_->second.next_ = second.next_; }
};

namespace __gnu_cxx {
  template<> class hash<state15_t> {
  public:
    size_t operator()( const state15_t &s ) const { return(s.p1_^s.p2_); }
  };
};

class hash_t : public __gnu_cxx::hash_map<state15_t,node_t> { };  // class
hash_t hash; // hash instance

class priority_queue_t {
protected:
  size_t maxsz_;
  value_t *array_;
public:
  priority_queue_t( size_t maxsz ) : maxsz_(maxsz) { array_ = new value_t[maxsz_]; }
  virtual ~priority_queue_t() { delete[] array_; }
  value_t *first();
  void insert( value_t *n ) { array_[n->second.f()].link(n); }
  void reorder( value_t *n, int newg );
  void print( std::ostream &os ) const
  {
    for( size_t i = 0; i < maxsz_; ++i ) {
      for( value_t *v = array_[i].second.next_; v != 0; v = v->second.next_ ) {
        os << v->first << v->second << std::endl;
      }
    }
  }
};

int
main( int argc, char **argv )
{
  state15_t state;
  node_t node(10,5,true);
  priority_queue_t pq(100);

  std::cout << "sizeof(state15_t)=" << sizeof(state15_t)
            << ", sizeof(node_t)=" << sizeof(node_t)
            << std::endl << std::endl;

  state.down(); state.down(); state.down(); state.right(); state.right(); state.right();
  std::cout << state.allowed_steps() << std::endl << std::endl;

  hash.insert( std::make_pair(state,node) );
  hash_t::iterator it = hash.find(state);
  std::cout << (*it).first << (*it).second << std::endl << std::endl;
  pq.insert((value_t*)&*it);

//   state.right();
//   state.right();
//   state.right();
//   state.down();
//   state.down();
//   state.down();
//   state.right();
  state.left();
  node.set_g(node.g());
  node.set_open(false);
  hash.insert( std::make_pair(state,node) );
  it = hash.find(state);
  std::cout << (*it).first << (*it).second << std::endl << std::endl;
  pq.insert((value_t*)&*it);

  std::cout << "hash size = " << hash.size() << std::endl << std::endl;;

  std::cout << "priority queue:" << std::endl;
  pq.print(std::cout);

  return(0);
}


