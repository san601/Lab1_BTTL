#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int tu_so = 1, mau_so = 0;
    cout << "Nhap tu so: ";
    cin >> tu_so;
    while (mau_so == 0)
    {
        cout << "Nhap mau so: ";
        cin >> mau_so;
    }
    // Rut gon phan so
    int gcd = __gcd(tu_so, mau_so);
    tu_so /= gcd;
    mau_so /= gcd;
    // Neu mau so am thi dua dau am len tu so
    if (mau_so < 0) tu_so *= -1, mau_so *= -1;
    cout << "Phan so duoc rut gon la: " << tu_so << "/" << mau_so;
    return 0;
}