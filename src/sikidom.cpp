#include <cmath>
#include <cstdlib>
#include <istream>

#include "sikidom.h"
#include "pont.h"
#include "matek.h"

//Sikidom tagfuggvenyei

Sikidom::Sikidom(const Sikidom& s){
  kp = s.kp;
  p = s.p;
}

Sikidom& Sikidom::operator=(const Sikidom& s){
  kp = s.kp;
  p = s.p;
  return *this;
}

Sikidom& Sikidom::Mozgat(const int _x, const int _y){
  kp.setx(kp.getx() + _x);
  kp.sety(kp.gety() + _y);
  p.setx(kp.getx() + _x);
  p.sety(p.gety() + _y);
  return *this;
}

Sikidom& Sikidom::Forgat(const double deg, const Pont& center = Pont(0,0)){
  p.Forgat(deg, center);
  kp.Forgat(deg, center);
  return *this;
}

bool Sikidom::Tartalmazza(const int r) const {
  const Pont origo(0, 0);
  return ( kp.dst(origo) + kp.dst(p) <= r); 
}

//Kor tagfuggvenyei

double Kor::Terulet() const {
  double r = kp.dst(p);
  return (r*r*M_PI);
}

bool Kor::Rajtavan(const Pont& _p) const {
  return (kp.dst(_p) <= kp.dst(p));
}

std::ostream& operator<<(std::ostream& os, const Kor& k){
  os << "kör, kp: " << k.kp << " egy pontja: " << k.p;
  return os;
}

std::istream& operator>>(std::istream& is, const Kor& k){

}

//Haromszog tagfuggvenyei

double Haromszog::Terulet() const {
  const double R = kp.dst(p); //köréírt kör sugara
  return (R*R*sqrt(3.0)/4.0);
}
 
bool Haromszog::Rajtavan(const Pont& P) const {
  // https://en.wikipedia.org/wiki/Barycentric_coordinate_system

  // t = terulet
  // a = |PB x PA| / 2t
  // b = |PC x PA| / 2t
  // c = |PA x PB| / 2t
  // return ( a >= 0 && b >= 0 && c >= 0)
  
  const double t = Terulet();
  const Pont A = p;
  Haromszog temp(*this);
  temp.Forgat(120, temp.kp);
  const Pont B = temp.p;
  temp.Forgat(120, temp.kp);
  const Pont C = temp.p;

  const double a = AbsCrossProd(P, B, P, A) / (2*t);
  const double b = AbsCrossProd(P, C, P, A) / (2*t);
  const double c = AbsCrossProd(P, A, P, B) / (2*t);
  return ( a >= 0 && b >= 0 && c >= 0 );
}
 
std::ostream& operator<<(std::ostream& os, const Haromszog& h) {
  os << "háromszög, kp: " << h.kp << "egy pontja: " << h.p;
  return os;
}

std::istream& operator>>(std::istream&, Haromszog&){

}

//Negyzet tagfuggvenyei

double Negyzet::Terulet() const {
  const double R = kp.dst(p);
  return (R*R*2);
}
  
bool Negyzet::Rajtavan(const Pont& P) const {
  const double angle = asin((p.gety()-kp.gety())/(p.getx()-kp.getx()));
  Negyzet n0(*this);
  Pont p0(P);
  n0.Forgat(angle, kp);
  p0.Forgat(angle, kp);
  p0.Mozgat(-kp.getx(), -kp.gety());
  n0.Mozgat(-kp.getx(), -kp.gety());
  return (fabs(n0.kp.getx()) >= fabs(p0.getx()) && fabs(n0.kp.gety()) >= fabs(P.gety()));
}

std::ostream& operator<<(std::ostream& os, const Negyzet& n) {
  os << "négyzet, kp: " << n.kp << "egy pontja: " << n.p;
  return os;
}
 
std::istream& operator>>(std::istream&, Negyzet&) {

}
