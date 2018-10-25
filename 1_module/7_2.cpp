#include <iostream>
#include <cassert>

#define LONG_LONG_SIZE sizeof(long long)
#define BIT_VALUES 256

int getByte(const long long value, int byte) {
  return (value >> (8 * byte) & 255);  // getting a new byte, moving on 64 bit and checking not getting bigger value than one byte
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LSD(long long* array, int size) {
  assert(size > 0 && array);
  for (int i = 0; i < LONG_LONG_SIZE; ++i) {
    long long* valuesCounters = new long long[BIT_VALUES] {0};

    for (int j = 0; j < size; j++) {
      valuesCounters[getByte(array[j], i)]++;
    }

    for (int j = 1; j < BIT_VALUES; j++) {
      valuesCounters[j] += valuesCounters[j - 1];
    }

    long long* tempArray = new long long[size];

    for (int j = size - 1; j >= 0 ; j--) {
      tempArray[--valuesCounters[getByte(array[j], i)]] = array[j];
    }

    std::copy(tempArray, tempArray + size, array);

    delete[] valuesCounters;
    delete[] tempArray;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  int numbersAmount;
  std::cin >> numbersAmount;
  assert(numbersAmount > 0 && numbersAmount <= 1000000);

  long long* numbers = new long long[numbersAmount];
  for (int i = 0; i < numbersAmount; ++i) {
    std::cin >> numbers[i];
  }

  LSD(numbers, numbersAmount);

  for (int i = 0; i < numbersAmount; ++i) {
    std::cout << numbers[i] << ' ';
  }

  delete[] numbers;

  return 0;
}

/*
input:
 10
0 1000000 1 3 5000 0 89 765 2 1
output:
0 0 1 1 2 3 1000000 89 5000 765
 */