#include "Login.h"
#include "Object.h"
#include "File_Handler.h"
#include "Encode_String.h"
#include "Search_Objects.h"
#include "Random_Name_Gen.h"
#include "Image_Display.h"
#include "Error_Handler.h"
#include "Shared_String.h"
#include "Users.h"
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <myio.h>
#include <sys\stat.h>
#include <Log_Print.h>

Login l;
File_Handler fh;
Search_Objects so;
Image_Display id;
Users user;

bool Check_Cred;

BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType) {
 if (CTRL_CLOSE_EVENT == dwCtrlType) {
  if(Check_Cred)
  fh.Parse_Information();
  return true;
 }
 return false;
}

void Get_Input() {
std::string input;

 printf("%s>", l.Get_Username().c_str());
 std::getline(std::cin, input);

 std::transform(input.begin(), input.end(), input.begin(), ::tolower);
 if (input == "new login object" || input == "nlo") {
  Object::obj().New_Login_Object();
 }
 else if (input == "new image object" || input == "nio") {
  Object::obj().New_Image_Object();
 }

 if (input == "objects") {
  Object::obj().Get_Objects();
 }
 else if (input == "exit") {
  return;
 }
 else if (input == "delete login latest" || input == "dll") {
  Object::obj().Delete_Login_Object_By_Latest();
 }
 else if (input == "delete login index" || input.find("dli") != std::string::npos) {
  Object::obj().Delete_Login_Object_By_Index(myio::stoiEX(input));
 }
 else if (input == "delete image latest" || input == "dil") {
  Object::obj().Delete_Image_Object_By_Latest();
 }
 else if(input.find("search-comment") != std::string::npos || input.find("sc") != std::string::npos){
  input.erase(0, 3);
  so.Search_Phrase_Comment(input);
 }
 else if (input.find("search-user") != std::string::npos || input.find("su") != std::string::npos) {
  input.erase(0, 3);
  so.Search_Phrase_User(input);
 }
 else if (input.find("search-index") != std::string::npos || input.find("si") != std::string::npos) {
  so.Search_Phrase_Index(myio::stoiEX(input));
 }
 else if (input[0] == 'o' && input[1] == 'p' && input[2] == 'e' &&input[3] == 'n') {
  std::string sbuff = input;
  sbuff.erase(0, 5);
  if (myio::_Char_to_Int(sbuff[0]) == -1) Error_Handler::Call_Error(INVALID_INPUT_NUM_ARGUMENT, sbuff);
  else {
   std::string cbuff;
   New_Obj_Image *noiBuff = so.Search_Open_Image_Index(myio::stoiEX(sbuff));
   if (noiBuff != nullptr) {
	cbuff = noiBuff->encrypt_Path;
	cbuff = Shared_String::current_Path + cbuff;
	if (cbuff != "-1")
	 id.Open_Image_Viewer(Encode_String::es().Decrypt_AES_Image(cbuff));
	cbuff.empty();
   }
   else Error_Handler::Call_Error(INVALID_INDEX, sbuff);
  }
 }
 else if (input.find("help") != std::string::npos) {
  printf("new login object/nlo     -- Creates a new object with a Username and Password entry\n");
  printf("new image object/nio     -- Creates a new object that encrypts an image\n");
  printf("objects                  -- Displays all loaded objects\n");
  printf("delete login latest/dll  -- Deletes the last login object in the list\n");
  printf("delete login index//dli  -- Deletes the login object by its index\n");
  printf("delete image latest//dil -- Deletes the last image object in the list\n");
  printf("search-comment/sc        -- Searches through all object comments to find a certain string/phrase\n");
  printf("search-user/su           -- Searches through all object to find a certain user\n");
  printf("search-index/si          -- Searches object by specific index\n");
  printf("open                     -- Opens an encrypted image\n");
  printf("exit                     -- Exits the program\n");
 }


 Get_Input();
}

int main(int argc, char** argv) {
 Set_Log_Print_Level(LOG_LEVEL_ERROR);

 if (FALSE == SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE))
  Log_Error("Could not register Routine %i", GetLastError());

 Shared_String::current_Path = argv[0];


 Shared_String::current_Path.erase(Shared_String::current_Path.find_last_of("\\"), Shared_String::current_Path.length());

 Shared_String::save_File_Name = Shared_String::current_Path + "\\6CMH-YQBQ-DP1M-SCI7.END";
 Shared_String::current_Path += "\\";

 if (!Object::obj().File_Exists(Shared_String::current_Path + "USER1.usr")) {
  user.New_User();
 }
 else {
  user.Get_User();
 }

 printf("***LOGIN***\n");
 Check_Cred = l.Check_Credentials(user.Ret_User(), user.Ret_Pass());

 if (!Check_Cred)
  exit(-1);

 std::string nsfn = Shared_String::current_Path + "~6CMH-YQBQ-DP1M-SCI7.END";

 if (Object::obj().File_Exists(nsfn)) {
  printf("Found a file that only exists if the program has crashed...\nAnything that you want to keep?\n(Save file might be corrupt...)");
 }

 CopyFile(Shared_String::save_File_Name.c_str(), nsfn.c_str(), FALSE);

 DWORD attrib = GetFileAttributes(nsfn.c_str());
 SetFileAttributes(nsfn.c_str(), attrib | FILE_ATTRIBUTE_HIDDEN);


 fh.Get_Information();

 Get_Input();

 fh.Parse_Information();
}