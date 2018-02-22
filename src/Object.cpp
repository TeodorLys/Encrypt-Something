#include "Object.h"
#include <string>
#include <iostream>
#include <algorithm>
#include "Error_Handler.h"
#include "Encode_String.h"
#include "Shared_String.h"

bool Object::File_Exists(const std::string name) {
 struct stat Buffer;
 return(stat(name.c_str(), &Buffer) == 0);
}

Object::~Object() {
 //delete root;
 //delete traverse;
}

Object::Object() {
 root = new New_Obj_Login;
 root->next = nullptr;
 root->index = 0;
 traverse = root;

 Img_root = new New_Obj_Image;
 Img_root->next = nullptr;
 Img_root->index = 0;
 Img_traverse = Img_root;
}

void Object::Insert_Login_Object(std::string c, std::string user, std::string passw) {
 traverse->next = new New_Obj_Login;
 traverse->comment = c;
 traverse->username = user;
 traverse->pass = passw;
 traverse->index = current_Login_Index;
 traverse = traverse->next;
 traverse->next = nullptr;
}

void Object::New_Login_Object() {
 std::string com;
 std::string us;
 std::string pa;
 printf("Add Comment: ");
 std::getline(std::cin, com);
 printf("Add Username: ");
 std::getline(std::cin, us);
 printf("Add Password: ");
 std::getline(std::cin, pa);

 traverse->next = new New_Obj_Login;
 traverse->comment = com;
 traverse->username = us;
 traverse->pass = pa;
 traverse->index = current_Login_Index++;
 traverse = traverse->next;
 traverse->next = nullptr;
}

void Object::Insert_Image_Object(std::string path, std::string comment, std::string ep) {
 //printf("Did it?\n");
 Img_traverse->next = new New_Obj_Image;
 Img_traverse->comment = comment;
 Img_traverse->pathName = path;
 //printf("%i\n", current_Image_Index);
 Img_traverse->index = current_Image_Index;
 Img_traverse->encrypt_Path = ep;
 Img_traverse = Img_traverse->next;
 Img_traverse->next = nullptr;
}

void Get_Path(std::string *path) {
 
 printf("Add Path: ");
 std::getline(std::cin, *path);

 if (!Object::obj().File_Exists(*path)) {
  Error_Handler::Call_Error(INVALID_FILE_EXISTANCE, *path);
  Get_Path(path);
 }
 else
  return;
}

void Object::New_Image_Object() {
 //Reset Traverse...
 Img_traverse = Img_root;
 while (Img_traverse->next != nullptr) {
  Img_traverse = Img_traverse->next;
 }

 std::string com;
 std::string path;
 printf("Add Comment: ");
 std::getline(std::cin, com);
 Get_Path(&path);

 Img_traverse->next = new New_Obj_Image;
 Img_traverse->comment = com;
 Img_traverse->pathName = path;
 Img_traverse->encrypt_Path = Encode_String::es().Encrypt_AES_Image(path);
 Img_traverse->index = ++current_Image_Index;
 Img_traverse = Img_traverse->next;
 Img_traverse->next = nullptr;
}

void Object::Delete_Login_Object_By_Latest() {
 New_Obj_Login *nbegin = root;

 while (nbegin->next->next != nullptr) {
  nbegin = nbegin->next;
 }

 nbegin->next = nullptr;
}


void Object::Delete_Login_Object_By_Index(int i) {
 New_Obj_Login *nbegin = root;
 New_Obj_Login *prev = root;
 New_Obj_Login *RenewIndex = root;
 bool found = false;
 while (nbegin->next != nullptr) {
  prev = nbegin;
  nbegin = nbegin->next;
  if (nbegin->index == i) {
   found = true;
   break;
  }
 }

 std::string in;

 printf("Are you sure you want to Delete this?: \n");
 Print_Login_Object(*nbegin);
 printf("(Y/N): ");
 std::getline(std::cin, in);

 std::transform(in.begin(), in.end(), in.begin(), ::tolower);

 if (found && in.find("y") != std::string::npos) {
  prev->next = nbegin->next;
  delete nbegin;
  int newIndex = 0;
  while (RenewIndex != nullptr) {
   RenewIndex->index = newIndex;
   RenewIndex = RenewIndex->next;
   newIndex++;
  }

 }
}

void Object::Delete_Image_Object_By_Latest() {
 New_Obj_Image *nbegin = Img_root;
 if (current_Image_Index != 0) {
  while (nbegin->next->next != nullptr/* || nbegin->next != nullptr*/) {
   nbegin = nbegin->next;
  }
 }
 else {
  Error_Handler::Call_Error(LAST_INDEX, "Delete_Image_Objects_By_Latest");
 }

 std::string p = Shared_String::current_Path;

 p += nbegin->encrypt_Path;

 DeleteFile(p.c_str());
 nbegin->next = nullptr;

 current_Image_Index--;
}

void Object::Get_Objects() {

 New_Obj_Login *nBegin = root;
 New_Obj_Image *ibegin = Img_root;

 while (nBegin->next != nullptr) {
  Print_Login_Object(*nBegin);
  nBegin = nBegin->next;
 }

 while (ibegin->next != nullptr) {
  Print_Image_Object(ibegin);
  ibegin = ibegin->next;
 }

}

void Object::Print_Login_Object(New_Obj_Login &obj) {
 printf("\n\tComment:  %s\n", obj.comment.c_str());
 printf("\tUser:     %s\n", obj.username.c_str());
 printf("\tPassword: %s\n", obj.pass.c_str());
 printf("\tIndex: %i\n", obj.index);
}

void Object::Print_Image_Object(New_Obj_Image *obj) {
 printf("\n\tComment:  %s\n", obj->comment.c_str());
 printf("\tPath:       %s\n", obj->pathName.c_str());
 printf("\tIndex:      %i\n", obj->index);
 printf("\tNewFile:    %s\n", obj->encrypt_Path.c_str());
}
