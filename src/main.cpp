#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "gtest_lite.h"
#include "pont.h"
#include "sikidom.h"
#include "tomb.hpp"

int main(int argc, char** argv) {

  //fajl beolvasas
  std::ifstream inputFile("input.txt");
  Tomb<Sikidom*> beolvasott_sikidomok;

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);

    Sikidom* sikidom = nullptr;
    iss >> &sikidom;
    std::cout << "beolvasva: " << sikidom;

    //eltaroljuk, ha az egysegkoron kivul van
    if(sikidom->Kivul(1)){
      beolvasott_sikidomok.push_back(sikidom);
    } else {
      delete sikidom;
    }
  }
 
  inputFile.close();

  //tesztesetek
  std::cout<<"\nKOR TESZT\n";
  TEST(Kor, masolo){
    Kor k1(Pont(0,0), Pont(1,1));
    Kor k2 = k1;
    EXPECT_EQ(Pont(0,0), k2.getkp()) << "kp nem jo" ;
    EXPECT_EQ(Pont(1,1), k2.getp()) << "p nem jo" ;
    k2.Mozgat(2,3);
    k1 = k2;
    EXPECT_EQ(Pont(2,3), k1.getkp()) << "= nem jo" ;
    EXPECT_EQ(Pont(3,4), k1.getp());
  } ENDM

  TEST(Kor, Terulet){
    Kor k1(Pont(0,0), Pont(1,0));
    EXPECT_DOUBLE_EQ(M_PI, k1.Terulet()) << "terulet nem jo" ;
  } ENDM

  std::cout << "\nHAROMSZOG TESZT\n";
  TEST(Haromszog, terulet){
    Haromszog h1(Pont(0,0), Pont(1,0));
    EXPECT_DOUBLE_EQ(sqrt(3) * 3.0 / 4.0, h1.Terulet()) << "terulet nem jo" ;
  } ENDM

  TEST(Haromszog, rajtavan) {
    Haromszog h1(Pont(0,0), Pont(0,1));
    EXPECT_TRUE(h1.Rajtavan(Pont(0,0)));
    EXPECT_TRUE(h1.Rajtavan(Pont(0.4, 0.0)));
    EXPECT_TRUE(h1.Rajtavan(Pont(0.4, -0.4)));
    EXPECT_FALSE(h1.Rajtavan(Pont(0.5, 0.5)));
    EXPECT_FALSE(h1.Rajtavan(Pont(10,10)));
  } ENDM

  TEST(Haromszog, Kivul) {
    Haromszog h2(Pont(10,10), Pont(10,12));
    EXPECT_TRUE(h2.Kivul(1));
    EXPECT_TRUE(h2.Kivul(10));
    EXPECT_FALSE(h2.Kivul(20));
  } ENDM

  std::cout << "\nNEGYZET TESZT\n";
  TEST(Negyzet, masolo){
    Negyzet n1(Pont(0,0), Pont(1,1));
    Negyzet n2 = n1;
    EXPECT_EQ(Pont(0,0), n2.getkp()) << "kp nem jo" ;
    EXPECT_EQ(Pont(1,1), n2.getp()) << "p nem jo" ;
    n2.Mozgat(2,4);
    n1 = n2; //n1.kp = 2,4; n1.p = 3,5;
    EXPECT_EQ(Pont(2,4), n1.getkp()) << "= nem jo" ;
    EXPECT_EQ(Pont(3,5), n1.getp());
  } ENDM

  TEST(Negyzet, terulet){
    Negyzet n1(Pont(0,0), Pont(1,1));
    EXPECT_DOUBLE_EQ(4.0, n1.Terulet()) << "terulet nem jo" ;
  } ENDM

  //tesztesetek vege
  std::cout << "\n---TESZTESETEK VEGE---\n";

  //pontok beolvasasa a felhasznalotol
  Tomb<std::size_t> megjelolt_sikidomok_i;
  line = std::string();
  std::cout << "\nAdjon meg koordinatakat! (formatum: \"x,y\")\n";
  while(std::getline(std::cin, line)){
    std::istringstream iss(line);
    Pont point_in;
    try{
      iss >> point_in; // pont formatum check
    } catch (std::runtime_error &e) {
      std::cout << "formatum hiba!: " << e.what() << '\n';
      continue;
    }

    std::size_t i = 0;
    std::size_t n = 0;
    for(const auto& sikidom : beolvasott_sikidomok) {
      if(sikidom->Rajtavan(point_in)){
        std::cout << "a pontot tartalmazza: " << sikidom;
        if(megjelolt_sikidomok_i.find(i) < 0) megjelolt_sikidomok_i.push_back(i);
        ++n;
      }
      ++i;
    }
    if(n == 0) std::cout << "egyetlen sikidom sem tartalmazza ezt a pontot.\n";
    std::cout << "\nAdjon meg koordinatakat! (formatum: \"x,y\", vagy \"(x,y)\")\n";
  }

  //eltaroltak kiirasa
  std::ofstream outputFile("output.txt");
  std::cout << "\nFAJLBA KIIRVA:\n";
  for (const auto& index : megjelolt_sikidomok_i) {
    outputFile << beolvasott_sikidomok[index];
    std::cout << beolvasott_sikidomok[index];
  }

  outputFile.close();

  for(std::size_t i = 0; i < beolvasott_sikidomok.size(); ++i){
    delete beolvasott_sikidomok[i];
  }
}