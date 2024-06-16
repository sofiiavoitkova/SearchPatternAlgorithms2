#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <stdexcept>
#include <vector>

class Node {
public:
    std::string key;
    int value;
    Node(const std::string& key, int value) : key(key), value(value) {}
};

class HashMap {
public:
    unsigned int SIZE;
    std::vector<Node*> table;

    HashMap(unsigned int size) : SIZE(size) {
        table.resize(SIZE);
        for (unsigned int i = 0; i < SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    unsigned int getHash(const std::string& k) const {
        unsigned int value = 0;
        for (char ch : k) {
            value = 31 * value + ch;
        }
        return value;
    }

    int getIndex(const std::string& key) const {
        unsigned int h = getHash(key) % SIZE;
        unsigned int n = 0;
        unsigned int index;

        while (n < SIZE) {
            index = (h + n * n) % SIZE;
            if (table[index] == nullptr || table[index]->key == key) {
                return index;
            }
            n++;
        }
        return -1;
    }

    void insert(const std::string& key, const int& value) {
        int index = getIndex(key);

        if (table[index] == nullptr) {
            table[index] = new Node(key, value);
        } else {
            table[index]->value = value;
        }

    }

    bool contains(const std::string& key) const {
        int index = getIndex(key);
        return index != -1 && table[index] != nullptr && table[index]->key == key;
    }

    ~HashMap() {
        for (auto node : table) {
            delete node;
        }
    }
};

void loadHashDictionary(const std::string& dictionaryFile, std::unordered_set<std::string>& hashDictionary) {
    std::ifstream file(dictionaryFile);
    std::string word;
    if (file.is_open()) {
        while (file >> word) {
            hashDictionary.insert(word);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << dictionaryFile << std::endl;
    }
}

#endif // HASH_H
