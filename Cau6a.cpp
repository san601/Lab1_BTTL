#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

int N = 1e5 + 5;

int main() {
    vector <int> ket_qua, a, b;
    int n;
    cout << "Nhap so luong phan tu cua mang A: ";
    cin >> n;
    cout << "Nhap mang A\n";
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        a.push_back(temp);
    }
    int m;
    cout << "Nhap so luong phan tu cua mang B: ";
    cin >> m;
    cout << "Nhap mang B\n";
    for (int i = 0; i < m; i++)
    {
        int temp;
        cin >> temp;
        b.push_back(temp);
    }

    auto i = b.begin();
    while (i != b.end())
    {
        auto temp = search(i, b.end(), a.begin(), a.end());
        if (temp != b.end())
        {
            ket_qua.push_back(abs(distance(temp, b.begin())));
            i = temp + n;
        }
        else i++;
    }
    cout << "Mang A xuat hien o cac vi tri: ";
    for (auto i : ket_qua) cout << i << " ";
    return 0;
}
