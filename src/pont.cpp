#include "pont.h"
#include <cmath>

Pont::Pont(const Pont &p) {
  x = p.x;
  y = p.y;
}

Pont &Pont::operator=(const Pont &p) {
  x = p.x;
  y = p.y;
  return *this;
}

Pont &Pont::setx(double _x) {
  x = _x;
  return *this;
}

Pont &Pont::sety(double _y) {
  y = _y;
  return *this;
}

double Pont::getx() const { return x; }

double Pont::gety() const { return y; }

Pont Pont::operator+(const Pont& b) const {
  return Pont(x + b.x, y + b.y);
}

Pont Pont::operator-(const Pont& b) const {
  return Pont(x - b.x, y - b.y);
}

bool Pont::operator==(const Pont &p) const { return (x == p.x && y == p.y); }

bool Pont::operator!=(const Pont &p) const { return !(*this == p); }

Pont &Pont::Mozgat(const double _x, const double _y) {
  x += _x;
  y += _y;
  return *this;
}

Pont &Pont::Forgat(const double rad, const Pont &center = Pont(0, 0)) {
  x -= center.x;
  y -= center.y;
  double new_x = getx() * cos(rad) - gety() * sin(rad);
  double new_y = getx() * sin(rad) + gety() * cos(rad);
  x = new_x + center.x;
  y = new_y + center.y;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Pont &p) {
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

/** @brief formatum: (x,y)
 */
std::istream &operator>>(std::istream &is, Pont &p) {
  char ch;
  if (is >> ch && ch == '(') {
    is >> p.x >> ch >> p.y >> ch;
  } else {
    is >> p.x >> ch >> p.y;
  }
  return is;
}

double Pont::dst(const Pont &p) const {
  return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

double dst(const Pont& a, const Pont& b){
  return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
}

double AbsCrossProd(const Pont &A1, const Pont &A2, const Pont &B1,
                    const Pont &B2) {
  return std::abs((A2.getx() - A1.getx()) * (B2.gety() - B1.gety()) -
              (A2.gety() - A1.gety()) * (B2.getx() - B1.getx()));
}
