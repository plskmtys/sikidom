#include "haromszog.h"
#include <cmath>
#include <iostream>

// Haromszog tagfuggvenyei

/** @brief Haromszog területét számoló függvény.
 * A kiszamitas modja: R^2 * 3 * sqrt(3) / 4
 * @return A háromszög területe.
 * 
*/
double Haromszog::Terulet() const {
  const double R = kp.dst(p); // köréírt kör sugara (a háromszög szabályos)
  return (R * R * 3.0 * sqrt(3.0) / 4.0);
}

/** @brief Haromszog Rajtavan függvény.
 * A függvény eldönti, hogy egy pont rajta van-e a háromszögön.
 * @param P a vizsgált pont.
 * @return true, ha a pont rajta van a háromszögön, egyébként false.
 * 
*/
bool Haromszog::Rajtavan(const Pont &P) const {
  const Pont A = p;
  Pont B = p;
  B.Forgat(2.0*M_PI/3.0, kp);
  Pont C = p;
  C.Forgat(4.0*M_PI/3.0, kp);

  return IsOnTriangle(P, A, B, C);
}

/** @brief Haromszog Kivul függvény.
 * Eldönti, hogy a háromszög kívül van-e egy adott sugarú, origo középpontú körön.
 * @param r a kör sugara.
 * @return true, ha a háromszög kívül van a körön, egyébként false.
 * 
*/
bool Haromszog::Kivul(const std::size_t r = 1) const {
  if(r >= dst(kp, Pont(0,0))) return false;
  Pont circle_closest;
  const double alpha = atan2(kp.gety(), kp.getx());
  circle_closest = Pont(r * cos(alpha), r * sin(alpha));

  return !Rajtavan(circle_closest);
}

/** @brief Haromszog kiíró függvény.
 * A függvény kiírja a háromszög adatait a megadott output streambe.
 * @param os a kimeneti stream.
 * 
*/
void Haromszog::Write(std::ostream &os) const {
  os << "{Haromszog, " << kp << ", " << p << "}\n";
}

/** @brief Haromszog beolvasó függvény.
 * A függvény beolvassa a háromszög adatait a megadott input streamből.
 * @param is a bemeneti stream.
 * 
*/
void Haromszog::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}

/** @brief IsOnTriangle függvény.
 * A függvény eldönti, hogy egy pont rajta van-e egy háromszögön.
 * @param P a vizsgált pont.
 * @param A háromszög egyik csúcsa.
 * @param B háromszög másik csúcsa.
 * @param C háromszög harmadik csúcsa.
 * @return true, ha a pont rajta van a háromszögön, egyébként false.
 * @details A kiszamitas modja:
 * https://en.wikipedia.org/wiki/Barycentric_coordinate_system#Determining_location_with_respect_to_a_triangle
*/
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

    // pont a haromszogon belul van, ha a feltetelek teljesulnek
    return (u >= 0) && (v >= 0) && (u + v <= 1);
}