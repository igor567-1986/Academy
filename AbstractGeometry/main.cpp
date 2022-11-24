#define _USE_MATH_DEFINES
#include<iostream>
#include<Windows.h>
using namespace std;

namespace Geometry
{
	enum Color
	{
		red=0x000000FF,
		green =0x0000FF00,
		blue=0x00FF0000,
		yellow=0x0000BBFF,
		white=0x00FFFFFF,
		grey=0x00AAAAAA,

		console_default = 0x07,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_yellow = 0xEE
	};

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_widht;
		Color color;

	public:
		unsigned int get_start_x()const { return start_x; }
		unsigned int get_start_y()const { return start_y; }
		unsigned int get_start_get_line()const { return line_widht; }
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 800)start_x = 800;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 500)start_y = 500;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_widht)
		{
			if (line_widht > 30)line_widht = 30;
			this->line_widht = line_widht;
		}
		Shape(unsigned int start_x,unsigned int start_y,unsigned int line_widht,Color color) :color(color) 
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_widht);
		}
		
		virtual ~Shape() {}
		virtual double get_area()const = 0;
		virtual double get_perimetr()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры:" << get_area() << endl;
			cout << "Периметр фигуры:" << get_perimetr() << endl;
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
			if (side > 200)side = 200;
			this->side = side;
		}
		// Constructors
		Square(double side,unsigned int start_x,unsigned int start_y, unsigned int line_widht, Color color)
			:Shape(start_x,start_y,line_widht, color)
		{
			set_side(side);
		}
		~Square() {}
		double get_area()const override { return side * side; }
		double get_perimetr()const override { return side * 4; }
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
			if (width < 30)width = 30;
			if (width > 300)width = 300;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < 20)length = 20;
			if (length > 200)length = 200;
			this->length = length;
		}
		//Constructors
		Rectangle(double width, double length, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Shape(start_x,start_y,line_widht, color)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}
		double get_area()const override
		{
			return width * length;
		}
		double get_perimetr()const override
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
			HPEN hPen = CreatePen(PS_SOLID, line_widht, color);
			//4)Создаем кисть.Кисть рисует заливку в замкнутой сфере
			HBRUSH hBrush = CreateSolidBrush(color);
			//5)Выбираем чем и на чем мы будем рисовать
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//6) Рисуем прямоугольник
			::Rectangle(hdc, start_x,start_y, start_x+width,start_y+length);
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
			if (radius < 20)radius = 20;
			if (radius > 220)radius = 220;
			this->radius = radius;
		}
		Circle(double radius, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Shape(start_x,start_y,line_widht, color)
		{
			set_radius(radius);
		}
		~Circle() {};
		double get_area()const override { return M_PI * radius * radius; }
		double get_perimetr()const override { return 2 * M_PI * radius; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_widht, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Ellipse(hdc, start_x, start_y, start_x+radius*2,start_y+radius*2);
			DeleteObject(hPen);
			DeleteObject(hBrush);
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
	public:
		/*double get_a()const { return a; }
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
		}*/
		Triangle(unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Shape(start_x, start_y, line_widht, color){}
		 virtual double get_height()const = 0;
		 void info()const 
		 {
			 cout << "Height:\t" << get_height() << endl;
			 Shape::info();
		 }
		//Triangle(double a, double b, double c, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
		//	:Shape(start_x,start_y,line_widht, color)
		//{
		//	set_a(a);
		//	set_b(b);
		//	set_c(c);
		//}
		//~Triangle() {};
		//double area()const override
		//{
		//	double p = (a + b + c) / 2;
		//	return sqrt(p*(p - a)*(p - b)*(p - c));
		//}
		//double perimetr()const override { return a + b + c; }
		//void draw()const override
		//{
		//	HWND hwnd = GetConsoleWindow();
		//	HDC hdc = GetDC(hwnd);
		//	HPEN hpen = CreatePen(PS_SOLID, 1, color);
		//	HBRUSH hbrush = CreateSolidBrush(color);
		//	SelectObject(hdc, hpen);
		//	SelectObject(hdc, hbrush);
		//	
		//	//Polygon(hdc,POINT,3);
		//	DeleteObject(hpen);
		//	DeleteObject(hbrush);
		//	ReleaseDC(hwnd, hdc);
		//}
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const { return side; }
		void set_side(double side)
		{
			if (side < 20)side = 20;
			if (side > 200)side = 200;
			this->side = side;
		}
		EquilateralTriangle(double side, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Triangle(start_x, start_y, line_widht, color)
		{
			set_side(side);
		}
		~EquilateralTriangle(){}
		double get_height()const override
		{
			return 2 * get_area() / side;
		}
		double get_area()const override { return side * side * sqrt(3) / 4; }
		double get_perimetr()const override { return side * 3; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_widht, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			POINT vert[] =
			{
				{start_x,start_y + side},
				{start_x + side,start_y + side},
				{start_x + side / 2,start_y + side - get_height()}

			};
			Polygon(hdc, vert, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const 
		{
			cout << typeid(*this).name() << endl;
			cout << "Side:\t" << side << endl;
			Triangle::info();
		}
	};
	class IsoscelesTriangle :public Triangle
	{
		double side;
		double footing;
	public:
		double get_side()const { return side; }
		double get_footing()const { return footing; }
		void set_footing(double footing)
		{
			if (footing < 20)footing = 20;
			if (footing > 400)footing = 400;
			this->footing = footing;
		}
		void set_side(double side)
		{
			if (side < footing / 2)cout << "Eror:Такой треугольник не существует." << endl;
			if (side < 20)side = 20;
			if (side > 300)side = 300;
			this->side = side;
		}
		IsoscelesTriangle(double side, double footing, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Triangle(start_x, start_y, line_widht, color)
		{
			set_side(side);
			set_footing(footing);
		}
		~IsoscelesTriangle(){}
		double get_height()const override
		{
			return sqrt((side * side) - (footing * footing) / 4);
		}
		double get_area()const override
		{
			return get_height() * footing / 2;
		}
		double get_perimetr()const override
		{
			return side * 2 + footing;
		}
		void draw()const override
		{
			if (side <footing/2)return ;
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_widht, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc,hPen );
			SelectObject(hdc, hBrush);
			POINT vert[] =
			{
				{start_x,start_y + side},
				{start_x + footing,start_y + side},
				{start_x + footing / 2,start_y + side - get_height()}
			};
			Polygon(hdc, vert, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Side:" << side << endl;
			cout << "Footing" << footing << endl;
			Triangle::info();
		}
	};
	class RightTriangle :public Triangle
	{
		double cathetA;
		double cathetB;
		double hypotenuse;
	public:
		double get_cathetA()const    { return cathetA; }
		double get_cathetB()const    { return cathetB; }
		double get_hypotenuse()const { return hypotenuse; }
		void set_cathetA(double cathetA)
		{
			if (cathetA < 20)cathetA = 20;
			if (cathetA < 400)cathetA = 400;
			this->cathetA = cathetA;
		}
		void set_cathetB(double cathetB)
		{
			if (cathetB < 20)cathetB = 20;
			if (cathetB < 400)cathetB = 400;
			this->cathetB = cathetB;
		}
		void set_hypotenuse()
		{
			double hypotenuse;
			hypotenuse = sqrt((get_cathetA() * get_cathetA()) + (get_cathetB() + get_cathetB()));
			this->hypotenuse = hypotenuse;
		}
		RightTriangle(double cathetA, double cathetB, unsigned int start_x, unsigned int start_y, unsigned int line_widht, Color color)
			:Triangle(start_x, start_y, line_widht, color)
		{
			set_cathetA(cathetA);
			set_cathetB(cathetB);
			set_hypotenuse();
		}
		~RightTriangle(){}
		double get_height()const override   { return cathetA * cathetB / hypotenuse; }
		double get_area()const override	    { return(hypotenuse * get_height()) / 2; }
		double get_perimetr()const override	{ return cathetA + cathetB + hypotenuse; }
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_widht, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc,hPen);
			SelectObject(hdc,hBrush);
			POINT vert[] =
			{
				{start_x,start_y+cathetA},
				{start_x+cathetB,start_x+cathetA},
				{start_x,start_y+cathetA-get_height()}
			};
			Polygon(hdc, vert, 3);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "cathetA:" << cathetA << endl;
			cout << "cathetB:" << cathetB << endl;
			cout << "hypotenuse:" << hypotenuse << endl;
			Triangle::info();
		}
	};
}


void main()
{
	setlocale(LC_ALL, "");
	//Shape shape;
	Geometry:: Square square(8,100,100,11,Geometry:: Color::console_red);
	square.info();

	Geometry::Rectangle rect(150, 70,300,100,11,Geometry::Color::grey);
	rect.info();

	Geometry::Circle cir(100,500,100,11, Geometry::Color::yellow);
	cir.info();

	Geometry::EquilateralTriangle e_try(70, 300, 300, 2, Geometry::Color::green);
	e_try.info();

	Geometry::IsoscelesTriangle i_try(150, 240, 400, 400, 2, Geometry::Color::white);
	i_try.info();

	Geometry::RightTriangle r_try(180, 150, 350, 450, 2, Geometry::Color::red);
	r_try.info();
}