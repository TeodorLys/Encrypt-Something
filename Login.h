#pragma once
#include <string>
class Login {
private:
 std::string username;
 bool Validate = false;
 size_t user;
 size_t pass;
 std::string userCheck;
 std::string passCheck;
 std::string acceptedStrings = "§1234567890+´qwertyuiopåäsdfghjklöä'<zxcvbnm,.-½!()=?QWERTYUIOPÅASDFGHJKLÖÄ*>ZXCVBNM;:_@£$€{[]}\\|¨ ";
 int tryCounter = 0;
public:
 void Enter_Credentials();
 void Validate_Credentials();
 std::string Get_Username();
 bool Check_Credentials(std::string, std::string);
};

