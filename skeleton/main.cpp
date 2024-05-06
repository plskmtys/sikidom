#include <iostream>
#include "tomb.hpp"
#include "pont.h"
#include "sikidom.h"

int main(int argc, char** argv) {
  Tomb<Sikidom> tomb;

  Kor k1(Pont(1), Pont(2));
  tomb.add(k1);
  std::cout << "tombbe belerakva: " << k1 << std::endl;

  Haromszog h1(Pont(0), Pont(-1));
  tomb.add(h1);
  std::cout << "tombbe belerakva: " << h1 << std::endl;

  Negyzet n1(Pont(4), Pont(0));
  tomb.add(n1);
  std::cout << "tombbe belerakva: " << n1 << std::endl;

  std::cout << "ezek vannak a tombben:" << std::endl;
  for(const auto& elem: tomb){
    std::cout << elem << std::endl;
  }
}
