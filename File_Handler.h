#pragma once
#include <fstream>
#include "Object.h"

class File_Handler {

private:
 std::fstream file;

public:
 File_Handler();
 ~File_Handler();

 void Parse_Information();
 void Get_Information();
};

