/*
 * Современники
 *
 * Группа людей называется современниками если был такой момент,
 * когда они могли собраться вместе. Для этого в этот момент
 * каждому из них должно было уже исполниться 18 лет,
 * но ещё не исполниться 80 лет. Дан список Жизни Великих Людей.
 * Необходимо получить максимальное количество современников.
 * В день 18летия человек уже может принимать участие в собраниях,
 * а в день 80летия и в день смерти уже не может.
 *
 * Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
 * В этих случаях принимать участие в собраниях он не мог.
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <cstring>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Date {
 public:
  Date() = default;

  Date(int day, int month, int year) : day_(day), month_(month), year_(year) {}

  Date(const Date&) = default;
  Date(Date&&) = default;
  Date& operator=(const Date&) = default;
  Date& operator=(Date&&) = default;

  ~Date() = default;

  // set
  void setDay(const int day) { day_ = day; }
  void setMonth(const int month) { month_ = month; }
  void setYear(const int year) { year_ = year; }

  // get
  int getDay() { return day_; }
  int getMonth() { return month_; }
  int getYear() { return  year_; }

  // input and output
  friend std::istream& operator>>(std::istream& stream, Date& date);
  friend std::ostream& operator<<(std::ostream& stream, Date& date);

  // comparison
  friend bool operator==(const Date& firstDate, const Date& secondDate);
  friend bool operator>(const Date& firstDate, const Date& secondDate);
  friend bool operator<(const Date& firstDate, const Date& secondDate);
  friend bool operator>=(const Date& firstDate, const Date& secondDate);
  friend bool operator<=(const Date& firstDate, const Date& secondDate);

 private:
  int day_;
  int month_;
  int year_;
};

// operators of input and output
std::istream& operator>>(std::istream& stream, Date& date) {
  stream >> date.day_ >> date.month_ >> date.year_;
  return stream;
}

std::ostream& operator<<(std::ostream& stream, Date& date) {
  stream << date.day_ << ' ' << date.month_ << ' ' << date.year_ << '\n';
  return stream;
}

// operators of comparison
bool operator==(const Date& firstDate, const Date& secondDate) {
  return (firstDate.day_ == secondDate.day_ &&
          firstDate.month_ == secondDate.month_ &&
          firstDate.year_ == secondDate.year_);
}

bool operator>(const Date& firstDate, const Date& secondDate) {
  if (firstDate.year_ > secondDate.year_) {
    return true;
  } else if (firstDate.year_ < secondDate.year_) {
    return false;
  } else {
    if (firstDate.month_ > secondDate.month_) {
      return true;
    } else if (firstDate.month_ < secondDate.month_) {
      return false;
    } else {
      return firstDate.day_ > secondDate.day_;
    }
  }
}

bool operator<(const Date& firstDate, const Date& secondDate) {
  if (firstDate.year_ < secondDate.year_) {
    return true;
  } else if (firstDate.year_ > secondDate.year_) {
    return false;
  } else {
    if (firstDate.month_ < secondDate.month_) {
      return true;
    } else if (firstDate.month_ > secondDate.month_) {
      return false;
    } else {
      return firstDate.day_ < secondDate.day_;
    }
  }
}

bool operator>=(const Date& firstDate, const Date& secondDate) {
  if (firstDate.year_ > secondDate.year_) {
    return true;
  } else if (firstDate.year_ < secondDate.year_) {
    return false;
  } else {
    if (firstDate.month_ > secondDate.month_) {
      return true;
    } else if (firstDate.month_ < secondDate.month_) {
      return false;
    } else {
      return firstDate.day_ >= secondDate.day_;
    }
  }
}

bool operator<=(const Date& firstDate, const Date& secondDate) {
  if (firstDate.year_ < secondDate.year_) {
    return true;
  } else if (firstDate.year_ > secondDate.year_) {
    return false;
  } else {
    if (firstDate.month_ < secondDate.month_) {
      return true;
    } else if (firstDate.month_ > secondDate.month_) {
      return false;
    } else {
      return firstDate.day_ <= secondDate.day_;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, class Comparison>
void merge(const T* firstArray, const size_t firstArraySize,
           const T* secondArray, const size_t secondArraySize,
           T* mergedArray, Comparison comparison) {

  size_t firstArrayIndex = 0, secondArrayIndex = 0, mergedArrayIndex = 0;

  while (firstArrayIndex < firstArraySize && secondArrayIndex < secondArraySize) {
    if (comparison(firstArray[firstArrayIndex], secondArray[secondArrayIndex])) {
      mergedArray[mergedArrayIndex++] = firstArray[firstArrayIndex++];
    } else {
      mergedArray[mergedArrayIndex++] = secondArray[secondArrayIndex++];
    }
  }

  // if there are elements left in firstArray
  while (firstArrayIndex < firstArraySize) {
    mergedArray[mergedArrayIndex++] = firstArray[firstArrayIndex++];
  }

  // еif there are elements left in secondArray
  while (secondArrayIndex < secondArraySize) {
    mergedArray[mergedArrayIndex++] = secondArray[secondArrayIndex++];
  }
}

template <typename T, class Comparison>
void mergeSort(T* array, size_t arraySize, Comparison comparison) {
  if (arraySize <= 1) {
    return;
  }

  size_t firstIntervalSize = arraySize / 2, secondIntervalSize = arraySize - firstIntervalSize;

  mergeSort(array, firstIntervalSize, comparison);
  mergeSort(array + firstIntervalSize, secondIntervalSize, comparison);

  T* temp = new T[arraySize];
  merge(array, firstIntervalSize, array + firstIntervalSize, secondIntervalSize, temp, comparison);
  memcpy(array, temp, sizeof(T) * arraySize);
  delete[] temp;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Event {  // consists of a date and a type of event (birth or death)
  Date date;
  bool meaning;  // true - birth, +1 contemporary; false - death, -1 contemporary
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int maxContemporariesNumber(std::vector<std::pair<Date, Date>>& datesList) {
  Event* dateInterval = new Event[datesList.size() * 2];

  size_t datesAmount = 0;
  for (auto &i : datesList) {
    // приводим интервалы дат к интервалам длины (80 - 18)
    Date leftBorder(i.first.getDay(), i.first.getMonth(), i.first.getYear() + 18);
    Date rightBorder(i.first.getDay(), i.first.getMonth(), i.first.getYear() + 80);

    if (leftBorder >= i.second) {
      continue;
    }

    if (rightBorder > i.second) {  // if a man dies earlier than gets 80 years old than move the right border
      rightBorder = i.second;
    }

    dateInterval[datesAmount++] = { leftBorder, true };
    dateInterval[datesAmount++] = {rightBorder, false };
   }

  mergeSort(dateInterval, datesAmount, [](const Event& left,
                                          const Event& right){ return left.date <= right.date; });

  int maxContemporariesNumber = 0, tempMax = 0;
  for (int i = 0; i < datesAmount; ++i) {
    dateInterval[i].meaning ? tempMax++ : tempMax--;
    if (tempMax > maxContemporariesNumber) {
      maxContemporariesNumber = tempMax;
    }
  }

  delete[] dateInterval;

  return maxContemporariesNumber;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  int numberOfPeople = 0;
  std::cin >> numberOfPeople;

  std::vector<std::pair<Date, Date>> greatPeopleLivesList(numberOfPeople);

  for (int i = 0; i < numberOfPeople; i++) {
    std::cin >> greatPeopleLivesList[i].first >> greatPeopleLivesList[i].second;
  }

  std::cout << maxContemporariesNumber(greatPeopleLivesList) << '\n';

  return 0;
}