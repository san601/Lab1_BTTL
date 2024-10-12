#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

//float lai_suat_dai_han = 0.046;
//float lai_suat_ngan_han = 0.03;
float lai_suat_khong_ky_han = 0.005;

int ENCODED_DATE[2][14] = {
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

struct SoTietKiem
{
    /*
     * Struct luu tru thong tin cua so tiet kiem
     *
     * Attributes:
     *      ma_so (string): ma so cua so tiet kiem
     *      ky_han (int): so thang cua 1 ky han
     *      loai_tiet_kiem (string): loai tiet kiem
     *      ho_ten_khach_hang (string): ho ten khach hang
     *      cmnd (string): so CMND cua khach hang
     *      ngay_mo_so (string): ngay mo so
     */

    string ma_so;               // max 5 ky tu
    int ky_han;                 // so thang
    string loai_tiet_kiem;
    string ho_ten_khach_hang;   // max 30 ky tu
    string cmnd;                // 9 hoac 12 ky tu
    string ngay_mo_so;          // dd/mm/yyyy
    float so_tien_gui;          // so tien gui ban dau > 0
};

vector <struct SoTietKiem> so_tiet_kiem;

bool nam_nhuan(int nam)
{
    /*
     * Ham kiem tra nam co phai la nam nhuan hay khong
     *
     * Args:
     *      nam (int): nam can kiem tra
     *
     * Returns:
     *      bool: true neu la nam nhuan, false neu khong phai
     */

    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

bool ngay_mo_so_hop_le(string ngay_mo_so)
{
    /*
     * Ham kiem tra ngay mo so co hop le hay khong
     *
     * Args:
     *      ngay_mo_so (string): ngay mo so can kiem tra
     *
     * Returns:
     *      bool: true neu hop le, false neu khong hop le
     */

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
    /*
     * Kiem tra do dai hop le, khong chua ky tu dac biet va khoang trang
     *
     * Args:
     *      ma_so (string): ma so can kiem tra
     */

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
    /*
     * Kiem tra so CMND hop le
     *
     * Args:
     *      cmnd (string): so CMND can kiem tra
     */

    return (cmnd.length() == 9 || cmnd.length() == 12);
}

bool so_tien_gui_hop_le(float so_tien_gui)
{
    /*
     * Kiem tra so tien gui hop le
     *
     * Args:
     *      so_tien_gui (float): so tien gui ban dau
     */

    return (so_tien_gui > 0);
}

void input()
{
    /*
     * Nhap thong tin so tiet kiem
     */

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

        cin.ignore();
        cout << "Nhap loai tiet kiem: ";
        getline(cin, so.loai_tiet_kiem);
        if (so.loai_tiet_kiem == "Dai han") so.ky_han = 12;
        else if (so.loai_tiet_kiem == "Ngan han") so.ky_han = 3;
        else so.ky_han = 0;

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
    /*
     * In thong tin cua so tiet kiem
     */

    cout << endl;
    printf("Ma so: %s\n", so.ma_so.c_str());
    printf("Ky han: %d thang\n", so.ky_han);
    printf("Ho ten khach hang: %s\n", so.ho_ten_khach_hang.c_str());
    printf("So CMND: %s\n", so.cmnd.c_str());
    printf("Ngay mo so: %s\n", so.ngay_mo_so.c_str());
    printf("So tien gui ban dau: %.2f dong\n", so.so_tien_gui);
    cout << endl;
}

int khoang_cach_giua_2_ngay(string date_1, string date_2)
{
    /*
     * Tinh so ngay giua 2 ngay
     *
     * Args:
     *      date_1 (string): ngay 1
     *      date_2 (string): ngay 2
     */

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

float tinh_lai(string ma_so, float lai_suat_dai_han, float lai_suat_ngan_han)
{
    /*
     * Tinh lai suat dua tren ngay mo so va ngay hien tai
     *
     * Args:
     *      ma_so (string): ma so cua so tiet kiem can tinh
     */

    string ngay_hien_tai = "09/10/2024";
    float lai = 0;
    for (auto& so : so_tiet_kiem)
    {
        if (so.ma_so == ma_so)
        {
            int so_ngay = khoang_cach_giua_2_ngay(so.ngay_mo_so, ngay_hien_tai);
            // Tinh theo cong thuc lai binh thuong + lai khong ky han
            if (so_ngay < so.ky_han * 30 || so.ky_han == 0) // Lai khong ky han
                lai = so.so_tien_gui * lai_suat_khong_ky_han * so_ngay / 365;
            else
            {
                if (so.ky_han < 6) // Ngan han
                {
                    lai = so.so_tien_gui * lai_suat_ngan_han * so.ky_han * 30 / 365 * floor(so_ngay / (so.ky_han * 30));
                    lai += so.so_tien_gui * lai_suat_khong_ky_han * (so_ngay % (so.ky_han * 30)) / 365;
                } else // Dai han
                {
                    lai = so.so_tien_gui * lai_suat_dai_han * so.ky_han * 30 / 365 * floor(so_ngay / (so.ky_han * 30));
                    lai += so.so_tien_gui * lai_suat_khong_ky_han * (so_ngay % (so.ky_han * 30)) / 365;
                }
            }
        }
    }
    return lai;
}

void cap_nhat_lai_suat(string ma_so)
{
    /*
     * Cap nhat lai suat cho so tiet kiem
     *
     * Args:
     *      ma_so (string): ma so cua so tiet kiem can cap nhat
     */

    float lai_suat_dai_han, lai_suat_ngan_han;
    cout << "Nhap lai suat dai han (%/nam): ";
    cin >> lai_suat_dai_han;
    lai_suat_dai_han /= 100;
    cout << "Nhap lai suat ngan han (%/nam): ";
    cin >> lai_suat_ngan_han;
    lai_suat_ngan_han /= 100;

    for (auto& so : so_tiet_kiem)
    {
        if (so.ma_so == ma_so)
        {
            cout << "Tien lai cua ban la : " << tinh_lai(ma_so, lai_suat_dai_han, lai_suat_ngan_han) << endl;
        }
    }
}


void tim_kiem(string str)
{
    /*
     * Tim kiem so tiet kiem theo ma so hoac CMND
     *
     * Args:
     *      str (string): ma so hoac CMND can tim
     */

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
    /*
     * So sanh 2 ngay
     *
     * Args:
     *      ngay_a (string): ngay a
     *      ngay_b (string): ngay b
     *
     * Return:
     *      bool: true neu ngay a nho hon ngay b, false neu nguoc lai
     */
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
    /*
     * Liet ke danh sach so tiet kiem trong khoang thoi gian tu ngay_bat_dau den ngay_ket_thuc
     *
     * Args:
     *      ngay_bat_dau (string): ngay bat dau
     *      ngay_ket_thuc (string): ngay ket thuc
     */
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

void rut_tien()
{
    /*
     * Rut tien tu so tiet kiem
     */

    string ma_so;
    cout << "Nhap ma so can rut tien: ";
    cin >> ma_so;
    string cmnd;
    cout << "Nhap so CMND cua so: ";
    cin >> cmnd;

    for (auto& so:so_tiet_kiem)
    {
        if (so.ma_so == ma_so && so.cmnd == cmnd)
        {
            // Kiem tra rut dung ky han
            if (so.ky_han != 0)
            {
                if (khoang_cach_giua_2_ngay(so.ngay_mo_so, "09/10/2024") < so.ky_han * 30)
                {
                    cout << "Lai suat thap hon neu ban rut truoc ky han" << endl;
                    cout << "So du trong tai khoan la: " << so.so_tien_gui + tinh_lai(ma_so, 0.046, 0.03) << " dong" << endl;
                }
            }
            float so_tien_rut;
            cout << "Nhap so tien can rut: ";
            cin >> so_tien_rut;
            if (so_tien_rut <= so.so_tien_gui + tinh_lai(ma_so, 0.046, 0.03))
            {
                so.so_tien_gui = so.so_tien_gui + tinh_lai(ma_so, 0.046, 0.03) - so_tien_rut;
                cout << "Rut tien thanh cong" << endl;
            }
            else cout << "So tien khong du" << endl;
        }
    }
}

int main()
{
    input();
    string str;
    while (true)
    {
        // Tao menu cho nguoi dung chon chuc nang
        cout << "1. Xuat du lieu so tiet kiem\n";
        cout << "2. Chuc nang nang cao\n";
        cout << "3. Tim kiem va liet ke\n";
        cout << "4. Sap xep danh sach so tiet kiem\n";
        cout << "5. Thoat chuong trinh\n";
        cout << "Chon chuc nang: ";
        int chuc_nang;
        cin >> chuc_nang;
        switch (chuc_nang) {
            case 1:
            {
                for (const auto &so: so_tiet_kiem)
                {
                    output(so);
                }
                break;
            }
            case 2:
            {
                int opt;
                cout << "1. Cap nhat lai suat\n";
                cout << "2. Tinh toan tien lai\n";
                cout << "3. Rut tien\n";
                cin >> opt;
                switch (opt)
                {
                    case 1:
                    {
                        cout << "Nhap ma so can cap nhat lai suat: ";
                        cin >> str;
                        cap_nhat_lai_suat(str);
                        break;
                    }
                    case 2:
                    {
                        cout << "Nhap ma so can tinh lai: ";
                        cin >> str;
                        cout << "Tien lai cua ban la : " << tinh_lai(str, 0.046, 0.03) << endl;
                        break;
                    }
                    case 3:
                    {
                        rut_tien();
                        break;
                    }
                }
                break;
            }
            case 3:
            {
                string ngay_bat_dau, ngay_ket_thuc;
                cout << "Nhap ma so hoac CMND can tim: ";
                cin >> str;
                tim_kiem(str);
                cout << "Nhap ngay bat dau va ngay ket thuc: ";
                cin >> ngay_bat_dau >> ngay_ket_thuc;
                liet_ke(ngay_bat_dau, ngay_ket_thuc);
                break;
            }
            case 4:
            {
                cout << "1. Sap xep so tiet kiem theo so tien gui giam dan\n";
                cout << "2. Sap xep so tiet kiem theo ngay mo so tang dan\n";
                cout << "3. Tro ve menu chinh\n";
                cout << "Chon cach sap xep: ";

                int cach_sap_xep;
                cin >> cach_sap_xep;
                switch (cach_sap_xep) {
                    case 1:
                    {
                        sort_tien_giam_dan();
                        for (const auto &so: so_tiet_kiem) {
                            output(so);
                        }
                    }
                        break;
                    case 2:
                    {
                        sort_ngay_mo_tang_dan();
                        for (const auto &so: so_tiet_kiem) {
                            output(so);
                        }
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            default:
                return 0;
        }
    }
}