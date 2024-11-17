#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include<sstream> //iss(istringstream),oss(ostringstream) kullanmak i�in
#include <windows.h> //komut ekran�na renk vermek i�in
#include <locale.h> //setlocale, t�rk�e karakter i�in yaz�labilir.yazmasak da olur.
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
	system("color 30"); //komut ekran�n� renklendiriyoruz
	girisEkrani();



	bool devam = true;
	while (devam)
	{
		anaMenu();
		cout << "Ana men�ye mi gitmek istersiniz yoksa ��k�� m� yapmak istersiniz? (ana men�: 1, ��k��: 0 ): ";
		cin >> devam;

		if(devam!=1 && devam!=0)
		{
			cout << "Hatal� de�er girdiniz.";
		}
	}

	cout << "��k�� yap�l�yor.Ho��akal�n..." << endl;


	return 0;
}





void ogrenciEkle()
{

	system("cls");


	cout << "\t \t \t-----------1)��renci Ekleme Ekran�-----------" << endl << endl;

	char devam;


	do
	{
		int ogrenciNo;
		ogrenciNo = sonNo();
		ogrenciNo++;

		cout << "Yeni ��rencinin numaras�= " << ogrenciNo << endl;


		string ogrenciAdi, ogrenciSoyadi, ogrenciTc;



		cout << "��renci ad�n� giriniz= ";
		cin.ignore();
		getline(cin, ogrenciAdi);

		cout << "��renci soyad�n� giriniz= ";
		getline(cin, ogrenciSoyadi);
		cout << endl;


		bool gecerliTc = false;
		do
		{
			cout << "��renci TC'sini giriniz (11 haneli)= ";
			cin >> ogrenciTc;

			if (ogrenciTc.length() == 11 && all_of(ogrenciTc.begin(), ogrenciTc.end(), ::isdigit))
			{
				gecerliTc = true;
			}
			else
			{
				cout << "Ge�ersiz TC kimlik numaras�. 11 haneli olmal� ve sadece rakamlardan olu�mal�d�r.\n\n";
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

			cout << " ��renci ekleme i�lemi ba�ar�yla tamamland�. " << endl << endl;
		}
		else
		{
			cout << "Dosya ac�lamadi.Sorry. ";
		}


		cout << "��renci eklemeye devam etmek istiyor musunuz ? (evet:e/ hay�r:h) : ";
		cin >> devam;

	} while (devam == 'e');

}



int sonNo()
{
	ifstream OgrenciDosyasi("Ogrenci.txt");
	string satir, sonSatir, ogrenciNo;


	if (!OgrenciDosyasi.is_open())
	{
		cout << "Dosya A��lamad�.";
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


	cout << "\t \t \t----------- 2)��renci silme i�lemi -----------" << endl;
	char secim;
	do {

		int ogrenciNo;
		cout << "Silmek istedi�iniz ��rencinin numaras�n� giriniz: ";
		cin >> ogrenciNo;

		string satir, No;
		ifstream OgrenciDosyasi("Ogrenci.txt");
		ofstream Ogrenci_Temp("Ogrenci_Temp.txt", ios::app);

		if (!OgrenciDosyasi.is_open() || !Ogrenci_Temp.is_open())
		{
			cout << " Dosya A��lamad�! ";
			return -1;
		}
		bool silindi = false;
		while (getline(OgrenciDosyasi, satir))
		{

			if (!satir.empty())
			{
				istringstream iss(satir);
				getline(iss, No, '#');

				if (stoi(No) != ogrenciNo) //okunan sat�rdaki silece�imiz ��renci de�il,o zaman onu temp dosyas�na yaz.silinmesin.
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
			cout << "��renci ba�ar�yla silindi." << endl;
		}
		else /*(!silindi)*/
		{
			cout << "��renci bulunamad�." << endl;
		}

		cout << "��renci silmeye devam etmek istiyor musunuz ? (evet:e/ hay�r:h) : ";
		cin >> secim;



	} while (secim == 'e');
	return 0;

}



void ogrenciGuncelle(int ogrenciNo)
{
	string satir, No, isim, soyisim, ogrenciTc;

	bool ogrenciBulundu = false; // ��renci bulunup bulunmad���n� kontrol etmek i�in
	
	
	ifstream OgrenciDosyasi("Ogrenci.txt");
	ofstream Ogrenci_Temp("Ogrenci_Temp.txt");

	if (!OgrenciDosyasi.is_open() || !Ogrenci_Temp.is_open())
	{
		cout << "G�ncellemek i�in dosya acilamadi";
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

				// ��renci bulundu, g�ncelleme i�lemi yap�lacak
				ogrenciBulundu = true;

				cout << "G�ncelledi�iniz ki�inin ad�n� giriniz= ";
				cin >> isim;
				cout << endl;


				cout << "G�ncelledi�iniz ki�inin soyad�n� giriniz= ";
				cin >> soyisim;
				cout << endl;

				cout << "G�ncelledi�iniz ki�inin TC'sini giriniz=";
				cin >> ogrenciTc;

				Ogrenci_Temp << No << '#' << isim << '#' << soyisim << '#' << ogrenciTc << "\n";
			}
		}
	}

	if (!ogrenciBulundu) {
		cout << "��renci bulunamad�." << endl;
	}
	else {
		// ��renci bulunduysa dosyalar� g�ncelle

		OgrenciDosyasi.close();
		Ogrenci_Temp.close();
		remove("Ogrenci.txt");
		rename("Ogrenci_Temp.txt", "Ogrenci.txt");

		cout << "��renci ba�ar�yla g�ncellendi." << endl;
	}
}




void ogrenciListesi()
{
	cout << "\t \t \t----------- 5) ��renci Listesi -----------" << endl << endl;
	string satir, ogrenciNo, isim, soyisim, ogrenciTc;
	ifstream OgrenciDosyasi("Ogrenci.txt");
	if (!OgrenciDosyasi.is_open())
	{
		cout << " Liste i�in dosya A��lamad�! ";
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
	cout << "\t \t \t-----------1)��renci Arama Ekran�-----------" << endl << endl;
	ifstream OgrenciDosyasi("Ogrenci.txt");
	string satir, ogrenciNo, isim, soyisim, ogrenciTc;

	if (!OgrenciDosyasi.is_open()) {
		cout << "Dosya arama yapmak i�in a��lamad�. ";
		return;
	}


	bool arand� = false;
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
				arand� = true;
			}

		}

	}

	if (!arand�) {
		cout << "Arama i�leminde hata olu�tu." << endl;
	}

	OgrenciDosyasi.close();
}


void ogrenciNotEkle(int ogrenciNo)
{
	ifstream OgrenciDosyasi("Ogrenci.txt");
	ofstream NotDosyasi("Notlar.txt", ios::app);

	if (!OgrenciDosyasi.is_open() || !NotDosyasi.is_open()) {
		cout << "Dosya a��lamad�!";
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
		cout << "B�t�nleme notunu giriniz (yoksa -1 giriniz): ";
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
		cout << "Notlar ba�ar�yla eklendi." << endl;
	}
	else {
		cout << "Not girmek i�in ��renci bulunamad�." << endl;
	}

	OgrenciDosyasi.close();
	NotDosyasi.close();
}

void ogrenciNotListesi() {

	/*cin.get();*/
	string satir, ogrenciNo, ogrenciAdi, ogrenciSoyadi, vize, final, butunleme, ortalama;
	ifstream NotDosyasi("Notlar.txt");

	if (!NotDosyasi.is_open()) {
		cout << "Not eklemek i�in dosya a��lamad�!";
		return;
	}

	cout << "��renci No\t�sim\t Soyisim\tVize\t\tFinal\t\tB�t�nleme\tOrtalama\n";
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
		cout << "Dosya a��lamad�!";
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
			cout << "Mevcut B�t�nleme Notu: " << butunleme << endl;

			cout << "Yeni Vize notunu giriniz: ";
			cin >> vize;
			cout << endl;
			cout << "Yeni Final notunu giriniz: ";
			cin >> final;
			cout << "Yeni B�t�nleme notunu giriniz (yoksa -1 giriniz): ";
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
		cout << "G�ncellemek i�in ��renci bulunamad�." << endl;
	}

	NotDosyasi.close();
	NotDosyasi_Temp.close();
	remove("Notlar.txt");
	rename("Notlar_Temp.txt", "Notlar.txt");
}


void anaMenu()
{
	system("cls");

	cout << "\t \t \t \t1.��renci Ekleme " << endl;
	cout << "\t \t \t \t2.��renci Silme  " << endl;
	cout << "\t \t \t \t3.��renci Bilgilerini D�zenleme" << endl;
	cout << "\t \t \t \t4.��renci Arama " << endl;
	cout << "\t \t \t \t5.��renci Listesi " << endl;
	cout << "\t \t \t \t6. ��renci Not Ekleme" << endl;
	cout << "\t \t \t \t7. ��renci Not Listesi" << endl;
	cout << "\t \t \t \t8. ��renci Not G�ncelleme" << endl;
	cout << "\t \t \t \t9. Sistemden ��k�� " << endl << endl;


	int ogrenciNo;
	string ogrenciAdi;
	string ogrenciSoyadi;
	string ogrenciTc;



	int islem = 0;
	cout << "\t \t  L�tfen yapmak istedi�iniz i�lemin numaras�n� girin = ";
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
		cout << "G�ncellemek istedi�iniz ��rencinin numaras�n� giriniz: ";
		cin >> ogrenciNo;
		ogrenciGuncelle(ogrenciNo);
		break;
	}

	case 4: {
		cout << "Aranacak ��rencinin ad�n� giriniz: ";
		cin.ignore();
		getline(cin, ogrenciAdi);

		cout << "Aranacak ��rencinin soyad�n� giriniz: ";
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
		cout << "Notunu eklemek istedi�iniz ��rencinin numaras�n� giriniz: ";
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
		cout << "Notlar�n� g�ncellemek istedi�iniz ��rencinin numaras�n� giriniz: ";
		cin >> ogrenciNo;
		ogrenciNotGuncelle(ogrenciNo);
		break;
		
	}
	case 9:
	{
		cout << "��k�� y�nlendiriliyor." << endl;
		break;
	}
	default:
		cout << "Ge�ersiz se�im." << endl;
		break;
	}

}


void girisEkrani()
{

	cout << "\t \t \t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\t \t \t" << endl;
	cout << "\t \t \t&&                                 &&\t \t \t" << endl;
	cout << "\t \t \t&&  ��RENC� B�LG� Y�NET�M S�STEM�  &&\t \t \t" << endl;
	cout << "\t \t \t&&                                 &&\t \t \t" << endl;
	cout << "\t \t \t&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& \t \t \t" << endl << endl;

	cout << "\t\t\t    _��renci Sistemine Ho� Geldiniz_" << endl << endl;
	cout << "\t\t\t   | Giri� yapmak i�in Enter'a bas�n�z.|" << endl << endl;


	cin.get();
}
