/*  “Считалочка”
 *
 * В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * (Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 * затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.)
 * Необходимо определить номер уцелевшего. N, k ≤ 10000.
 */

#include <iostream>
#include <cassert>

struct listNode {
    size_t Data;
    listNode* Next;
    listNode* Prev;
};

class List {
private:
    listNode* Head;
public:
    List() = delete;

    List(const size_t N) {
        Head = new listNode;
        Head->Data = 0;
        Head->Prev = nullptr;
        Head->Next = nullptr;

        listNode* temp = Head;

        for (size_t i = 1; i < N; ++i) {  // i = 0 - Head
            auto node = new listNode;
            node->Data = i;
            node->Prev = temp;
            node->Next = nullptr;

            temp->Next = node;
            temp = node;
        }
        temp->Next = Head;
        Head->Prev = temp;
    }

    ~List() {
        while (Head->Next != Head) {
            listNode* temp = Head;
            Head->Prev->Next = Head->Next;
            Head->Next->Prev = Head->Prev;
            Head = Head->Next;
            delete temp;
        }
        delete Head;
    }

    size_t getHead() const {
        assert(Head);
        return Head->Data;
    }

    void moveHead(const size_t index) {
        assert(Head);
        for (size_t i = 0; i < index; ++i)
            Head = Head->Next;
    }

    void popHead() {
        assert(Head);
        if (Head && Head->Next) {
            Head->Next->Prev = Head->Prev;
            Head->Prev->Next = Head->Next;
            listNode *temp = Head;
            Head = Head->Next;
            delete temp;
        }
    }
};

int main() {
    size_t N = 0, k = 0;
    std::cin >> N >> k;
    assert((N > 0) && (N <= 10000) &&
           (k > 0) && (k <= 10000));

    List warriors(N);
    for (int i = 0; i < N - 1; ++i) {
        warriors.moveHead(k - 1);
        warriors.popHead();
    }
    std::cout << warriors.getHead() + 1;

    return 0;
}
