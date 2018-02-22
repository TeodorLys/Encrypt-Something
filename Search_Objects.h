#pragma once
#include <string>
#include "New_Object.h"
class Search_Objects
{
public:
 Search_Objects();
 void Search_Phrase_Comment(const std::string &s);
 void Search_Phrase_User(const std::string &s);
 void Search_Phrase_Index(const int i);
 New_Obj_Image *Search_Open_Image_Index(int i);
};

