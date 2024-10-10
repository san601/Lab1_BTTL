#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct ChuyenBay
{
    string ma_chuyen_bay;   // Toi da 5 ky tu, khong co khoang trang hay ky tu dac biet
    string ngay_bay;        // Dinh dang dd/mm/yyyy, kiem tra hop le
    string gio_bay;         // Dinh dang 24h (00:00 - 23:59), kiem tra hop le
    string noi_di;          // Toi da 20 ky tu, khong co so hoac ky tu dac biet
    string noi_den;         // Tuong tu noi_di
};

vector <struct ChuyenBay> chuyen_bay;

bool ma_chuyen_bay_hop_le(string ma_chuyen_bay)
{
    if (ma_chuyen_bay.length() > 5) return false;
    for (char c : ma_chuyen_bay)
    {
        if (!isalnum(c)) return false;
    }
    return true;
}

bool gio_bay_hop_le(string gio_bay)
{
    if (gio_bay.length() != 5) return false;
    if (gio_bay[2] != ':') return false;
    if (!isdigit(gio_bay[0]) || !isdigit(gio_bay[1]) || !isdigit(gio_bay[3]) || !isdigit(gio_bay[4])) return false;
    if (stoi(gio_bay.substr(0, 2)) < 0 || stoi(gio_bay.substr(0, 2)) > 23) return false;
    if (stoi(gio_bay.substr(3, 2)) < 0 || stoi(gio_bay.substr(3, 2)) > 59) return false;
    return true;
}

bool nam_nhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

bool ngay_bay_hop_le(string ngay_bay)
{
    if (ngay_bay.length() != 10) return false;
    if (ngay_bay[2] != '/' || ngay_bay[5] != '/') return false;
    if (!isdigit(ngay_bay[0]) || !isdigit(ngay_bay[1]) || !isdigit(ngay_bay[3]) || !isdigit(ngay_bay[4]) || !isdigit(ngay_bay[6]) || !isdigit(ngay_bay[7]) || !isdigit(ngay_bay[8]) || !isdigit(ngay_bay[9])) return false;
    int ngay = stoi(ngay_bay.substr(0, 2));
    int thang = stoi(ngay_bay.substr(3, 2));
    int nam = stoi(ngay_bay.substr(6, 4));

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

bool dia_diem_hop_le(string dia_diem)
{
    if (dia_diem.length() > 20) return false;
    for (char c : dia_diem)
    {
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;
}

void input(int n)
{
    // Nhap thong tin chuyen bay
    for (int i = 0; i < n; i++)
    {
        struct ChuyenBay tmp;
        cout << "Nhap ma chuyen bay: ";
        while (true)
        {
            cin >> tmp.ma_chuyen_bay;
            if (ma_chuyen_bay_hop_le(tmp.ma_chuyen_bay)) break;
            cout << "Ma chuyen bay khong hop le. Vui long nhap lai:\n";
        }
        cout << "Nhap ngay bay (dd/mm/yyyy): ";
        while (true)
        {
            cin >> tmp.ngay_bay;
            if (ngay_bay_hop_le(tmp.ngay_bay)) break;
            cout << "Ngay bay khong hop le. Vui long nhap lai:\n";
        }

        cout << "Nhap gio bay (hh:mm): ";
        while (true)
        {
            cin >> tmp.gio_bay;
            if (gio_bay_hop_le(tmp.gio_bay)) break;
            cout << "Gio bay khong hop le. Vui long nhap lai:\n";
        }

        cin.ignore();
        cout << "Nhap noi di: ";
        while (true)
        {
            getline(cin, tmp.noi_di);
            if (dia_diem_hop_le(tmp.noi_di)) break;
            cout << "Noi di khong hop le. Vui long nhap lai:\n";
        }
        cout << "Nhap noi den: ";
        while (true)
        {
            getline(cin, tmp.noi_den);
            if (dia_diem_hop_le(tmp.noi_den)) break;
            cout << "Noi den khong hop le. Vui long nhap lai:\n";
        }
        chuyen_bay.push_back(tmp);
    }
}

void tim_kiem_theo_ma(string ma_chuyen_bay)
{
    for (auto i : chuyen_bay)
    {
        if (i.ma_chuyen_bay == ma_chuyen_bay)
        {
            cout << "Ma chuyen bay: " << i.ma_chuyen_bay << endl;
            cout << "Ngay bay: " << i.ngay_bay << endl;
            cout << "Gio bay: " << i.gio_bay << endl;
            cout << "Noi di: " << i.noi_di << endl;
            cout << "Noi den: " << i.noi_den << endl;
        }
    }
}

void tim_kiem_theo_noi_di(string noi_di)
{
    for (auto i : chuyen_bay)
    {
        if (i.noi_di == noi_di)
        {
            cout << endl;
            cout << "Ma chuyen bay: " << i.ma_chuyen_bay << endl;
            cout << "Ngay bay: " << i.ngay_bay << endl;
            cout << "Gio bay: " << i.gio_bay << endl;
            cout << "Noi di: " << i.noi_di << endl;
            cout << "Noi den: " << i.noi_den << endl;
            cout << endl;
        }
    }
}

void tim_kiem_theo_noi_den(string noi_den)
{
    for (auto i : chuyen_bay)
    {
        if (i.noi_den == noi_den)
        {
            cout << endl;
            cout << "Ma chuyen bay: " << i.ma_chuyen_bay << endl;
            cout << "Ngay bay: " << i.ngay_bay << endl;
            cout << "Gio bay: " << i.gio_bay << endl;
            cout << "Noi di: " << i.noi_di << endl;
            cout << "Noi den: " << i.noi_den << endl;
            cout << endl;
        }
    }
}

bool ngay_nho_hon(string ngay_a, string ngay_b)
{
    int ngay = stoi(ngay_a.substr(0, 2));
    int thang = stoi(ngay_a.substr(3, 2));
    int nam = stoi(ngay_a.substr(6, 4));

    if (nam != stoi(ngay_b.substr(6, 4))) return nam < stoi(ngay_b.substr(6, 4));
    if (thang != stoi(ngay_b.substr(3, 2))) return thang < stoi(ngay_b.substr(3, 2));
    if (ngay != stoi(ngay_b.substr(0, 2))) return ngay < stoi(ngay_b.substr(0, 2));
    return true;
}

bool gio_nho_hon(string gio_a, string gio_b)
{
    int gio = stoi(gio_a.substr(0, 2));
    int phut = stoi(gio_a.substr(3, 2));

    if (gio != stoi(gio_b.substr(0, 2))) return gio < stoi(gio_b.substr(0, 2));
    if (phut != stoi(gio_b.substr(3, 2))) return phut < stoi(gio_b.substr(3, 2));
    return true;
}

void sap_xep_chuyen_bay_theo_ngay_va_gio()
{
    sort(chuyen_bay.begin(), chuyen_bay.end(), [](ChuyenBay a, ChuyenBay b) {
        if (a.ngay_bay != b.ngay_bay) return ngay_nho_hon(a.ngay_bay, b.ngay_bay);
        return gio_nho_hon(a.gio_bay, b.gio_bay);
    });
    for (auto i : chuyen_bay)
    {
        cout << endl;
        cout << "Ma chuyen bay: " << i.ma_chuyen_bay << endl;
        cout << "Ngay bay: " << i.ngay_bay << endl;
        cout << "Gio bay: " << i.gio_bay << endl;
        cout << "Noi di: " << i.noi_di << endl;
        cout << "Noi den: " << i.noi_den << endl;
        cout << endl;
    }
}

void danh_sach_chuyen_bay_cu_the(string noi_di, string ngay)
{
    for (auto i : chuyen_bay)
    {
        if (i.noi_di == noi_di && i.ngay_bay == ngay)
        {
            cout << endl;
            cout << "Ma chuyen bay: " << i.ma_chuyen_bay << endl;
            cout << "Ngay bay: " << i.ngay_bay << endl;
            cout << "Gio bay: " << i.gio_bay << endl;
            cout << "Noi di: " << i.noi_di << endl;
            cout << "Noi den: " << i.noi_den << endl;
            cout << endl;
        }
    }
}

void so_luong_chuyen_bay(string noi_di, string noi_den)
{
    int cnt = 0;
    for (auto i : chuyen_bay)
    {
        if (i.noi_di == noi_di && i.noi_den == noi_den) cnt++;
    }
    cout << "So luong chuyen bay tu " << noi_di << " den " << noi_den << " la: " << cnt << endl;
}

int main()
{
    int n;
    cout << "Nhap so luong chuyen bay: ";
    cin >> n;
    input(n);

    while (true)
    {
        // tao menu cho nguoi dung chon function can dung
        cout << "1. Tim kiem chuyen bay theo ma chuyen bay\n";
        cout << "2. Tim kiem chuyen bay theo noi di\n";
        cout << "3. Tim kiem chuyen bay theo noi den\n";
        cout << "4. Sap xep chuyen bay theo ngay va gio\n";
        cout << "5. Hien thi danh sach cac chuyen bay khoi hanh tu 1 noi trong 1 ngay\n";
        cout << "6. Dem so luong chuyen bay khoi hanh tu 1 noi den 1 noi nhat dinh\n";
        cout << "7. Thoat chuong trinh\n";
        cout << "Chon chuc nang: ";
        int chuc_nang;
        cin >> chuc_nang;
        switch (chuc_nang)
        {
            case 1:
            {
                string ma_chuyen_bay;
                cout << "Nhap ma chuyen bay can tim: ";
                cin >> ma_chuyen_bay;
                tim_kiem_theo_ma(ma_chuyen_bay);
                break;
            }
            case 2:
            {
                string noi_di;
                cout << "Nhap noi di can tim: ";
                cin.ignore();
                getline(cin, noi_di);
                tim_kiem_theo_noi_di(noi_di);
                break;
            }
            case 3:
            {
                string noi_den;
                cout << "Nhap noi den can tim: ";
                cin.ignore();
                getline(cin, noi_den);
                tim_kiem_theo_noi_den(noi_den);
                break;
            }
            case 4:
            {
                sap_xep_chuyen_bay_theo_ngay_va_gio();
                break;
            }
            case 5:
            {
                string noi_di, ngay;

                cout << "Nhap noi di: ";
                while (true)
                {
                    getline(cin, noi_di);
                    if (dia_diem_hop_le(noi_di)) break;
                    cout << "Noi di khong hop le. Vui long nhap lai:\n";
                }

                cout << "Nhap ngay bay (dd/mm/yyyy): ";
                while (true)
                {
                    cin >> ngay;
                    if (ngay_bay_hop_le(ngay)) break;
                    cout << "Ngay bay khong hop le. Vui long nhap lai:\n";
                }
                danh_sach_chuyen_bay_cu_the(noi_di, ngay);
                break;
            }
            case 6:
            {
                string noi_di, noi_den;
                cout << "Nhap noi di: ";
                while (true)
                {
                    getline(cin, noi_di);
                    if (dia_diem_hop_le(noi_di)) break;
                    cout << "Noi di khong hop le. Vui long nhap lai:\n";
                }
                cout << "Nhap noi den: ";
                while (true)
                {
                    getline(cin, noi_den);
                    if (dia_diem_hop_le(noi_den)) break;
                    cout << "Noi den khong hop le. Vui long nhap lai:\n";
                }
                so_luong_chuyen_bay(noi_di, noi_den);
                break;
            }
            default:
            {
                return 0;
            }
        }
    }
}