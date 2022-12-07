#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>

class Student {
public:
    Student(uint8_t age, uint16_t score, char grade, const std::string &name) :
            age(age),
            score(score),
            grade(grade),
            name(name) {}


    Student() = default;

    friend std::ostream &operator<<(std::ostream &ovs, const Student &st) {
        ovs << "\t\t{\n\t\t\t\"name\": \"" << st.name << ",\n\t\t\t\"age\": " << unsigned(st.age)
            << ",\n\t\t\t\"score\": " << st.score << ",\n\t\t\t\"grade\": \"" << st.grade << "\"\n\t\t}";
        return ovs;
    }

private:

    uint8_t age;
    char grade;
    uint16_t score;
    std::string name;
};

int mainFunc(int argc, char **argv) {
    if (argc != 2) {
        exit(-1);
    }

    std::ifstream ovs(argv[argc - 1], std::ios::binary | std::ios::in);

    if (ovs) {
        uint32_t count;
        ovs.read((char *) &count, sizeof(uint32_t));
        std::cout << "{\n\t\"total_count\": " << count << ",\n\t\"students\": [\n";
        for (uint32_t i = count; i > 0; i--) {
            uint8_t age;
            char grade;
            uint16_t score;
            std::string name;
            ovs.read((char *) &age, 1);
            ovs.read((char *) &grade, 1);
            ovs.read((char *) &score, 2);
            char buf;
            do {
                ovs.read((char *) &buf, 1);
                if (buf == 0) {
                    break;
                }
                name += buf;
            } while (buf != 0);
            Student st(age, score, grade, name);
            std::cout << st;
            if (i > 1) {
                std::cout << ",\n";
            }
        }
        std::cout << "\n\t]\n}";
    } else {
        exit(-1);
    }
}
