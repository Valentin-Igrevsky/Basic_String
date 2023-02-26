#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

bool is_perfect(uint64_t &num) {
    size_t numC;
    bool c_flag;
    uint64_t sum = 0;
    if (num > 100) {
        numC = sqrt(num) + 1;
        c_flag = true;
    } else {
        numC = num;
    }
    for (size_t del = 1; del < numC; ++del) {
        if (num % del == 0) {
            sum += del;
            if (num / del != del && c_flag && num / del != num) {
                sum += (num / del);
            }
        }
        if (sum > num) break;
    }
    return (num == sum);
}

int mainFunc2_0(int argc, char **argv) {
    std::string path = "file_with_numbers.txt";
    std::ofstream stream;
    stream.open(path);
    if (stream.is_open()) {
        for (size_t i = 1; i < argc; ++i) {
            size_t num = std::stoull(argv[i]);
            if (is_perfect(num)) {
                stream << num << std::endl;
            }
        }
    }
    stream.close();
    return 0;
}



