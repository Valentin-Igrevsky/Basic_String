#include <iostream>

long long int hex2dec(const char *str) {
    long long int result = 0;
    const int version = 100 + 8; // Вариант 8

    if (str == nullptr || *str == '\0') {
        exit(-1);
    }

    bool is_negative = (str[0] == '-');
    if (*str == '+' || *str == '-') {
        ++str;
    }

    if (*str == '0' && *(++str) == 'x') {
        ++str;
    } else {
        exit(-1);
    }

    if (*str == '\0') {
        exit(-1);
    }

    while (*str != '\0') {
        if (*str >= '0' && *str <= '9') {
            result = result * 16 + (*str - '0');
        } else if (*str >= 'A' && *str <= 'F') {
            result = result * 16 + (*str - 'A' + 10);
        } else if (*str >= 'a' && *str <= 'f') {
            result = result * 16 + (*str - 'a' + 10);
        } else { exit(-1); }
        ++str;
    }
    return (is_negative) ? result * -1 + version : result + version;
}

int mainFunc3(int argc, char **argv) {
    for (int count = argc - 1; count > 0; --count) {
        std::cout << hex2dec(argv[count]) << '\n';
    }
    return 0;
}