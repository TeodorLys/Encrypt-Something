#include "File_Handler.h"
#include "Encode_String.h"
#include "Object.h"
#include "Shared_String.h"
#include <myio.h>


File_Handler::File_Handler(){}

File_Handler::~File_Handler() {
 file.close();
}

void File_Handler::Parse_Information() {
 std::string login;
 std::string image;
 New_Obj_Login *nbegin = Object::obj().root;
 New_Obj_Image *ibegin = Object::obj().Img_root;
 file.open(Shared_String::save_File_Name, std::fstream::out | std::fstream::binary);

 login = Encode_String::es().Encrypt_AES("NEW_LOGIN_OBJECTS BEGIN:") + "\n";

 while (nbegin->next != nullptr) {
  login += Encode_String::es().Encrypt_AES("i:" + std::to_string(nbegin->index)) + "\n";
  login += Encode_String::es().Encrypt_AES("c:" + nbegin->comment) + "\n";
  login += Encode_String::es().Encrypt_AES("u:" + nbegin->username) + "\n";
  login += Encode_String::es().Encrypt_AES("p:" + nbegin->pass) + "\n";
  nbegin = nbegin->next;
  file << login;
  login = "";
 }
 login = Encode_String::es().Encrypt_AES("NEW_LOGIN_OBJECTS END:") + "\n";

 file << login;

 image = Encode_String::es().Encrypt_AES("NEW_IMAGE_OBJECTS BEGIN:") + "\n";

 while (ibegin->next != nullptr) {
  image += Encode_String::es().Encrypt_AES("i:" + myio::_Int_to_String(ibegin->index)) + "\n";
  image += Encode_String::es().Encrypt_AES("c:" + ibegin->comment) + "\n";
  image += Encode_String::es().Encrypt_AES("p:" + ibegin->pathName) + "\n";
  image += Encode_String::es().Encrypt_AES("e:" + ibegin->encrypt_Path) + "\n";
  ibegin = ibegin->next;
  file << image;
  image = "";
 }

 image = Encode_String::es().Encrypt_AES("NEW_IMAGE_OBJECTS END:") + "\n";

 file << image;

 file.close();

 std::string nsfn = Shared_String::current_Path + "\\~6CMH-YQBQ-DP1M-SCI7.END";

 DeleteFile(nsfn.c_str());
}

void File_Handler::Get_Information() {
 file.open(Shared_String::save_File_Name, std::fstream::in | std::fstream::binary);
 
 bool image_Object = false;
 bool img_commentfound = false;
 bool img_pathfound = false;
 bool img_indexfound = false;
 bool img_Encryptfound = false;

 bool login_Object = false;
 bool commentfound = false;
 bool userfound    = false;
 bool passfound    = false;
 bool indexfound   = false;

 New_Obj_Login buff;
 New_Obj_Image ibuff;

 std::string sbuff;

 std::string s;

 for (std::string sb; std::getline(file, sb);) {
  s = Encode_String::es().Decrypt_AES(sb.c_str());

  if (login_Object) {   
   if(s[0] == 'i' && s[1] == ':'){
	sbuff = s;
	sbuff.erase(0, 2);
	buff.index = myio::stoiEX(sbuff);
	indexfound = true;
   }
   else if (s[0] == 'c' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	buff.comment = sbuff;
	commentfound = true;
   }
   else if (s[0] == 'u' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	buff.username = sbuff;
	userfound = true;
   }
   else if (s[0] == 'p' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	buff.pass = sbuff;
	passfound = true;
   }
  }
  else if (image_Object) {
   //printf("%s\n", s.c_str());
   if (s[0] == 'i' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	ibuff.index = myio::stoiEX(sbuff);
	//printf("%i, %s\n", myio::stoiEX(sbuff), sbuff.c_str());
	img_indexfound = true;
   }
   else if (s[0] == 'c' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	ibuff.comment = sbuff;
	img_commentfound = true;
   }
   else if (s[0] == 'p' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	ibuff.pathName = sbuff;
	img_pathfound = true;
   }
   else if (s[0] == 'e' && s[1] == ':') {
	sbuff = s;
	sbuff.erase(0, 2);
	ibuff.encrypt_Path = sbuff;
	img_Encryptfound = true;
   }
  }



  if (s.find("NEW_LOGIN_OBJECTS BEGIN:") != std::string::npos)
   login_Object = true;
  else if (s.find("NEW_LOGIN_OBJECTS END:") != std::string::npos)
   login_Object = false;
  else if (s.find("NEW_IMAGE_OBJECTS BEGIN:") != std::string::npos)
   image_Object = true;
  else if (s.find("NEW_IMAGE_OBJECTS END:") != std::string::npos)
   image_Object = false;
  
  if (indexfound && commentfound && userfound && passfound) {
   Object::obj().current_Login_Index = buff.index;
   Object::obj().Insert_Login_Object(buff.comment, buff.username, buff.pass);
   indexfound = false;
   commentfound = false;
   userfound = false;
   passfound = false;
  }
  else if (img_commentfound && img_indexfound && img_pathfound && img_Encryptfound) {
   //printf("All found\n");
   Object::obj().current_Image_Index = ibuff.index;
   //printf("%i\n", Object::obj().current_Image_Index);
   Object::obj().Insert_Image_Object(ibuff.pathName, ibuff.comment, ibuff.encrypt_Path);
   img_commentfound = false;
   img_indexfound = false;
   img_pathfound = false;
   img_Encryptfound = false;
  }
 }
 file.close();
}
