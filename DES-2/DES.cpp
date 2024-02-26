#include "DES.h"
#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <sstream>
#include "des_utils.h"
#include "DES.h"
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
using namespace std;

#ifndef DES_UTILS_H
#define DES_UTILS_H

/********************************************/
/* Tables for initial and final permutation */
/********************************************/

// initial permutation
// int IP[64] = {
// 	58,	50,	42,	34,	26,	18,	10,	2,
// 	60,	52,	44,	36,	28,	20,	12,	4,
// 	62,	54,	46,	38,	30,	22,	14,	6,
// 	64,	56,	48,	40,	32,	24,	16,	8,
// 	57,	49,	41,	33,	25,	17,	9,	1,
// 	59,	51,	43,	35,	27,	19,	11,	3,
// 	61,	53,	45,	37,	29,	21,	13,	5,
// 	63,	55,	47,	39,	31,	23,	15,	7
// };

// // final permutation
// int FP[64] = {
// 	40,	8,	48,	16,	56,	24,	64,	32,
// 	39,	7,	47,	15,	55,	23,	63,	31,
// 	38,	6,	46,	14,	54,	22,	62,	30,
// 	37,	5,	45,	13,	53,	21,	61,	29,
// 	36,	4,	44,	12,	52,	20,	60,	28,
// 	35,	3,	43,	11,	51,	19,	59,	27,
// 	34,	2,	42,	10,	50,	18,	58,	26,
// 	33,	1,	41,	9,	49,	17,	57,	25
// };

/*********************************/
/* Tables for the round function */
/*********************************/

// expansion box
int E[48] = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11,
             12, 13, 12, 13, 14, 15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21,
             22, 23, 24, 25, 24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

int P[32] = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
             2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

// substitution boxes
// addressable using xxyyyy where xx are the first and last bits, and yyyy are
// the middle 4 bits
int S1[64] = {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
              0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
              4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
              15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};

int S2[64] = {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
              3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
              0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
              13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};

int S3[64] = {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
              13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
              13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
              1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12};

int S4[64] = {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
              13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
              10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
              3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};

int S5[64] = {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
              14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
              4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
              11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};

int S6[64] = {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
              10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
              9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
              4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};

int S7[64] = {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
              13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
              1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
              6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};

int S8[64] = {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
              1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
              7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
              2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

int *SBOXMAP[] = {S1, S2, S3, S4, S5, S6, S7, S8};

#endif

string shift_left(string sub_key);
vector<string> key_gen(string key);
string expansion(string right_block);
string pBox(string right_block);
string sBox(string right_block);
string round(string right_block, string key);
int binToDec(string bin);
string decToBin(int dec);
string XOR(string bin1, string bin2, int len);
string encryption(string plaintext, vector<string> keys);
string decryption(string encrypted, vector<string> keys);
vector<string> block_generation(string text, int encryption);
vector<string> asciiToBinary(vector<string> blocks);
string binaryToAscii(string blocks);
string readfile(string filename);
int write_file(string text, string filename);
string hexToBinary(string hexstring);
string unpadded(string padded);

#include <bitset>
using namespace std;

string shift_left(string sub_key)
{
    char first_char = sub_key[0];
    for (int i = 0; i < 27; i++)
    {
        sub_key[i] = sub_key[i + 1];
    }
    sub_key[27] = first_char;
    return sub_key;
}

vector<string> key_gen(string key)
{
    vector<string> sub_keys;
    string small_key = "";
    for (int i = 0; i < 56; i++)
    {
        small_key += key[(int)PC1[i] - 1];
    }

    string left = small_key.substr(0, 28);
    string right = small_key.substr(28, 28);
    for (int i = 0; i < 16; i++)
    {
        if (i == 0 || i == 1 || i == 8 || i == 15)
        {
            left = shift_left(left);
            right = shift_left(right);
        }
        else
        {
            left = shift_left(left);
            left = shift_left(left);
            right = shift_left(right);
            right = shift_left(right);
        }
        string final_sub_key = left + right;
        string round_key = "";
        for (int j = 0; j < 48; j++)
        {
            round_key += final_sub_key[(int)PC2[j] - 1];
        }
        sub_keys.push_back(round_key);
    }
    return sub_keys;
}

/*******************************/
/* Tables for the key schedule */
/*******************************/

// PC-1 table (initial key permutation)
int PC1[56] = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
               10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
               63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
               14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4};

// PC-2 table (permutation for generating each subkey)
int PC2[48] = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
               26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
               51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string hexToBinary(string hexstring)
{
    string binary_string;
    for (int i = 0; i < hexstring.size(); i++)
    {
        switch (hexstring[i])
        {
        case '0':
            binary_string += "0000";
            break;
        case '1':
            binary_string += "0001";
            break;
        case '2':
            binary_string += "0010";
            break;
        case '3':
            binary_string += "0011";
            break;
        case '4':
            binary_string += "0100";
            break;
        case '5':
            binary_string += "0101";
            break;
        case '6':
            binary_string += "0110";
            break;
        case '7':
            binary_string += "0111";
            break;
        case '8':
            binary_string += "1000";
            break;
        case '9':
            binary_string += "1001";
            break;
        case 'A':
            binary_string += "1010";
            break;
        case 'a':
            binary_string += "1010";
            break;
        case 'B':
            binary_string += "1011";
            break;
        case 'b':
            binary_string += "1011";
            break;
        case 'C':
            binary_string += "1100";
            break;
        case 'c':
            binary_string += "1100";
            break;
        case 'D':
            binary_string += "1101";
            break;
        case 'd':
            binary_string += "1101";
            break;
        case 'E':
            binary_string += "1110";
            break;
        case 'e':
            binary_string += "1110";
            break;
        case 'F':
            binary_string += "1111";
            break;
        case 'f':
            binary_string += "1111";
            break;
        }
    }
    return binary_string;
}

vector<string> asciiToBinary(vector<string> blocks)
{
    vector<string> binary_blocks;
    for (int i = 0; i < blocks.size(); i++)
    {
        string binary_block;
        for (int j = 0; j < 8; j++)
        {
            binary_block += bitset<8>(blocks[i][j]).to_string();
        }
        binary_blocks.push_back(binary_block);
    }
    return binary_blocks;
}

string binaryToAscii(string blocks)
{
    string ascii_blocks = "";
    string ascii_blocks_trial = "";
    int extra_block = blocks.size() % 64;
    for (int i = 0; i < blocks.size() / 64; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            unsigned long dec =
                bitset<8>(blocks.substr(64 * i, 64).substr(8 * j, 8)).to_ulong();
            ascii_blocks += dec;
        }
    }
    if (extra_block / 8)
    {
        for (int j = 0; j < extra_block / 8; j++)
        {
            unsigned long dec =
                bitset<8>(blocks.substr(blocks.size() - extra_block, extra_block)
                              .substr(8 * j, 8))
                    .to_ulong();
            ascii_blocks_trial +=
                blocks.substr(blocks.size() - extra_block, extra_block)
                    .substr(8 * j, 8);
            ascii_blocks += dec;
        }
    }
    return ascii_blocks;
}

int binToDec(string bin)
{
    unsigned long dec = bitset<6>(bin).to_ulong();
    return dec;
}

string decToBin(int dec)
{
    string binary = bitset<4>(dec).to_string();
    return binary;
}

string readfile(string filename)
{
    ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    string output = buffer.str();
    return output;
}

string XOR(string bin1, string bin2, int len)
{
    string output;
    if (len == 48)
    {
        bitset<48> binary1(bin1);
        bitset<48> binary2(bin2);
        output = (binary1 ^= binary2).to_string();
    }
    else if (len == 32)
    {
        bitset<32> binary1(bin1);
        bitset<32> binary2(bin2);
        output = (binary1 ^= binary2).to_string();
    }
    else
    {
        bitset<64> binary1(bin1);
        bitset<64> binary2(bin2);
        output = (binary1 ^= binary2).to_string();
    }
    return output;
}

vector<string> block_generation(string text, int encryption)
{
    vector<string> blocks;
    if (encryption)
    {
        int num_of_blocks = text.size() / 8;
        int padding = (text.size()) % 8;
        if (padding)
        {
            int padding_num = 8 - padding;
            for (int i = 0; i < padding_num; i++)
            {
                if (i < 2)
                {
                    text += 10;
                }
                else
                {
                    text += (padding_num - 2);
                }
            }
            num_of_blocks += 1;
        }
        else
        {
            for (int i = 0; i < 8; i++)
            {
                if (i < 2)
                {
                    text += 10;
                }
                else
                {
                    text += 6;
                }
            }
            num_of_blocks += 1;
        }
        for (int i = 0; i < num_of_blocks; i++)
        {
            blocks.push_back(text.substr(i * 8, 8));
        }
        return blocks;
    }
    else
    {
        for (int i = 0; i < text.size() / 8; i++)
        {
            blocks.push_back(text.substr(i * 8, 8));
        }
        return blocks;
    }
}

int write_file(string text, string filename)
{
    fstream file;
    file.open(filename, ios_base::out);
    if (!file.is_open())
    {
        cout << "Unable to open the file.\n";
        return 0;
    }
    string myStr = text;
    file << myStr;
    file.close();
    return 0;
}

string unpadded(string padded)
{
    string check = padded.substr((padded.size() - 4), 4);
    if (check.compare("1010") == 0)
    {
        if (padded.substr((padded.size() - 8), 4).compare("1010"))
        {
            return padded.substr(0, (padded.size() - 16));
        }
        else
        {
            return padded.substr(0, (padded.size() - 8));
        }
    }
    else
    {
        unsigned long num_bytes = bitset<4>(check).to_ulong();
        return padded.substr(0, (padded.size() - (8 * (num_bytes + 2))));
    }
}

// initial permutation
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

// final permutation
int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

string expansion(string right_block)
{
    string expanded = "";
    for (int i = 0; i < 48; i++)
    {
        expanded += right_block[(int)E[i] - 1];
    }
    return expanded;
}

string pBox(string right_block)
{
    string permuted = "";
    for (int i = 0; i < 32; i++)
    {
        permuted += right_block[(int)P[i] - 1];
    }
    return permuted;
}

string sBox(string right_block)
{
    string substituted = "";
    for (int i = 0; i < 8; i++)
    {
        string sub_block = right_block.substr(6 * i, 6);
        string new_sub = "";
        new_sub += sub_block[0];
        new_sub += sub_block[5];
        new_sub += sub_block.substr(1, 4);
        int index = binToDec(new_sub);
        int substituted_dec = (int)SBOXMAP[i][index];
        string substituted_block = decToBin(substituted_dec);
        substituted += substituted_block;
    }

    return substituted;
}

// Your DES implmentaion has to encrypt and decrypt 64 bit of binary string
//  you only have to make changes to this file
//  Required blocks, operations and functions example = XOR, sBox etc. are
//  already provided, check operations.cpp and rounds.cpp

string encryption(string plaintext, vector<string> keys) {
  string encrypted;
  encrypted = "0";
  ;
  // Start Your code from here //

  string permuted_text = "";
  for (int i = 0; i < 64; i++) {
    permuted_text += plaintext[IP[i] - 1];
  }

  string left_block = permuted_text.substr(0, 32);
  string right_block = permuted_text.substr(32, 32);

  for (int i = 0; i < 16; i++) {
    string temp = right_block;
    right_block = XOR(expansion(right_block), keys[i], 48);
    right_block = sBox(right_block);
    right_block = pBox(right_block);
    right_block = XOR(left_block, right_block, 32);
    left_block = temp;
  }

  string swapped_blocks = right_block + left_block;

  string final_permutation = "";
  for (int i = 0; i < 64; i++) {
    final_permutation += swapped_blocks[FP[i] - 1];
  }

  encrypted = final_permutation;

  return encrypted;
}

string decryption(string encrypted, vector<string> keys)
{
    string decrypted;
    // Start Your code from here //

    string permuted_text = "";
    for (int i = 0; i < 64; i++)
    {
        permuted_text += encrypted[IP[i] - 1];
    }

    string left_block = permuted_text.substr(0, 32);
    string right_block = permuted_text.substr(32, 32);

    for (int i = 0; i < 16; i++)
    {
        string temp = right_block;
        right_block = XOR(expansion(right_block), keys[15 - i], 48);
        right_block = sBox(right_block);
        right_block = pBox(right_block);
        right_block = XOR(left_block, right_block, 32);
        left_block = temp;
    }

    string swapped_blocks = right_block + left_block;

    string final_permutation = "";
    for (int i = 0; i < 64; i++)
    {
        final_permutation += swapped_blocks[FP[i] - 1];
    }

    decrypted = final_permutation;

    return decrypted;
}


using namespace std;

int main()
{
    char *mySecret = getenv("key1");
    string key = mySecret;
    string text;
    vector<string> sub_keys = key_gen(key);
    cin >> text;
    string test_type = text.substr(0, text.find(","));
    string text_main = text.substr(text.find(",") + 1, text.size());
    if (!test_type.compare("encrypt"))
        cout << encryption(text_main, sub_keys);
    else
    {
        cout << decryption(text_main, sub_keys);
    }

    string plaintext = "0123456789ABCDEF";
    vector<string> keys = key_gen("133457799BBCDFF1");

    string encrypted_text = encryption(plaintext, keys);

    cout << "Encrypted text: " << encrypted_text << endl;

    return 0;
}