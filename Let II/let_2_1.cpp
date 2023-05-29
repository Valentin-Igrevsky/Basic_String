#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct user {
    user() = default;

    user(std::string name, int age) : name_(name), age_(age) {}

    ~user() = default;

    std::string name_;
    int age_;
};

user cstr2struct(char *&tmp_str) {
    std::string str = tmp_str;
    size_t pos = str.find(':');
    std::string name = str.substr(0, pos);
    std::string age = str.substr(pos + 1);
    return user(name, std::stoi(age));
}

void struct2json(std::vector<user> &users, std::ofstream &ofs) {
    std::vector<std::string> arg = {"name", "age"};
    std::vector<std::string> sorted_by = {"name_gt", "age_less"};
    ofs << "{";
    for (size_t i = 0; i < arg.size(); ++i) {
        sort(users.begin(), users.end(), [&arg, &i](const user &left, const user &right) {
            if (arg[i] == "name") {
                return left.name_ < right.name_;
            } else if (arg[i] == "age") {
                return left.age_ > right.age_;
            } else {
                return false;
            }
        });

        ofs << "\n\t\"sorted_by_" << sorted_by[i] << "\" : [";
        for (size_t j = 0; j < users.size(); ++j) {
            std::string tmp = R"({"name": ")" + users[j].name_ + R"(", "age": )" + std::to_string(users[j].age_) + "}";
            if (j != (users.size() - 1)) {
                tmp += ", ";
            }
            ofs << tmp;
        }
        ofs << "]";
        if (i != (arg.size() - 1)) {
            ofs << ",";
        }
    }
    ofs << "\n}";
}

int mainFunc2_1(int argc, char **argv) {
    std::ofstream stream;
    stream.open("sorted.json");

    std::vector<user> my_users(argc - 1);
    for (size_t i = 0; i < argc - 1; ++i) {
        my_users[i] = cstr2struct(argv[i + 1]);
    }
    struct2json(my_users, stream);

    stream.close();
    return 0;
}