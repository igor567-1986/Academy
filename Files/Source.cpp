#include<iostream>
#include<fstream>
using namespace std;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout;          // 1)Создаем поток
	fout.open("File.txt", std::ios::app);       //2)Открываем поток
	// std::ios::app- append означает не переписывать ,а дописывать в конец файла
	fout << "Hello Files" << endl;//3)Пишем в поток
	fout.close();                //4)Закрываем поток

	system("notepad File.txt");// Функция system()запускает любую прогграму к которой есть доступ в PATH Windows  
#endif // WRITE_TO_FILE
   
#ifdef READ_FROM_FILE
	ifstream fin("File.txt");
	if (fin.is_open())
	{
		//Будем читать файл
		const int SIZE = 256;
		char buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
		cout << fin.tellg() << "\n"; // позиция курсора
		fin.close();
	}
	else
	{
		std::cerr << "Eror:file not found" << endl;
	}

#endif // READ_FROM_FILE

}