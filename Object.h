#pragma once
#include "New_Object.h"
#define LOGIN_OBJECT 55
#define INFO_OBJECT 56

class Object {
public:
 Object();
 ~Object();

 New_Obj_Login *traverse;
 New_Obj_Login *root;
 bool theEnd = false;
 New_Obj_Image *Img_traverse;
 New_Obj_Image *Img_root;

 static Object& obj() {
  static Object o;
  return o;
 }
 void New_Login_Object();
 void Insert_Login_Object(std::string c, std::string user, std::string passw);
 void Insert_Image_Object(std::string path, std::string comment, std::string ep);
 void New_Image_Object();
 void Delete_Login_Object_By_Latest();
 void Delete_Login_Object_By_Index(int i);
 void Delete_Image_Object_By_Latest();
 void Get_Objects();
 void Print_Login_Object(New_Obj_Login &obj);
 void Print_Image_Object(New_Obj_Image *obj);
 bool File_Exists(const std::string name);
 int current_Login_Index = 0;
 int current_Image_Index = 0;

};

