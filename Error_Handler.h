#pragma once
#include <string>

#define INVALID_INPUT_NUM_ARGUMENT 20
#define LAST_INDEX 21
#define INVALID_FILE_EXISTANCE 22
#define INVALID_INDEX 23

class Error_Handler
{
public:
 Error_Handler();
 static void Call_Error(int arg, std::string s);
};

