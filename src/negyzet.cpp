#include "negyzet.h"
#include <cmath>
#include <iostream>
#include "kor.h"
// Negyzet tagfuggvenyei

/** @brief Negyzet területét számoló függvény.
 * A kiszamitas modja: R^2 * 2
 * @return A négyzet területe.
 * 
*/
double Negyzet::Terulet() const {
  const double R = kp.dst(p);
  return (R * R * 2);
}

/** @brief Negyzet Rajtavan függvény.
 * A függvény eldönti, hogy egy pont rajta van-e a négyzeten.
 * @param P a vizsgált pont.
 * @return true, ha a pont rajta van a négyzeten, egyébként false.
 * 
*/
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

/** @brief Negyzet Kivul függvény.
 * Eldönti, hogy a négyzet kívül van-e egy adott sugarú, origo középpontú körön.
 * @param r a kör sugara.
 * @return true, ha a négyzet kívül van a körön, egyébként false.
 * 
*/
bool Negyzet::Kivul(const std::size_t r) const {
  const Kor egysegkor(Pont(0,0), Pont(r,0));
  if(Rajtavan(Pont(0,0))
    || egysegkor.Rajtavan(kp)
    || egysegkor.Rajtavan(p))
    {  return false; }
  Pont circle_closest;
  const double alpha = atan2(kp.gety(), kp.getx());
  circle_closest = Pont(r * cos(alpha), r * sin(alpha));

  return !Rajtavan(circle_closest);
}

/** @brief Negyzet kiíró függvény.
 * A függvény kiírja a négyzet adatait a megadott output streambe.
 * @param os a kimeneti stream.
 * 
*/
void Negyzet::Write(std::ostream &os) const {
  os << "{Negyzet, " << kp << ", " << p << "}\n";
}

/** @brief Negyzet beolvasó függvény.
 * A függvény beolvassa a négyzet adatait a megadott input streamből.
 * @param is a bemeneti stream.
 * 
*/
void Negyzet::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}