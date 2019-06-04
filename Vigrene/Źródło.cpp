#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <math.h>

using namespace std;

long double indeks(string line)
{
	int N = line.length();
	int n = 0;//ilosc zliczen dla danego znaku
	int sum=0;
	long double INDEX = 0;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < N; j++) {
			if ((int)line[j] == 97 + i) {
				n++;
			}
        }
		sum += n*(n - 1);
		n = 0;
	}
	INDEX = 10000*sum/(N*N -N);
	return INDEX;
}
long double indeks2(string column1, string column2, int d)
{
	int N1 = column1.length();
	int N2 = column2.length();
	int n1 = 0;//ilosc zliczen dla danego znaku dla 1 kolumny
	int n2 = 0;//ilosc zliczen dla danego znaku dla 2 kolumny
	int sum = 0;
	long double INDEX = 0;
	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < N1; j++) {
			if ((int)column1[j] == 97 + i) {
				n1++;
			}
		}
		for (int j = 0; j < N2; j++) {
			if ((int)column2[j] == 97 +(i+d)%26) {
				n2++;
			}
		}
		sum += n1 * n2;
		n1 = 0;
		n2 = 0;
		
	}
	INDEX = 10000 * sum / (N1*N2);
	return INDEX;

}
string readFILE(string line)
{
	string linia;

	fstream plik;

	plik.open("tekst_Vigenere2.txt", ios::in);
	if (plik.good() == true)
	{
		while (!plik.eof())
		{
			getline(plik, linia);
			line += linia;
		}
		plik.close();
	}
	return line;
}
void writeFILE(string line)
{

	fstream plik;

	plik.open("tekst_Vigenere2_szyfrogram.txt", ios::out);
	if (plik.good() == true)
	{
		plik << line;
	
	}
	plik.close();
	
}
string szyfrogram(string line,string klucz)
{
	int x;
	int n = klucz.length();
	for (int i = 0; i < line.length(); i++) {
		
		
		x = ((int)line[i] -97);
		x = (x + (int)klucz[i%n]-97)%26;
		line[i] = static_cast<char>(x+97);
	}
	
	return line;
}
string deszyfrogram(string line, string klucz,int dl_klucz)
{
	int x;
	for (int i = 0; i < line.length(); i++) {


		x = ((int)line[i] - 97);
		x = (x+ 26-(int)klucz[i%(dl_klucz)] + 97)%26 ;
		line[i] = static_cast<char>(x + 97);

	}
	return line;
}

void divide(int dl_klucz,string line,string *columns) {
	string line_divided;
	for (int j = 0; j < dl_klucz; j++) {
		for (int i = 0; i < line.length(); i++) {
			if (i % (dl_klucz) == j)
			{
				line_divided += line[i];
			}
		}
		columns[j] = line_divided;
		cout << "Indeks koincydencji dla kolumny " << j+1 << ": " << indeks(line_divided)/10000 << endl;;
		line_divided.clear();
	}
}
void findKEY(string line,string *column,int *character_shift,int dl_klucz) {
	int i = 0;
	int j = 0;
	int x;// zmienna pomocnicza
	string KLUCZ2;
	string character;
	string line2;
	character_shift[0]=0;
	
		while (i < dl_klucz - 1) {
			cout << "indeks wzajemnej koincydencji dla kolumny " << " 1" << " i " << i + 2 << ": " << indeks2(column[0], column[i + 1], j) / 10000 << endl;
			cout << "Wcisnij '1'-zgodny indeks. Wcisnij '2'-przesuniecie +1 :" << endl;;
			cin >> x;
			if (x == 1) {

				character_shift[i + 1] = j;
				i++;
				j = 0;
			}
			else {
				j++;
			}
		}
	
	cout << "Twoj klucz to : ";
	for (int i = 0; i < dl_klucz ; i++) {
		cout <<"k[0]+"<< character_shift[i]%26 << ",";
	}
	while (1) {
		cout << endl << "Zgadnij pierwsza litere klucza: ";
		cin >> character;
		cout << "Twoj klucz to:";
		for (int i = 0; i < dl_klucz; i++) {
			KLUCZ2 += " ";
			KLUCZ2[i] = static_cast<char>(97+((int)character[0] +character_shift[i]-97)%26);
		}
		cout << KLUCZ2;
	    line2=deszyfrogram(line, KLUCZ2, dl_klucz);
		cout << endl << line2<<endl;
	}
}
int main()
{
	string klucz = "tvz";
    string line;
	
	int dl_klucz;
	line=readFILE(line);
  
	line=szyfrogram(line,klucz);
    writeFILE(line);

	cout << "Zgadnij dlugosc klucza: ";
	cin >> dl_klucz;
	string *column=new string[dl_klucz];
	int *character_shift =new int[dl_klucz];
	divide(dl_klucz, line,column);
	findKEY(line,column,character_shift,dl_klucz);
	
	system("PAUSE");
	return(0);
}