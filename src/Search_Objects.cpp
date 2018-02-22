#include "Search_Objects.h"
#include "Object.h"
#include <algorithm>

Search_Objects::Search_Objects() {}


void Search_Objects::Search_Phrase_Comment(const std::string &s) {
 New_Obj_Login *nbegin = Object::obj().root;
 New_Obj_Image *ibegin = Object::obj().Img_root;
 bool found = false;
 std::string com;

 while (nbegin->next != nullptr) {
  com = nbegin->comment;
  std::transform(com.begin(), com.end(), com.begin(), ::tolower);
  if (com.find(s) != std::string::npos) {
   Object::obj().Print_Login_Object(*nbegin);
  }
  nbegin = nbegin->next;
 }
 
 while (ibegin->next != nullptr) {
  com = ibegin->comment;
  std::transform(com.begin(), com.end(), com.begin(), ::tolower);
  if (com.find(s) != std::string::npos) {
   Object::obj().Print_Image_Object(ibegin);
  }
  ibegin = ibegin->next;
 }
}


void Search_Objects::Search_Phrase_User(const std::string &s) {
 New_Obj_Login *nbegin = Object::obj().root;
 bool found = false;
 std::string user;

 while (nbegin->next != nullptr) {
  user = nbegin->username;
  std::transform(user.begin(), user.end(), user.begin(), ::tolower);
  if (user.find(s) != std::string::npos) {
   found = true;
   break;
  }
  nbegin = nbegin->next;
 }
 if (found)
  Object::obj().Print_Login_Object(*nbegin);
}

void Search_Objects::Search_Phrase_Index(const int i) {
 New_Obj_Login *nbegin = Object::obj().root;
 bool found = false;
 int index;

 while (nbegin->next != nullptr) {
  index = nbegin->index;
  
  if (index == i) {
   found = true;
   break;
  }
  nbegin = nbegin->next;
 }
 if (found)
  Object::obj().Print_Login_Object(*nbegin);
}

New_Obj_Image *Search_Objects::Search_Open_Image_Index(int i) {
 New_Obj_Image *nbegin = Object::obj().Img_root;
 bool found = false;
 int index;

 while (nbegin->next != nullptr) {
  index = nbegin->index;

  if (index == i) {
   found = true;
   break;
  }
  nbegin = nbegin->next;
 }
 if (found)
  return nbegin;
 else return nullptr;
}
