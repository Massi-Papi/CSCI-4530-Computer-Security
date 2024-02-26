#include "DES.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string encryption_flag;
  cin >> encryption_flag;
  string key = hexToBinary("02FFA374EB55F57B");
  string IV = hexToBinary("0C36AA5FB0C4A18D");
  string output;
  if (encryption_flag[0] == 'e') {
    // This is just a personal opinion by your TA
    string input = "SpongeBob SquarePants is a good show, but the new episodes are a little weird";
    vector<string> plaintext_blocks = block_generation(input, 1);
    vector<string> plaintext_binary = asciiToBinary(plaintext_blocks);
    string encrypted = CBC_encryption(plaintext_binary, key, IV);
    string encrypted_ascii = binaryToAscii(encrypted);
    cout << encrypted;
    output = encrypted_ascii;
    write_file(encrypted_ascii, "encrypted.txt");
  } else if (encryption_flag[0] == 'd') {
    string input = readfile("encrypted.txt");
    vector<string> encrypted_blocks = block_generation(input, 0);
    vector<string> encrypted_binary = asciiToBinary(encrypted_blocks);
    string decrypted_binary = CBC_decryption(encrypted_binary, key, IV);
    string decrypted_unpadded = unpadded(decrypted_binary);
    string decrypted = binaryToAscii(decrypted_unpadded);
    cout << decrypted;
  }
}
