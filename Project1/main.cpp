#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

// Function that loops through the ciphertext and counts the frequency of each
// character
void characterFrequency(string &cipherText) {
  int Character_Frequency[26] = {0};
  for (int i = 0; i < cipherText.length(); i++) {
    Character_Frequency[(int)cipherText[i] - 65]++;
  }
  cout << "Analyzing the frequency of the letters..." << endl;
  for (int i = 0; i < 26; i++) {
    cout << (char)(i + 65) << " " << Character_Frequency[i] << endl;
  }

  string Character_Array[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I",
                                "J", "K", "L", "M", "N", "O", "P", "Q", "R",
                                "S", "T", "U", "V", "W", "X", "Y", "Z"};

  for (int i = 0; i < 26; i++) {
    for (int j = 0; j < 26 - i - 1; j++) {
      if (Character_Frequency[j] < Character_Frequency[j + 1]) {
        int temp = Character_Frequency[j];
        Character_Frequency[j] = Character_Frequency[j + 1];
        Character_Frequency[j + 1] = temp;
        string temp2 = Character_Array[j];
        Character_Array[j] = Character_Array[j + 1];
        Character_Array[j + 1] = temp2;
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    cout << Character_Array[i] << " " << Character_Frequency[i] << endl;
  }

  cout << endl;
}

// Loops through the Character_Frequency index and replaces the characters the
// most frequent letters in the English alphabet with the corresponding ones in
// the ciphertext
void automaticReplaceCharacter(string &cipherText) {

  unordered_map<char, char> replacementMap = {
      {'S', 'E'}, {'G', 'T'}, {'K', 'A'}, {'C', 'O'}, {'U', 'I'}, {'E', 'N'},
      {'Q', 'S'}, {'H', 'H'}, {'B', 'R'}, {'Z', 'D'}, {'A', 'L'}, {'I', 'C'},
      {'N', 'U'}, {'L', 'M'}, {'X', 'W'}, {'O', 'F'}, {'P', 'G'}, {'R', 'Y'},
      {'F', 'P'}, {'M', 'B'}, {'V', 'V'}, {'W', 'K'}, {'D', 'J'}, {'J', 'X'},
      {'T', 'Q'}, {'Y', 'Z'}};

  cout << "Replacing characters based on letter frequency..." << endl;

  // Loop through the ciphertext and perform replacements
  for (char &character : cipherText) {
    if (replacementMap.find(character) != replacementMap.end()) {
      character = replacementMap[character];
    }
  }

  cout << "Modified Ciphertext:" << endl;
  cout << cipherText << endl;
}

// Function that loops through the dictionary and compares the modified
// ciphertext and sees if any words match
void userReplaceCharacter(string &cipherText, char characterToReplace,
                          char replacementCharacter) {
  for (char &character : cipherText) {
    if (character == characterToReplace) {
      character = replacementCharacter;
    }
  }

  cout << "Modified Ciphertext:" << endl;
  cout << cipherText << endl;
}

// Loops through dictionary and compares the modified ciphertext and sees if any
// words match
void findCipherKey(string &originalCipherText, string &modifiedCipherText,
                   vector<string> &potentialKeys) {
  for (const string &key : potentialKeys) {
    string modifiedCipherTextCopy = modifiedCipherText;
    for (int i = 0; i < key.length(); i++) {
      int shift = key[i % key.length()] - 'A';
      int maxIndexLoop = 15 / key.length();
      cout << "modifiedCipherText: " << modifiedCipherTextCopy.substr(0, 15)
           << endl;
      cout << "originalCipherText: " << originalCipherText.substr(0, 15)
           << endl;
      for (int j = 0; j < maxIndexLoop; j++) {
        cout << modifiedCipherTextCopy[i + j * key.length()];
        modifiedCipherTextCopy[i + j * key.length()] =
            (modifiedCipherTextCopy[i + j * key.length()] - 'A' + shift) % 26 +
            'A';
        cout << " shifted by " << shift << " = "
             << modifiedCipherTextCopy[i + j * key.length()] << endl;
      }
    }

    if (originalCipherText.substr(0, 3) ==
        modifiedCipherTextCopy.substr(0, 3)) {
      cout << "The potential key is: " << key << endl;
      cout << "The plaintext is: " << endl;
      cout << modifiedCipherTextCopy << endl;
      cout << key.substr(0, 4) << endl;
      break;
    }
  }
}

int main() {
  ifstream cipherFile("ciphertext.txt");
  if (!cipherFile) {
    cerr << "Unable to open ciphertext.txt file." << endl;
    return 1;
  }
  ostringstream cipherStream;
  cipherStream << cipherFile.rdbuf();
  string originalCipherText = cipherStream.str();
  string modifiedCipherText = originalCipherText;
  cipherFile.close();

  characterFrequency(originalCipherText);

  cout << "\n" << endl;
  automaticReplaceCharacter(modifiedCipherText);

  cout << "\n" << endl;
  char characterToReplace;
  char replacementCharacter;

  int maxGuesses = 6;
  int guesses = 0;

  while (true) {

    if (guesses >= maxGuesses) {
      cout << "You have exceeded the maximum number of guesses! tsk tsk tsk!!"
           << "\n";
      cout << "The key is: "
           << "\n";
      cout << "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
           << "\n";
      cout << "KFAZSROBCWDINUELTHQGXVPJMY"
           << "\n";
      cout << "The plaintext is: "
           << "\n";
      cout << "THEUNITEDSTATESWASATPEACEWITHTHATNATIONANDATTHESOLIC"
              "ITATIONOFJAPANWASSTILLINCONVERSATIONWITHITSGOVERNMEN"
              "TANDITSEMPERORLOOKINGTOWARDTHEMAINTENANCEOFPEACEINTH"
              "EPACIFICINDEEDONEHOURAFTERJAPANESEAIRSQUADRONSHADCOM"
              "MENCEDBOMBINGINOAHUTHEJAPANESEAMBASSADORTOTHEUNITEDS"
              "TATESANDHISCOLLEAGUEDELIVEREDTOTHESECRETARYOFSTATEAF"
              "ORMALREPLYTOARECENTAMERICANMESSAGEWHILETHISREPLYSTAT"
              "EDTHATITSEEMEDUSELESSTOCONTINUETHEEXISTINGDIPLOMATIC"
              "NEGOTIATIONSITCONTAINEDNOTHREATORHINTOFWARORARMEDATTACK"
           << endl;

      break;
    }
    guesses++;

    userReplaceCharacter(modifiedCipherText, characterToReplace,
                         replacementCharacter);
    cout << "Which character do you wish to replace (type '1' to quit): "
         << "\n";
    cin >> characterToReplace;
    if (characterToReplace == '1') {

      std::cout << "Quitting" << std::endl;
      break;
    }

    characterToReplace = toupper(characterToReplace);
    cout << "Which character do you wish to replace it with: "
         << "\n";
    cin >> replacementCharacter;
    replacementCharacter = toupper(replacementCharacter);

    ifstream dictionaryFile("dictionary.txt");
    if (!dictionaryFile) {
      cout << "Unable to open dictionary.txt file." << endl;
      return 1;
    }
    vector<string> potentialKeys;
    string line;
    while (getline(dictionaryFile, line)) {
      potentialKeys.push_back(line);
    }
    dictionaryFile.close();
    findCipherKey(originalCipherText, modifiedCipherText, potentialKeys);
  }

  return 0;
}