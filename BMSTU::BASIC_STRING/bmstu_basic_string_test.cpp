#include <gtest/gtest.h>
#include "bmstu_basic_string.h"

TEST(Constructor, Default) {
    bmstu::basic_string<char> my_str;
    EXPECT_EQ(my_str.size(), 0);
    EXPECT_STREQ(my_str.c_str(), "");
}

TEST(Constructor, English_C_String) {
    bmstu::basic_string my_str("It is test bmstu string.");
    const char *c_str = "It is test bmstu string.";
    EXPECT_EQ(my_str.size(), 24);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Constructor, English_BMSTU_String) {
    const char *c_str = "bmstu string";
    bmstu::basic_string my_str("bmstu string");
    bmstu::basic_string my_str_copy(my_str);
    EXPECT_EQ(my_str.size(), 12);
    EXPECT_STREQ(my_str.c_str(), c_str);
    EXPECT_EQ(my_str_copy.size(), my_str.size());
    EXPECT_STREQ(my_str_copy.c_str(), my_str.c_str());
}

TEST(Constructor, English_Aggregate_init) {
    const char *c_str = "Test string";
    bmstu::basic_string my_str({'T', 'e', 's', 't', ' ', 's', 't', 'r', 'i', 'n', 'g'});
    EXPECT_EQ(my_str.size(), 11);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Operator, Copy_English_C_String) {
    const char *c_str = "C-string";
    bmstu::basic_string my_str = c_str;
    EXPECT_EQ(my_str.size(), 8);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Operator, Copy_English_BMSTU_String) {
    const char *c_str = "BMSTU-string";
    bmstu::basic_string my_str = "BMSTU-string";
    bmstu::basic_string my_str_copy = my_str;
    EXPECT_EQ(my_str.size(), 12);
    EXPECT_STREQ(my_str.c_str(), c_str);
    EXPECT_EQ(my_str_copy.size(), my_str.size());
    EXPECT_STREQ(my_str_copy.c_str(), my_str.c_str());
}

TEST(Constructor, Move_English_BMSTU_String) {
    const char *c_str = "STR TO MOVE";
    bmstu::basic_string my_str = "STR TO MOVE";
    bmstu::basic_string my_str_moved(std::move(my_str));
    EXPECT_EQ(my_str_moved.size(), 11);
    EXPECT_STREQ(my_str_moved.c_str(), c_str);
    EXPECT_EQ(my_str.size(), 0);
    EXPECT_STREQ(my_str.c_str(), "");
}

TEST(Operator, Move_English_BMSTU_String) {
    const char *c_str = "STR TO MOVE";
    bmstu::basic_string my_str = "STR TO MOVE";
    bmstu::basic_string my_str_moved = std::move(my_str);
    EXPECT_EQ(my_str_moved.size(), 11);
    EXPECT_STREQ(my_str_moved.c_str(), c_str);
    EXPECT_EQ(my_str.size(), 0);
    EXPECT_STREQ(my_str.c_str(), "");
}

TEST(Operator, Concatenation_And_Assignment_Char) {
    bmstu::basic_string my_str = "Test";
    my_str += 's';
    EXPECT_EQ(my_str.size(), 5);
    EXPECT_STREQ(my_str.c_str(), "Tests");
}

TEST(Operator, Concatenation_And_Assignment_English_C_String) {
    const char *c_str = " of string";
    bmstu::basic_string my_str = "Test";
    my_str += c_str;
    EXPECT_EQ(my_str.size(), 14);
    EXPECT_STREQ(my_str.c_str(), "Test of string");
}

TEST(Operator, Concatenation_And_Assignment_English_BMSTU_String) {
    bmstu::basic_string my_str_first = "Test";
    bmstu::basic_string my_str_second = " of string";
    my_str_first += my_str_second;
    EXPECT_EQ(my_str_second.size(), 10);
    EXPECT_STREQ(my_str_second.c_str(), " of string");
    EXPECT_EQ(my_str_first.size(), 14);
    EXPECT_STREQ(my_str_first.c_str(), "Test of string");
}

TEST(Operator, Concatenation_English_BMSTU_String) {
    bmstu::basic_string my_str_first = "Test";
    bmstu::basic_string my_str_second = " of string";
    bmstu::basic_string my_str_third = my_str_first + my_str_second;
    EXPECT_EQ(my_str_first.size(), 4);
    EXPECT_STREQ(my_str_first.c_str(), "Test");
    EXPECT_EQ(my_str_second.size(), 10);
    EXPECT_STREQ(my_str_second.c_str(), " of string");
    EXPECT_EQ(my_str_third.size(), 14);
    EXPECT_STREQ(my_str_third.c_str(), "Test of string");
}

TEST(Operator, Index_English_BMSTU_String) {
    bmstu::basic_string my_str = "Index";
    EXPECT_EQ(my_str[0] - 'I', 0);
}

TEST(Constructor, Russian_C_String) {
    bmstu::basic_string my_str(L"Да да провода");
    const wchar_t *c_str = L"Да да провода";
    EXPECT_EQ(my_str.size(), 13);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Constructor, Russian_BMSTU_String) {
    const wchar_t *c_str = L"Я Богдан";
    bmstu::basic_string my_str(L"Я Богдан");
    bmstu::basic_string my_str_copy(my_str);
    EXPECT_EQ(my_str.size(), 8);
    EXPECT_STREQ(my_str.c_str(), c_str);
    EXPECT_EQ(my_str_copy.size(), my_str.size());
    EXPECT_STREQ(my_str_copy.c_str(), my_str.c_str());
}

TEST(Constructor, Russian_Aggregate_init) {
    const wchar_t *c_str = L"Что-то на татарском";
    bmstu::basic_string my_str(
            {L'Ч', L'т', L'о', L'-', L'т', L'о', L' ', L'н', L'а', L' ', L'т', L'а', L'т', L'а', L'р', L'с', L'к', L'о',
             L'м'});
    EXPECT_EQ(my_str.size(), 19);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Operator, Copy_Russian_C_String) {
    const wchar_t *c_str = L"Мне хана!";
    bmstu::basic_string my_str = c_str;
    EXPECT_EQ(my_str.size(), 9);
    EXPECT_STREQ(my_str.c_str(), c_str);
}

TEST(Operator, Copy_Russian_BMSTU_String) {
    const wchar_t *c_str = L"Ну это шиза...";
    bmstu::basic_string my_str = L"Ну это шиза...";
    bmstu::basic_string my_str_copy = my_str;
    EXPECT_EQ(my_str.size(), 14);
    EXPECT_STREQ(my_str.c_str(), c_str);
    EXPECT_EQ(my_str_copy.size(), my_str.size());
    EXPECT_STREQ(my_str_copy.c_str(), my_str.c_str());
}

TEST(Constructor, Move_Russian_BMSTU_String) {
    const wchar_t *c_str = L"Шутки, как всегда, на высоте";
    bmstu::basic_string my_str = L"Шутки, как всегда, на высоте";
    bmstu::basic_string my_str_moved(std::move(my_str));
    EXPECT_EQ(my_str_moved.size(), 28);
    EXPECT_STREQ(my_str_moved.c_str(), c_str);
    EXPECT_EQ(my_str.size(), 0);
    EXPECT_STREQ(my_str.c_str(), L"");
}

TEST(Operator, Move_Russian_BMSTU_String) {
    const wchar_t *c_str = L"Шутки, как всегда, на высоте";
    bmstu::basic_string my_str = L"Шутки, как всегда, на высоте";
    bmstu::basic_string my_str_moved = std::move(my_str);
    EXPECT_EQ(my_str_moved.size(), 28);
    EXPECT_STREQ(my_str_moved.c_str(), c_str);
    EXPECT_EQ(my_str.size(), 0);
    EXPECT_STREQ(my_str.c_str(), L"");
}

TEST(Operator, Concatenation_And_Assignment_WcharT) {
    bmstu::basic_string my_str = L"Дядя, не надо";
    my_str += L'!';
    EXPECT_EQ(my_str.size(), 14);
    EXPECT_STREQ(my_str.c_str(), L"Дядя, не надо!");
}

TEST(Operator, Concatenation_And_Assignment_Russian_C_String) {
    const wchar_t *c_str = L"не надо!";
    bmstu::basic_string my_str = L"Дядя, ";
    my_str += c_str;
    EXPECT_EQ(my_str.size(), 14);
    EXPECT_STREQ(my_str.c_str(), L"Дядя, не надо!");
}

TEST(Operator, Concatenation_And_Assignment_Russian_BMSTU_String) {
    bmstu::basic_string my_str_first = L"Да ты чё? ";
    bmstu::basic_string my_str_second = L"Нееет!";
    my_str_first += my_str_second;
    EXPECT_EQ(my_str_second.size(), 6);
    EXPECT_STREQ(my_str_second.c_str(), L"Нееет!");
    EXPECT_EQ(my_str_first.size(), 16);
    EXPECT_STREQ(my_str_first.c_str(), L"Да ты чё? Нееет!");
}

TEST(Operator, Concatenation_Russian_BMSTU_String) {
    bmstu::basic_string my_str_first = L"Боже мой!";
    bmstu::basic_string my_str_second = L" Не может быть!";
    bmstu::basic_string my_str_third = my_str_first + my_str_second;
    EXPECT_EQ(my_str_first.size(), 9);
    EXPECT_STREQ(my_str_first.c_str(), L"Боже мой!");
    EXPECT_EQ(my_str_second.size(), 15);
    EXPECT_STREQ(my_str_second.c_str(), L" Не может быть!");
    EXPECT_EQ(my_str_third.size(), 24);
    EXPECT_STREQ(my_str_third.c_str(), L"Боже мой! Не может быть!");
}

TEST(Operator, Index_Russian_BMSTU_String) {
    bmstu::basic_string my_str = L"Индекс";
    EXPECT_EQ(my_str[4] - L'к', 0);
}


TEST(StringTest, DefaultConstructor) {
    bmstu::string str;
    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, DefaultConstructorW) {
    bmstu::wstring str;
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorW) {
    bmstu::wstring str{};
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructor) {
    bmstu::wstring str{};
    ASSERT_STREQ(str.c_str(), L"");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, InitializerListConstructorNonEmpty) {
    bmstu::wstring str{L'С', L'Л', L'О', L'В', L'О'};
    ASSERT_STREQ(str.c_str(), L"СЛОВО");
    ASSERT_EQ(str.size(), 5);
}

TEST(StringTest, ConstructorSizeW) {
    bmstu::wstring str(10);
    ASSERT_STREQ(str.c_str(), L"          ");
    ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSize) {
    bmstu::string str(10);
    ASSERT_STREQ(str.c_str(), "          ");
    ASSERT_EQ(str.size(), 10);
}

TEST(StringTest, ConstructorSizeOne) {
    bmstu::wstring str(1);
    ASSERT_STREQ(str.c_str(), L" ");
    ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, FromCStr) {
    bmstu::string str("str\n");
    ASSERT_STREQ(str.c_str(), "str\n");
    ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStr) {
    bmstu::wstring str(L"おはよう");
    ASSERT_STREQ(str.c_str(), L"おはよう");
    ASSERT_EQ(str.size(), 4);
}

TEST(StringTest, FromWCStrSymbol) {
    bmstu::wstring str(L"おはよう");
    ASSERT_STREQ(str.c_str(), L"おはよう");
    wchar_t c = L'お';
    ASSERT_EQ(str[0], c);
}

TEST(StringTest, USymbolsW) {
    bmstu::wstring str(L"お");
    ASSERT_STREQ(str.c_str(), L"お");
    wchar_t c = L'お';
    ASSERT_EQ(str.size(), 1);
}

TEST(StringTest, USymbol) {
    bmstu::string str("\xe3\x81\x8a\x00");
    ASSERT_STREQ(str.c_str(), "お");
    ASSERT_EQ(str.size(), 3);
}


TEST(StringTest, USymbols) {
    bmstu::string str("おはよう");
    ASSERT_STREQ(str.c_str(), "おはよう");
    ASSERT_EQ(str.size() + 1, sizeof("おはよう"));
}

TEST(StringTest, Empty) {
    bmstu::string empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_STREQ(empty.c_str(), "");
}

TEST(StringTest, EmptyW) {
    bmstu::wstring empty;
    ASSERT_EQ(empty.size(), 0);
    ASSERT_STREQ(empty.c_str(), L"");
}

TEST(StringTest, CopyAssignW) {

    bmstu::wstring empty(L"Non Empty строка");
    bmstu::wstring nonempty = empty;
    ASSERT_STREQ(nonempty.c_str(), L"Non Empty строка");
    ASSERT_EQ(nonempty.size(), 16);
}

TEST(StringTest, CopyConstructor) {

    bmstu::string empty("Non Empty строка");
    bmstu::string nonempty = empty;
    ASSERT_STREQ(nonempty.c_str(), "Non Empty строка");
    ASSERT_EQ(nonempty.size(), sizeof("Non Empty строка") - 1);
}

TEST(StringTest, CopyAssignConstructor) {

    bmstu::string *str = new bmstu::string("str");
    bmstu::string *nonempty = new bmstu::string;
    *nonempty = *str;
    ASSERT_STREQ(nonempty->c_str(), "str");
    ASSERT_EQ(nonempty->size(), sizeof("str") - 1);
    delete str;
    delete nonempty;
}

TEST(StringTest, MoveAssignConstructor) {
    bmstu::string str = "str";
    bmstu::string str2 = "other";
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);

    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructor2) {
    bmstu::string str = "str";
    bmstu::string str2 = "other";
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);

    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, CopyAssignConstructor2) {
    bmstu::string str = "str";
    bmstu::string str2(bmstu::string("other"));
    str2 = std::move(str);
    ASSERT_STREQ(str2.c_str(), "str");
    ASSERT_EQ(str2.size(), sizeof("str") - 1);

    ASSERT_STREQ(str.c_str(), "");
    ASSERT_EQ(str.size(), 0);
}

TEST(StringTest, MoveAssignConstructorW) {
    bmstu::wstring str2(std::move(bmstu::wstring(L"other")));
    ASSERT_STREQ(str2.c_str(), L"other");
    ASSERT_EQ(str2.size(), (sizeof(L"other") / sizeof(wchar_t)) - 1);
}

TEST(StringTest, CStrCopyAssign) {
    const char *str = "Simple Str";
    bmstu::string b_str;
    b_str = str;
    ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, CStrCopyAssignW) {
    const wchar_t *str = L"Простая строка";
    bmstu::wstring b_str;
    b_str = str;
    ASSERT_STREQ(b_str.c_str(), str);
}

TEST(StringTest, AssignCStr) {
    bmstu::wstring str = L"123456789";
    ASSERT_STREQ(str.c_str(), L"123456789");
}

TEST(StringTest, ConcatOpW) {
    bmstu::wstring a_str(L"right");
    bmstu::wstring b_str(L"_left");
    auto c_str = a_str + b_str;
    ASSERT_STREQ(c_str.c_str(), L"right_left");
}

TEST(StringTest, ConcatOp) {
    bmstu::string a_str("right");
    bmstu::string b_str("_left");
    auto c_str = a_str + b_str;
    ASSERT_STREQ(c_str.c_str(), "right_left");
}

TEST(StringTest, OStream) {
    bmstu::string a_str("String value");
    std::stringstream ss;
    ss << a_str;
    ASSERT_STREQ(ss.str().c_str(), "String value");
}

TEST(StringTest, OStreamW) {
    bmstu::wstring a_str(L"String значение");
    std::wstringstream ss;
    ss << a_str;
    ASSERT_STREQ(ss.str().c_str(), L"String значение");
}

TEST(StringTest, IStream) {
    std::stringstream ss;
    ss.str("Value of\nstring");
    bmstu::string a_str;
    std::string a;
    ss >> a_str;
    ASSERT_STREQ(a_str.c_str(), "Value of\nstring");
}

TEST(StringTest, IStreamW) {
    std::wstringstream ss;
    ss.str(L"Value of\nстрока");
    bmstu::wstring a_str;
    ss >> a_str;
    ASSERT_STREQ(a_str.c_str(), L"Value of\nстрока");
}

TEST(StringTest, IStreamWNewLine) {
    std::wstringstream ss;
    ss.str(L"Value of\nstring");
    bmstu::wstring a_str;
    ss >> a_str;
    ASSERT_STREQ(ss.str().c_str(), L"Value of\nstring");
}

TEST(StringTest, ConcatSymbol) {
    bmstu::wstring a_str;
    a_str += L'S';
    ASSERT_STREQ(a_str.c_str(), L"S");
    a_str += L'т';
    ASSERT_STREQ(a_str.c_str(), L"Sт");
    a_str += L'р';
    ASSERT_STREQ(a_str.c_str(), L"Sтр");
    ASSERT_EQ(a_str.size(), 3);
}

TEST(StringTest, Item) {
    bmstu::wstring a_str(L"СТРОКААГ");
    ASSERT_EQ(a_str[0], L'С');
    ASSERT_EQ(a_str[1], L'Т');
    ASSERT_EQ(a_str[a_str.size() - 1], L'Г');
}