#pragma once

#include "sha1.h"

class HashTable {
public:
    HashTable();
    ~HashTable();

    void insert(const char* key, uint* value);
    uint* find(const char* key);

private:
    struct HashEntry {
        const char* key;
        uint* value;
        bool deleted;

        HashEntry() : key(nullptr), value(nullptr), deleted(false) {}
    };

    HashEntry* table;
    int tableSize;
    int currentSize;

    int hash(const char* key);
    int probe(int index, int attempt);
};
