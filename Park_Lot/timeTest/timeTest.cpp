#include <iostream>
#include <ctime>
#include <locale>

using namespace std;

int main() {
    // Türkçe dil ayarlarý için bir locale oluþtur
    locale::global(locale("tr_TR.utf8"));

    // Þu anki zamaný al
    time_t now;
    struct tm current_time;

    if (time(&now) == -1 || localtime_s(&current_time, &now) != 0) {
        cerr << "Zaman alýnamadý veya iþlenemedi." << endl;
        return 1;
    }

    // Türkçe tarih formatýný ayarla
    char tarih_formati[] = "%A, %d %B %Y";
    char saat_formati[] = "%H:%M:%S";

    char tarih_str[80];
    char saat_str[80];

    // Tarih ve saat bilgilerini formatla
    strftime(tarih_str, sizeof(tarih_str), tarih_formati, &current_time);
    strftime(saat_str, sizeof(saat_str), saat_formati, &current_time);

    // Türkçe tarihi ve saati görüntüle
    cout << "Tarih: " << tarih_str << endl;
    cout << "Saat: " << saat_str << endl;

    return 0;
}
