#pragma once
#include <string>
class One_Time_Run {

private:
 bool one_Time = false;
 bool encrypt = false;
 bool password = false;
 bool decrypt = false;
 bool found_File = false;
 bool File_Is_Too_Biff = false;
 bool Parsed_String = false;
 std::string file_Path = "";
 std::string passW = "";

public:
 One_Time_Run() {}

 void Set_Public(bool t) { one_Time = t; }
 bool Get_Public() { return one_Time; }

 void Encrypt_Given_Item();
 void Parse_String(int argc, char **argv);

private:
 void Manual_File_Write(bool encrypt_File);

};

