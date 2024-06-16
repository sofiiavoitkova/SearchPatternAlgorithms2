#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <fstream>

class Trie {
public:
    bool isLeaf;
    Trie* nodes[128];

    Trie() {
        isLeaf = false;
        for (int i = 0; i < 128; i++) {
            nodes[i] = nullptr;
        }
    }

    void insert(const std::string& key) {
        Trie* temp = this;
        for (char ch : key) {
            if (temp->nodes[ch] == nullptr) {
                temp->nodes[ch] = new Trie();
            }
            temp = temp->nodes[ch];
        }
        temp->isLeaf = true;
    }

    bool search(const std::string& key) const {
        const Trie* temp = this;
        for (char ch : key) {
            temp = temp->nodes[ch];
            if (temp == nullptr) {
                return false;
            }
        }
        return temp->isLeaf;
    }

    ~Trie() {
        for (int i = 0; i < 128; i++) {
            delete nodes[i];
        }
    }
};

void loadWordList(Trie& trie, const std::string& filename) {
    std::ifstream file(filename);
    std::string word;
    if (file.is_open()) {
        while (file >> word) {
            trie.insert(word);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

#endif // TRIE_H
