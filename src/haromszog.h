#include "sikidom.h"
#include <cmath>

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

bool IsOnTriangle(const Pont&, const Pont&, const Pont&, const Pont&);