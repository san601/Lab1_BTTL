#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

float lai_suat_1_nam = 0.046;
float lai_suat_6_thang = 0.03;

int ENCODED_DATE[2][14] = {
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

struct SoTietKiem
{
    string ma_so;               // max 5 ky tu
    string loai_tiet_kiem;      // max 10 ky tu
    string ho_ten_khach_hang;   // max 30 ky tu
    string cmnd;                // 9 hoac 12 ky tu
    string ngay_mo_so;          // dd/mm/yyyy
    float so_tien_gui;          // so tien gui ban dau > 0
};

vector <struct SoTietKiem> so_tiet_kiem;

bool nam_nhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

bool ngay_mo_so_hop_le(string ngay_mo_so)
{
    if (ngay_mo_so.length() != 10) return false;
    if (ngay_mo_so[2] != '/' || ngay_mo_so[5] != '/') return false;
    if (!isdigit(ngay_mo_so[0]) || !isdigit(ngay_mo_so[1]) || !isdigit(ngay_mo_so[3]) || !isdigit(ngay_mo_so[4]) || !isdigit(ngay_mo_so[6]) || !isdigit(ngay_mo_so[7]) || !isdigit(ngay_mo_so[8]) || !isdigit(ngay_mo_so[9])) return false;
    int ngay = stoi(ngay_mo_so.substr(0, 2));
    int thang = stoi(ngay_mo_so.substr(3, 2));
    int nam = stoi(ngay_mo_so.substr(6, 4));

    if (nam < 0) return false;

    switch (thang)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return (ngay >= 1 && ngay <= 31);
        case 4: case 6: case 9: case 11:
            return (ngay >= 1 && ngay <= 30);
        case 2:
            if (nam_nhuan(nam)) {
                return (ngay >= 1 && ngay <= 29);  // Nam nhuan
            } else {
                return (ngay >= 1 && ngay <= 28);  // Nam thuong
            }
        default:
            return false;
    }
}

bool ma_so_hop_le(string ma_so)
{
    // kiem tra do dai hop le, khong chua ky tu dac biet va khoang trang
    if (ma_so.length() <= 5)
    {
        for (char c : ma_so)
        {
            if (!isalnum(c))
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool cmnd_hop_le(string cmnd)
{
    return (cmnd.length() == 9 || cmnd.length() == 12);
}

bool so_tien_gui_hop_le(float so_tien_gui)
{
    return (so_tien_gui > 0);
}

void input()
{
    cout << "Nhap so luong so: ";
    int n; cin >> n;

    for (int i = 0; i < n; i++)
    {
        struct SoTietKiem so;
        cout << "Nhap ma so: ";
        while (true) {
            cin >> so.ma_so;
            if (ma_so_hop_le(so.ma_so)) break;
            cout << "Ma so khong hop le. Vui long nhap lai:\n";
        }

        cout << "Nhap loai tiet kiem: ";
        cin.ignore();
        getline(cin, so.loai_tiet_kiem);

        cout << "Nhap ho ten khach hang: ";
        getline(cin, so.ho_ten_khach_hang);

        cout << "Nhap so CMND: ";
        while (true) {
            cin >> so.cmnd;
            if (cmnd_hop_le(so.cmnd)) break;
            cout << "So CMND khong hop le. Vui long nhap lai:\n";
        }

        cout << "Nhap ngay mo so: ";
        while (true) {
            cin >> so.ngay_mo_so;
            if (ngay_mo_so_hop_le(so.ngay_mo_so)) break;
            cout << "Ngay mo so khong hop le. Vui long nhap lai:\n";
        }

        cout << "Nhap so tien gui ban dau: ";
        while (true) {
            cin >> so.so_tien_gui;
            if (so_tien_gui_hop_le(so.so_tien_gui)) break;
            cout << "So tien gui ban dau khong hop le. Vui long nhap lai:\n";
        }
        so_tiet_kiem.push_back(so);
    }
}

void output(struct SoTietKiem so)
{
    // output
    cout << endl;
    printf("Ma so: %s\n", so.ma_so.c_str());
    printf("Loai tiet kiem: %s\n", so.loai_tiet_kiem.c_str());
    printf("Ho ten khach hang: %s\n", so.ho_ten_khach_hang.c_str());
    printf("So CMND: %s\n", so.cmnd.c_str());
    printf("Ngay mo so: %s\n", so.ngay_mo_so.c_str());
    printf("So tien gui ban dau: %.2f dong\n", so.so_tien_gui);
    cout << endl;
}

int khoang_cach_giua_2_ngay(string date_1, string date_2)
{
    int ngay_1 = stoi(date_1.substr(0, 2));
    int thang_1 = stoi(date_1.substr(3, 2));
    int nam_1 = stoi(date_1.substr(6, 4));

    int ngay_2 = stoi(date_2.substr(0, 2));
    int thang_2 = stoi(date_2.substr(3, 2));
    int nam_2 = stoi(date_2.substr(6, 4));

    // Tinh so ngay giua ngay 1 va ngay 01/01/0000
    int so_ngay_1 = 0;
    int ngay_goc = 1;
    int thang_goc = 1;
    int nam_goc = 0;
    while (nam_goc + 1 < nam_1)
    {
        so_ngay_1 += nam_nhuan(nam_goc) ? 366 : 365;
        nam_goc++;
    }
    while (thang_goc < thang_1)
    {
        so_ngay_1 += ENCODED_DATE[nam_nhuan(nam_1)][thang_goc];
        thang_goc++;
    }
    so_ngay_1 += ngay_1;

    // Tinh so ngay giua ngay 2 va ngay 01/01/0000
    int so_ngay_2 = 0;
    ngay_goc = 1;
    thang_goc = 1;
    nam_goc = 0;
    while (nam_goc + 1 <= nam_2)
    {
        so_ngay_2 += nam_nhuan(nam_goc) ? 366 : 365;
        nam_goc++;
    }
    while (thang_goc <= thang_2)
    {
        so_ngay_2 += ENCODED_DATE[nam_nhuan(nam_2)][thang_goc];
        thang_goc++;
    }
    so_ngay_2 += ngay_2;

    // Tinh so ngay giua 2 ngay
    return so_ngay_2 - so_ngay_1;
}

void tinh_lai(string ma_so)
{
    string ngay_hien_tai = "09/10/2024";
    float lai = 0;
    for (auto& so : so_tiet_kiem)
    {
        if (so.ma_so == ma_so)
        {
            int so_ngay = khoang_cach_giua_2_ngay(so.ngay_mo_so, ngay_hien_tai);
            if (so_ngay >= 365)
                lai = so.so_tien_gui * lai_suat_1_nam * so_ngay / 365;
            else if (so_ngay >= 180)
                lai = so.so_tien_gui * lai_suat_6_thang * so_ngay / 180;
        }
    }
    cout << "So tien lai: " << lai << " dong" << endl;
}

void tim_kiem(string str)
{
    if (str.length() <= 5)
    {
        for (auto so:so_tiet_kiem)
        {
            if (so.ma_so == str)
            {
                output(so);
            }
        }
    }
    else if (str.length() == 9 || str.length() == 12)
    {
        for (auto so:so_tiet_kiem)
        {
            if (so.cmnd == str)
            {
                output(so);
            }
        }
    }
    else cout << "Khong tim thay so tiet kiem" << endl;
}

bool ngay_nho_hon(string ngay_a, string ngay_b)
{
    int ngay = stoi(ngay_a.substr(0, 2));
    int thang = stoi(ngay_a.substr(3, 2));
    int nam = stoi(ngay_a.substr(6, 4));

    int temp = stoi(ngay_b.substr(6, 4));
    if (nam != stoi(ngay_b.substr(6, 4))) return nam < stoi(ngay_b.substr(6, 4));
    if (thang != stoi(ngay_b.substr(3, 2))) return thang < stoi(ngay_b.substr(3, 2));
    if (ngay != stoi(ngay_b.substr(0, 2))) return ngay < stoi(ngay_b.substr(0, 2));
    return true;
}

void liet_ke(string ngay_bat_dau, string ngay_ket_thuc)
{
    for (auto so:so_tiet_kiem)
    {
        if (ngay_nho_hon(so.ngay_mo_so, ngay_ket_thuc) && ngay_nho_hon(ngay_bat_dau, so.ngay_mo_so))
        {
            output(so);
        }
    }
}

void sort_tien_giam_dan()
{
    /*
     * Sap xep so tiet kiem theo so tien gui giam dan
     */
    sort(so_tiet_kiem.begin(), so_tiet_kiem.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
        return a.so_tien_gui > b.so_tien_gui;
    });
}

void sort_ngay_mo_tang_dan()
{
    /*
     * Sap xep so tiet kiem theo ngay mo so tang dan
     */
    sort(so_tiet_kiem.begin(), so_tiet_kiem.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
        return ngay_nho_hon(a.ngay_mo_so, b.ngay_mo_so);
    });
}

int main()
{
    input();
    for (const auto& so : so_tiet_kiem)
    {
        output(so);
    }
    string str;
    cout << "Nhap ma so/cmnd cua so can tim: ";
    cin >> str;
    tim_kiem(str);
    string ngay_bat_dau, ngay_ket_thuc;
    cout << "Nhap ngay bat dau va ngay ket thuc: ";
    cin >> ngay_bat_dau >> ngay_ket_thuc;
    cout << "Danh sach so tiet kiem trong khoang thoi gian tren: " << endl;
    liet_ke(ngay_bat_dau, ngay_ket_thuc);
    cout << "Sap xep so tiet kiem theo so tien gui giam dan: " << endl;
    sort_tien_giam_dan();
    for (const auto& so : so_tiet_kiem)
    {
        output(so);
    }
    cout << "Sap xep so tiet kiem theo ngay mo so tang dan: " << endl;
    sort_ngay_mo_tang_dan();
    for (const auto& so : so_tiet_kiem)
    {
        output(so);
    }
    return 0;
}