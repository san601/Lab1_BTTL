#include <iostream>
#include <algorithm>

using namespace std;

void output(int tu_so, int mau_so)
{
    /*
     * Ham xuat phan so sau khi rut gon
     *
     * Args:
     *      tu_so (int): tu so cua phan so
     *      mau_so (int): mau so cua phan so
     */

    int gcd = __gcd(tu_so, mau_so);
    tu_so /= gcd;
    mau_so /= gcd;
    if (mau_so < 0) tu_so *= -1, mau_so *= -1;
    if (tu_so == 0) printf("0\n");
    else if (mau_so == 1) printf("%d\n", tu_so);
    else printf("%d/%d\n", tu_so, mau_so);
}

void tong(int tu_so_1, int mau_so_1, int tu_so_2, int mau_so_2)
{
    /*
     * Ham tinh tong hai phan so
     *
     * Args:
     *      tu_so_1 (int): tu so cua phan so 1
     *      mau_so_1 (int): mau so cua phan so 1
     *      tu_so_2 (int): tu so cua phan so 2
     *      mau_so_2 (int): mau so cua phan so 2
     */

    int tu_so = (tu_so_1 * mau_so_2) + (tu_so_2 * mau_so_1);
    int mau_so = mau_so_1 * mau_so_2;
    printf("Tong la ");
    output(tu_so, mau_so);
}

void hieu(int tu_so_1, int mau_so_1, int tu_so_2, int mau_so_2)
{
    /*
     * Ham tinh hieu hai phan so
     *
     * Args:
     *      tu_so_1 (int): tu so cua phan so 1
     *      mau_so_1 (int): mau so cua phan so 1
     *      tu_so_2 (int): tu so cua phan so 2
     *      mau_so_2 (int): mau so cua phan so 2
     */

    int tu_so = (tu_so_1 * mau_so_2) - (tu_so_2 * mau_so_1);
    int mau_so = mau_so_1 * mau_so_2;
    printf("Hieu la ");
    output(tu_so, mau_so);
}

void tich(int tu_so_1, int mau_so_1, int tu_so_2, int mau_so_2)
{
    /*
     * Ham tinh tich hai phan so
     *
     * Args:
     *      tu_so_1 (int): tu so cua phan so 1
     *      mau_so_1 (int): mau so cua phan so 1
     *      tu_so_2 (int): tu so cua phan so 2
     *      mau_so_2 (int): mau so cua phan so 2
     */

    int tu_so = tu_so_1 * tu_so_2;
    int mau_so = mau_so_1 * mau_so_2;
    printf("Tich la ");
    output(tu_so, mau_so);
}

void thuong(int tu_so_1, int mau_so_1, int tu_so_2, int mau_so_2)
{
    /*
     * Ham tinh phep chia hai phan so
     *
     * Args:
     *      tu_so_1 (int): tu so cua phan so 1
     *      mau_so_1 (int): mau so cua phan so 1
     *      tu_so_2 (int): tu so cua phan so 2
     *      mau_so_2 (int): mau so cua phan so 2
     */

    int tu_so = tu_so_1 * mau_so_2;
    int mau_so = mau_so_1 * tu_so_2;
    if (mau_so == 0) cout << "Khong the chia cho 0";
    else
    {
        printf("Thuong la ");
        output(tu_so, mau_so);
    }
}

int main() {
    int tu_so_1 = 0, mau_so_1 = 0, tu_so_2 = 0, mau_so_2 = 0;
    cout << "Nhap tu so 1: ";
    fflush(stdout);
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
    tong(tu_so_1, mau_so_1, tu_so_2, mau_so_2);
    hieu(tu_so_1, mau_so_1, tu_so_2, mau_so_2);
    tich(tu_so_1, mau_so_1, tu_so_2, mau_so_2);
    thuong(tu_so_1, mau_so_1, tu_so_2, mau_so_2);
    return 0;
}
