#include <iostream>

struct ListNode {
    int val;
    ListNode *next_;

    ListNode() : val(0), next_(nullptr) {}

    ListNode(int x) : val(x), next_(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next_(next) {}

    ~ListNode() {
        delete next_;
    }

    friend ListNode add_two_linked_numbers(ListNode *l1, ListNode *l2) {
        ListNode result;
        ListNode *tmp = &result;
        int sum = 0;

        while (l1 || l2) {
            if (l1) {
                sum += l1->val;
                l1 = l1->next_;
            }

            if (l2) {
                sum += l2->val;
                l2 = l2->next_;
            }

            tmp->val = sum % 10;
            sum = sum / 10;

            if (l1 || l2) {
                tmp->next_ = new ListNode();
                tmp = tmp->next_;
            } else if (sum) {
                tmp->next_ = new ListNode(sum);
            }
        }
        return result;
    }
};

void Print_ListNode(ListNode *lst) {
    std::cout << "[";
    while (lst) {
        std::cout << lst->val;
        lst = lst->next_;
        if (lst) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;
}

int mainFunc2_4() {
    ListNode l1(4, new ListNode(8, new ListNode(8, new ListNode(2))));
    ListNode l2(1, new ListNode(2, new ListNode(3)));
    ListNode res = add_two_linked_numbers(&l1, &l2);

    /// Вывод введенных значений

    Print_ListNode(&l1);
    Print_ListNode(&l2);

    /// Вывод получившегося значения

    Print_ListNode(&res);

}