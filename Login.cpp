#include "Login.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Encode_String.h"
#include <myio.h>
#include <Log_Print.h>

void Login::Enter_Credentials() {

 printf("Username: ");

 std::getline(std::cin, username);

 while (GetAsyncKeyState(VK_RETURN));

 printf("Password: ");

 std::string end = "";
 char cbuff;
 while (!GetAsyncKeyState(VK_RETURN)) {
  
  if (!GetAsyncKeyState(VK_BACK)) {
   cbuff = _getch();
   if (end.size() < 50 && acceptedStrings.find(cbuff) != std::string::npos) {
	end.push_back(cbuff);
	printf("*");
   }
  }
  else if(end.size() != 0){
   printf("\b");
   printf(" ");
   printf("\b");
   end.pop_back();
   _getch();
  }
 }
 
 char firstL = toupper(username[0]);
 user = std::hash<std::string>{}(username);
 pass = std::hash<std::string>{}(end);

 username.erase(0, 1);
 username.insert(0, 1, firstL);

 Encode_String::es().set_Pass(std::to_string(static_cast<unsigned int>(user + pass)));
 
 printf("\n");
 tryCounter++;
 
 Validate_Credentials();
}

void Login::Validate_Credentials() {
 Log_Warning("%s, %s, %s", Encode_String::es().Decrypt_AES(userCheck), Encode_String::es().Decrypt_AES(passCheck), myio::_Int_to_String(static_cast<unsigned int>(user + pass)));
 if (Encode_String::es().Decrypt_AES(userCheck) != myio::_Int_to_String(user) && Encode_String::es().Decrypt_AES(passCheck) != myio::_Int_to_String(pass) && tryCounter != 3) {
  printf("***ACCESS DENIED***\n");
  Enter_Credentials();
 }
 else {
  if (tryCounter != 3) {
  printf("***ACCESS GRANTED***\n");
  Validate = true;
  Encode_String::es().set_Pass(myio::_Int_to_String(static_cast<int>(user + pass)));
 }
 else {
  printf("***TRY LIMIT REACHED***\n");
  Validate = false;
  std::cin.get();
 }
 }
}


bool Login::Check_Credentials(std::string uc, std::string pc) {
 userCheck = uc;
 passCheck = pc;

 Log_Warning("%s, %s", uc, pc);

 Enter_Credentials();
 return Validate;
}


std::string Login::Get_Username() {
 return username;
}