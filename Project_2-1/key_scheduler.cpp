#include "key_utils.h"
#include <bitset>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string shift_left(string sub_key) {
  /* Write a function which takes a binary string as input and outputs a binary
   * string with a left shift. Left shift operation shifts every bit left to its
   * orginal postion, except the first bit, which circles back to the end of the
   * block
   */
  ///////START YOUR CODE HERE///////

  string first = sub_key.substr(0, 1);
  sub_key = sub_key.substr(1, 28) + first;
  return sub_key;
}

vector<string> key_gen(string key) {
  /* Write a function which takes the key, which is a 64-bit binary string and
   * generate an out vector where every element is a sub-key in a binary string
   * format. "key_utils.h" contains the required PC1 and PC2 block.
   */
  ///////START YOUR CODE HERE///////

  vector<string> sub_keys;
  string key_56 = "";

  for (int i = 0; i < 56; i++) {
    key_56 += key[PC1[i] - 1];
  }

  string left = key_56.substr(0, 28);
  string right = key_56.substr(28, 56);

  for (int i = 0; i < 16; i++) {
    if (i == 0 || i == 1 || i == 8 || i == 15) {
      left = shift_left(left);
      right = shift_left(right);
    }

    else{
      left = shift_left(shift_left(left));
      right = shift_left(shift_left(right));
    }
    string key_48 = left + right;
    string sub_key = "";

    for (int j = 0; j < 48; j++) {
      sub_key += key_48[PC2[j] - 1];
    }
    sub_keys.push_back(sub_key);
  }
  return sub_keys;
}
