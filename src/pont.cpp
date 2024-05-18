#include "pont.h"
#include <cmath>
#include <stdexcept>

/** @brief Pont osztály másoló konstruktora.
 * @param p másolandó pont
 * 
*/
Pont::Pont(const Pont &p) {
  x = p.x;
  y = p.y;
}

/** @brief Pont osztály értékadó operátora.
 * @param p másolandó pont
 * @return *this
 * 
*/
Pont &Pont::operator=(const Pont &p) {
  x = p.x;
  y = p.y;
  return *this;
}

/** @brief Pont osztály x koordinátájának beállítása.
 * @param _x beállítandó x koordináta
 * @return *this
 * 
*/
Pont &Pont::setx(double _x) {
  x = _x;
  return *this;
}

/** @brief Pont osztály y koordinátájának beállítása.
 * @param _y beállítandó y koordináta
 * @return *this
 * 
*/
Pont &Pont::sety(double _y) {
  y = _y;
  return *this;
}

/** @brief Pont osztály x koordinátájának lekérdezése.
 * @return x koordináta értéke
 * 
*/
double Pont::getx() const { return x; }

/** @brief Pont osztály y koordinátájának lekérdezése.
 * @return y koordináta értéke
 * 
*/
double Pont::gety() const { return y; }

/** @brief Pont osztály összeadó operátora.
 * @param b a másik pont
 * @return az összeg
 * 
*/
Pont Pont::operator+(const Pont& b) const {
  return Pont(x + b.x, y + b.y);
}

/** @brief Pont osztály kivonó operátora.
 * @param b a másik pont
 * @return a különbség
 * 
*/
Pont Pont::operator-(const Pont& b) const {
  return Pont(x - b.x, y - b.y);
}

/** @brief Pont osztály egyenlőség operátora.
 * @param p a másik pont
 * @return igaz, ha a két pont koordinátái egyenlők, egyébként hamis.
 * 
*/
bool Pont::operator==(const Pont &p) const { return (x == p.x && y == p.y); }

/** @brief Pont osztály egyenlőtlenség operátora.
 * @param p a másik pont
 * @return igaz, ha a két pont koordinátái nem egyenlők, egyébként hamis.
 * 
*/
bool Pont::operator!=(const Pont &p) const { return !(*this == p); }

/** @brief Pont osztály mozgató metódusa.
 * @param _x x irányú elmozdulás
 * @param _y y irányú elmozdulás
 * @return *this
 * 
*/
Pont &Pont::Mozgat(const double _x, const double _y) {
  x += _x;
  y += _y;
  return *this;
}

/** @brief Pont osztály forgató metódusa.
 * @param rad forgatás szöge radiánban
 * @param center a forgatás középpontja
 * @return *this
 * 
*/
Pont &Pont::Forgat(const double rad, const Pont &center = Pont(0, 0)) {
  x -= center.x;
  y -= center.y;
  double new_x = getx() * cos(rad) - gety() * sin(rad);
  double new_y = getx() * sin(rad) + gety() * cos(rad);
  x = new_x + center.x;
  y = new_y + center.y;
  return *this;
}

/** @brief Pont osztály kiíró operátora.
 * @param os output stream referencia
 * @param p a kiírandó pont
 * @return output stream referencia
 * 
*/
std::ostream &operator<<(std::ostream &os, const Pont &p) {
  os << '(' << p.x << ',' << p.y << ')';
  return os;
}

/** @brief Pont osztály beolvasó operátora.
 * formátumok: "(x,y)" vagy "x,y".
 * @param is input stream referencia
 * @param p a beolvasandó pont
 * @return input stream referencia
 */
std::istream &operator>>(std::istream &is, Pont &p) {
  char ch;
  is >> std::ws >> ch;
  if (ch == '(') {
    is >> p.x;
    is >> std::ws >> ch;
    if (ch == ',') {
      is >> p.y;
      is >> std::ws >> ch;
      if (ch == ')') {
        return is;
      }
    }
  } else {
    is.putback(ch);
    is >> p.x >> ch;
    if (ch == ',') {
        is >> p.y;
        return is;
    }
  }

  throw(std::runtime_error("nem (x,y) vagy x,y formaban adta meg a koordinatakat."));
}

/** @brief Pont osztály távolság számító metódusa.
 * @param p a másik pont
 * @return a két pont távolsága
 * 
*/
double Pont::dst(const Pont &p) const {
  return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
}

/** @brief két pont közötti távolság számító függvény.
 * @param a egyik pont
 * @param b másik pont
 * @return a két pont távolsága
 * 
*/
double dst(const Pont& a, const Pont& b){
  return sqrt((a.getx() - b.getx()) * (a.getx() - b.getx()) + (a.gety() - b.gety()) * (a.gety() - b.gety()));
}
