#include <cmath>
#include <istream>

#include "pont.h"
#include "sikidom.h"

// Sikidom tagfuggvenyei

Sikidom::Sikidom(const Sikidom &s) {
  kp = s.kp;
  p = s.p;
}

Sikidom &Sikidom::operator=(const Sikidom &s) {
  kp = s.kp;
  p = s.p;
  return *this;
}

Sikidom &Sikidom::Mozgat(const int _x, const int _y) {
  kp.setx(kp.getx() + _x);
  kp.sety(kp.gety() + _y);
  p.setx(kp.getx() + _x);
  p.sety(p.gety() + _y);
  return *this;
}

Sikidom &Sikidom::Forgat(const double deg, const Pont &center = Pont(0, 0)) {
  p.Forgat(deg, center);
  kp.Forgat(deg, center);
  return *this;
}

bool Sikidom::Tartalmazza(const int r) const {
  const Pont origo(0, 0);
  return (kp.dst(origo) + kp.dst(p) <= r);
}


Sikidom* Sikidom::createSikidom(const std::string& s) {
  std::string type(s);
  if(type[0] == '{') {
      type.erase(0, 1);
  }
  Sikidom* sikidom;
  if (type == "Kor,") {
    sikidom = new Kor;
  } else if (type == "Haromszog,") {
    sikidom = new Haromszog;
  } else if (type == "Negyzet,") {
    sikidom = new Negyzet;
  } else {
    throw "Unknown object type";
  }
  return sikidom;
}

std::istream& operator>>(std::istream& is, Sikidom* sikidom){
  sikidom->Read(is);
  return is;
}

std::ostream& operator<<(std::ostream& os, const Sikidom * const sikidom){
  sikidom->Write(os);
  return os;
}

Sikidom::~Sikidom() {}

// Kor tagfuggvenyei

double Kor::Terulet() const {
  double r = kp.dst(p);
  return (r * r * M_PI);
}

bool Kor::Rajtavan(const Pont &_p) const { return (kp.dst(_p) <= kp.dst(p)); }

void Kor::Write(std::ostream &os) const {
  os << "{Kor, " << kp << ", " << p << "}\n";
}

void Kor::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}

bool Kor::Kivul(const std::size_t r) const  {
  return (kp.dst(p) + kp.dst(Pont(0,0)) > r);
}

std::ostream &operator<<(std::ostream &os, const Kor &k) {
  k.Write(os);
  return os;
}

std::istream &operator>>(std::istream &is, Kor &k) {
  k.Read(is);
  return is;
}

// Haromszog tagfuggvenyei

double Haromszog::Terulet() const {
  const double R = kp.dst(p); // köréírt kör sugara (a háromszög szabályos)
  return (R * R * sqrt(3.0) / 4.0);
}

bool Haromszog::Rajtavan(const Pont &P) const {
  const Pont A = p;
  Haromszog temp(*this);
  temp.Forgat(120, temp.kp);
  const Pont B = temp.p;
  temp.Forgat(120, temp.kp);
  const Pont C = temp.p;

  return IsOnTriangle(P, A, B, C);
}

void Haromszog::Write(std::ostream &os) const {
  os << "{Haromszog, " << kp << ", " << p << "}\n";
}

void Haromszog::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}

bool Haromszog::Kivul(const std::size_t r) const {
  return true;
}

std::ostream &operator<<(std::ostream &os, const Haromszog &h) {
  h.Write(os);
  return os;
}

std::istream &operator>>(std::istream &is, Haromszog &h) {
  h.Read(is);
  return is;
}

// Negyzet tagfuggvenyei

double Negyzet::Terulet() const {
  const double R = kp.dst(p);
  return (R * R * 2);
}

bool Negyzet::Rajtavan(const Pont &P) const {
  const double angle = asin((p.gety() - kp.gety()) / (p.getx() - kp.getx()));
  Negyzet n_tmp(*this);
  Pont p_tmp(P);
  n_tmp.Forgat(angle, kp);
  p_tmp.Forgat(angle, kp);
  p_tmp.Mozgat(-kp.getx(), -kp.gety());
  n_tmp.Mozgat(-kp.getx(), -kp.gety());
  return (fabs(n_tmp.kp.getx()) >= fabs(p_tmp.getx()) &&
          fabs(n_tmp.kp.gety()) >= fabs(P.gety()));
}

void Negyzet::Write(std::ostream &os) const {
  os << "{Negyzet, " << kp << ", " << p << "}\n";
}

void Negyzet::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}

bool Negyzet::Kivul(const std::size_t r) const {
  return true;
}

std::ostream &operator<<(std::ostream &os, const Negyzet &n) {
  n.Write(os);
  return os;
}

std::istream &operator>>(std::istream &is, Negyzet &n) {
  n.Read(is);
  return is;
}

bool IsOnTriangle(const Pont& P, const Pont& A, const Pont& B, const Pont& C){
  // https://en.wikipedia.org/wiki/Barycentric_coordinate_system

  // t = terulet
  // a = |PB x PA| / 2t
  // b = |PC x PA| / 2t
  // c = |PA x PB| / 2t
  // return ( a >= 0 && b >= 0 && c >= 0)

  const double terulet = 0.5 * std::abs((A.getx()*(B.gety()-C.gety()) 
                                        + B.getx()*(C.gety()-A.gety())
                                        + C.getx()*(A.gety()-B.gety())));

  const double a = AbsCrossProd(P, B, P, A) / (2 * terulet);
  const double b = AbsCrossProd(P, C, P, A) / (2 * terulet);
  const double c = AbsCrossProd(P, A, P, B) / (2 * terulet);
  return (a >= 0 && b >= 0 && c >= 0);
}
