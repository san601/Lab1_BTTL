#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

using namespace std;

int ENCODED_DATE[2][14] = {
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}
};

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

void decode(int ngay, int nam)
{
    /*
     * Ham chuyen doi ngay encoded sang ngay thang nam
     *
     * Args:
     *      ngay (int): ngay encoded
     *      nam (int): nam cua ngay
     */

    int n = 1;
    while (ngay - ENCODED_DATE[nam_nhuan(nam)][n] > 0)
    {
        n++;
    }
    printf("%d/%d/%d", ngay - ENCODED_DATE[nam_nhuan(nam)][n - 1], n - 1, nam);
}

bool hop_le(string ngay_thang_nam)
{
    /*
     * Ham kiem tra ngay thang nam co hop le hay khong
     *
     * Args:
     *      ngay_thang_nam (string): ngay thang nam can kiem tra
     *
     * Returns:
     *      bool: true neu hop le, false neu khong hop le
     */

    // Kiem tra dung dinh dang dd/mm/yyyy
    if (ngay_thang_nam.length() != 10) return false;
    if (ngay_thang_nam[2] != '/' || ngay_thang_nam[5] != '/') return false;
    if (!isdigit(ngay_thang_nam[0]) || !isdigit(ngay_thang_nam[1]) || !isdigit(ngay_thang_nam[3]) || !isdigit(ngay_thang_nam[4]) || !isdigit(ngay_thang_nam[6]) || !isdigit(ngay_thang_nam[7]) || !isdigit(ngay_thang_nam[8]) || !isdigit(ngay_thang_nam[9])) return false;

    // Lay ngay, thang, nam tu ngay bay
    int ngay = stoi(ngay_thang_nam.substr(0, 2));
    int thang = stoi(ngay_thang_nam.substr(3, 2));
    int nam = stoi(ngay_thang_nam.substr(6, 4));

    // Kiem tra nam hop le
    if (nam < 0) return false;

    // Kiem tra ngay thang hop le
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

int main() {
    string ngay_thang_nam;
    cout << "Nhap ngay thang nam (dd/mm/yyyy): ";
    while (true)
    {
        cin >> ngay_thang_nam;
        if (hop_le(ngay_thang_nam)) break;
        cout << "Ngay thang nam khong hop le. Vui long nhap lai:\n";
    }

    int ngay = stoi(ngay_thang_nam.substr(0, 2));
    int thang = stoi(ngay_thang_nam.substr(3, 2));
    int nam = stoi(ngay_thang_nam.substr(6, 4));

    int encoded_date = ENCODED_DATE[nam_nhuan(nam)][thang] + ngay;
    int yesterday = encoded_date - 1, year_of_yesterday = nam;
    int tomorrow = encoded_date + 1, year_of_tomorrow = nam;
    if (yesterday <= 0)
    {
        year_of_yesterday--;
        yesterday = ENCODED_DATE[nam_nhuan(year_of_yesterday)][13];
    }
    if (tomorrow > ENCODED_DATE[nam_nhuan(nam)][13])
    {
        year_of_tomorrow++;
        tomorrow = 1;
    }
    printf("Day la ngay thu %d trong nam", encoded_date);
    cout << "\nNgay truoc do la ";
    decode(yesterday, year_of_yesterday);
    cout << "\nNgay ke tiep la ";
    decode(tomorrow, year_of_tomorrow);

    return 0;
}
