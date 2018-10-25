/*
 * Реализовать очередь с помощью двух стеков.
 * Использовать стек, реализованный с помощью динамического буфера.
 */

#include <iostream>
#include <cassert>

#define QUEUE_IS_EMPTY -1

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Stack{
 public:
  Stack() = default;
  Stack(const Stack& object);
  Stack(Stack&& object);
  Stack& operator=(const Stack& object);
  Stack& operator=(Stack&& object);
  ~Stack();

  void push(T data);
  T pop();
  bool isEmpty() const;

 private:
  size_t size_ = 0;
  size_t capacity_ = 1;
  T* array_ = new T[capacity_];
};

template <typename T>
Stack<T>::Stack(const Stack& object) : size_(object.size_), capacity_(object.capacity_) {
  array_ = new T[capacity_];
  for (int i = 0; i < size_; i++) {
    array_[i] = object.array_[i];
  }
}

template <typename T>
Stack<T>::Stack(Stack&& object) : size_(object.size_), capacity_(object.capacity_) {
  delete[] array_;
  array_ = object.array_;
  object.array_ = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack &object) {
  size_ = object.size_;
  capacity_ = object.capacity_;
  delete[] array_;
  array_ = new T[capacity_];
  for (int i = 0; i < size_; i++) {
    array_[i] = object.array_[i];
  }
  return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack &&object) {
  size_ = object.size_;
  capacity_ = object.capacity_;
  delete[] array_;
  array_ = object.array_;
  object.array_ = nullptr;
  return *this;
}

template <typename T>
Stack<T>::~Stack() {
  delete[] array_;
}

template <typename T>
void Stack<T>::push(T data) {
  assert(size_ <= capacity_);
  if (size_ == capacity_) {
    capacity_ *= 2;
    int* newArray = new T[capacity_];
    for (int i = 0; i < size_; i++) {
      newArray[i] = array_[i];
    }
    delete[] array_;
    array_ = newArray;
  }
  array_[size_++] = data;
}

template <typename T>
T Stack<T>::pop() {
  assert(size_ > 0);
  return array_[--size_];
}

template <typename T>
bool Stack<T>::isEmpty() const {
  return size_ == 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Queue {
 public:
  Queue() = default;
  Queue(const Queue& object);
  Queue(Queue&& object);
  Queue& operator=(const Queue& object) = default;
  Queue& operator=(Queue&& object);
  ~Queue() = default;

  void pushBack(T data);
  T popFront();
  bool isEmpty() const;

 private:
  Stack<T> backStack_;
  Stack<T> frontStack_;
};

template <typename T>
Queue<T>::Queue(const Queue& object) {
  frontStack_ = object.frontStack_;
  backStack_ = object.backStack_;
}

template <typename T>
Queue<T>::Queue(Queue&& object)  {
  frontStack_ = object.frontStack_;
  backStack_ = object.backStack_;
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue &&object) {
  frontStack_ = object.frontStack_;
  backStack_ = object.backStack_;
  return *this;
}

template <typename T>
void Queue<T>::pushBack(T data){
  backStack_.push(data);
}

template <typename T>
T Queue<T>::popFront() {
  if (frontStack_.isEmpty() && backStack_.isEmpty()) {
    return QUEUE_IS_EMPTY;
  }

  if (!frontStack_.isEmpty()) {
    return frontStack_.pop();
  }

  while (!backStack_.isEmpty()) {
    frontStack_.push(backStack_.pop());
  }
  return frontStack_.pop();
}

template <typename T>
bool Queue<T>::isEmpty() const {
  return backStack_.isEmpty() && frontStack_.isEmpty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  int n = 0;
  std::cin >> n;
  assert(n >= 0 && n <= 1000000);

  Queue<int> stackBasedQueue;

//  for (int i = 0; i < n; i++) {
//    int command = 0, value = 0;
//    std::cin >> command >> value;
//    assert(command == 2 || command == 3);
//
//    if (command == 2) {
//      if (value != stackBasedQueue.popFront()) {
//        std::cout << "NO\n";
//        return 0;
//      }
//    }
//
//    if (command == 3) {
//      stackBasedQueue.pushBack(value);
//    }
//  }

  Stack<int> stackToMove = Stack<int>()

  Queue<int> queueToMove = Queue<int>();


  std::cout << "YES\n";

  return 0;
}