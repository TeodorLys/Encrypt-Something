#include "Random_Name_Gen.h"
#include <random>
#include <myio.h>
#include <time.h>

std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

Random_Name_Gen::Random_Name_Gen(){
 tstart = std::chrono::high_resolution_clock::now();
}

int Random_Name_Gen::Gen_Section_Num() {
 tend = std::chrono::high_resolution_clock::now();
 int a = std::chrono::duration_cast<std::chrono::nanoseconds>(tstart - tend).count();

 srand(a);

 int r = rand() % letters.size();
 
 //printf("%i\n", r);

 return r;
}

std::string Random_Name_Gen::Create_Section_Name() {
 std::string sec = myio::_Int_to_String(Gen_Section_Num());
 int buff;

 std::string newSection;

 for (int a = 0; a < 4; a++) {
  //buff = myio::_Char_to_Int(c);
  newSection += letters[Gen_Section_Num()];
 }

 return newSection;
}

std::string Random_Name_Gen::Create_Random_Name() {
 std::string end;
 
 Random_Name_Gen g;

 for (int a = 0; a < 4; a++) {
  std::string s = g.Create_Section_Name();
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  s += "-";
  end += s;
 }

 end.pop_back();

 return end;
}
