/*
 * Порядковая статистика
 *
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9]
 * размера n. Требуется найти k-ю порядковую статистику.
 * т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1)
 * в отсортированном массиве. Напишите нерекурсивный алгоритм.
 *
 * Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами
 * от конца массива к началу.
 *
 */

#include <iostream>
#include <cassert>
#include <algorithm>

template <class T>
size_t medianOfThree(T* array, size_t begin, size_t end) {
  size_t middle = (begin + end) / 2;

  size_t biggest = std::max(array[begin], std::max(array[middle], array[end]));

  if (biggest == array[begin]) {
    return (array[middle] > array[end]) ? middle : end;
  } else if (biggest == array[middle]) {
    return (array[begin] > array[end]) ? begin : end;
  } else {
    return (array[begin] > array[middle]) ? begin : middle;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
size_t partition(T* array, size_t begin, size_t end) {
  size_t pivot = medianOfThree(array, begin, end);

  if (pivot != begin) {
    std::swap(array[begin], array[pivot]);
    pivot = begin;
  }

  size_t i = end;

  for (size_t j = end; j > begin; j--) {
    if (array[j] >= array[pivot]) {
      if (j != i) {
        std::swap(array[j], array[i]);
      }
      i--;
    }
  }

  if (pivot != i) {
    std::swap(array[pivot], array[i]);
  }

  return i;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
T kStatistic(T* array, const size_t size, const size_t k) {
  size_t  begin = 0, end = size - 1;
  size_t pivot = partition(array, begin, end);

  while (pivot != k) {
    if (pivot > k) {
      end = pivot;
    } else if (pivot < k) {
      begin = pivot + 1;
    }
    pivot = partition(array, begin, end);
  }
  return array[pivot];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t n, k;
  std::cin >> n >> k;
  assert(n > 0 && (k >= 0 && k < n));

  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  std::cout << kStatistic(array, n, k) << '\n';

  delete[] array;

  return 0;
}