#include "pont.h"
#include <cstddef>
#include <iostream>

#ifndef SIKIDOM_SIKIDOM_H
#define SIKIDOM_SIKIDOM_H

class Sikidom {
protected:
  /** @brief Középpont.
   */
  Pont kp;

  /** @brief A síkidom egy csúcsa.
   */
  Pont p;

  // enum Type{kor, haromszog, negyzet};/** @brief konstruktor.

  Sikidom(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : kp(_kp), p(_p) {}

public:
  /** @brief Másoló konstruktor.
   * @param masik Sokszög, amiből átmásoljuk a pontokat.
   */
  Sikidom(const Sikidom &);

  /** @brief Értékadó operátor.
   * @param rhs Az = jobb oldalán álló sokszög.
   */
  Sikidom &operator=(const Sikidom &);

  Pont getkp() const { return kp; }

  Pont getp() const { return p; }

  bool Tartalmazza(const int) const;

  /** @brief Egy sokszög mozgatását teszi lehetővé.
   * @param _x x tengely irányú mozgatás mértéke.
   * @param _y y tengely irányú mozgatás mértéke.
   */
  Sikidom &Mozgat(const int _x, const int _y);

  /** @brief Egy sokszög forgatását teszi lehetővé.
   * @param deg forgatás mértéke, fokban.
   */
  Sikidom &Forgat(const double, const Pont &);

  /** @brief A sokszög területét adja vissza.
   */
  virtual double Terulet() const = 0;

  virtual bool Rajtavan(const Pont &) const = 0;

  virtual void Write(std::ostream& os) const = 0;

  virtual void Read(std::istream& is) = 0;

  static Sikidom* createSikidom(const std::string& type);


  //virtual std::ostream &operator<<(const Sikidom &) = 0;


  //friend std::istream &operator>>(std::istream &, Sikidom *);

  virtual ~Sikidom() = 0;
};

class Kor : public Sikidom {
public:
  Kor(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Kor(const Kor &_k) : Sikidom(_k) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;
  
  //std::ostream &operator<<( const Kor &);


  //friend std::istream &operator>>(std::istream &, Kor &);

  ~Kor() override {}
};

class Haromszog : public Sikidom {
public:
  Haromszog(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Haromszog(const Haromszog &_h) : Sikidom(_h) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;

  //friend std::ostream &operator<<(std::ostream &, const Haromszog &);


  //friend std::istream &operator>>(std::istream &, Haromszog &);

  ~Haromszog() override {}
};

class Negyzet : public Sikidom {
public:
  Negyzet(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Negyzet(const Negyzet &_n) : Sikidom(_n) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;

  //friend std::ostream &operator<<(std::ostream &, const Negyzet &);


  //friend std::istream &operator>>(std::istream &, Negyzet &);

  ~Negyzet() override {}
};

#endif // !SIKIDOM_SIKIDOM_H
