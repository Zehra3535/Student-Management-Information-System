#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include<sstream> //iss(istringstream),oss(ostringstream) kullanmak için
#include <windows.h> //komut ekranýna renk vermek için
#include <locale.h> //setlocale, türkçe karakter için yazýlabilir.yazmasak da olur.
#include <algorithm> // Include this for all_of
#include <cctype>    // Include this for isdigit
using namespace std;


void ogrenciEkle();
int sonNo();
int ogrenciSil();
void ogrenciGuncelle(int);
void ogrenciListesi();
void ogrenciAra(string, string);
void anaMenu();
void girisEkrani();
void ogrenciNotEkle(int);
void ogrenciNotListesi();
void ogrenciNotGuncelle(int ogrenciNo);





int main() {
	setlocale(LC_ALL, "Turkish");
	system("color 30"); //komut ekranýný renklendiriyoruz
	girisEkrani();



	bool devam = true;
	while (devam)
	{
		anaMenu();
		cout << "Ana menüye mi gitmek istersiniz yoksa çýkýþ mý yapmak istersiniz? (ana menü: 1, çýkýþ: 0 ): ";
		cin >> devam;

		if(devam!=1 && devam!=0)
		{
			cout << "Hatalý deðer girdiniz.";
		}
	}

	cout << "Çýkýþ yapýlýyor.Hoþçakalýn..." << endl;


	return 0;
}





void ogrenciEkle()
{

	system("cls");


	cout << "\t \t \t-----------1)Öðrenci Ekleme Ekraný-----------" << endl << endl;

	char devam;


	do
	{
		int ogrenciNo;
		ogrenciNo = sonNo();
		ogrenciNo++;

		cout << "Yeni öðrencinin numarasý= " << ogrenciNo << endl;


		string ogrenciAdi, ogrenciSoyadi, ogrenciTc;



		cout << "Öðrenci adýný giriniz= ";
		cin.ignore();
		getline(cin, ogrenciAdi);

		cout << "Öðrenci soyadýný giriniz= ";
		getline(cin, ogrenciSoyadi);
		cout << endl;


		bool gecerliTc = false;
		do
		{
			cout << "Öðrenci TC'sini giriniz (11 haneli)= ";
			cin >> ogrenciTc;

			if (ogrenciTc.length() == 11 && all_of(ogrenciTc.begin(), ogrenciTc.end(), ::isdigit))
			{
				gecerliTc = true;
			}
			else
			{
				cout << "Geçersiz TC kimlik numarasý. 11 haneli olmalý ve sadece rakamlardan oluþmalýdýr.\n\n";
			}
		} while (gecerliTc == false);// !gecerliTc

		//The line using 'all_of' is meant to check if all characters in the ogrenciTc string are digits.
		// The 'all_of' function is part of the <algorithm> header in C++.This line of code verifies that
		//every character in the TC number string is a digit, ensuring that the TC number consists only of numeric characters.


		ofstream OgrenciDosyasi("Ogrenci.txt", ios::app);

		if (OgrenciDosyasi.is_open())
		{
			OgrenciDosyasi << ogrenciNo << '#' << ogrenciAdi << '#' << ogrenciSoyadi << '#' << ogrenciTc << "\n";
			OgrenciDosyasi.close();

			cout << " Öðrenci ekleme iþlemi baþarýyla tamamlandý. " << endl << endl;
		}
		else
		{
			cout << "Dosya acýlamadi.Sorry. ";
		}


		cout << "Öðrenci eklemeye devam etmek istiyor musunuz ? (evet:e/ hayýr:h) : ";
		cin >> devam;

	} while (devam == 'e');

}



int sonNo()
{
	ifstream OgrenciDosyasi("Ogrenci.txt");
	string satir, sonSatir, ogrenciNo;


	if (!OgrenciDosyasi.is_open())
	{
		cout << "Dosya Açýlamadý.";
		return -1;
	}

	bool dosyaBos = 1;

	while (getline(OgrenciDosyasi, satir))
	{
		sonSatir = satir;

		dosyaBos = 0;
	}
	if (!dosyaBos)
	{
		istringstream iss(sonSatir);
		getline(iss, ogrenciNo, '#');
		OgrenciDosyasi.close();

		return stoi(ogrenciNo);
	}
	else {
		return 0;
	}
}




int ogrenciSil()
{


	cout << "\t \t \t----------- 2)Öðrenci silme iþlemi -----------" << endl;
	char secim;
	do {

		int ogrenciNo;
		cout << "Silmek istediðiniz öðrencinin numarasýný giriniz: ";
		cin >> ogrenciNo;

		string satir, No;
		ifstream OgrenciDosyasi("Ogrenci.txt");
		ofstream Ogrenci_Temp("Ogrenci_Temp.txt", ios::app);

		if (!OgrenciDosyasi.is_open() || !Ogrenci_Temp.is_open())
		{
			cout << " Dosya Açýlamadý! ";
			return -1;
		}
		bool silindi = false;
		while (getline(OgrenciDosyasi, satir))
		{

			if (!satir.empty())
			{
				istringstream iss(satir);
				getline(iss, No, '#');

				if (stoi(No) != ogrenciNo) //okunan satýrdaki sileceðimiz öðrenci deðil,o zaman onu temp dosyasýna yaz.silinmesin.
				{
					Ogrenci_Temp << satir << endl;
				}
				else
				{
					silindi = true;
				}
			}
		}
		OgrenciDosyasi.close();
		Ogrenci_Temp.close();

		remove("Ogrenci.txt");
		rename("Ogrenci_Temp.txt", "Ogrenci.txt");

		if (silindi) {
			cout << "Öðrenci baþarýyla silindi." << endl;
		}
		else /*(!silindi)*/
		{
			cout << "Öðrenci bulunamadý." << endl;
		}

		cout << "Öðrenci silmeye devam etmek istiyor musunuz ? (evet:e/ hayýr:h) : ";
		cin >> secim;



	} while (secim == 'e');
	return 0;

}



void ogrenciGuncelle(int ogrenciNo)
{
	string satir, No, isim, soyisim, ogrenciTc;

	bool ogrenciBulundu = false; // Öðrenci bulunup bulunmadýðýný kontrol etmek için
	
	
	ifstream OgrenciDosyasi("Ogrenci.txt");
	ofstream Ogrenci_Temp("Ogrenci_Temp.txt");

	if (!OgrenciDosyasi.is_open() || !Ogrenci_Temp.is_open())
	{
		cout << "Güncellemek için dosya acilamadi";
		return;
	}

	while (getline(OgrenciDosyasi, satir))
	{
		if (satir != "") {
			istringstream iss(satir);
			getline(iss, No, '#');

			if (stoi(No) != ogrenciNo)
			{
				Ogrenci_Temp << satir << endl;
			}
			else {

				// Öðrenci bulundu, güncelleme iþlemi yapýlacak
				ogrenciBulundu = true;

				cout << "Güncellediðiniz kiþinin adýný giriniz= ";
				cin >> isim;
				cout << endl;


				cout << "Güncellediðiniz kiþinin soyadýný giriniz= ";
				cin >> soyisim;
				cout << endl;

				cout << "Güncellediðiniz kiþinin TC'sini giriniz=";
				cin >> ogrenciTc;

				Ogrenci_Temp << No << '#' << isim << '#' << soyisim << '#' << ogrenciTc << "\n";
			}
		}
	}

	if (!ogrenciBulundu) {
		cout << "Öðrenci bulunamadý." << endl;
	}
	else {
		// Öðrenci bulunduysa dosyalarý güncelle

		OgrenciDosyasi.close();
		Ogrenci_Temp.close();
		remove("Ogrenci.txt");
		rename("Ogrenci_Temp.txt", "Ogrenci.txt");

		cout << "Öðrenci baþarýyla güncellendi." << endl;
	}
}




void ogrenciListesi()
{
	cout << "\t \t \t----------- 5) Öðrenci Listesi -----------" << endl << endl;
	string satir, ogrenciNo, isim, soyisim, ogrenciTc;
	ifstream OgrenciDosyasi("Ogrenci.txt");
	if (!OgrenciDosyasi.is_open())
	{
		cout << " Liste için dosya Açýlamadý! ";
		return;
	}
	while (getline(OgrenciDosyasi, satir))
	{
		if (satir != "")
		{
			istringstream iss(satir);
			getline(iss, ogrenciNo, '#');
			getline(iss, isim, '#');
			getline(iss, soyisim, '#');
			getline(iss, ogrenciTc, '#');
			cout << ogrenciNo << "\t\t" << isim << "\t" << soyisim << "\t\t" << ogrenciTc << "\n \n";
		}
	}
	OgrenciDosyasi.close();
}





void ogrenciAra(string ogrenciAdi, string ogrenciSoyadi)
{
	cout << "\t \t \t-----------1)Öðrenci Arama Ekraný-----------" << endl << endl;
	ifstream OgrenciDosyasi("Ogrenci.txt");
	string satir, ogrenciNo, isim, soyisim, ogrenciTc;

	if (!OgrenciDosyasi.is_open()) {
		cout << "Dosya arama yapmak için açýlamadý. ";
		return;
	}


	bool arandý = false;
	cout << "ogrenciNo\tAd\tSoyad\togrenciTc\n";
	while (getline(OgrenciDosyasi, satir)) {
		if (satir != "") {
			istringstream iss(satir);
			getline(iss, ogrenciNo, '#');
			getline(iss, isim, '#');
			getline(iss, soyisim, '#');
			getline(iss, ogrenciTc, '#');

			if (isim == ogrenciAdi && soyisim == ogrenciSoyadi) {
				cout << ogrenciNo << "\t\t" << isim << "\t" << soyisim << "\t" << ogrenciTc << "\n \n";
				arandý = true;
			}

		}

	}

	if (!arandý) {
		cout << "Arama iþleminde hata oluþtu." << endl;
	}

	OgrenciDosyasi.close();
}


void ogrenciNotEkle(int ogrenciNo)
{
	ifstream OgrenciDosyasi("Ogrenci.txt");
	ofstream NotDosyasi("Notlar.txt", ios::app);

	if (!OgrenciDosyasi.is_open() || !NotDosyasi.is_open()) {
		cout << "Dosya açýlamadý!";
		return;
	}

	string satir, No, ogrenciAdi, ogrenciSoyadi, ogrenciTc;
	bool ogrenciBulundu = false;

	while (getline(OgrenciDosyasi, satir)) {
		istringstream iss(satir);
		getline(iss, No, '#');
		if (stoi(No) == ogrenciNo) {
			ogrenciBulundu = true;
			getline(iss, ogrenciAdi, '#');
			getline(iss, ogrenciSoyadi, '#');
			getline(iss, ogrenciTc, '#');
			break;
		}
	}

	if (ogrenciBulundu)
	{
		double vize, final, butunleme;
		cout << "Vize notunu giriniz: ";
		cin >> vize;
		cout << endl;
		cout << "Final notunu giriniz: ";
		cin >> final;
		cout << "Bütünleme notunu giriniz (yoksa -1 giriniz): ";
		cin >> butunleme;

		double ortalama;
		if (butunleme == -1)
		{
			ortalama = (vize * 0.4) + (final * 0.6);
		}
		else
		{
			ortalama = (vize * 0.4) + (butunleme * 0.6);
		}
		NotDosyasi << ogrenciNo << '#' << ogrenciAdi << '#' << ogrenciSoyadi << '#' << vize << '#' << final << '#' << butunleme << '#' << ortalama << "\n";
		cout << "Notlar baþarýyla eklendi." << endl;
	}
	else {
		cout << "Not girmek için öðrenci bulunamadý." << endl;
	}

	OgrenciDosyasi.close();
	NotDosyasi.close();
}

void ogrenciNotListesi() {

	/*cin.get();*/
	string satir, ogrenciNo, ogrenciAdi, ogrenciSoyadi, vize, final, butunleme, ortalama;
	ifstream NotDosyasi("Notlar.txt");

	if (!NotDosyasi.is_open()) {
		cout << "Not eklemek için dosya açýlamadý!";
		return;
	}

	cout << "Öðrenci No\tÝsim\t Soyisim\tVize\t\tFinal\t\tBütünleme\tOrtalama\n";
	while (getline(NotDosyasi, satir)) {
		if (satir != "") {
			istringstream iss(satir);
			getline(iss, ogrenciNo, '#');
			getline(iss, ogrenciAdi, '#');
			getline(iss, ogrenciSoyadi, '#');
			getline(iss, vize, '#');
			getline(iss, final, '#');
			getline(iss, butunleme, '#');
			getline(iss, ortalama, '#');
			cout << ogrenciNo << "\t\t" << ogrenciAdi << "\t " << ogrenciSoyadi << "\t\t" << vize << "\t\t" << final << "\t\t" << butunleme << "\t\t" << ortalama << "\n \n";
		}
	}
	NotDosyasi.close();
}



void ogrenciNotGuncelle(int ogrenciNo) {
	ifstream NotDosyasi("Notlar.txt");
	ofstream NotDosyasi_Temp("Notlar_Temp.txt");

	if (!NotDosyasi.is_open() || !NotDosyasi_Temp.is_open()) {
		cout << "Dosya açýlamadý!";
		return;
	}

	string satir, No, ogrenciAdi, ogrenciSoyadi, vize, final, butunleme, ortalama;
	bool ogrenciyiBuldu= false;

	while (getline(NotDosyasi, satir)) {
		istringstream iss(satir);
		getline(iss, No, '#');
		getline(iss, ogrenciAdi, '#');
		getline(iss, ogrenciSoyadi, '#');
		getline(iss, vize, '#');
		getline(iss, final, '#');
		getline(iss, butunleme, '#');
		getline(iss, ortalama, '#');

		if (stoi(No) == ogrenciNo) {
			ogrenciyiBuldu = true;
			cout << "Mevcut Vize Notu: " << vize << endl;
			cout << "Mevcut Final Notu: " << final << endl;
			cout << "Mevcut Bütünleme Notu: " << butunleme << endl;

			cout << "Yeni Vize notunu giriniz: ";
			cin >> vize;
			cout << endl;
			cout << "Yeni Final notunu giriniz: ";
			cin >> final;
			cout << "Yeni Bütünleme notunu giriniz (yoksa -1 giriniz): ";
			cin >> butunleme;

			double yeniOrtalama;
			if (butunleme == "-1") {
				yeniOrtalama = (stod(vize) * 0.4) + (stod(final) * 0.6);
			}
			else {
				yeniOrtalama = (stod(vize) * 0.4) + (stod(butunleme) * 0.6);
			}

			NotDosyasi_Temp << No << '#' << ogrenciAdi << '#' << ogrenciSoyadi << '#' << vize << '#' << final << '#' << butunleme << '#' << to_string(yeniOrtalama) << "\n";
		}
		else {
			NotDosyasi_Temp << satir << "\n";
		}
	}

	if (!ogrenciyiBuldu) {
		cout << "Güncellemek için öðrenci bulunamadý." << endl;
	}

	NotDosyasi.close();
	NotDosyasi_Temp.close();
	remove("Notlar.txt");
	rename("Notlar_Temp.txt", "Notlar.txt");
}


void anaMenu()
{
	system("cls");

	cout << "\t \t \t \t1.Öðrenci Ekleme " << endl;
	cout << "\t \t \t \t2.Öðrenci Silme  " << endl;
	cout << "\t \t \t \t3.Öðrenci Bilgilerini Düzenleme" << endl;
	cout << "\t \t \t \t4.Öðrenci Arama " << endl;
	cout << "\t \t \t \t5.Öðrenci Listesi " << endl;
	cout << "\t \t \t \t6. Öðrenci Not Ekleme" << endl;
	cout << "\t \t \t \t7. Öðrenci Not Listesi" << endl;
	cout << "\t \t \t \t8. Öðrenci Not Güncelleme" << endl;
	cout << "\t \t \t \t9. Sistemden Çýkýþ " << endl << endl;


	int ogrenciNo;
	string ogrenciAdi;
	string ogrenciSoyadi;
	string ogrenciTc;



	int islem = 0;
	cout << "\t \t  Lütfen yapmak istediðiniz iþlemin numarasýný girin = ";
	cin >> islem;
	cout << endl;


	switch (islem)
	{

	case 1:
	{
		ogrenciEkle();
		break;
	}

	case 2:
	{
		ogrenciSil();
		break;
	}

	case 3:
	{
		cout << "Güncellemek istediðiniz öðrencinin numarasýný giriniz: ";
		cin >> ogrenciNo;
		ogrenciGuncelle(ogrenciNo);
		break;
	}

	case 4: {
		cout << "Aranacak öðrencinin adýný giriniz: ";
		cin.ignore();
		getline(cin, ogrenciAdi);

		cout << "Aranacak öðrencinin soyadýný giriniz: ";
		getline(cin, ogrenciSoyadi);

		ogrenciAra(ogrenciAdi, ogrenciSoyadi);
		break;

	}

	case 5:
	{

		ogrenciListesi();
		break;
	}
	case 6:
	{
		cout << "Notunu eklemek istediðiniz öðrencinin numarasýný giriniz: ";
		cin >> ogrenciNo;
		ogrenciNotEkle(ogrenciNo);
		break;
	}
	case 7:
	{
		ogrenciNotListesi();
		break;
	}
	case 8:
	{
		cout << "Notlarýný güncellemek istediðiniz öðrencinin numarasýný giriniz: ";
		cin >> ogrenciNo;
		ogrenciNotGuncelle(ogrenciNo);
		break;
		
	}
	case 9:
	{
		cout << "Çýkýþ yönlendiriliyor." << endl;
		break;
	}
	default:
		cout << "Geçersiz seçim." << endl;
		break;
	}

}


void girisEkrani()
{

	cout << "\t \t \t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\t \t \t" << endl;
	cout << "\t \t \t&&                                 &&\t \t \t" << endl;
	cout << "\t \t \t&&  ÖÐRENCÝ BÝLGÝ YÖNETÝM SÝSTEMÝ  &&\t \t \t" << endl;
	cout << "\t \t \t&&                                 &&\t \t \t" << endl;
	cout << "\t \t \t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \t \t \t" << endl << endl;

	cout << "\t\t\t    _Öðrenci Sistemine Hoþ Geldiniz_" << endl << endl;
	cout << "\t\t\t   | Giriþ yapmak için Enter'a basýnýz.|" << endl << endl;


	cin.get();
}
