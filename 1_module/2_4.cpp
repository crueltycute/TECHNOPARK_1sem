/*
 * Поиск близнеца
 *
 * Дан отсортированный массив различных целых чисел A[0..n-1]
 * и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i]
 * найдите минимальный индекс элемента массива A[k],
 * ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000.
 * Время работы поиска для каждого элемента B[i]: O(log(k)).
 */

#include <iostream>
#include <cassert>

size_t binarySearch(const int* array, size_t left, size_t right, const int value) {
  assert(array);

  while (right - left > 1) {
    size_t mid = (left + right) / 2;
    if (array[mid] > value) {
      right = mid;
    } else {
      left = mid;
    }
  }
  return abs(value - array[left]) <= abs(array[right] - value) ? left : right;
}

size_t indexOfClosestValue(const int* const array, const size_t arraySize, const int value) {
  assert(array);

  // simple cases
  if (value <= array[0]) {
    return 0;
  }
  if (value > array[arraySize - 1]) {
    return arraySize - 1;
  }

  // finding borders of area to use binary search on
  size_t rightBorder = 1;
  while (array[rightBorder - 1] < value && (rightBorder << 1) < arraySize) {
    rightBorder <<= 1;
  }

  size_t left = rightBorder >> 2;

  if (array[rightBorder] < value) {
    rightBorder = arraySize - 1;
  }

  size_t right = rightBorder;

  return binarySearch(array, left, right, value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t n;
  std::cin >> n;
  // assert(n > 0 && n <= 11000);
  int* A = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> A[i];
  }

  size_t m;
  std::cin >> m;
  // assert(m > 0 && m <= 1000);
  int* B = new int[m];
  for (int i = 0; i < m; ++i) {
    std::cin >> B[i];
  }

  for (int i = 0; i < m; ++i)
    std::cout << indexOfClosestValue(A, n, B[i]) << ' ';

  delete[] A;
  delete[] B;

  return 0;
}