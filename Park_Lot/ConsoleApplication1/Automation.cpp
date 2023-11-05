// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <locale.h>
#include <vector>
#include <ctime>
#include <locale>
#include <string>
#include <limits>
using namespace std;

// Ýki boyutlu bir string matris döndüren bir fonksiyon
vector<vector<string>> createStringMatrix(int numRows, int numCols) {
    vector<vector<string>> matrix(numRows, vector<string>(numCols));

    // Matris standart olarak boþ olacak þekilde "E" olarak doldurulur
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = "E";
        }
    }

    return matrix;
}
// Matris yeni bir vector<vector<string>> deðerine aktarýlýr
vector<vector<string>> Park = createStringMatrix(5, 10);

// fonksiyonlarýmýzýn prototipleri. Bir nevi C#'taki partial classlar gibi
int checkState(int count);
void options();
void fullParkList();
void exitCar();
void insertCar();

//Tarih bilgisini string olarak döndüren fonksiyonumuz.
string* dateInfo() {
    string* dateAndTime = new string[2];
    // Türkçe dil ayarlarý için bir locale oluþturduk
    locale::global(locale("tr_TR.utf8"));
    setlocale(LC_ALL, "Turkish");
    // Þu anki zamaný aldýk
    time_t now;
    struct tm current_time;
    // Anlýk zamaný alma durumunu kontrol ediyoruz
    if (time(&now) == -1 || localtime_s(&current_time, &now) != 0) {
        cerr << "Zaman alýnamadý veya iþlenemedi." << endl;
    }

    // Türkçe tarih formatýný ayarladýk
    char tarih_formati[] = "%A, %d %B %Y";
    char saat_formati[] = "%H:%M:%S";

    char tarih_str[80];
    char saat_str[80];

    // Tarih ve saat bilgilerini formatladýk
    strftime(tarih_str, sizeof(tarih_str), tarih_formati, &current_time);
    strftime(saat_str, sizeof(saat_str), saat_formati, &current_time);

    dateAndTime[0] = tarih_str;
    dateAndTime[1] = saat_str;

    return dateAndTime;

}

//Kullanýcý giriþ bilgilerini almamýzla beraber giriþ bilgilerini pointer string olarak return ediyoruz.
string* LoginSequence(){
    string* loginInfos = new string[2];
    cout << "\t \t \t \t Kullanýcý Adýnýz => ";
    cin >> loginInfos[0];
    cout << "\t \t \t \t Þifreniz => ";
    cin >> loginInfos[1];
    return loginInfos;
}

//Kapatma sekansýný geciktiren hazýr bir method oluþturduk.
void closeSequence(int multiple=1) {
    for (int i = 0; i < multiple; i++) {
    Sleep(1000);
    cout << ".";
    }

}

int main()
{
    //Türkçe yazdýrýr ve UTF-8 desteði saðlar
    setlocale(LC_ALL, "Turkish");
    //Programýn çýktý olan her kýsmýna "/t" yani tabsler ekledim ki mümkün mertebe ortada hizalý olsun 
    cout << "\t \t \t \t  <<<<< Hoþ Geldiniz >>>>>\n\n";
    Sleep(1000);
    checkState(1);
}

//Giriþ durumunu kontrol eder ve buna göre programý giriþ kýsmýndan baþa sarar
int checkState(int count = 1) {
    int loginCount = count;
    string* loginInfo = LoginSequence();
    if (loginCount < 3) {
        if (loginInfo[0] != "Admin" || loginInfo[1] != "Admin") {
            loginCount++;
            cout << "\t \t \t \t  Hatalý giriþ yaptýnýz!!! lütfen tekrar deneyiniz \n\n";
            return checkState(loginCount);
        }
        else {
            cout << "\n\t \t \t \t  Hoþ geldin " << loginInfo[0] << "\n\n";
            options();
        }
    }
    else if (loginCount >= 3)
    {
        cout << "\t \t \t \t Çok fazla hatalý giriþ yaptýnýz!!! Giriþ sistemi yeniden baþlatýlýyor";
        closeSequence(3);
        cout << "\n\n";
        return main();
    }

}

//Kullanýcý baþarýlý bir þekilde girdikten sonra karþýsýna seçeneklerin çýktýðý ana menü
void options() {
    int optNumb;
    cout << "\n\n \t \t \t \t Aþaðýdaki seçenekleri seçmek için lütfen ilgili numarayý giriniz \n\n";
    cout << "\t \t \t \t 1.) Park Halindeki Araçlarýn Listesi \n";
    cout << "\t \t \t \t 2.) Park Halindeki Araç Çýkýþý \n";
    cout << "\t \t \t \t 3.) Yeni Araç Giriþi \n";
    cout << "\t \t \t \t 4.) Çýkýþ \n";
    cout << "\t \t \t \t Seçeneðiniz => ";
    cin >> optNumb;
    //Seçtiði seçenekler için oluþturduðumuz durumlar.Recursive çaðrý kullandýk
    switch (optNumb) {
    case 1:fullParkList(); break;
    case 2:exitCar(); break;
    case 3:insertCar(); break;
    case 4:return; break;
    default:cout << "\n\n\t \t \t \t !!! Lütfen geçerli bir numara giriniz !!! \n\n";
        options();
        break;
    }
}
//Özelleþtirilmiþ görünümü ile otopark yuvalarý.
void fullParkList() {
    cout << "\t \t \t \t Geri dönmek için lütfen 1 yazýp 'Enter' tuþuna basýnýz: \n\n";
    for (int i = 0; i < 5; i++) {
        cout << "\t \t \t \t"<< (i+1) <<". Kattaki park yuvalarý \n";
        cout << "\t \t \t \t";
        for (int j = 0; j < 10; j++) {
            cout <<" | " << Park[i][j] << " | ";
        }
        cout << "\n\n";
    }

    int optNumb;
    cout << "\t \t \t \t => ";
    cin >> optNumb;
    switch (optNumb) {
    case 1:cout << "\t \t \t \t Ana Menü'ye dönülüyor "; closeSequence(3); options(); break;
    default:cout << "\n\n\t \t \t \t !!! Lütfen geçerli bir numara giriniz !!! \n\n";
        fullParkList();
        break;
    }
}

//Araç çýkarma iþlemimiz burada gerçekleþiyor
void exitCar() {
    int floorNumb;
    cout << "\n\n\t \t \t \t Lütfen bir kat seçiniz (1-5) ya da geri dönmek için 0 yazýp 'Enter' tuþuna basýnýz => ";
    cin >> floorNumb;
    if (floorNumb > 5 || floorNumb < 1) {
        if (floorNumb == 0) {
            cout << "\n\n\t \t \t \t Ana Menü'ye geri dönülüyor";
            closeSequence(3);
            options();
        }
        else {
			cout << "\n\n\t \t \t \t !!! Geçersiz kat numarasý !!!";
			exitCar();
        }

    }
    else {
        cout << "\t \t \t \t" << floorNumb << ". Kattaki park yuvalarý \n\n";
        cout << "\t \t \t \t";
        for (int j = 0; j < 10; j++) {
            cout << " | " << Park[floorNumb-1][j] << " | ";
        }
        cout << "\n\t \t \t \t Lütfen bir park yeri numarasý seçiniz (1-10)=> ";
        int parkSlotNum;
        cin >> parkSlotNum;
        if (parkSlotNum > 10 || parkSlotNum < 1) {
            cout << "\n\n\t \t \t \t !!! Geçersiz park yeri numarasý !!!";
            exitCar();
        }
        else {
            if (Park[floorNumb - 1][parkSlotNum - 1] == "E") {
                cout << "\n\n\t \t \t \t !!! Bu katta bulunan araç yuvasý zaten boþ. Ana Menü'ye geri dönülüyor !!!";
                closeSequence(3);
                options();
            }
            else {
                cout << "\n\n\t \t \t \t " << Park[floorNumb - 1][parkSlotNum - 1] << "Bu araç otoparktan baþarýlý bir þekilde çýkartýldý.\nAna Menü'ye geri dönülüyor";
                Park[floorNumb - 1][parkSlotNum - 1] = "E";
                closeSequence(3);
                options();
            }
        }
    }

}

void insertCar() {
    int floorNumb;
    cout << "\n\n\t \t \t \t Lütfen bir kat seçiniz (1-5) ya da geri dönmek için 0 yazýp 'Enter' tuþuna basýnýz => ";
    cin >> floorNumb;
    if (floorNumb > 5 || floorNumb < 1) {
        if (floorNumb == 0) {
            cout << "\n\n\t \t \t \t Ana Menü'ye geri dönülüyor";
            closeSequence(3);
            options();
        }
        else {
            cout << "\n\n\t \t \t \t !!! Geçersiz kat numarasý !!!";
            insertCar();
        }

    }
    else {
        int emptyCount=0;
        vector<int> parkSlotNumbs;
        for (int j = 0; j < 10; j++) {
            if (Park[floorNumb - 1][j] == "E") {
                emptyCount++;
                parkSlotNumbs.push_back((j + 1));
            }
        }

        if (emptyCount == 0) {
            cout << "\n\n\t \t \t \t Bu kattaki tüm park yuvalarý dolu !!! Baþlangýca yönlendiriliyorsunuz";
            closeSequence(2);
            insertCar();
        }
        else 
        {
            cout << "\n\t \t \t \t Boþ park yuva numaralarý => ";
            for (int i=0; i<parkSlotNumbs.size();i++)
            {
                cout << " | " << parkSlotNumbs[i] << " | ";
            }
            cout << "\n\t \t \t \t Lütfen bir park yeri numarasý seçiniz (1-10) => ";
            int parkSlotNum;
            cin >> parkSlotNum;
            if (parkSlotNum > 10 || parkSlotNum < 1) {
                cout << "\n\n\t \t \t \t !!! Geçersiz park yeri numarasý !!!";
                insertCar();
            }
            else if (Park[floorNumb - 1][parkSlotNum - 1] != "E") {
                cout << "\n\n\t \t \t \t Seçili park yuvasý dolu !!! Baþlangýca yönlendiriliyorsunuz";
                closeSequence(2);
                insertCar();
            }
            else {
                cout << "\n\n\t \t \t \t";
                cout << "Araç plakasýný giriniz => ";
                string carLicensePlate;
                cin.ignore(1);
                getline(cin, carLicensePlate);
                if (carLicensePlate.empty()) {
                    getline(cin, carLicensePlate);
                }
                else {
                    cout << "Girilen metin: " << carLicensePlate << endl;
                }

                string* dateAndTime = dateInfo();
                Park[floorNumb - 1][parkSlotNum - 1] = to_string(floorNumb) + ". Kat Park No." + to_string(parkSlotNum) + " - " + (carLicensePlate) +" - " + dateAndTime[0] + " - " + dateAndTime[1];
                cout << "\n\n\t \t \t \t Park yerine araç ekleme iþlemi tamamlandý. Ana Menü'ye dönüyorsunuz";
                string text = Park[floorNumb - 1][parkSlotNum - 1];
                closeSequence(3);
                options();

            }

        }
    }
}




