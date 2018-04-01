#include "Encode_String.h"
#include "Random_Name_Gen.h"
#include "Shared_String.h"
#include <sstream>
#include <iomanip>
#include <files.h>
#include <default.h>
#include <SFML\System\Thread.hpp>

Encode_String::Encode_String() {}
int ab = 0;

void thread_Test() {
 while (Encode_String::es().test > 0) {
  if(ab != Encode_String::es().test)
   printf("%i\n", Encode_String::es().test);
  ab = Encode_String::es().test;
 }
}

//The old way to encrypt stuff
std::string Encode_String::String_To_Hex(const std::string &s) {
 std::ostringstream ret;

 unsigned int c;
 for (std::string::size_type i = 0; i < s.length(); ++i)
 {
  c = (unsigned int)(unsigned char)s[i];
  ret << std::hex << std::setfill('0') << std::setw(2) << std::nouppercase << c;
 }
 return ret.str();
}

//The old way to decrypt stuff...
std::string Encode_String::Hex_To_String(const std::string &in) {
 std::string newstring;

 for (int a = 0; a < in.length(); a += 2) {
  std::string byte = in.substr(a, 2);
  char c = (char)(int)strtol(byte.c_str(), NULL, 16);
  newstring.push_back(c);
 }

 return newstring;
}

//Encrypts any form of string...
std::string Encode_String::Encrypt_AES(const std::string &s) {
 CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE);
 encrypt = "";
 iv = pass + pass;
 CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
 CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption e;

 hkdf.DeriveKey(key, key.size(), (const byte*)pass.data(), pass.size(), (const byte*)iv.data(), iv.size(), NULL, 0);
 e.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, key + CryptoPP::AES::MAX_KEYLENGTH);
 CryptoPP::StringSource encry(s, true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(encrypt)));
 
 return encrypt;
}

//Decrypts any string 
std::string Encode_String::Decrypt_AES(const std::string &s) {
 recovered = "";
 CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE);
 iv = pass + pass;
 CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
 CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryption;
 
 hkdf.DeriveKey(key, key.size(), (const byte*)pass.data(), pass.size(), (const byte*)iv.data(), iv.size(), NULL, 0);
 decryption.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, key + CryptoPP::AES::MAX_KEYLENGTH);
 CryptoPP::StringSource decrypt(s, true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(recovered)));

 return recovered;
}

std::string Encode_String::Encrypt_AES_String_By_Given_Password(std::string &s, const std::string &pw) {
 CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE);
 encrypt = "";
 iv = pw + pw;
 CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
 CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption e;

 hkdf.DeriveKey(key, key.size(), (const byte*)pw.data(), pw.size(), (const byte*)iv.data(), iv.size(), NULL, 0);
 e.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, key + CryptoPP::AES::MAX_KEYLENGTH);
 CryptoPP::StringSource encry(s.c_str(), true, new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(encrypt)));

 return encrypt;
}

std::string Encode_String::Decrypt_AES_String_By_Given_Password(std::string &s, const std::string &pw) {
 recovered = "";
 CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH + CryptoPP::AES::BLOCKSIZE);
 iv = pw + pw;
 CryptoPP::HKDF<CryptoPP::SHA256> hkdf;
 CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption decryption;

 hkdf.DeriveKey(key, key.size(), (const byte*)pw.data(), pw.size(), (const byte*)iv.data(), iv.size(), NULL, 0);
 decryption.SetKeyWithIV(key, CryptoPP::AES::MAX_KEYLENGTH, key + CryptoPP::AES::MAX_KEYLENGTH);
 CryptoPP::StringSource decrypt(s.c_str(), true, new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(recovered)));

 return recovered;
}

//encrypts a file, specifically an image, but can be used for any file.
//Should probably change this name...
std::string Encode_String::Encrypt_AES_Image(const std::string &s) {

 std::string fExtension = s;
 fExtension.erase(0, s.find_first_of("."));

 std::string endpath = Random_Name_Gen::Create_Random_Name() + fExtension;
 std::string endpBuff = Shared_String::current_Path.c_str() + endpath;
 CryptoPP::FileSource f(s.c_str(), true, new CryptoPP::DefaultEncryptor(pass.c_str(), new CryptoPP::FileSink(endpBuff.c_str())));
 
 return endpath;
}

//Decrypts a file
//Should probably change this name too.
std::string Encode_String::Decrypt_AES_Image(const std::string &s) {
 std::string c = "";
 
 CryptoPP::FileSource fc(s.c_str(), true, new CryptoPP::DefaultDecryptor(pass.c_str(), new CryptoPP::StringSink(c)));

 return c;
}


void Encode_String::Decrypt_AES_File_By_Given_Password(std::string s, const std::string &pw) {
 std::string p = s + "_Encrypted";
 sf::Thread t(thread_Test);

 t.launch();

 CryptoPP::FileSink *fsink = new CryptoPP::FileSink(p.c_str());
 fsink->count = &test;
 CryptoPP::FileSource fc(s.c_str(), true, new CryptoPP::DefaultDecryptor(pw.c_str(), fsink));

 t.terminate();
}

void Encode_String::Encrypt_AES_File_By_Given_Password(std::string s, const std::string &pw) {
 std::string p = s + "_Encrypted";
 sf::Thread t(thread_Test);

 t.launch();

 CryptoPP::FileSink *fsink = new CryptoPP::FileSink(p.c_str());
 fsink->count = &test;
 CryptoPP::FileSource f(s.c_str(), true, new CryptoPP::DefaultEncryptor(pw.c_str(), fsink));

 t.terminate();
}