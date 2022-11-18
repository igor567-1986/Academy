#include<iostream>
#include<string>
#include<fstream>

using namespace std;

#define delimetr "\n-------------------------------------\n"

#define HUMAN_TAKE_PARAMETRS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARMETRS last_name,first_name,age


class Human
{
	static const int FULL_NAME_LEHGTH=20;
	static const int AGE_LENGTH = 5;
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
	virtual ~Human() { cout << "Hdestructor\t" << this << endl; }
	     //Methods
	virtual std::ostream& print(std::ostream& os)const
	{
		return os<< last_name << " " << first_name << " " << age << "лет.";
	}
	virtual std::ofstream& print(std::ofstream& ofs)const
	{
		//ofs << last_name << " " << first_name << " " << age;
		ofs.width(FULL_NAME_LEHGTH);
		ofs << std::left;
		ofs << last_name + " " + first_name;
		ofs.width(AGE_LENGTH);
		ofs << std::right;
		ofs << age;
		return ofs;
	}
	virtual std::ifstream& scan(std::ifstream& ifs)
	{
		ifs >> last_name >> first_name >> age;
		return ifs;
	}
};
std::ostream& operator<<(std::ostream& os, const Human& obj) 
{	
	return obj.print(os);
}
std::ofstream& operator<<(std::ofstream& ofs, const Human& obj)
{
	return obj.print(ofs);
}
std::ifstream& operator>> (std::ifstream& ifs,  Human& obj)
{
	return obj.scan(ifs);
}

#define STUDENT_TAKE_PARAMETRS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETRS speciality,group,rating,attendance

class Student:public Human
{
	static const int SPECIALTY_LENGHT=25;
	static const int GROUP_LENGTH = 10;
	static const int RATING_LENGHT = 8;
	static const int ATTENDENCE_LENGTH = 8;
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
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os)<<", " << speciality << " " << group << " " << rating << " " << attendance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs)<<" ";
		ofs.width(SPECIALTY_LENGHT);
		ofs << std::left;
		ofs << speciality;
		ofs.width(GROUP_LENGTH);
		ofs << group; 
		ofs.width(RATING_LENGHT);
		ofs << std::right;
		ofs << rating; 
		ofs.width(ATTENDENCE_LENGTH);
		ofs	<< attendance;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		const int SIZE = SPECIALTY_LENGHT;
		char buffer[SIZE]{};
		ifs.read(buffer,SIZE-1);
		for (int i = SIZE - 2; buffer[i] == ' '; i--)buffer[i] = 0;
		while (buffer[0] == ' ')
		{
			for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1];
		}
		speciality = buffer;
		ifs >> group;
		ifs >> rating;
		ifs >> attendance;
		return ifs;
	}
};

class Teacher:public Human
{
	static const int SPECIALTY_LENGTH = 25;
	static const int EXPERIANCE_LENGTH = 7;
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
	std::ostream& print(std::ostream& os)const override
	{
		return Human::print(os)<<" " << speciality << " " << experiance;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Human::print(ofs) << " ";
		ofs.width(SPECIALTY_LENGTH);
		ofs << std::left;
		ofs << speciality;
		ofs.width(EXPERIANCE_LENGTH);
		ofs << right;
		ofs << experiance;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Human::scan(ifs);
		const int SIZE = SPECIALTY_LENGTH;
		char buffer[SIZE]{};
		ifs.read(buffer, SIZE-1);
		for (int i = SIZE - 2; buffer[i] == ' '; i--)buffer[i] = 0;
		while (buffer[0] == ' ')
		{
			for (int i = 0; buffer[i]; i++)buffer[i] = buffer[i + 1];
		}
		speciality = buffer;
		ifs >> experiance;
		return ifs;
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
	std::ostream&  print(std::ostream& os)const override
	{
		return Student::print(os)<<", " << "Тема дипломного проекта:" << thesis_topic;
	}
	std::ofstream& print(std::ofstream& ofs)const override
	{
		Student::print(ofs) << " "<< thesis_topic;
		return ofs;
	}
	std::ifstream& scan(std::ifstream& ifs)override
	{
		Student::scan(ifs);
		std::getline(ifs, thesis_topic);
		return ifs;
	}
};

Human* HumanFactory(const std::string& type)
{
	// Этот метод создает обьекты в динамической памяти
	if (type.find("Student") != std::string::npos)return new Student("", "", 0, "", "", 0, 0);
	if (type.find("Graduate") != std::string::npos)return new Graduate("", "", 0, "", "", 0, 0, "");
	if (type.find("Teacher") != std::string::npos)return new Teacher("", "", 0, "", 0);
}

void print( Human* group[], const int n)
{
	for (int i = 0; i < n; i++)	{cout << *group[i] << endl;	}
}
void save( Human* group[],const int n ,const std::string& falename)
{
	std::ofstream fout(falename);
	for (int i = 0; i < n ; i++)
	{
		fout.width(15);
		fout << std::left;
		fout << typeid(*group[i]).name() << ":\t";
		fout << *group[i] << endl;	
	}
	fout.close();
	std::string command = "notepad " + falename;
	system(command.c_str());
}
Human** load(const std::string& filename, int& n)
{
	std::ifstream fin(filename);
	//1) Вычисляем размер массива
	if (fin.is_open())
	{
		std::string buffer;
		for (n=0;!fin.eof();n++)
		{
			std::getline(fin, buffer);
		}
		n--;
	}
	//2)Выделяем память под массив
	Human** group = new Human*[n] {};
	//3) Возвращаемся в начало файла для того чтобы прочитать строки,изагрузить их в обьекты
	fin.clear();
	fin.seekg(0);

	//4) Загружаем обьекты из файла:
	if (fin.is_open())
	{
		std::string type;
		for (int i = 0; i < n; i++)
		{
			std::getline(fin, type,':');
			//cout << buffer << endl;
			group[i] = HumanFactory(type);
			fin >> *group[i];
		}
	}
	return group;
}

 //#define INHERITANCE

void main()
{
	setlocale(LC_ALL, "");
#ifdef INHERITANCE
	Human human("Montana", "Antonio", 25);
	human.print();
	cout << delimetr << endl;
	Student  stud("Pinkman", "Jessy", 25, "Chemistry", "WW_220", 90, 95);
	stud.print();
	cout << delimetr << endl;
	Teacher Professor("White", "Walter", 50, "Chemistry", 20);
	Professor.print();
	cout << delimetr << endl;
	Graduate grad("Shreder", "Jessy", 25, "Chemistry", "WW_220", 90, 95, "Investigation of gas hydrates obtained from emulsions water / decan, water/ oil");
	grad.print();
#endif // INHERITANCE

	//std::ofstream fout;
	//fout.open("File.txt");//,std::ios::app);
	//fout << ("new Student(\"Pinkman\", \"Jessy\", 25, \"Chemistry\", \"WW_220\", 90, 95\),\n")
	//	<< ("new Teacher(\"White\", \"Walter\", 50, \"Chemistry\", 20),\n")
	//	<< ("new Graduate(\"Shreder\", \"Jessy\", 25, \"Chemistry\", \"WW_220\", 90, 95, \"Investigation of gas hydrates obtained from emulsions water / decan, water/ oil\"),\n")
	//	<< ("new Student(\"Vercetti\", \"Tomas\", 30, \"Crminalistic\", \"Vice\", 90, 93),\n")
	//	<< ("new Teacher(\"Diaz\", \"Ricardo\", 50, \"Weapon distribution\", 15),\n")
	//	<< ("new Teacher(\"Enstein\", \"Albert\", 143, \"Astronomy\", 120)\n") << endl;
	//const int SIZE = 1024;
	//char buffer[SIZE] = {};
	//ifstream fin("File.txt");
	//if (fin.is_open())
	//{
	//	while (!fin.eof())
	//	{
	//		//fin >> buffer;
	//		fin.getline(buffer, SIZE);
	//		cout << buffer << endl;
	//	}
	//	fin.close();
	//}
	//else
	//{
	//	std::cerr << "Eror:file not found" << endl;
	//}


	      // Polymorphism
	
	/*Human* group[] =
	{
		new Student("Pinkman", "Jessy", 25, "Chemistry", "WW_220", 90, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 20),
		new Graduate("Shreder", "Jessy", 25, "Chemistry", "WW_220", 90, 95, "Investigation of gas hydrates obtained from emulsions water / decan, water/ oil"),
		new Student("Vercetti","Tomas",30,"Crminalistic","Vice",90,93),
		new Teacher("Diaz","Ricardo",50,"Weapon distribution",15),
		new Teacher("Enstein","Albert",143,"Astronomy",120)
	};*/
	//print(group, sizeof(group) / sizeof(group[0]));
	//save(group, sizeof(group) / sizeof(group[0]),"group.txt");
	//for (int i = 0; i < sizeof(group) / sizeof(Human*); i++)
	//{
	//	cout << *group[i] << endl;
	//	cout << delimetr << endl;
	//}

	int n= 0;
	Human** group = load("Group.txt", n);
	print(group, n);
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}

}