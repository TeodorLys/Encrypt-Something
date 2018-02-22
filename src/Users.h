#pragma once
#include <fstream>
#include "Shared_String.h"

class Users {
private:
 std::fstream file;
 std::string userPath;
 std::string userCheck;
 std::string passCheck;
 size_t userHash;
 size_t passHash;
public:
 Users();
 void New_User();
 void Get_User();
 std::string& Ret_Pass() {
  return passCheck;
 }

 std::string& Ret_User() {
  return userCheck;
 }
};

