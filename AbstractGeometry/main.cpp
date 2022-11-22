#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE
	};

	class Shape
	{
	protected:
		Color color;
	public:
		Shape(Color color) :color(color) {}
		virtual ~Shape() {}
		virtual double area()const = 0;
		virtual double perimetr()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры:" << area() << endl;
			cout << "Периметр фигуры:" << perimetr() << endl;
			draw();
		}
	};
	class Square :public Shape
	{
		double side;
	public:
		double get_side()const { return side; }
		void set_side(double side)
		{
			if (side < 5)side = 5;
			if (side > 20)side = 20;
			this->side = side;
		}
		// Constructors
		Square(double side, Color color) :Shape(color)
		{
			set_side(side);
		}
		~Square() {}
		double area()const override { return side * side; }
		double perimetr()const override { return side * 4; }
		void draw()const override
		{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата:" << side << endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width < 8)width = 8;
			if (width > 30)width = 30;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 3)length = 3;
			if (length > 20)length = 20;
			this->length = length;
		}
		//Constructors
		Rectangle(double width, double length, Color color) :Shape(color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double area()const override
		{
			return width * length;
		}
		double perimetr()const override
		{
			return (width + length) * 2;
		}
		void draw()const override 
		{
		/*	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/
			//Получаем окно консоли
			HWND hwnd = GetConsoleWindow();
			//2) Получаем контекст устройства для окна консоли
			HDC hdc = GetDC(hwnd);//Это то чем мы будем рисовать
			//3)Создаем карандаш-это то чем будем рисовать(карандаш рисует линии)
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			//4)Создаем кисть.Кисть рисует заливку в замкнутой сфере
			HBRUSH hBrush = CreateSolidBrush(color);
			//5)Выбираем чем и на чем мы будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) Рисуем прямоугольник
			::Rectangle(hdc, 100, 200, 300, 400);
			//удаляем карандаш
			DeleteObject(hPen);
			DeleteObject(hBrush);
			//Освобождаем контекст устройства
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина  прямоугольника:" << width << endl;
			cout << "Длина  прямоугольника:" << length << endl;
			Shape::info();
		}

	};
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const{return radius;	}
		void set_radius(double radius)
		{
			if (radius < 5)radius = 5;
			if (radius > 20)radius = 20;
			this->radius = radius;
		}
		Circle(double radius, Color color) :Shape(color)
		{
			set_radius(radius);
		}
		~Circle() {};
		double area()const override { return 3.14 * radius * radius; }
		double perimetr()const override { return 2 * 3.14 * radius; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, 1, color);
			HBRUSH hbrush = CreateSolidBrush(color);
			SelectObject(hdc, hpen);
			SelectObject(hdc, hbrush);
			Ellipse(hdc, 310, 200, 410, 300);
			DeleteObject(hpen);
			DeleteObject(hbrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "радиус круга:" << radius << endl;
			Shape::info();
		}
	};
	class Triangle :public Shape
	{
		double a;
		double b;
		double c;
	public:
		double get_a()const { return a; }
		double get_b()const { return b; }
		double get_c()const { return c; }
		void set_a(double a)
		{
			if (a < 2)a = 2;
			if (a > 20)a = 20;
			this->a = a;
		}
		void set_b(double b)
		{
			if (b < 2)b = 2;
			if (b > 20)b = 20;
			this->b = b;
		}
		void set_c(double c)
		{
			if (c < 2)c = 2;
			if (c > 20)c = 20;
			this->c = c;
		}
		
		Triangle(double a, double b, double c,Color color):Shape(color)
		{
			set_a(a);
			set_b(b);
			set_c(c);
		}
		~Triangle() {};
		double area()const override
		{
			double p = (a + b + c) / 2;
			return sqrt(p*(p - a)*(p - b)*(p - c));
		}
		double perimetr()const override { return a + b + c; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hpen = CreatePen(PS_SOLID, 1, color);
			HBRUSH hbrush = CreateSolidBrush(color);
			SelectObject(hdc, hpen);
			SelectObject(hdc, hbrush);
			int POINT[] = new int{2,3};
			Polygon(hdc,POINT,3);
			DeleteObject(hpen);
			DeleteObject(hbrush);
			ReleaseDC(hwnd, hdc);
		}
	};
}


void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry:: Square square(8,Geometry:: Color::console_red);
	square.info();

	Geometry::Rectangle rect(15, 7,Geometry::Color::console_yellow);
	rect.info();

	Geometry::Circle cir(5.3, Geometry::Color::console_blue);
	cir.info();
}