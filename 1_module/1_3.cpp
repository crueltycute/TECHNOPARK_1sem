/*
 * Нужная сумма
 *
 * Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m)
 * и число k. Найти количество таких пар индексов (i, j),
 * что A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.
 *
 * Указание. Обходите массив B от конца к началу.
 */

#include <iostream>
#include <cassert>

int main() {
    int n;
    std::cin >> n;
    assert(n > 0 && n <= 100000);
    int* A = new int[n];
    assert(A);
    for (int i = 0; i < n; ++i)
        std::cin >> A[i];

    int m;
    std::cin >> m;
    assert(m > 0 && m <= 100000);
    int* B = new int[m];
    assert(B);
    for (int i = m - 1; i >= 0; i--)
        std::cin >> B[i];

    int k;
    std::cin >> k;

    size_t pairCounter = 0;
    size_t i = 0, j = 0;

    while (i < n && j < m) {
        int sum = A[i] + B[j];
        if (sum > k) {
            j++;
        } else if (sum < k) {
            i++;
        } else if (sum == k) {
            pairCounter++;
            j++;
        }
    }

    std::cout << pairCounter << '\n';

    return 0;
}