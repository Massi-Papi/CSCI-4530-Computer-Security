#include "DES.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//////Dont make any changes to main.cpp/////////////
int main() {
  string key_hex;
  cin >> key_hex;
  string key = hexToBinary(key_hex);
  string print_key = binaryToAscii(key);
  vector<string> sub_keys = key_gen(key);
  for (string i : sub_keys)
    cout << i << ' ';
}