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
    for (size_t i = 0; i <  str_len/2; i++) {
        if (tolower(str[i]) != tolower(str[str.length() - i - 1])) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        exit(-1);
    }

    std::string file = read_file_from_path(argv[argc - 1]);

    size_t count = 1;
    for (char i: file) {
        if (i == '\n') {
            count += 1;
        }
    }

    auto palindromes = new std::string[count];

    size_t i = 0;
    size_t str_count = 0;
    while (count > 0) {
        std::string line;
        while (file[i] != '\n') {
            if (file[i] == '\0') {
                break;
            }

            line += file[i];
            i += 1;
        }

        if (is_palindrome(line)) {
            palindromes[str_count] = line;
            str_count++;
        }

        count--;
        i++;
    };

    printf("{\n\t\"count_palindromes\": %zu,\n\t\"palindromes\": [\"", str_count);
    for (size_t i = 0; i < str_count - 1; i++) {
        printf("%s\", ", palindromes[i].c_str());
    }
    printf("%s\"]\n}", palindromes[str_count - 1].c_str());

    delete[] palindromes;
    return 0;
}