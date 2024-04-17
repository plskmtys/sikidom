#include <iostream>

#ifndef SOKSZOG_PONT_H
#define SOKSZOG_PONT_H

class Pont{
private:
  double x, y;
public:
  Pont(const double _x = 0, const double _y = 0): x(_x), y(_y){}

  Pont(const Pont&);

  Pont& operator=(const Pont&);

  Pont& setx(double);

  Pont& sety(double);

  double getx() const;

  double gety() const;

  bool operator==(const Pont&) const;

  bool operator!=(const Pont&) const;

  double dst(const Pont&) const;

  Pont& Mozgat(const double _x = 0, const double _y = 0);

  Pont& Forgat(const double, const Pont&);
  
  friend std::ostream& operator<<(std::ostream&, const Pont&);

  friend std::istream& operator>>(std::istream&, Pont&);
};

#endif
