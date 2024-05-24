#include <cmath>
#include <istream>
#include <algorithm>

#include "pont.h"
#include "sikidom.h"
#include "kor.h"
#include "haromszog.h"
#include "negyzet.h"

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
