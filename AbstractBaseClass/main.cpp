#include<iostream>
using namespace std;

class Animal
{
	std::string name;
public:
	virtual void sound()const = 0;
};
class Cat:public Animal
{

};
class Tiger :public Cat
{
public:
	void sound()const override
	{
		cout << "Pppppppp." << endl;
	}
};
class Lion : public Cat
{
public:
	void sound()const override
	{
		cout << "Ùà ÿ òåáÿ ñõàâàþ." << endl;
	}
};
class Dog:public Animal{};
class Wolf :public Dog
{
public:
	void sound()const override
	{
		cout << "Àóóóóóóóóóóó" << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Animal slonohobotan;
	//Cat tom;
	Tiger tiger;
	tiger.sound();

	Lion killer;
	killer.sound();

	Wolf heart;
	heart.sound();

	Animal* zoo[] =
	{
		new Lion,
		new Tiger,
		new Wolf
	};
}