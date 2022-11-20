#include<iostream>
#include "bmstu_string.h"
#include <string>

int main()
{
    bmstu::string<char> str1 = "АБОБА";
    bmstu::string<char> str2 = "ABOBA";
    std::cout << str1 + str2;
}