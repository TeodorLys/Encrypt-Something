#include "Error_Handler.h"



Error_Handler::Error_Handler()
{
}

void Error_Handler::Call_Error(int arg, std::string s) {
 switch (arg) {
 case INVALID_INPUT_NUM_ARGUMENT:
  printf("[ERROR]: INVALID ARGUMENT: %s. ONLY NUMBERS ACCEPTED.\n", s.c_str());
  break;

 case LAST_INDEX:
  printf("[ERROR]: LAST_INDEX: %s. THERE ARE NO MORE IN THIS CONAINER.\n", s.c_str());
  break;

 case INVALID_FILE_EXISTANCE:
  printf("[ERROR]: FILE DOES NOT EXIST: %s.\n", s.c_str());
  break;

 case INVALID_INDEX:
  printf("[ERROR]: INDEX WAS NOT FOUND: %s.\n", s.c_str());

  break;

 default:
  break;
 }

}
