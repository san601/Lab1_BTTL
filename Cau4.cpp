#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 3.1415926535;

double factorial(int n)
{
    /*
     * Ham tinh giai thua cua mot so
     *
     * Args:
     *      n (int): so can tinh giai thua
     *
     * Returns:
     *      double: giai thua cua n
     */

    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    double x;
    printf("Nhap so can tinh: ");
    cin >> x;
    printf("sin(%.5lf) = ", x);
    // Chuyen x ve khoang [0, 2*PI]
    x = fmod(x, 2 * PI);

    int n = 0;
    double sin = 0;
    double pow_x = x;
    double fact = 1;
    while (n <= 17)
    {
        sin += pow_x / fact;
        n++;
        pow_x *= x * x * (-1);
        fact = factorial(2 * n + 1);
    }
    printf("%.5lf", sin);
    return 0;
}
