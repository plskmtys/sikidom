#include "pont.h"
#include <cstddef>
#include <iostream>
#include <memory>

#ifndef SIKIDOM_SIKIDOM_H
#define SIKIDOM_SIKIDOM_H


/** @brief Sikidom osztály.
 * A sikidom osztály egy absztrakt osztály,
 * melynek leszármazottai a különböző (szabályos) síkidomokat reprezentálják,
 * középpontjukkal és egy csúcsukkal.
*/
class Sikidom {
protected:
  /** @brief Középpont.
   */
  Pont kp;

  /** @brief A síkidom egy csúcsa.
   */
  Pont p;

  /** @brief Sikidom konstruktor.
   * @param _kp középpont.
   * @param _p egy csúcs.
  */
  Sikidom(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : kp(_kp), p(_p) {}

public:
  Sikidom(const Sikidom &);

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

  virtual bool Kivul(const std::size_t r) const = 0;

  friend std::ostream &operator<<(std::ostream&, const Sikidom * const);

  friend std::istream& operator>>(std::istream& is, Sikidom** sikidom);

  virtual ~Sikidom() = 0;
};

/** @brief Kor osztály.
 * A Kor osztály a Sikidom leszármazottja,
 * mely egy kör síkidomot reprezentál,
 * középpontjával és egy csúcsával.
*/
class Kor : public Sikidom {
public:
  Kor(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Kor(const Kor &_k) : Sikidom(_k) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;

  bool Kivul(const std::size_t r) const override;
  
  friend std::ostream &operator<<(std::ostream &, const Kor &);

  ~Kor() override {}
};

/** @brief Haromszog osztály.
 * A Haromszog osztály a Sikidom leszármazottja,
 * mely egy háromszög síkidomot reprezentál,
 * középpontjával és egy csúcsával.
*/
class Haromszog : public Sikidom {
public:
  Haromszog(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Haromszog(const Haromszog &_h) : Sikidom(_h) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;

  bool Kivul(const std::size_t r) const override;

  friend std::ostream &operator<<(std::ostream &, const Haromszog &);

  ~Haromszog() override {}
};

/** @param Negyzet osztály.
 * A Negyzet osztály a Sikidom leszármazottja,
 * mely egy négyzet síkidomot reprezentál,
 * középpontjával és egy csúcsával.
*/
class Negyzet : public Sikidom {
public:
  Negyzet(Pont _kp = Pont(0, 0), Pont _p = Pont(0, 0)) : Sikidom(_kp, _p) {}

  Negyzet(const Negyzet &_n) : Sikidom(_n) {}

  double Terulet() const override;

  bool Rajtavan(const Pont &) const override;

  void Write(std::ostream& os) const override;

  void Read(std::istream& is) override;

  bool Kivul(const std::size_t r) const override;

  friend std::ostream &operator<<(std::ostream &, const Negyzet &);

  ~Negyzet() override {}
};

bool IsOnTriangle(const Pont&, const Pont&, const Pont&, const Pont&);

#endif // !SIKIDOM_SIKIDOM_H