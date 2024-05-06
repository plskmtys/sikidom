#include "pont.h"
#include <cmath>

Pont::Pont(const Pont& p){
  x = p.x;
  y = p.y;
}

Pont& Pont::operator=(const Pont& p){
  x = p.x;
  y = p.y;
  return *this;
}

Pont& Pont::setx(double _x){
  x = _x;
  return *this;
}

Pont& Pont::sety(double _y){
  y = _y;
  return *this;
}

double Pont::getx() const { return x; }

double Pont::gety() const { return y; }

bool Pont::operator==(const Pont& p) const { return (x == p.x && y == p.y); }

bool Pont::operator!=(const Pont& p) const { return !(*this==p); }

Pont& Pont::Mozgat(const double _x, const double _y){
  x += _x;
  y += _y;
  return *this;
}

Pont& Pont::Forgat(const double deg, const Pont& center = Pont(0, 0)){
  //origo koruli forgatas:
  //Rv = x =  x*cos ß - y*sin ß
  //     y =  x*sin ß + y*cos ß

  x -= center.x;
  y -= center.y;
  setx(getx() * cos(deg) - gety() * sin(deg));
  sety(gety() * sin(deg) + gety() * cos(deg));
  x += center.x;
  y += center.y;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Pont& p){
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

std::istream& operator>>(std::istream& is, Pont& p){
  char ch;
  is >> ch >> p.x >> ch >> p.y >> ch;
  return is;
}

double Pont::dst(const Pont& p) const { return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y)); }

double AbsCrossProd(const Pont& A1, const Pont& A2, const Pont& B1, const Pont& B2){
  return fabs((A2.getx() - A1.getx()) * (B2.gety() - B1.gety()) - (A2.gety() - A1.gety()) * (B2.getx() - B1.getx()));
}
