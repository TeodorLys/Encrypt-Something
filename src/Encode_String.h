#pragma once

#include <string>
#include <base64.h>
#include <osrng.h>
#include <hkdf.h>
#include <aes.h>
#include <modes.h>
#include <Filter.h>

class Encode_String {
public:
 int test = 1;

private:
 std::string pass, iv;
 std::string encrypt, recovered;

public:
 Encode_String();

 static Encode_String& es() {
  static Encode_String e;
  return e;
 }

 static std::string Hex_To_String(const std::string& in);
 static std::string String_To_Hex(const std::string& s);
 std::string Encrypt_AES(const std::string &s);
 std::string Decrypt_AES(const std::string &s);
 std::string Encrypt_AES_Image(const std::string &s);
 std::string Decrypt_AES_Image(const std::string &s);
 void Encrypt_AES_File_By_Given_Password(std::string s, const std::string &pw);
 void Decrypt_AES_File_By_Given_Password(std::string s, const std::string &pw);
 std::string Encrypt_AES_String_By_Given_Password(std::string &s, const std::string &pw);
 std::string Decrypt_AES_String_By_Given_Password(std::string &s, const std::string &pw);
 void set_Pass(const std::string &s) {
  pass = s;
 }


};

