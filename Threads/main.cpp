#include <iostream>
#include <thread>
using namespace std;
using namespace std::chrono_literals;

bool finish = false;

void Plus()
{
	while (!finish)
	{
	cout << "+ ";
	std::this_thread::sleep_for(1s);
	}
}

void Minus()
{
	while (!finish)
	{
		cout << "- ";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	setlocale(LC_ALL, "");
	//Plus();
	//Minus();
	std::thread plus_thread(Plus);
	std::thread minus_thread(Minus);

	cin.get();//Метод get ожидает нажатие enter
	finish = true;

	// Метод join() останавливает поток, и синхронизирует его с основным потоком
	minus_thread.join();
	plus_thread.join();

}