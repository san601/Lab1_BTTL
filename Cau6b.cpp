#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

struct HocSinh
{
    string ho_ten;
    string xep_hang;
    float diem_toan;
    float diem_van;
    float diem_nn;
    float diem_trung_binh;
};

vector <struct HocSinh> hoc_sinh;

bool ten_hop_le(string ten) {
    /*
     * Kiem tra ten hoc sinh hop le
     *
     * Args:
     *      ten (string): ten hoc sinh can kiem tra
     *
     * Returns:
     *      bool: true neu hop le, false neu khong hop le
     */

    // kiem tra do dai ten
    if (ten.length() < 1 || ten.length() > 50) {
        return false;
    }

    // kiem tra ky tu hop le
    for (char c : ten) {
        if (!isalpha(c) && !isspace(c)) {
            return false;
        }
    }

    // kiem tra viet hoa ky tu dau tien
    if (!isupper(ten[0])) {
        return false;
    }

    // kiem tra viet hoa sau dau cach
    for (int i = 1; i < ten.length(); i++) {
        if ((isupper(ten[i]) && ten[i - 1] != ' ') || (islower(ten[i]) && ten[i - 1] == ' ')) {
            return false;
        }
    }

    return true;
}

float diem_trung_binh(float diem_toan, float diem_van, float diem_nn)
{
    /*
     * Tinh diem trung binh cua hoc sinh
     *
     * Args:
     *      diem_toan (float): diem mon toan
     *      diem_van (float): diem mon van
     *      diem_nn (float): diem mon ngoai ngu
     *
     * Returns:
     *      float: diem trung binh
     */

    // diem trung binh = (2 * diem toan + diem van + diem ngoai ngu) / 4
    return (2 * diem_toan + diem_van + diem_nn) / 4;
}

string xep_hang(float dtb)
{
    /*
     * Xep hang hoc sinh
     *
     * Args:
     *      dtb (float): diem trung binh cua hoc sinh
     *
     * Returns:
     *      string: xep hang hoc sinh
     */

    if (dtb >= 9) return "Xuat sac";
    if (dtb >= 8) return "Gioi";
    if (dtb >= 6.5) return "Kha";
    if (dtb >= 5) return "Trung binh";
    return "Yeu";
}

void input(int n)
{
    /*
     * Nhap thong tin hoc sinh
     *
     * Args:
     *      n (int): so luong hoc sinh
     */

    for (int i = 0; i < n; i++)
    {
        string ten;
        float diem_toan, diem_van, diem_nn;
        struct HocSinh tmp;

        // Nhap va kiem tra hop le ten hoc sinh
        cout << "Nhap ten hoc sinh: ";
        while(true)
        {
            getline(cin, ten);
            if (!ten_hop_le(ten)) {
                cout << "Ten khong hop le. Vui long nhap lai: ";
                continue;
            }
            else break;
        }

        // Nhap va kiem tra diem toan, van, ngoai ngu hop le
        while (true)
        {
            cout << "Nhap diem toan (trong khoang tu 0 den 10): ";
            cin >> diem_toan;
            if (diem_toan >= 0 && diem_toan <= 10) break;
        }
        while (true)
        {
            cout << "Nhap diem van (trong khoang tu 0 den 10): ";
            cin >> diem_van;
            if (diem_van >= 0 && diem_van <= 10) break;
        }
        while (true)
        {
            cout << "Nhap diem ngoai ngu (trong khoang tu 0 den 10): ";
            cin >> diem_nn;
            if (diem_nn >= 0 && diem_nn <= 10) break;
        }

        // Luu thong tin hoc sinh
        tmp.ho_ten = ten;
        tmp.diem_toan = diem_toan;
        tmp.diem_van = diem_van;
        tmp.diem_nn = diem_nn;
        tmp.diem_trung_binh = diem_trung_binh(diem_toan, diem_van, diem_nn);
        tmp.xep_hang = xep_hang(tmp.diem_trung_binh);
        hoc_sinh.push_back(tmp);
        cin.ignore();
    }
}

void dtb_cao_nhat()
{
    /*
     * Tim hoc sinh co diem trung binh cao nhat
     */

    struct HocSinh tmp;
    for (auto i : hoc_sinh)
    {
        if (i.diem_trung_binh > tmp.diem_trung_binh) tmp = i;
    }
    cout << "Danh sach hoc sinh co diem trung binh cao nhat la:\n";
    for (auto i : hoc_sinh)
    {
        if (i.diem_trung_binh == tmp.diem_trung_binh)
            cout << "  -   " << i.ho_ten << " voi diem trung binh la " << i.diem_trung_binh << " va xep loai " << i.xep_hang << endl;
    }
}

void diem_toan_thap_nhat()
{
    /*
     * Tim hoc sinh co diem toan thap nhat
     *
     * Args:
     *      ten (string): ten hoc sinh can tim kiem
     */

    struct HocSinh tmp;
    tmp.diem_toan = 11;
    cout << "Danh sach hoc sinh co diem toan thap nhat la:\n";
    for (auto i : hoc_sinh)
    {
        if (i.diem_toan < tmp.diem_toan) tmp = i;
    }
    for (auto i : hoc_sinh)
    {
        if (i.diem_toan == tmp.diem_toan)
            cout << "  -   " << i.ho_ten << " voi diem toan la " << i.diem_toan << " va xep loai " << i.xep_hang << endl;
    }

}

void tim_kiem_hoc_sinh(string ten)
{
    /*
     * Tim kiem hoc sinh theo ten
     *
     * Args:
     *      ten (string): ten hoc sinh can tim kiem
     */
    transform(ten.begin(), ten.end(), ten.begin(), ::tolower);

    for (auto i : hoc_sinh)
    {
        string tmp = i.ho_ten;
        transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
        if (tmp.find(ten) != string::npos) cout << "  ->   Hoc sinh co ten " << ten << " la: " << i.ho_ten << " voi diem trung binh la " << i.diem_trung_binh << " va xep loai " << i.xep_hang << endl;
    }
}

int main() {
    int n = 3;
    input(n);
    dtb_cao_nhat();
    string ten;
    cout << "Nhap ten hoc sinh can tim kiem: ";
    cin >> ten;
    tim_kiem_hoc_sinh(ten);
    diem_toan_thap_nhat();
    return 0;
}
