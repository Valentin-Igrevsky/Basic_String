#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

std::string read_file(const std::string &path) {
    std::ifstream file(path);
    if (file) {
        std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
    } else {
        return {};
    }
}

bool compar(char ch) {
    return ((std::ispunct(ch)  || (ch == '\n') || (ch == '\r') || (ch == '-')) && (ch != '_'));
}

void trigrama_couter(std::string &file, std::map<std::string, size_t> &mp) {
    std::string trigrama = file.substr(0,3);
    for (size_t i = 3; i < file.size() - 1; ++i) {
        if (mp.count(trigrama)) {
            mp[trigrama] += 1;
        } else {
            mp.insert(std::make_pair(trigrama, 1));
        }
        trigrama.erase(trigrama.begin());
        trigrama += file[i];
    }
}

void print_top_ten_trigrams(std::map<std::string, size_t> &mp, std::vector<std::pair<std::string, size_t>> &keys) {
    auto it = mp.begin();
    for (int i = 0; it != mp.end(); ++i, it++) {
        keys.push_back({it->first, it->second});
    }

    sort(keys.begin(), keys.end(),
         [](const std::pair<std::string, size_t> &left, const std::pair<std::string, size_t> &right) {
             return left.second > right.second;
         });

    for (size_t i = 0; i < 10; ++i) {
        std::cout << keys[i].first << '\t' << keys[i].second << std::endl;
    }
}

int mainFunc2_2(int argc, char **argv) {
    if (argc == 2) {
        std::string path(argv[argc-1]);
        std::string file = read_file(path);
        replace(file.begin(), file.end(), L' ', L'_');
        std::remove_if(file.begin(), file.end(), compar);

        std::map<std::string, size_t> mp;
        std::vector<std::pair<std::string, size_t>> keys;

        trigrama_couter(file, mp);
        print_top_ten_trigrams(mp, keys);
    } else {
       exit(-1);
    }
    return 0;
}