#include "DES.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

int main() {
  char *mySecret = getenv("key1");
  string key = mySecret;
  string text;
  vector<string> sub_keys = key_gen(key);
  cin >> text;
  string test_type = text.substr(0, text.find(","));
  string text_main = text.substr(text.find(",") + 1, text.size());
  if (!test_type.compare("encrypt"))
    cout << encryption(text_main, sub_keys);
  else {
    cout << decryption(text_main, sub_keys);
  }
}