#include <gtest/gtest.h>
#include <iostream>
#include "bmstu_list.h"

TEST(Constructor, Default) {
    bmstu::list<int> my_list;
    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 0);
    ASSERT_TRUE(it_b == it_e);

    --it_b;
    --it_e;
    ASSERT_TRUE(it_b == it_e);
}

TEST(Constructor, IList) {
    bmstu::list<int> my_list({0, 1, 2, 3, 4});
    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 5);
    for (int a = 0; it_b != it_e; ++it_b, ++a) {
        ASSERT_TRUE(*it_b == a);
        ASSERT_TRUE(my_list[a] == a);
    }

    --it_e;
    it_b = my_list.begin() - 1;
    for (int a = 4; it_b != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(my_list[a] == a);
    }
}

TEST(Constructor, Iterators) {
    bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
    bmstu::list<int>::iterator it_b_1 = my_list_1.begin() + 1;
    bmstu::list<int>::iterator it_e_1 = my_list_1.end() - 1;


    bmstu::list<int> my_list_2(it_b_1, it_e_1);
    bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
    bmstu::list<int>::iterator it_e_2 = my_list_2.end();

    ASSERT_EQ(my_list_1.size(), 5);
    ASSERT_EQ(my_list_2.size(), 3);
    for (int a = 1; it_b_2 != it_e_2; ++it_b_2, ++a) {
        ASSERT_TRUE(*it_b_2 == a);
        ASSERT_TRUE(my_list_2[a - 1] == a);
    }

    --it_e_2;
    it_b_2 = my_list_2.begin() - 1;
    for (int a = 3; it_b_2 != it_e_2; --it_e_2, --a) {
        ASSERT_TRUE(*it_e_2 == a);
        ASSERT_TRUE(my_list_2[a - 1] == a);
    }
}

TEST(Constructor, Copy) {
    bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
    bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
    bmstu::list<int>::iterator it_e_1 = my_list_1.end();

    bmstu::list<int> my_list_2(my_list_1);
    bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
    bmstu::list<int>::iterator it_e_2 = my_list_2.end();

    ASSERT_EQ(my_list_1.size(), 5);
    ASSERT_EQ(my_list_2.size(), 5);
    for (int a = 0; it_b_2 != it_e_2; ++it_b_1, ++it_b_2, ++a) {
        ASSERT_TRUE(*it_b_1 == a);
        ASSERT_TRUE(*it_b_2 == a);
        ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
    }

    --it_e_1;
    --it_e_2;
    it_b_1 = my_list_1.begin() - 1;
    it_b_2 = my_list_2.begin() - 1;
    for (int a = 4; it_b_2 != it_e_2; --it_e_1, --it_e_2, --a) {
        ASSERT_TRUE(*it_e_1 == a);
        ASSERT_TRUE(*it_e_2 == a);
        ASSERT_TRUE(my_list_1[a] == my_list_2[a]);
    }
}

TEST(Constructor, Move) {
    bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
    bmstu::list<int> my_list_2(std::move(my_list_1));
    bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
    bmstu::list<int>::iterator it_e_2 = my_list_2.end();

    ASSERT_EQ(my_list_1.size(), 0);
    ASSERT_EQ(my_list_2.size(), 5);
    for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
        ASSERT_TRUE(*it_b_2 == a);
        ASSERT_TRUE(my_list_2[a] == a);
    }
}

TEST(Method, push_back) {
    bmstu::list<int> my_list({0, 1, 2, 3, 4});

    my_list.push_back(5);

    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 6);
    for (int a = 0; it_b != it_e; ++it_b, ++a) {
        ASSERT_TRUE(*it_b == a);
        ASSERT_TRUE(my_list[a] == a);
    }

    --it_e;
    it_b = my_list.begin() - 1;
    for (int a = 5; it_b != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(my_list[a] == a);
    }
}

TEST(Method, push_front) {
    bmstu::list<int> my_list({1, 2, 3, 4, 5});

    my_list.push_front(0);

    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 6);
    for (int a = 0; it_b != it_e; ++it_b, ++a) {
        ASSERT_TRUE(*it_b == a);
        ASSERT_TRUE(my_list[a] == a);
    }

    --it_e;
    it_b = my_list.begin() - 1;
    for (int a = 5; it_b != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(my_list[a] == a);
    }
}

TEST(Method, clear) {
    bmstu::list<int> my_list({1, 2, 3, 4, 5});

    my_list.clear();

    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 0);
    ASSERT_TRUE(it_b == it_e);

    --it_b;
    --it_e;
    ASSERT_TRUE(it_b == it_e);
}

TEST(Method, swap) {
    bmstu::list<int> my_list_1({0, 1, 2, 3, 4});
    bmstu::list<int> my_list_2({7, 8, 9});

    my_list_1.swap(my_list_2);

    bmstu::list<int>::iterator it_b_1 = my_list_1.begin();
    bmstu::list<int>::iterator it_e_1 = my_list_1.end();
    bmstu::list<int>::iterator it_b_2 = my_list_2.begin();
    bmstu::list<int>::iterator it_e_2 = my_list_2.end();

    ASSERT_EQ(my_list_1.size(), 3);
    ASSERT_EQ(my_list_2.size(), 5);

    for (int a = 7; it_b_1 != it_e_1; ++it_b_1, ++a) {
        ASSERT_TRUE(*it_b_1 == a);
        ASSERT_TRUE(my_list_1[a - 7] == a);
    }

    --it_e_1;
    it_b_1 = my_list_1.begin() - 1;
    for (int a = 9; it_b_1 != it_e_1; --it_e_1, --a) {
        ASSERT_TRUE(*it_e_1 == a);
        ASSERT_TRUE(my_list_1[a - 7] == a);
    }

    for (int a = 0; it_b_2 != it_e_2; ++it_b_2, ++a) {
        ASSERT_TRUE(*it_b_2 == a);
        ASSERT_TRUE(my_list_2[a] == a);
    }

    --it_e_2;
    it_b_2 = my_list_2.begin() - 1;
    for (int a = 4; it_b_2 != it_e_2; --it_e_2, --a) {
        ASSERT_TRUE(*it_e_2 == a);
        ASSERT_TRUE(my_list_2[a] == a);
    }
}

TEST(Operapor, Index) {
    bmstu::list<int> my_list({0, 1, 2, 0, 4});
    my_list[3] = 3;

    ASSERT_EQ(my_list.size(), 5);

    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();
    for (int a = 0; it_b != it_e; ++it_b, ++a) {
        ASSERT_TRUE(*it_b == a);
        ASSERT_TRUE(my_list[a] == a);
    }

    --it_e;
    it_b = my_list.begin() - 1;
    for (int a = 4; it_b != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(my_list[a] == a);
    }


}

TEST(Operator, EQs) {
    bmstu::list<int> my_list_1({0, 1, 2, 3, 4, 5, 6});
    bmstu::list<int> my_list_2({0, 1, 2, 3, 4, 5, 6});
    bmstu::list<int> my_list_3({0, 1, 2, 3, 4, 5, 7});
    bmstu::list<int> my_list_4({1, 2, 3, 4, 5, 7, 8});
    bmstu::list<int> my_list_5({1, 1, 2, 3, 4, 5, 7});

    ASSERT_TRUE(my_list_1 == my_list_2);
    ASSERT_FALSE(my_list_1 == my_list_3);
    ASSERT_TRUE(my_list_1 != my_list_3);
    ASSERT_FALSE(my_list_1 != my_list_2);
    ASSERT_TRUE(my_list_1 < my_list_4);
    ASSERT_TRUE(my_list_4 > my_list_1);
    ASSERT_TRUE(my_list_1 <= my_list_5);
    ASSERT_TRUE(my_list_5 >= my_list_1);
}

TEST(Operator, LeftShift) {
    bmstu::list<int> my_list({0, 1, 2, 3, 4, 5, 6});
    std::stringstream ss;
    ss << my_list;
    ASSERT_STREQ(ss.str().c_str(), "{0, 1, 2, 3, 4, 5, 6}");
}

TEST(Method, insert) {
    bmstu::list<int> my_list({0, 1, 2, 4});
    bmstu::list<int>::iterator it = my_list.end();
    ASSERT_THROW(my_list.insert(it, 5), std::logic_error);

    it = it - 2;
    my_list.insert(it, 3);
    bmstu::list<int>::iterator it_b = my_list.begin();
    bmstu::list<int>::iterator it_e = my_list.end();

    ASSERT_EQ(my_list.size(), 5);
    for (int a = 0; it_b != it_e; ++it_b, ++a) {
        ASSERT_TRUE(*it_b == a);
        ASSERT_TRUE(my_list[a] == a);
    }

    --it_e;
    it_b = my_list.begin() - 1;
    for (int a = 4; it_b != it_e; --it_e, --a) {
        ASSERT_TRUE(*it_e == a);
        ASSERT_TRUE(my_list[a] == a);
    }
}
