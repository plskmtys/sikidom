#include <cmath>
#include <istream>
#include <algorithm>

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

Sikidom &Sikidom::Forgat(const double rad, const Pont &center = Pont(0, 0)) {
  p.Forgat(rad, center);
  if(kp != center) kp.Forgat(rad, center);
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
  return ((kp.dst(Pont(0,0)) - kp.dst(p)) > r);
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
  Pont B = p;
  B.Forgat(2.0*M_PI/3.0, kp);
  Pont C = p;
  C.Forgat(4.0*M_PI/3.0, kp);

  return IsOnTriangle(P, A, B, C);
}

bool Haromszog::Kivul(const std::size_t r = 1) const {
  if(r >= dst(kp, Pont(0,0))) return false;
  Pont circle_closest;
  const double alpha = atan2(kp.gety(), kp.getx());
  circle_closest = Pont(r * cos(alpha), r * sin(alpha));

  return !Rajtavan(circle_closest);
}

void Haromszog::Write(std::ostream &os) const {
  os << "{Haromszog, " << kp << ", " << p << "}\n";
}

void Haromszog::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
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
  if(P == kp || P == p) return true;
  Pont a = p - kp;
  Pont b = P - kp;
  double dot_product = a.getx() * b.getx() + a.gety() * b.gety();
  double length_a = sqrt(a.getx() * a.getx() + a.gety() * a.gety());
  double length_b = sqrt(b.getx() * b.getx() + b.gety() * b.gety());
  const double angle = acos(dot_product / (length_a * length_b));
  Negyzet n_tmp(*this);
  Pont p_tmp(P);
  n_tmp.Forgat(angle, kp);
  p_tmp.Forgat(angle, kp);
  p_tmp.Mozgat(-kp.getx(), -kp.gety());
  n_tmp.Mozgat(-kp.getx(), -kp.gety());
  const double side_len = sqrt(2) * dst(kp,p);
  return (fabs(p_tmp.getx()) <= side_len / 2.0 &&
          fabs(p_tmp.gety()) <= side_len / 2.0);
}

bool Negyzet::Kivul(const std::size_t r) const {
  const Kor egysegkor(Pont(0,0), Pont(r,0));
  if(Rajtavan(Pont(0,0)) || egysegkor.Rajtavan(kp) || egysegkor.Rajtavan(p)) return false;
  Pont circle_closest;
  const double alpha = atan2(kp.gety(), kp.getx());
  circle_closest = Pont(r * cos(alpha), r * sin(alpha));

  return !Rajtavan(circle_closest);
}

void Negyzet::Write(std::ostream &os) const {
  os << "{Negyzet, " << kp << ", " << p << "}\n";
}

void Negyzet::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}


std::ostream &operator<<(std::ostream &os, const Negyzet &n) {
  n.Write(os);
  return os;
}

std::istream &operator>>(std::istream &is, Negyzet &n) {
  n.Read(is);
  return is;
}

bool IsOnTriangle1(const Pont& P, const Pont& A, const Pont& B, const Pont& C){
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
  const double epsilon = 0.00001;
  return (/*a >= 0 && b >= 0 && c >= 0 &&*/ (std::abs(a + b + c - 1) <= epsilon));
}

bool IsOnTriangle(const Pont& P, const Pont& A, const Pont& B, const Pont& C) {
    // vektorok kiszamitasa
    Pont v0 = { C.getx() - A.getx(), C.gety() - A.gety() };
    Pont v1 = { B.getx() - A.getx(), B.gety() - A.gety() };
    Pont v2 = { P.getx() - A.getx(), P.gety() - A.gety() };

    // keresztszorzatok kiszamitasa
    double dot00 = v0.getx() * v0.getx() + v0.gety() * v0.gety();
    double dot01 = v0.getx() * v1.getx() + v0.gety() * v1.gety();
    double dot02 = v0.getx() * v2.getx() + v0.gety() * v2.gety();
    double dot11 = v1.getx() * v1.getx() + v1.gety() * v1.gety();
    double dot12 = v1.getx() * v2.getx() + v1.gety() * v2.gety();

    // koordinatak kiszamitasa
    double invDenom = 1.0 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    // Check if point is in or on triangle
    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

