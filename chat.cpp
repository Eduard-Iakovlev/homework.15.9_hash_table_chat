#include "chat.h"
#include "iostream"
#include "string.h"
#include "hash_table.h"

Chat::Chat() {
    data_count = 0;
}
void Chat::reg(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
 // Вычислите хеш пароля
    uint passwordHash = computePasswordHash(_pass, pass_length);

    // Вставьте пару ключ-значение в хеш-таблицу
    authTable.insert(_login, &passwordHash);
}
bool Chat::login(char _login[LOGINLENGTH], char _pass[], int pass_length) {
    // Ваш код
    // Нужно вернуть true в случае успешного логина
    // Найдите хеш пароля по логину в хеш-таблице
    uint* storedPasswordHash = authTable.find(_login);

    if (storedPasswordHash != nullptr) {
        // Сравните хеш пароля с введенным паролем
        uint inputPasswordHash = computePasswordHash(_pass, pass_length);

        if (*storedPasswordHash == inputPasswordHash) {
            // Пароль совпадает, пользователь аутентифицирован
            return true;
        }
    }

    // Пароль не совпадает или логин не найден
    return false;
}

int Chat::computePasswordHash(const char* key, int pass_length)
{
    unsigned long long hashValue = 0;
    unsigned long long multiplier = 263; // Простое число, например

    // Пройдите по символам ключа и вычислите хеш-значение
    for (int i = 0; key[i]; i++) {
        hashValue = (hashValue * multiplier + key[i]) % tableSize;
    }

    return static_cast<int>(hashValue);

}
