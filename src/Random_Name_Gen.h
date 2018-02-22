#pragma once

#include <string>
#include <chrono>
class Random_Name_Gen {
private:
 int Gen_Section_Num();
 std::string Create_Section_Name();
 std::chrono::high_resolution_clock::time_point tstart;
 std::chrono::high_resolution_clock::time_point tend;

public:
 Random_Name_Gen();

 static std::string Create_Random_Name();
};

