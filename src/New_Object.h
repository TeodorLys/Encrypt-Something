#pragma once
#include <string>

struct New_Obj_Login {
 std::string username;
 std::string pass;
 std::string comment;
 int index;
 struct New_Obj_Login *next;
};

struct New_Obj_Image {
 std::string comment;
 std::string pathName;
 std::string encrypt_Path;
 int index;
 struct New_Obj_Image *next;
};