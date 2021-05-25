#include <iostream>
using namespace std;
class Complex {
private:

	int re;
	int im;

protected:

	int getRe() { return re; };
	int getIm() { return im; };

	void setRe(int _re) { re = _re; };
	void setIm(int _im) { im = _im; };

public:

	//Для того чтобы вызывать методы класса Complex из объекта передоваемого в агрументы
	//Я использовал для перегрузки оперторов присвоения 82 и 89 строчка
	friend class Vector2D;

	Complex(int _re = 0, int _im = 0)
	{
		re = _re;
		im = _im;
	}
	
	//Обязателен для постфикстного инкремента(++)/декремента(--)
	Complex(const Complex& obj)
	{
		this->re = obj.re;
		this->im = obj.im;
	}

	// Для демонстрации
	friend ostream& operator<<(ostream& out, const Complex& obj);

	//Для варианта 1
	friend Complex& operator+ (Complex& obj1, Complex& obj2);
	Complex& operator--() 
	{
		--re;
		--im;
		return *this;
	}

	//Для варианта 2
	Complex& operator- (Complex& obj)
	{
		this->re = this->re - obj.re;
		this->im = this->im - obj.im;
		return *this;
	}
	//---------------------------------------+
	//                                       | Для постфикса
	//                                       V
	friend Complex operator++(Complex& obj, int);
	//           ^
	//           | ВНИМЕНИЕ & ЗДЕСЬ НЕТ!
	//-----------+

	//Для варианта 3
	Complex& operator++()
	{
		++re;
		++im;
		return *this;
	}
	//Дружественная функция для + была объявлена выше, поэтому так:
	//friend Complex& operator+ (Complex& obj1, Complex& obj2);
};

class Vector2D : public Complex {
public:
	Vector2D(int _re = 0, int _im = 0) : Complex(_re, _im) {};

	//Обязателен для всех вариантов
	//Перегрузка оператора присвоения для Vector2D и Complex
	//для того чтобы работало присвоение типа: v3 = v1 + v2
	//иначе будет вовращаться объект класса Complex
	Vector2D& operator= (Vector2D& obj)
	{
		this->setRe(obj.getRe());
		this->setIm(obj.getIm());
		return *this;
	}

	Vector2D& operator= (Complex& obj)
	{
		this->setRe(obj.getRe());
		this->setIm(obj.getIm());
		return *this;
	}
};

//Для варианта 1,3
Complex& operator+ (Complex& obj1, Complex& obj2) {
	obj1.re = obj1.re + obj2.re;
	obj1.im = obj1.im + obj2.im;
	return obj1;
}

//Для варианта 2
Complex operator++(Complex& obj, int)
{
	Complex temp(obj);
	obj.re++;
	obj.im++;
	return temp;
}

// Для демонстрации
ostream& operator<<(ostream& out, const Complex& obj)
{
	out << obj.re << ((obj.im >= 0) ? "+" : "-") << obj.im << "i";
	return out;
}

int main()
{
	Vector2D v1(1, 1);
	Vector2D v2(2, 2);
	Vector2D v3(8, 8);
	
	v3 = v1 + v2;

	cout << v3;
}