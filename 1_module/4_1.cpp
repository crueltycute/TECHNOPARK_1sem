#include <iostream>
#include <cassert>
#include <vector>

class Heap {
 public:
    Heap() = delete;
    Heap(int* array, size_t size);
    Heap& operator=(const Heap& object);
    Heap& operator=(Heap&& object);
    Heap(const Heap& object);
    Heap(Heap&& object);
    ~Heap();

    size_t getSize();

    bool isEmpty();

    void add(const int value);
    int peekMax();
    int extractMax();

 private:
    size_t realSize_ = 0;
    size_t size_ = 0;
    int* array_ = nullptr;

    void siftUp(size_t i);
    void siftDown(size_t i);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Heap::Heap(int* array, size_t size) : size_(size), realSize_(size) {
  array_ = new int[size_];
  std::copy(array, array + size, array_);
  for (int i = size / 2 - 1; i >= 0 ; --i) {
    siftDown(i);
  }
}

Heap& Heap::operator=(const Heap& object) {
  delete[] array_;
  size_ = object.size_;
  realSize_ = object.realSize_;
  array_ = new int[size_];
  std::copy(object.array_, object.array_ + size_, array_);
  return *this;
}

Heap& Heap::operator=(Heap&& object) {
  delete[] array_;
  array_ = object.array_;
  object.array_ = nullptr;
  size_ = object.size_;
  realSize_ = object.realSize_;
  return *this;
}

Heap::Heap(const Heap& object) : size_(object.size_), realSize_(object.realSize_) {
  array_ = new int[realSize_];
  std::copy(object.array_, object.array_ + object.size_, array_);
}

Heap::Heap(Heap&& object) : size_(object.size_), realSize_(object.realSize_) {
  delete[] array_;
  std::move(object.array_, object.array_ + object.size_, array_);
  object.array_ = nullptr;
}

Heap::~Heap() {
  delete[] array_;
}

size_t Heap::getSize() {
  return size_;
}

void Heap::siftDown(size_t i) {
  size_t leftChild = i * 2 + 1, rightChild = i * 2 + 2, largestChild = i;
  if (leftChild < size_ && array_[leftChild] > array_[i]) {
    largestChild = leftChild;
  }
  if (rightChild < size_ && array_[rightChild] > array_[largestChild]) {
    largestChild = rightChild;
  }
  if (largestChild != i) {
    std::swap(array_[i], array_[largestChild]);
    siftDown(largestChild);
  }
}

void Heap::siftUp(size_t i) {
  while (i > 0) {
    size_t parent = (i - 1) / 2;
    if (array_[i] <= array_[parent]) {
      return;
    }
    std::swap(array_[i], array_[parent]);
    i = parent;
  }
}

bool Heap::isEmpty() {
  return size_ == 0;
}

void Heap::add(const int value) {
  array_[size_++] = value;
  siftUp(size_ - 1);
}

int Heap::peekMax() {
  return array_[0];
}

int Heap::extractMax() {
  assert(!isEmpty());

  int result = array_[0];
  array_[0] = array_[size_ - 1];
  size_--;

  siftDown(0);

  return result;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int findEatingsNumber(Heap& heap, int K) {
  int eatingsNumber = 0;
  while (heap.getSize() > 0) {
    int alreadyCarriedWeight = 0;
    std::vector<int> chosenFruits;

    while (alreadyCarriedWeight + heap.peekMax() <= K && heap.getSize() > 0) {  // getting fruits
      int fruitWeight = heap.extractMax();
      alreadyCarriedWeight += fruitWeight;
      chosenFruits.push_back(fruitWeight);
    }

    while (chosenFruits.size() != 0) { // biting fruits
      if (chosenFruits.back() != 1) {
        heap.add(chosenFruits.back() / 2);
      }
      chosenFruits.pop_back();
    }

    ++eatingsNumber;
  }
  return eatingsNumber;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t n;
  assert(n >= 0 || n <= 50000);
  std::cin >> n;

  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  int K;
  std::cin >> K;
  assert(K >= 0 || K <=1000);

  Heap heap(array, n);

  std::cout << findEatingsNumber(heap, K) << '\n';

  return 0;
}