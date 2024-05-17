#include <cmath>
#include <istream>
#include <algorithm>

#include "pont.h"
#include "sikidom.h"

// Sikidom tagfuggvenyei

/**
 * Sikidom osztaly Copy konstruktora.
 *
 * @param s Referencia a lemasolando Sikidomra
 */
Sikidom::Sikidom(const Sikidom &s) {
  kp = s.kp;
  p = s.p;
}

/// @brief Sikidom osztaly egyenloseg operatora.
/// @param s 
/// @return Az egymásután fűzhető műveletek miatt Sikidom referencia.
Sikidom &Sikidom::operator=(const Sikidom &s) {
  kp = s.kp;
  p = s.p;
  return *this;
}

/** @brief Sikidom osztály mozgató függvénye.
 * A függvény elmozgatja a síkidomot az x és y értékekkel.
 * @param _x x tengely irányú mozgatás mértéke.
 * @param _y y tengely irányú mozgatás mértéke.
 * @return Referencia a mozgatott síkidomra.
 * 
*/
Sikidom &Sikidom::Mozgat(const int _x, const int _y) {
  kp.setx(kp.getx() + _x);
  kp.sety(kp.gety() + _y);
  p.setx(p.getx() + _x);
  p.sety(p.gety() + _y);
  return *this;
}

/** @brief Sikidom osztály forgató függvénye.
 * A függvény elforgatja a síkidomot <rad> radiánnal.
 * @param rad forgatás mértéke, radiánban.
 * @param center a forgatás középpontja.
 * @return Referencia a forgatott síkidomra.
*/
Sikidom &Sikidom::Forgat(const double rad, const Pont &center = Pont(0, 0)) {
  p.Forgat(rad, center);
  if(kp != center) kp.Forgat(rad, center);
  return *this;
}

/** @brief Sikidom osztály statikus factory függvénye.
 * A függvény létrehoz egy új síkidomot a megadott típus alapján.
 * @param s a létrehozandó síkidom típusa szöveg formátumban.
 * @return A létrehozott síkidomra mutató pointer.
*/
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

/** @brief Sikidom osztály beolvasó operátora.
 * A függvény beolvassa a síkidomot a megadott input streamből.
 * @param is a bemeneti stream.
 * @param sikidom a beolvasott síkidomra mutató pointer.
 * @return A bemeneti stream referenciája.
 * 
*/
std::istream& operator>>(std::istream& is, Sikidom** sikidom){
  std::string type;
  is >> type;
  delete *sikidom;
  *sikidom = Sikidom::createSikidom(type);
  (*sikidom)->Read(is);
  return is;
}

/** @brief Sikidom osztály kiíró operátora.
 * A függvény kiírja a síkidomot a megadott output streambe.
 * @param os a kimeneti stream.
 * @param sikidom a kiírandó síkidomra mutató pointer.
 * @return A kimeneti stream referenciája.
 * 
*/
std::ostream& operator<<(std::ostream& os, const Sikidom * const sikidom){
  sikidom->Write(os);
  return os;
}

/** @brief Sikidom osztály destruktora.
 * nincs dinamikusan foglalt adattag, tehát nem kell semmit felszabadítani.
*/
Sikidom::~Sikidom() {}

// Kor tagfuggvenyei

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

