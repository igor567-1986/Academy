#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	
	char number[10] = {};
	char src_filename[_MAX_FNAME]={};//_MAX_FNAME это встроенаая константа которая содержит максимально возможную длинну имени файла
	char wal_filename[_MAX_FNAME] = {};
	char dhpcd_filename[_MAX_FNAME] = {};

	// src (source)-  файл источник,из которого изначально берутся 
	// dst (destination)- это конечный файл,в котором столбики будут поменяны
	cout << "Введите номер аудитории :"; cin >> number;
	// По введеному номеру аудитории формирует имена файлов,как исходного,так и конечного
	strcat(src_filename, number);
	strcat(src_filename, " RAW.txt"); // strcat - Выполняет конкатенацию строки
	// к первой строке (filename) добавляет вторую строку ("RAW.txt")
	strcat(wal_filename, number);
	strcat(wal_filename, " ready.txt");

	strcat(dhpcd_filename, number);
	strcat(dhpcd_filename, " .dhpcd");
	cout << "Source file:\t" << src_filename << endl;
	cout << "Dest file:\t" << wal_filename << endl;

	const int IP_SIZE = 16;
	const int MAC_SIZE = 18;

	char sz_ip_buffer[IP_SIZE] = {};
	char sz_mac_buffer[MAC_SIZE] = {};

	std::ofstream fout(wal_filename);
	std::ifstream fin(src_filename);

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> sz_ip_buffer;
			fin >> sz_mac_buffer;
			cout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
			fout << sz_mac_buffer << "\t\t" << sz_ip_buffer << endl;
		}
		//fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	fout.close();
	char sz_command[_MAX_FNAME] = "start notepad ";
	strcat(sz_command, wal_filename);
	system(sz_command);

	///////////////////////////////////////////////////////

	// Возвращаемся в начало файла
	fin.clear();
	fin.seekg(0);
	cout << fin.tellg() << endl;
	fout.open(dhpcd_filename);
	if (fin.is_open())
	{
		for (int i=1;!fin.eof();i++)
		{
			fin >> sz_ip_buffer >> sz_mac_buffer;
			for (int i = 0; sz_mac_buffer[i]; i++)
				if (sz_mac_buffer[i] == '-')sz_mac_buffer[i] = ':';
			cout << number << "-" << i << endl;
			cout << "{\n";
			cout << "\thardware ethernet\t"<< sz_mac_buffer<<";\n";
			cout << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			cout << "}\n";

            fout << number << "-" << i << endl;
			fout << "{\n";
			fout << "\thardware ethernet\t"<< sz_mac_buffer<<";\n";
			fout << "\tfixed-address\t\t" << sz_ip_buffer << ";\n";
			fout << "}\n";

		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	strcpy(sz_command + strlen("start notepad "), dhpcd_filename);
	system(sz_command);
}