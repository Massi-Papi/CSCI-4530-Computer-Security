#include "DES.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// The blocks has been padded and is already a vector of binary string
// The key and IV are also binary strings

string CBC_encryption(vector<string> blocks, string key, string IV) {
  string encrypted;
  string previous = IV;
  for (string block : blocks) {
    string xorBlock = XOR(block, previous, block.size());
    string currentEncrypted = encryption(xorBlock, key_gen(key));
    encrypted += currentEncrypted;
    previous = currentEncrypted;
  }
  return encrypted;
}

string CBC_decryption(vector<string> blocks, string key, string IV) {
  string decrypted;
  string previous = IV;
  for (string block : blocks) {
    string currentDecrypted = decryption(block, key_gen(key));
    string xorBlock = XOR(currentDecrypted, previous, currentDecrypted.size());
    decrypted += xorBlock;
    previous = block;
  }
  return decrypted;
}