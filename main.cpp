#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <cstring>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "naive.h"
#include "BBST.h"
#include "trie.h"
#include "hash.h"

std::string readTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string text;

    if (file.is_open()) {
        std::string line;
        while (file >> line) {
            text += line + " ";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
    }

    return text;
}

std::string removeCharsFromString(std::string str) {
    char chars[] = ".,;:'!?()- \"%$@#^&*=+`";
    for (unsigned int i = 0; i < strlen(chars); ++i) {
        str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
    }
    return str;
}

long long measureBuildNaiveDictionary(const std::string& dictionaryFile, std::vector<std::string>& dictionary) {
    auto start = std::chrono::high_resolution_clock::now();
    dictionary = buildDictionary(dictionaryFile);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureBuildAVLDicitionary(const std::string& dictionaryFile, AVLTree& dictionaryTree) {
    auto start = std::chrono::high_resolution_clock::now();
    dictionaryTree.loadDictionary(dictionaryFile);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureBuildTrieDictionary(const std::string& dictionaryFile, Trie& trie) {
    auto start = std::chrono::high_resolution_clock::now();
    loadWordList(trie, dictionaryFile);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureBuildHashDictionary(const std::string& dictionaryFile, std::unordered_set<std::string>& hashDictionary) {
    auto start = std::chrono::high_resolution_clock::now();
    loadHashDictionary(dictionaryFile, hashDictionary);
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureNaiveSearch(const std::string* textWords, int wordCount, const std::vector<std::string>& dictionary, bool* results) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < wordCount; ++i) {
        results[i] = isWordSpelledCorrectly(textWords[i], dictionary);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureAVLTreeSearch(const std::string* textWords, int wordCount, const AVLTree& dictionaryTree, bool* results) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < wordCount; ++i) {
        results[i] = dictionaryTree.search(textWords[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureTrieSearch(const std::string* textWords, int wordCount, const Trie& trie, bool* results) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < wordCount; ++i) {
        results[i] = trie.search(textWords[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

long long measureHashSearch(const std::string* textWords, int wordCount, const std::unordered_set<std::string>& hashDictionary, bool* results) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < wordCount; ++i) {
        results[i] = hashDictionary.find(textWords[i]) != hashDictionary.end();
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
}

int main() {
    AVLTree dictionaryTree;
    Trie trie;
    std::unordered_set<std::string> hashDictionary;
    std::vector<std::string> naiveDictionary;

    std::string dictionaryFile = "C:\\Users\\serwis\\CLionProjects\\un2\\words.txt";
    std::string textFile = "C:\\Users\\serwis\\CLionProjects\\un2\\pattern.txt";

    std::string text = readTextFromFile(textFile);
    std::istringstream iss(text);
    std::string word;
    std::vector<std::string> textWords;

    while (iss >> word) {
        textWords.push_back(removeCharsFromString(word));
    }

    int wordCount = textWords.size();
    bool* results = new bool[wordCount];

    std::cout << "size naive_build BBST_build trie_build hash_build naive_search BBST_search trie_search hash_search" << std::endl;
    for (int power = 1; power <= textWords.size(); power *= 10) {
        for (int d = 1; d < 10; d++) {
            int size = d * power;
            if (size > textWords.size()) break;

            long long naiveSearchTime = 0;
            long long BBSTSearchTime = 0;
            long long trieSearchTime = 0;
            long long hashSearchTime = 0;

            long long naiveBuildTime = measureBuildNaiveDictionary(dictionaryFile, naiveDictionary);
            long long BBSTBuildTime = measureBuildAVLDicitionary(dictionaryFile, dictionaryTree);
            long long trieBuildTime = measureBuildTrieDictionary(dictionaryFile, trie);
            long long hashBuildTime = measureBuildHashDictionary(dictionaryFile, hashDictionary);

            int T = 35;

            for (int t = 0; t < T; t++) {
                naiveSearchTime += measureNaiveSearch(textWords.data(), size, naiveDictionary, results);
                BBSTSearchTime += measureAVLTreeSearch(textWords.data(), size, dictionaryTree, results);
                trieSearchTime += measureTrieSearch(textWords.data(), size, trie, results);
                hashSearchTime += measureHashSearch(textWords.data(), size, hashDictionary, results);

            }

            std::cout << size << " "<< naiveSearchTime / T << " " << BBSTSearchTime / T << " " << trieSearchTime / T << " " << hashSearchTime / T << std::endl;
        }
    }

    delete[] results;

    return 0;
}
