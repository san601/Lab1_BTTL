#include <iostream>
#include <algorithm>

using namespace std;

// Tinh gia tri cua phan so, tra ve double
double gia_tri(int &tu_so, int &mau_so)
{
    /*
     * Ham tinh gia tri cua phan so duoi dang thap phan
     *
     * Args:
     *      tu_so (int): tu so cua phan so
     *      mau_so (int): mau so cua phan so
     *
     * Returns:
     *      double: gia tri cua phan so
     */

    // Tranh tran so
    int temp = __gcd(tu_so, mau_so);
    tu_so = tu_so / temp;
    mau_so = mau_so / temp;

    return 1.0 * tu_so / mau_so;
}

int main() {
    int tu_so_1 = 0, mau_so_1 = 0, tu_so_2 = 0, mau_so_2 = 0;

    cout << "Nhap tu so 1: ";
    cin >> tu_so_1;
    // Nhap va kiem tra mau so khac 0
    while (mau_so_1 == 0)
    {
        cout << "Nhap mau so 1: ";
        cin >> mau_so_1;
    }

    cout << "Nhap tu so 2: ";
    cin >> tu_so_2;
    // Nhap va kiem tra mau so khac 0
    while (mau_so_2 == 0)
    {
        cout << "Nhap mau so 2: ";
        cin >> mau_so_2;
    }

    // So sanh gia tri cua hai phan so
    if (gia_tri(tu_so_1, mau_so_1) > gia_tri(tu_so_2, mau_so_2))
        if (tu_so_1 == 0) printf("Phan so lon nhat la 0");
        else if (mau_so_1 == 1) printf("Phan so lon nhat la %d", tu_so_1);
        else printf("Phan so lon nhat la %d/%d", tu_so_1, mau_so_1);
    else if (gia_tri(tu_so_1, mau_so_1) < gia_tri(tu_so_2, mau_so_2))
        if (tu_so_2 == 0) printf("Phan so lon nhat la 0");
        else if (mau_so_2 == 1) printf("Phan so lon nhat la %d", tu_so_2);
        else printf("Phan so lon nhat la %d/%d", tu_so_2, mau_so_2);
    else puts("Hai phan so bang nhau");

    return 0;
}
