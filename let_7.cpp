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
        if (std::tolower(str[i]) != std::tolower(str[str_len - i - 1])) {
            return false;
        }
    }
    return true;
}

size_t file_lines_counter(const std::string &file) {
    size_t count = 0;
    for (char i: file) {
        if (i == '\n') {
            count += 1;
        }
    }
    return count;
}

auto pelindrome_counter(const std::string &file, size_t &count, size_t &p_count) {
    auto palindromes = new std::string[1];
    size_t i = 0;
    while (count > 0) {
        std::string line;
        while (file[i] != '\r' && file[i] != '\n') {
            if (file[i] == '\0') {
                break;
            }

            line += file[i];
            i++;
        }

        if (line.length() != 0) {
            count--;
            if (is_palindrome(line)) {
                p_count++;
                if (p_count == 1) {
                    palindromes[0]=line;
                } else {
                    auto temp_mas = new std::string[p_count];

                    for (int j = 0; j < p_count-1; j++) {
                        temp_mas[j] = palindromes[j];
                    }

                    temp_mas[p_count - 1] = line;

                    delete[] palindromes;
                    palindromes = new std::string[p_count];

                    for (int j = 0; j < p_count; j++) {
                        palindromes[j] = temp_mas[j];
                    }

                    delete[] temp_mas;
                }
            }
        }
        i++;
    }
    return palindromes;
}

int main(int argc, char *argv[]) {
    if (argc > 2) {
        exit(-1);
    }

    std::string file = read_file_from_path(argv[argc - 1]);
    size_t lines_count = file_lines_counter(file);

    size_t palindromes_count = 0;
    auto palindromes = pelindrome_counter(file, lines_count, palindromes_count);

    printf("{\n\t\"count_palindromes\": %zu,\n\t\"palindromes\": [", palindromes_count);
    for (size_t i = 0; i < palindromes_count; i++) {
        printf("\"%s\"", palindromes[i].c_str());
        if (i != palindromes_count-1) {
            std::cout << ", ";
        }
    }
    printf("]\n}");

    delete[] palindromes;
    return 0;
}