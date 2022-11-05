#include<iostream>
#include<string>

using namespace std;

#define delimetr "\n-------------------------------------\n"

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const { return last_name; }
	const std::string& get_first_name()const { return first_name; }
	unsigned int get_age()const { return age; }
	 //constructors
	Human(const std::string& last_name, const std::string& first_name, unsigned int age) :
		last_name(last_name), first_name(first_name), age(age)
	{
		cout << " Constructot\t" << this << endl;
	}
	~Human() { cout << "Hdestructor\t" << this << endl; }
	     //Methods
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << "лет.\n";
	}
};
class Student:public Human
{
	std::string speciality;
	std::string group;

};
void main()
{
	setlocale(LC_ALL, "");
	Human human("Montana", "Antonio", 25);
	human.print();
}