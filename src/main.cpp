#include <iostream>
#include "tomb.hpp"
#include "pont.h"
#include "sikidom.h"
#include "gtest_lite.h"

int main() {
  Kor k1(Pont(0, 0), Pont(1, 0));
  
  TEST(Kor, 0){
    EXPECT_EQ(Pont(0, 0), k1.getkp());
  END }

}
