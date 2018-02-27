#include "Users.h"
#include "Login.h"
#include "Error_Handler.h"
#include "Encode_String.h"
#include "Shared_String.h"
#include <myio.h>
#include <iostream>
#include <Log_Print.h>

Users::Users() {}

void Users::New_User() {
 //Uses a default name, cant really add a new user... for now.
 userPath = Shared_String::current_Path + "USER1.usr";
 printf("***NEW LOGIN***\n");

 std::string user;
 std::string pass;
 
 printf("Username: ");
 std::getline(std::cin, user);
 printf("Password: ");
 std::getline(std::cin, pass);

 Log_Warning("%s, %s", user.c_str(), pass.c_str());

 userHash = std::hash<std::string>{}(user);
 passHash = std::hash<std::string>{}(pass);

 //Uses both the user and password(combined) as the encryption password.
 Encode_String::es().set_Pass(std::to_string(static_cast<unsigned int>(userHash + passHash)));
 Log_Warning("%i, %i", static_cast<unsigned int>(userHash), static_cast<unsigned int>(passHash));
 Log_Warning("%s", std::to_string(static_cast<unsigned int>(userHash + passHash)));
 file.open(userPath, std::fstream::out);

 //Only saves the hash of the user.
 std::string push_Buff = Encode_String::es().Encrypt_AES(std::to_string(static_cast<unsigned int>(userHash))) + "\n";

 file << push_Buff;
 userCheck = push_Buff;
 //Only saves the hash of the password.
 push_Buff = Encode_String::es().Encrypt_AES(std::to_string(static_cast<unsigned int>(passHash))) + "\n";
 passCheck = push_Buff;

 file << push_Buff;
 file.close();
}

void Users::Get_User() {
 userPath = Shared_String::current_Path + "USER1.usr";
 file.open(userPath, std::fstream::in);
 int a = 0;
 if (file.is_open()) {
  for (std::string s; std::getline(file, s);) {
   if (a == 0) {
	userCheck = s;
   }
   else if (a == 1) {
	passCheck = s;
   }
   a++;
  }
 }
 file.close();
}