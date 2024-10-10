#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

const double PI = 3.1415926535;

double factorial(int n)
{
    if (n == 0 || n == 1) return 1;
    return n * factorial(n - 1);
}

double get_fraction(double x, int so_mu)
{
    double pow_x = pow(x, so_mu);
    return pow_x / factorial(so_mu);
}

int main() {
    double x;
    printf("Nhap so can tinh: ");
    cin >> x;
    while (x >= (2 * PI)) x -= (2 * PI);
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
