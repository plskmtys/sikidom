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

/** @brief formatum: "{Tipus, (kpX;kpY), (pX,pY)}\n"
 */
std::istream &operator>>(std::istream &is, Sikidom &s) {
  std::string tmp;
  is >> tmp;
  if (tmp[0] == '{') {
    tmp.erase(0, 1);
  }

  if (tmp == "kor,") {
    Kor k;
    is >> k;
    s = k;
  } else if (tmp == "haromszog,") {
    Haromszog h;
    is >> h;
    s = h;
  } else if (tmp == "negyzet,") {
    Negyzet n;
    is >> n;
    s = n;
  } else {
    throw "Nem lehet eldonteni, hogy milyen fajta sikidomot olvasunk be.";
  }

  return is;
}

Sikidom::~Sikidom() {}

// Kor tagfuggvenyei

double Kor::Terulet() const {
  double r = kp.dst(p);
  return (r * r * M_PI);
}

bool Kor::Rajtavan(const Pont &_p) const { return (kp.dst(_p) <= kp.dst(p)); }

std::ostream &operator<<(std::ostream &os, const Kor &k) {
  os << "kor, " << k.kp << ", " << k.p << '}';
  return os;
}

std::istream &operator>>(std::istream &is, Kor &k) {
  char ch;
  is >> k.kp >> ch >> k.p >> ch;
  return is;
}

// Haromszog tagfuggvenyei

double Haromszog::Terulet() const {
  const double R = kp.dst(p); // köréírt kör sugara (a háromszög szabályos)
  return (R * R * sqrt(3.0) / 4.0);
}

bool Haromszog::Rajtavan(const Pont &P) const {
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

  const double a = AbsCrossProd(P, B, P, A) / (2 * t);
  const double b = AbsCrossProd(P, C, P, A) / (2 * t);
  const double c = AbsCrossProd(P, A, P, B) / (2 * t);
  return (a >= 0 && b >= 0 && c >= 0);
}

std::ostream &operator<<(std::ostream &os, const Haromszog &h) {
  os << "{haromszog, " << h.kp << ", " << h.p << '}';
  return os;
}

std::istream &operator>>(std::istream &is, Haromszog &h) {
  char ch;
  is >> h.kp >> ch >> h.p >> ch;
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

std::ostream &operator<<(std::ostream &os, const Negyzet &n) {
  os << "{negyzet, " << n.kp << ", " << n.p << '}';
  return os;
}

std::istream &operator>>(std::istream &is, Negyzet &n) {
  char ch;
  is >> n.kp >> ch >> n.p >> ch;
  return is;
}
