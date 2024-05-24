#include "pont.h"
#include "sikidom.h"
#include <cstddef>
#include <iostream>

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