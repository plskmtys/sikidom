#include "gtest_lite.h"
#include "pont.h"
#include "sikidom.h"
#include "tomb.hpp"
#include <iostream>
#include <sstream>

int main() {
  Kor k1(Pont(0, 0), Pont(1, 0));
  // std::cout << k1 << std::endl;

  TEST(Kor, 0) {
    EXPECT_EQ(Pont(0, 0), k1.getkp());
    END
  }

  std::ifstream inputFile("inputfile.txt");
  Tomb<Sikidom*> sikidoms;

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    if(type[0] == '{') {
      type.erase(0, 1);
    }

    Sikidom* sikidom = Sikidom::createSikidom(type);
    sikidom->Read(iss);
    sikidoms.push_back(sikidom);
  }

  inputFile.close();

  std::ofstream outputFile("output.txt");

  for (Sikidom* sikidom : sikidoms) {
    sikidom->Write(outputFile);
  }

  outputFile.close();

  for (Sikidom* sikidom : sikidoms) {
    delete sikidom;
  }
}
