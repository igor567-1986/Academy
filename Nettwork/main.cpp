#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	
	char number[10] = {};
	char src_filename[_MAX_FNAME]={};//_MAX_FNAME это встроенаая константа которая содержит максимально возможную длинну имени файла
	char dst_filename[_MAX_FNAME] = {};
	// src (source)-  файл источник,из которого изначально берутся 
	// dst (destination)- это конечный файл,в котором столбики будут поменяны
	cout << "Введите номер аудитории :"; cin >> number;
	// По введеному номеру аудитории формирует имена файлов,как исходного,так и конечного
	strcat(src_filename, number);
	strcat(src_filename, "RAW.txt"); // strcat - Выполняет конкатенацию строки
	// к первой строке (filename) добавляет вторую строку ("RAW.txt")
	strcat(dst_filename, number);
	strcat(dst_filename, "ready.txt");
	const int IP_SIZE = 16;
	const int MAC_SIZE = 18;

	char sz_ip_buffer[IP_SIZE] = {};
	char sz_mac_buffer[MAC_SIZE] = {};

	std::ofstream fout("201 ready.txt");
	std::ifstream fin("201 RAW.txt");

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer;
			fin >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}

	fout.close();
	system("notepad 201 ready.txt");
}