#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string read_file_from_path(const std::string &path) {
    std::ifstream f(path);
    std::string result;
    if (f) {
        std::stringstream ss;
        ss << f.rdbuf();
        return ss.str();
    } else {
        return {};
    }
}

bool is_palindrome(const std::string &str) {
    size_t str_len = str.length();
    for (size_t i = 0; i < str_len / 2; i++) {
        if (std::tolower(str[i]) != std::tolower(str[str_len - i - 1])) {
            return false;
        }
    }
    return true;
}

std::string *palindrome_searcher(const std::string &file, size_t &count) {
    auto palindromes = new std::string[0];
    std::string line;
    for (char i: file) {
        if (i == '\r') {
            continue;
        } else if (i == '\n') {
            if (line.length() != 0 && is_palindrome(line)) {
                auto temp_mas = new std::string[count + 1];

                for (int j = 0; j < count; j++) {
                    temp_mas[j] = palindromes[j];
                }

                temp_mas[count] = line;
                count++;
                delete[] palindromes;
                palindromes = new std::string[count];

                for (int j = 0; j < count; j++) {
                    palindromes[j] = temp_mas[j];
                }

                delete[] temp_mas;
            }
            line.clear();
        } else {
            line += i;
        }
    }
    return palindromes;
}

int mainFunc(int argc, char *argv[]) {
    if (argc > 2) {
        exit(-1);
    }

    std::string file = read_file_from_path(argv[argc - 1]);
    size_t palindromes_count = 0;
    auto palindromes = palindrome_searcher(file, palindromes_count);

    printf("{\n\t\"count_palindromes\": %zu,\n\t\"palindromes\": [", palindromes_count);
    for (size_t i = 0; i < palindromes_count; i++) {
        printf("\"%s\"", palindromes[i].c_str());
        if (i != palindromes_count - 1) {
            std::cout << ", ";
        }
    }
    printf("]\n}");

    delete[] palindromes;
    return 0;
}