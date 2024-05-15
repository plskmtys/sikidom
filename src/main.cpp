#include <iostream>
#include <fstream>
#include <sstream>
//#include "gtest_lite.h"
#include "pont.h"
#include "sikidom.h"
#include "tomb.hpp"

int main() {
  Kor k1(Pont(0, 0), Pont(1, 0));

  /*
  TEST(Kor, 0) {
    EXPECT_EQ(Pont(0, 0), k1.getkp());
    END
  }
  */

  std::ifstream inputFile("inputfile.txt");
  Tomb<Sikidom*> beolvasott_sikidomok;

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string type;
    iss >> type;
    
    Sikidom* sikidom = Sikidom::createSikidom(type);
    iss >> sikidom;

    //eltaroljuk, ha 
    if(sikidom->Tartalmazza(1)){
      beolvasott_sikidomok.push_back(sikidom);
    }
  }
 
  inputFile.close();

  //eltaroltak kiirasa
  std::ofstream outputFile("output.txt");
  std::cout << "fajlba kiirva:\n";
  for (const auto& sikidom : beolvasott_sikidomok) {
    outputFile << sikidom;
    std::cout << sikidom;
  }

  outputFile.close();

}