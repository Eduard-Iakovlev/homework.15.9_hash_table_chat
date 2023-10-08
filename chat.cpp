#include "chat.h"
#include "iostream"
#include "string.h"
#include "hash_table.h"

Chat::Chat() {
    data_count = 0;
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // ��� ���
 // ��������� ��� ������
    uint passwordHash = computePasswordHash(_pass, pass_length);

    // �������� ���� ����-�������� � ���-�������
    authTable.insert(_login, &passwordHash);
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // ��� ���
    // ����� ������� true � ������ ��������� ������
    // ������� ��� ������ �� ������ � ���-�������
    uint* storedPasswordHash = authTable.find(_login);

    if (storedPasswordHash != nullptr) {
        // �������� ��� ������ � ��������� �������
        uint inputPasswordHash = computePasswordHash(_pass, pass_length);

        if (*storedPasswordHash == inputPasswordHash) {
            // ������ ���������, ������������ ����������������
            return true;
        }
    }

    // ������ �� ��������� ��� ����� �� ������
    return false;
}

int Chat::computePasswordHash(const char* key, int pass_length)
{
    unsigned long long hashValue = 0;
    unsigned long long multiplier = 263; // ������� �����, ��������

    // �������� �� �������� ����� � ��������� ���-��������
    for (int i = 0; key[i]; i++) {
        hashValue = (hashValue * multiplier + key[i]) % tableSize;
    }

    return static_cast<int>(hashValue);

}
