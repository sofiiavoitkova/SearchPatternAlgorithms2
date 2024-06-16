#ifndef NAIVE_H
#define NAIVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void naivesearch(const string& P, const string& T, bool& found) {
    int M = P.length();
    int N = T.length();

    for (int i = 0; i <= N - M; i++) {
        int j;
        for (j = 0; j < M; j++) {
            if (T[i + j] != P[j]) {
                break;
            }
        }
        if (j == M) {
            found = true;
            return;
        }
    }
    found = false;
}

vector<string> buildDictionary(const string& dictionaryFile) {
    vector<string> dictionary;
    ifstream file(dictionaryFile);
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    return dictionary;
}

bool isWordSpelledCorrectly(const string& word, const vector<string>& dictionary) {
    for (const auto& dictWord : dictionary) {
        bool found = false;
        naivesearch(word, dictWord, found);
        if (found) {
            return true;
        }
    }
    return false;
}

#endif // NAIVE_H
