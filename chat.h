#pragma once
#include "hash_table.h"
#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    Chat();
    void reg(char _login[LOGINLENGTH], char _pass[], int pass_length);
    bool login(char _login[LOGINLENGTH], char _pass[], int pass_length);

private:
    HashTable authTable;  // Используйте хеш-таблицу для хранения логинов и хешей паролей
    int data_count;
    int tableSize;

    int computePasswordHash(const char* key, int pass_length);

};