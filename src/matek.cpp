#include <cmath>

#include "matek.h"
#include "pont.h"

double AbsCrossProd(const Pont& A1, const Pont& A2, const Pont& B1, const Pont& B2){
  return fabs((A2.getx() - A1.getx()) * (B2.gety() - B1.gety()) - (A2.gety() - A1.gety()) * (B2.getx() - B1.getx()));
}
