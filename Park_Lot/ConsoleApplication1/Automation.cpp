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

// �ki boyutlu bir string matris d�nd�ren bir fonksiyon
vector<vector<string>> createStringMatrix(int numRows, int numCols) {
    vector<vector<string>> matrix(numRows, vector<string>(numCols));

    // Matris standart olarak bo� olacak �ekilde "E" olarak doldurulur
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            matrix[i][j] = "E";
        }
    }

    return matrix;
}
// Matris yeni bir vector<vector<string>> de�erine aktar�l�r
vector<vector<string>> Park = createStringMatrix(5, 10);

// fonksiyonlar�m�z�n prototipleri. Bir nevi C#'taki partial classlar gibi
int checkState(int count);
void options();
void fullParkList();
void exitCar();
void insertCar();

//Tarih bilgisini string olarak d�nd�ren fonksiyonumuz.
string* dateInfo() {
    string* dateAndTime = new string[2];
    // T�rk�e dil ayarlar� i�in bir locale olu�turduk
    locale::global(locale("tr_TR.utf8"));
    setlocale(LC_ALL, "Turkish");
    // �u anki zaman� ald�k
    time_t now;
    struct tm current_time;
    // Anl�k zaman� alma durumunu kontrol ediyoruz
    if (time(&now) == -1 || localtime_s(&current_time, &now) != 0) {
        cerr << "Zaman al�namad� veya i�lenemedi." << endl;
    }

    // T�rk�e tarih format�n� ayarlad�k
    char tarih_formati[] = "%A, %d %B %Y";
    char saat_formati[] = "%H:%M:%S";

    char tarih_str[80];
    char saat_str[80];

    // Tarih ve saat bilgilerini formatlad�k
    strftime(tarih_str, sizeof(tarih_str), tarih_formati, &current_time);
    strftime(saat_str, sizeof(saat_str), saat_formati, &current_time);

    dateAndTime[0] = tarih_str;
    dateAndTime[1] = saat_str;

    return dateAndTime;

}

//Kullan�c� giri� bilgilerini almam�zla beraber giri� bilgilerini pointer string olarak return ediyoruz.
string* LoginSequence(){
    string* loginInfos = new string[2];
    cout << "\t \t \t \t Kullan�c� Ad�n�z => ";
    cin >> loginInfos[0];
    cout << "\t \t \t \t �ifreniz => ";
    cin >> loginInfos[1];
    return loginInfos;
}

//Kapatma sekans�n� geciktiren haz�r bir method olu�turduk.
void closeSequence(int multiple=1) {
    for (int i = 0; i < multiple; i++) {
    Sleep(1000);
    cout << ".";
    }

}

int main()
{
    //T�rk�e yazd�r�r ve UTF-8 deste�i sa�lar
    setlocale(LC_ALL, "Turkish");
    //Program�n ��kt� olan her k�sm�na "/t" yani tabsler ekledim ki m�mk�n mertebe ortada hizal� olsun 
    cout << "\t \t \t \t  <<<<< Ho� Geldiniz >>>>>\n\n";
    Sleep(1000);
    checkState(1);
}

//Giri� durumunu kontrol eder ve buna g�re program� giri� k�sm�ndan ba�a sarar
int checkState(int count = 1) {
    int loginCount = count;
    string* loginInfo = LoginSequence();
    if (loginCount < 3) {
        if (loginInfo[0] != "Admin" || loginInfo[1] != "Admin") {
            loginCount++;
            cout << "\t \t \t \t  Hatal� giri� yapt�n�z!!! l�tfen tekrar deneyiniz \n\n";
            return checkState(loginCount);
        }
        else {
            cout << "\n\t \t \t \t  Ho� geldin " << loginInfo[0] << "\n\n";
            options();
        }
    }
    else if (loginCount >= 3)
    {
        cout << "\t \t \t \t �ok fazla hatal� giri� yapt�n�z!!! Giri� sistemi yeniden ba�lat�l�yor";
        closeSequence(3);
        cout << "\n\n";
        return main();
    }

}

//Kullan�c� ba�ar�l� bir �ekilde girdikten sonra kar��s�na se�eneklerin ��kt��� ana men�
void options() {
    int optNumb;
    cout << "\n\n \t \t \t \t A�a��daki se�enekleri se�mek i�in l�tfen ilgili numaray� giriniz \n\n";
    cout << "\t \t \t \t 1.) Park Halindeki Ara�lar�n Listesi \n";
    cout << "\t \t \t \t 2.) Park Halindeki Ara� ��k��� \n";
    cout << "\t \t \t \t 3.) Yeni Ara� Giri�i \n";
    cout << "\t \t \t \t 4.) ��k�� \n";
    cout << "\t \t \t \t Se�ene�iniz => ";
    cin >> optNumb;
    //Se�ti�i se�enekler i�in olu�turdu�umuz durumlar.Recursive �a�r� kulland�k
    switch (optNumb) {
    case 1:fullParkList(); break;
    case 2:exitCar(); break;
    case 3:insertCar(); break;
    case 4:return; break;
    default:cout << "\n\n\t \t \t \t !!! L�tfen ge�erli bir numara giriniz !!! \n\n";
        options();
        break;
    }
}
//�zelle�tirilmi� g�r�n�m� ile otopark yuvalar�.
void fullParkList() {
    cout << "\t \t \t \t Geri d�nmek i�in l�tfen 1 yaz�p 'Enter' tu�una bas�n�z: \n\n";
    for (int i = 0; i < 5; i++) {
        cout << "\t \t \t \t"<< (i+1) <<". Kattaki park yuvalar� \n";
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
    case 1:cout << "\t \t \t \t Ana Men�'ye d�n�l�yor "; closeSequence(3); options(); break;
    default:cout << "\n\n\t \t \t \t !!! L�tfen ge�erli bir numara giriniz !!! \n\n";
        fullParkList();
        break;
    }
}

//Ara� ��karma i�lemimiz burada ger�ekle�iyor
void exitCar() {
    int floorNumb;
    cout << "\n\n\t \t \t \t L�tfen bir kat se�iniz (1-5) ya da geri d�nmek i�in 0 yaz�p 'Enter' tu�una bas�n�z => ";
    cin >> floorNumb;
    if (floorNumb > 5 || floorNumb < 1) {
        if (floorNumb == 0) {
            cout << "\n\n\t \t \t \t Ana Men�'ye geri d�n�l�yor";
            closeSequence(3);
            options();
        }
        else {
			cout << "\n\n\t \t \t \t !!! Ge�ersiz kat numaras� !!!";
			exitCar();
        }

    }
    else {
        cout << "\t \t \t \t" << floorNumb << ". Kattaki park yuvalar� \n\n";
        cout << "\t \t \t \t";
        for (int j = 0; j < 10; j++) {
            cout << " | " << Park[floorNumb-1][j] << " | ";
        }
        cout << "\n\t \t \t \t L�tfen bir park yeri numaras� se�iniz (1-10)=> ";
        int parkSlotNum;
        cin >> parkSlotNum;
        if (parkSlotNum > 10 || parkSlotNum < 1) {
            cout << "\n\n\t \t \t \t !!! Ge�ersiz park yeri numaras� !!!";
            exitCar();
        }
        else {
            if (Park[floorNumb - 1][parkSlotNum - 1] == "E") {
                cout << "\n\n\t \t \t \t !!! Bu katta bulunan ara� yuvas� zaten bo�. Ana Men�'ye geri d�n�l�yor !!!";
                closeSequence(3);
                options();
            }
            else {
                cout << "\n\n\t \t \t \t " << Park[floorNumb - 1][parkSlotNum - 1] << "Bu ara� otoparktan ba�ar�l� bir �ekilde ��kart�ld�.\nAna Men�'ye geri d�n�l�yor";
                Park[floorNumb - 1][parkSlotNum - 1] = "E";
                closeSequence(3);
                options();
            }
        }
    }

}

void insertCar() {
    int floorNumb;
    cout << "\n\n\t \t \t \t L�tfen bir kat se�iniz (1-5) ya da geri d�nmek i�in 0 yaz�p 'Enter' tu�una bas�n�z => ";
    cin >> floorNumb;
    if (floorNumb > 5 || floorNumb < 1) {
        if (floorNumb == 0) {
            cout << "\n\n\t \t \t \t Ana Men�'ye geri d�n�l�yor";
            closeSequence(3);
            options();
        }
        else {
            cout << "\n\n\t \t \t \t !!! Ge�ersiz kat numaras� !!!";
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
            cout << "\n\n\t \t \t \t Bu kattaki t�m park yuvalar� dolu !!! Ba�lang�ca y�nlendiriliyorsunuz";
            closeSequence(2);
            insertCar();
        }
        else 
        {
            cout << "\n\t \t \t \t Bo� park yuva numaralar� => ";
            for (int i=0; i<parkSlotNumbs.size();i++)
            {
                cout << " | " << parkSlotNumbs[i] << " | ";
            }
            cout << "\n\t \t \t \t L�tfen bir park yeri numaras� se�iniz (1-10) => ";
            int parkSlotNum;
            cin >> parkSlotNum;
            if (parkSlotNum > 10 || parkSlotNum < 1) {
                cout << "\n\n\t \t \t \t !!! Ge�ersiz park yeri numaras� !!!";
                insertCar();
            }
            else if (Park[floorNumb - 1][parkSlotNum - 1] != "E") {
                cout << "\n\n\t \t \t \t Se�ili park yuvas� dolu !!! Ba�lang�ca y�nlendiriliyorsunuz";
                closeSequence(2);
                insertCar();
            }
            else {
                cout << "\n\n\t \t \t \t";
                cout << "Ara� plakas�n� giriniz => ";
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
                cout << "\n\n\t \t \t \t Park yerine ara� ekleme i�lemi tamamland�. Ana Men�'ye d�n�yorsunuz";
                string text = Park[floorNumb - 1][parkSlotNum - 1];
                closeSequence(3);
                options();

            }

        }
    }
}




