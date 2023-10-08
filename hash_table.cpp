#include "hash_table.h"
#include "chat.h"

HashTable::HashTable() {
    tableSize = SIZE;  
    currentSize = 0;
    table = new HashEntry[tableSize];
}

HashTable::~HashTable() {
    delete[] table;
}

int HashTable::hash(const char* key) {
    // ���������� ���� ���-�������, ��������, ������� ���������
    // � ������� ������ � ������� ��� ������� �����
    unsigned long long hashValue = 0;
    unsigned long long multiplier = 263; // ������� �����, ��������

    // �������� �� �������� ����� � ��������� ���-��������
    for (int i = 0; key[i]; i++) {
        hashValue = (hashValue * multiplier + key[i]) % tableSize;
    }

    return static_cast<int>(hashValue);
}

int HashTable::probe(int index, int attempt) {
    // ���������� ����� ������������� ������������
    // � ������� ����� ������ ��� ������� ������� ��� ������
    int step = attempt * attempt; // ������������ ���

    // ��������� ����� ������ � ������ ������������� ����
    int newIndex = (index + step) % tableSize;

    return newIndex;
}

void HashTable::insert(const char* key, uint* value) {
    // ������� �������� � �������������� ������ ������������� ������������
    int initialIndex = hash(key);
    int attempt = 0;
    int currentIndex = initialIndex;

    while (table[currentIndex].key != nullptr && !table[currentIndex].deleted) {
        attempt++;
        currentIndex = probe(initialIndex, attempt);
    }

    table[currentIndex].key = key;
    table[currentIndex].value = value;
    table[currentIndex].deleted = false;
}

uint* HashTable::find(const char* key) {
    // ����� �������� � �������������� ������ ������������� ������������
    int initialIndex = hash(key);
    int attempt = 0;
    int currentIndex = initialIndex;

    while (table[currentIndex].key != nullptr) {
        if (!table[currentIndex].deleted && strcmp(table[currentIndex].key, key) == 0) {
            return table[currentIndex].value;
        }

        attempt++;
        currentIndex = probe(initialIndex, attempt);
    }

    return nullptr; // ������� � �������� ������ �� ������
}