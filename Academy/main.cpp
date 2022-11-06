#include<iostream>
#include<string>

using namespace std;

#define delimetr "\n-------------------------------------\n"

#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARMETRS last_name,first_name,age


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
	Human( HUMAN_TAKE_PARAMETRS ) :
		last_name(last_name), first_name(first_name), age(age)
	{
		cout << " Constructot\t" << this << endl;
	}
	~Human() { cout << "Hdestructor\t" << this << endl; }
	     //Methods
	void print()const
	{
		cout << last_name << " " << first_name << " " << age << "���.\n";
	}
};

#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS speciality,group,rating,attendance

class Student:public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const { return speciality; }
	const std::string& get_group()const { return group; }
	double get_rating()const { return rating; }
	double get_attendance()const { return attendance; }
	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_group(const std::string& group) { this->group = group; }
	void set_raiting(double rating) { this->rating = rating; }
	void set_attendence(double attendance) { this->attendance = attendance; }

	     // Constructors
	Student	(HUMAN_TAKE_PARAMETRS,STUDENT_TAKE_PARAMETRS):Human(last_name,first_name,age)
	{
		this->speciality = speciality;
		this->group = group;
		this->rating = rating;
		this->attendance = attendance;
		cout << "SConstructor:\t" << this << endl;
	}
	~Student() { cout << "SDestructor:\t" << endl; }
	 //   methods
	void print()const
	{
		Human::print();
		cout << speciality << " " << group << " " << rating << " " << attendance << endl;
	}
};

class Teacher:public Human
{
	std::string speciality;
	unsigned int experiance;
public:
	const std::string& get_speciality()const { return speciality; }
	unsigned int get_experiance()const {	return experiance;	}
	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_experiance(unsigned int experiance ) { this->experiance = experiance; }
	 //  Constructors
	Teacher
	(
		HUMAN_TAKE_PARAMETRS,
		const std::string& speciality, unsigned int experiance
	) : Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experiance(experiance);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher() { cout << "TDestructor:\t" << endl; }

	//  Methods
	void print()const
	{
		Human::print();
		cout << speciality << " " << experiance << endl;
	}
};
class Graduate :public Student
{
	std::string thesis_topic;
public:
	const std::string& get_thesis_topic()const { return thesis_topic; }
	void set_thesis_topic(const std::string& thesis_topic) { this->thesis_topic = thesis_topic;	}

	 // Constructors
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, const std::string& thesis_topic) :Student(HUMAN_GIVE_PARMETRS,STUDENT_GIVE_PARAMETRS)
	{
		set_thesis_topic(thesis_topic);
		cout << "GConstructor\t" << this << endl;
	}
	~Graduate() { cout << "GDestructor:\t" << endl; }

	     // Methods
	void print()const
	{
		Student::print();
		cout << thesis_topic << endl;
	}
};


void main()
{
	setlocale(LC_ALL, "");
	Human human("Montana", "Antonio", 25);
	human.print();
	cout << delimetr << endl;
	Student  stud("Pinkman", "Jessy", 25, "Chemistry", "WW_220", 90, 95);
	stud.print();
	cout << delimetr << endl;
	Teacher Professor("White", "Walter", 50, "Chemistry", 20);
	Professor.print();
	cout << delimetr << endl;
	Graduate grad("Pinkman", "Jessy", 25, "Chemistry", "WW_220", 90, 95, "Investigation of gas hydrates obtained from emulsions water / decan, water/ oil");
	grad.print();
}