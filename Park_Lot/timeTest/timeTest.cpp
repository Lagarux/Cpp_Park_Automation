#include <iostream>
#include <ctime>
#include <locale>

using namespace std;

int main() {
    // T�rk�e dil ayarlar� i�in bir locale olu�tur
    locale::global(locale("tr_TR.utf8"));

    // �u anki zaman� al
    time_t now;
    struct tm current_time;

    if (time(&now) == -1 || localtime_s(&current_time, &now) != 0) {
        cerr << "Zaman al�namad� veya i�lenemedi." << endl;
        return 1;
    }

    // T�rk�e tarih format�n� ayarla
    char tarih_formati[] = "%A, %d %B %Y";
    char saat_formati[] = "%H:%M:%S";

    char tarih_str[80];
    char saat_str[80];

    // Tarih ve saat bilgilerini formatla
    strftime(tarih_str, sizeof(tarih_str), tarih_formati, &current_time);
    strftime(saat_str, sizeof(saat_str), saat_formati, &current_time);

    // T�rk�e tarihi ve saati g�r�nt�le
    cout << "Tarih: " << tarih_str << endl;
    cout << "Saat: " << saat_str << endl;

    return 0;
}
