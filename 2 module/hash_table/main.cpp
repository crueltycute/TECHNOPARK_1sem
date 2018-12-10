#include <iostream>
#include <vector>
#include <string>
#include <cassert>

template <class T>
struct Node {
  T data;
  bool deleted;
  bool empty;

  Node() : deleted(false), empty(true) {}
  Node(T data) : data(data), deleted(false), empty(true) {}
};

template <class T>
class hashTable {
public:
    hashTable();
    hashTable& operator=(const hashTable<T>& other) = default;
    hashTable& operator=(hashTable<T>&& other);
    hashTable(const hashTable<T>& other) = default;
    hashTable(hashTable<T>&& other);
    ~hashTable() = default;

    bool has(const T& element);
    bool add(const T& new_element);
    bool remove(const T& element);

private:
    std::vector<Node<T>> table_;
    size_t size_;

    size_t hashForString_(const T& element, const unsigned int& m);
    void rehash_();

    // constants
    const unsigned int INITIAL_TABLE_SIZE = 4;

//    const std::string EMPTY = "EMPTY";
//    const std::string DELETED = "DELETED";

    const float COEFFICIENT_OF_FULLNESS = 3.f / 4.f;
    const unsigned int HASH_COEFFICIENT = 11;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
hashTable<T>::hashTable() : size_(0) {
    table_ = std::vector<Node<T>>(INITIAL_TABLE_SIZE);
}

template <class T>
hashTable<T>& hashTable<T>::operator=(hashTable<T> &&other) {
    size_ = other.size_;
    table_ = std::move(other.table_);
    return *this;
}

template <class T>
hashTable<T>::hashTable(hashTable<T>&& other) {
    size_ = other.size_;
    table_ = std::move(other.table_);
}

template <class T>
size_t hashTable<T>::hashForString_(const T& element, const unsigned int& m) {
    size_t hash = 0;
    for (const char i : element) {
      hash = (hash * HASH_COEFFICIENT + i) % m;
    }

    return hash;
}

template <class T>
void hashTable<T>::rehash_() {
    auto prev_table = std::move(table_);
    size_t new_size = prev_table.size() * 2;

    table_ = std::vector<Node<T>>(new_size);
    size_ = 0;

    for (int i = 0; i < prev_table.size(); ++i)
       if (!prev_table[i].empty && !prev_table[i].deleted)
         add(prev_table[i].data);
}

template <class T>
bool hashTable<T>::has(const T& element) {
    size_t key_to_find, key;
    key = key_to_find = hashForString_(element, table_.size());

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[key].empty|| table_[key].deleted)
            return false;

        if (table_[key].data == element)
            return true;

        key = (key_to_find + (i + 1) * (2 * i + 1)) % table_.size();
    }

    return false;
}

template <class T>
bool hashTable<T>::add(const T& new_element) {
    if (has(new_element))
        return false;

    size_t key = hashForString_(new_element, table_.size());
    size_t key_to_add = key;

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[key].empty || table_[key].deleted)
            break;

        key = (key_to_add + (i + 1) * (2 * i + 1)) % table_.size();
    }

    table_[key].data = new_element;
    table_[key].empty = false;
    table_[key].deleted = false;
    size_++;

    if (static_cast<float>(size_) / static_cast<float>(table_.size()) >= COEFFICIENT_OF_FULLNESS)
        rehash_();

    return true;
}

template <class T>
bool hashTable<T>::remove(const T& element) {

    size_t key, key_to_remove;
    key = key_to_remove = hashForString_(element, table_.size());

    for (int i = 0; i < table_.size(); ++i) {
        if (table_[key].empty)
            return false;

        if (table_[key].data == element)
            break;

        key = (key_to_remove + (i + 1) * (2 * i + 1)) % table_.size();
    }
    table_[key].deleted = true;
    table_[key].empty = false;
    size_--;
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    hashTable<std::string> table;

    char operation;
    std::string element;

    while (std::cin >> operation >> element) {
        switch (operation) {
            case '+' :
              std::cout << (table.add(element) ? "OK\n" : "FAIL\n");
              break;
            case '-' :
              std::cout << (table.remove(element) ? "OK\n" : "FAIL\n");
              break;
            case '?' :
              std::cout << (table.has(element) ? "OK\n" : "FAIL\n");
              break;
            default:
              assert(false);
              break;
        }
    }

    return 0;
}