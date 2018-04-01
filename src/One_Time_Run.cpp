#include "One_Time_Run.h"
#include <filesystem>
#include <Log_Print.h>
#include <fstream>
#include "Encode_String.h"

void One_Time_Run::Parse_String(int argc, char **argv) {
 std::string temp;
 std::string current = std::experimental::filesystem::current_path().string();

 for (int a = 1; a < argc; a++) {
  temp = argv[a];

  if (a == 2) {
   if (temp.find("\\") == std::string::npos) {
	if (!std::experimental::filesystem::exists(current + "\\" + temp)) {
	 Log_Error("CAN'T FILE THAT FILE: %s", current + "\\" + temp);
	 exit(-1);
	}
	else {
	 found_File = true;
	 file_Path = current + "\\" + temp;
	}
   }
   else {
	if (!std::experimental::filesystem::exists(temp)) {
	 Log_Error("CAN'T FILE THAT FILE: %s", temp);
	 exit(-1);
	}
	else {
	 found_File = true;
	 file_Path = temp;
	}
   }
  }

   if (temp.find("-e") != std::string::npos)
	encrypt = true;
   else if (temp.find("-p") != std::string::npos) {
	password = true;
	passW = argv[a + 1];
	a++;
   }
   else if (temp.find("-d") != std::string::npos)
	decrypt = true;
 }

 //if (std::experimental::filesystem::file_size(file_Path) > 200000)
  //File_Is_Too_Biff = true;

 if (encrypt && decrypt) {
  Log_Error("YOU CAN'T ENCRYPT AND DECRYPT AT THE SAME TIME");
  exit(-1);
 }
 Parsed_String = true;
}

void One_Time_Run::Encrypt_Given_Item() {

 if (!Parsed_String) {
  Log_Error("PARSE_STRING() DID NOT RUN, THE PROGRAM IS BAD... IM SORRY: Best regards / The Programmer");
  exit(-1);
 }

 if (false) {
  if(encrypt)
   Manual_File_Write(true);
  else if(decrypt)
   Manual_File_Write(false);
 }
 else {
  if (encrypt)
   Encode_String::es().Encrypt_AES_File_By_Given_Password(file_Path, passW);
  else if(decrypt)
   Encode_String::es().Decrypt_AES_File_By_Given_Password(file_Path, passW);
 }
}

void One_Time_Run::Manual_File_Write(bool encrypt_File) {
 //const size_t bufferSize = 262144;
 //char _buffer[bufferSize];
 //char _ibuffer[bufferSize];

 std::ofstream file(file_Path + "_Encrypted", std::fstream::binary);
 std::ifstream ifile(file_Path, std::fstream::binary);

 if (!file.is_open())
  Log_Error("COULD NOT CREATE FILE!");
 if(!ifile.is_open())
  Log_Error("COULD NOT OPEN FILE!");

 //file.rdbuf()->pubsetbuf(_buffer, bufferSize);
 //ifile.rdbuf()->pubsetbuf(_ibuffer, bufferSize);

 if (encrypt_File)
  for (std::string s; std::getline(ifile, s);) {
   //printf("%s\n", s.c_str());
   if (s.size() > 512) {
	for(int a = 0; a < s.size() / 512; a++){

	 std::string temp;
	 for (int b = 0; b < 512; b++)
	  temp += s[b + (a * 512)];

	 file << Encode_String::es().Encrypt_AES_String_By_Given_Password(temp, passW);
	 temp = "";
	}
	
   }
  }
 else
  for (std::string s; std::getline(ifile, s);) {
   //printf("%s\n", s.c_str());
   if (s.size() > 512) {
	for (int a = 0; a < s.size() / 512; a++) {

	 std::string temp;
	 for (int b = 0; b < 512; b++)
	  temp += s[b + (a * 512)];

	 file << Encode_String::es().Decrypt_AES_String_By_Given_Password(temp, passW);
	 temp = "";
	}

   }
  }

 file.close();
 ifile.close();
}