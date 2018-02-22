#pragma once

#include <string>
#include <base64.h>
#include <osrng.h>
#include <hkdf.h>
#include <aes.h>
#include <modes.h>
#include <Filter.h>

class Encode_String {
private:
 CryptoPP::AutoSeededRandomPool rnd;


 std::string pass, iv;
 std::string encrypt, recovered;

 CryptoPP::HKDF<CryptoPP::SHA256> hkdf;

 byte iv2[CryptoPP::AES::BLOCKSIZE];

 void Renew_Key(CryptoPP::SecByteBlock &key);

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
 void set_Pass(const std::string &s) {
  pass = s;
 }

};

