#include <iostream>
#include <fstream>
#include <sstream>
#include "gtest_lite.h"
#include "pont.h"
#include "sikidom.h"
#include "tomb.hpp"

int main(int argc, char** argv) {

  std::ifstream inputFile("inputfile.txt");
  Tomb<Sikidom*> beolvasott_sikidomok;

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);

    Sikidom* sikidom = nullptr;
    iss >> &sikidom;

    //assert(sikidom != nullptr);

    //eltaroljuk, ha az egysegkoron kivul van
    if(sikidom->Kivul(1)){
      beolvasott_sikidomok.push_back(sikidom);
    }
  }
 
  inputFile.close();

  //eltaroltak kiirasa
  std::ofstream outputFile("output.txt");
  std::cout << "\nfajlba kiirva:\n";
  for (const auto& sikidom : beolvasott_sikidomok) {
    outputFile << sikidom;
    std::cout << sikidom;
  }

  outputFile.close();

  std::cout << "HAROMSZOG TESZT\n";
  TEST(Haromszog, rajtavan) {
    Haromszog h1(Pont(0,0), Pont(0,1));
    EXPECT_TRUE(h1.Rajtavan(Pont(0,0)));
    EXPECT_TRUE(h1.Rajtavan(Pont(0.4, 0.0)));
    EXPECT_TRUE(h1.Rajtavan(Pont(0.4, -0.4)));
    EXPECT_FALSE(h1.Rajtavan(Pont(0.5, 0.5)));
    EXPECT_FALSE(h1.Rajtavan(Pont(10,10)));
    END
  }

  TEST(Haromszog, Kivul) {
    Haromszog h2(Pont(10,10), Pont(10,12));
    EXPECT_TRUE(h2.Kivul(1));
    EXPECT_TRUE(h2.Kivul(10));
    EXPECT_FALSE(h2.Kivul(20));
    END
  }

  /*
  TEST(Haromszog, IsOnTriangle) {
    Haromszog h1(Pont(0,0), Pont(0,1));
    const Pont A = h1.getp();
    Pont B = h1.getp();
    B.Forgat(2.0*M_PI/3.0, h1.getkp());
    Pont C = h1.getp();
    C.Forgat(4.0*M_PI/3.0, h1.getkp());
    EXPECT_TRUE(IsOnTriangle(Pont(0,0), A, B, C));
    EXPECT_TRUE(IsOnTriangle(Pont(0.4, 0.0), A, B, C));
    EXPECT_TRUE(IsOnTriangle(Pont(0.4, -0.4), A, B, C));
    EXPECT_FALSE(IsOnTriangle(Pont(0.5, 0.5), A, B, C));
    EXPECT_FALSE(IsOnTriangle(Pont(10,10), A, B, C));
    END
  }
  */
}