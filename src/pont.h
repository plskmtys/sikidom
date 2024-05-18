#include <iostream>

#ifndef SIKIDOM_PONT_H
#define SIKIDOM_PONT_H

/** @brief Pont osztály
 *  A pontokat a síkon tárolja, x és y koordinátákkal.
 * 
 */
class Pont{
private:
  /** @brief Pont x koordinátája
   * 
  */
  double x;

  /** @brief Pont y koordinátája
   * 
  */
  double y;
public:
  Pont(const double _x = 0, const double _y = 0): x(_x), y(_y){}

  Pont(const Pont&);

  Pont& operator=(const Pont&);

  Pont& setx(double);

  Pont& sety(double);

  double getx() const;

  double gety() const;

  Pont operator+(const Pont&) const;

  Pont operator-(const Pont&) const;

  bool operator==(const Pont&) const;

  bool operator!=(const Pont&) const;

  double dst(const Pont&) const;

  Pont& Mozgat(const double _x = 0, const double _y = 0);

  Pont& Forgat(const double, const Pont&);
  
  friend std::ostream& operator<<(std::ostream&, const Pont&);

  friend std::istream& operator>>(std::istream&, Pont&);
};

double dst(const Pont& a, const Pont& b);

#endif //SIKIDOM_PONT_H
