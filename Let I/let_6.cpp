#include <iostream>
#include <string>


int mainFunc6() {
    const std::string symbols = "1234567890AaBbCcDdEeFfGgHgXxYyZz";
    size_t str_len = symbols.length();
    for (int i = 0; i < str_len; ++i) {
        for (int j = 0; j < str_len; ++j) {
            for (int k = 0; k < str_len; ++k) {
                for (int g = 0; g < str_len; ++g) {
                    for (int f = 0; f < str_len; ++f) {
                        std::cout << symbols[i] << symbols[j] << symbols[k] << symbols[g] << symbols[f] << std::endl;
                    }
                }
            }
        }
    }
    return 0;
};
