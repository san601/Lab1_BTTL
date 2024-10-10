#include <iostream>
#include <algorithm>

using namespace std;

// Tinh gia tri cua phan so, tra ve double
double gia_tri(int &tu_so, int &mau_so)
{
    /*
     * Args:
     *  tu_so: tu so cua phan so
     *  mau_so: mau so cua phan so
     *
     */
    int temp = __gcd(tu_so, mau_so);
    tu_so = tu_so / temp;
    mau_so = mau_so / temp;
    return 1.0 * tu_so / mau_so;
}

int main() {
    int tu_so_1 = 0, mau_so_1 = 0, tu_so_2 = 0, mau_so_2 = 0;
    cout << "Nhap tu so 1: ";
    cin >> tu_so_1;
    while (mau_so_1 == 0)
    {
        cout << "Nhap mau so 1: ";
        cin >> mau_so_1;
    }
    cout << "Nhap tu so 2: ";
    cin >> tu_so_2;
    while (mau_so_2 == 0)
    {
        cout << "Nhap mau so 2: ";
        cin >> mau_so_2;
    }

    if (gia_tri(tu_so_1, mau_so_1) > gia_tri(tu_so_2, mau_so_2))
        printf("Phan so lon nhat la %d/%d", tu_so_1, mau_so_1);
    else if (gia_tri(tu_so_1, mau_so_1) < gia_tri(tu_so_2, mau_so_2))
        printf("Phan so lon nhat la %d/%d", tu_so_2, mau_so_2);
    else puts("Hai phan so bang nhau");

    return 0;
}
