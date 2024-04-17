#include <cstddef>
#include <iostream>
#include <istream>
#include "pont.h"

#ifndef SIKIDOM_SIKIDOM_H
#define SIKIDOM_SIKIDOM_H

class Sikidom{
protected:
  /** @brief Középpont.
   */
  Pont kp;
  
  /** @brief A síkidom egy csúcsa.
   */
  Pont p;

  //enum Type{kor, haromszog, negyzet};
public:
  /** @brief konstruktor.
   */
  Sikidom(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)): kp(_kp), p(_p) {}

  /** @brief Másoló konstruktor.
   * @param masik Sokszög, amiből átmásoljuk a pontokat.
   */
  Sikidom(const Sikidom&);

  /** @brief Értékadó operátor.
   * @param rhs Az = jobb oldalán álló sokszög.
   */
  Sikidom& operator=(const Sikidom&);

  Pont getkp() const { return kp; }

  Pont getp() const { return p; }

  bool Tartalmazza(const int) const;
  
  /** @brief Egy sokszög mozgatását teszi lehetővé.
   * @param _x x tengely irányú mozgatás mértéke.
   * @param _y y tengely irányú mozgatás mértéke.
   */
  Sikidom& Mozgat(const int _x, const int _y);

  /** @brief Egy sokszög forgatását teszi lehetővé.
   * @param deg forgatás mértéke, fokban.
   */
  Sikidom& Forgat(const double, const Pont&);

  /** @brief A sokszög területét adja vissza.
   */
  virtual double Terulet() const;
  
  /** @brief Megadja, hogy két sokszög milyen arányban fedi egymást. 0 és 1 közötti értékkel tér vissza.
   * @param masik A másik sokszög, amivel összehasonlítjuk.
   */
  //virtual double Fedi(const Sikidom&) const;

  virtual bool Rajtavan(const Pont&) const;

  friend std::ostream& operator<<(std::ostream&, const Sikidom&);

  friend std::istream& operator>>(std::istream&, Sikidom&);

  virtual ~Sikidom() = 0;
};

class Kor: public Sikidom{
public:
  Kor(Pont _kp, Pont _p): Sikidom(_kp, _p) {}
  
  double Terulet() const override;

  bool Rajtavan(const Pont&) const override;
  
  friend std::ostream& operator<<(std::ostream&, const Kor&);

  friend std::istream& operator>>(std::istream&, Kor&);

  ~Kor() override {}
};

class Haromszog: public Sikidom{
public:
  Haromszog(Pont _kp, Pont _p): Sikidom(_kp, _p) {}

  double Terulet() const override;
  
  bool Rajtavan(const Pont&) const override;
  
  friend std::ostream& operator<<(std::ostream&, const Haromszog&);
  
  friend std::istream& operator>>(std::istream&, Haromszog&);

  ~Haromszog() override {}
};

class Negyzet: public Sikidom{
public:
  Negyzet(Pont _kp, Pont _p): Sikidom(_kp, _p) {}
  
  double Terulet() const override;
  
  bool Rajtavan(const Pont&) const override;

  friend std::ostream& operator<<(std::ostream&, const Negyzet&);
  
  friend std::istream& operator>>(std::istream&, Negyzet&);

  ~Negyzet() override {}
};

#endif // !SIKIDOM_SIKIDOM_H
