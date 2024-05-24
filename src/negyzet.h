#include "sikidom.h"

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