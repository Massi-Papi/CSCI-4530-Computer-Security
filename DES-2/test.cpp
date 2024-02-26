#include "DES.h"
#include "permutation.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string encryption(string plaintext, vector<string> keys)
{
    string encrypted;
    encrypted = "0";
    ;
    // Start Your code from here //

    string permuted_text = "";
    for (int i = 0; i < 64; i++)
    {
        permuted_text += plaintext[IP[i] - 1];
    }

    string left_block = permuted_text.substr(0, 32);
    string right_block = permuted_text.substr(32, 32);

    for (int i = 0; i < 16; i++)
    {
        string temp = right_block;
        right_block = XOR(expansion(right_block), keys[i], 48);
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
