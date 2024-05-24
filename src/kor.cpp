#include "pont.h"
#include "sikidom.h"
#include "kor.h"
#include <cmath>
#include <cstddef>
#include <iostream>

/** @brief Kor területét számoló függvény.
 * A kiszamitas modja: r^2 * pi
 * @return A kör területe.
 * 
*/
double Kor::Terulet() const {
  double r = kp.dst(p);
  return (r * r * M_PI);
}

/** @brief Kor Rajtavan függvény.
 * A függvény eldönti, hogy egy pont rajta van-e a körön.
 * @param _p a vizsgált pont.
 * @return true, ha a pont rajta van a körön, egyébként false.
 * 
*/
bool Kor::Rajtavan(const Pont &_p) const { return (kp.dst(_p) <= kp.dst(p)); }

/** @brief Kor kiíró függvény.
 * A függvény kiírja a kör adatait a megadott output streambe.
 * @param os a kimeneti stream.
 * 
*/
void Kor::Write(std::ostream &os) const {
  os << "{Kor, " << kp << ", " << p << "}\n";
}

/** @brief Kor beolvasó függvény.
 * A függvény beolvassa a kör adatait a megadott input streamből.
 * @param is a bemeneti stream.
 * 
*/
void Kor::Read(std::istream &is) {
  char ch;
  is >> kp >> ch >> p >> ch;
}

/** @brief Kor kivül függvény.
 * Eldönti, hogy a kör kívül van-e egy adott sugarú, origo középpontú körön.
 * @param r a kör sugara.
*/
bool Kor::Kivul(const std::size_t r) const  {
  return ((kp.dst(Pont(0,0)) - kp.dst(p)) > r);
}