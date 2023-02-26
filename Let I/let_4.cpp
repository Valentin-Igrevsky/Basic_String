#include <iostream>

struct MobilePhone {
    double weight;
    bool is_broken;
    double price;
};

void getXML(int id, double weight, bool is_broken, double price) {
    std::printf("\t<MobilePhone id=\"%i\" weight=\"%.1f\" is_broken=\"%s\" price=\"%.2f\"/>\n", id, weight,
                (is_broken) ? "true" : "false", price);
}

int mainFunc4() {
    uint64_t counter;
    std::cin >> counter;

    auto mobile_phones = new MobilePhone[counter];

    for (uint64_t i = 0; i < counter; i++) {
        std::cin >> mobile_phones[i].weight >> mobile_phones[i].is_broken >> mobile_phones[i].price;
    }

    std::cout << "<MobilePhones>\n";
    for (uint64_t i = 0; i < counter; i++) {
        getXML(i, mobile_phones[i].weight, mobile_phones[i].is_broken, mobile_phones[i].price);
    }
    std::cout << "</MobilePhones>\n";

    delete[] mobile_phones;

    return 0;
}
