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

	//��� ���� ����� �������� ������ ������ Complex �� ������� ������������� � ���������
	//� ����������� ��� ���������� ��������� ���������� 82 � 89 �������
	friend class Vector2D;

	Complex(int _re = 0, int _im = 0)
	{
		re = _re;
		im = _im;
	}
	
	//���������� ��� ������������� ����������(++)/����������(--)
	Complex(const Complex& obj)
	{
		this->re = obj.re;
		this->im = obj.im;
	}

	// ��� ������������
	friend ostream& operator<<(ostream& out, const Complex& obj);

	//��� �������� 1
	friend Complex& operator+ (Complex& obj1, Complex& obj2);
	Complex& operator--() 
	{
		--re;
		--im;
		return *this;
	}

	//��� �������� 2
	Complex& operator- (Complex& obj)
	{
		this->re = this->re - obj.re;
		this->im = this->im - obj.im;
		return *this;
	}
	//---------------------------------------+
	//                                       | ��� ���������
	//                                       V
	friend Complex operator++(Complex& obj, int);
	//           ^
	//           | �������� & ����� ���!
	//-----------+

	//��� �������� 3
	Complex& operator++()
	{
		++re;
		++im;
		return *this;
	}
	//������������� ������� ��� + ���� ��������� ����, ������� ���:
	//friend Complex& operator+ (Complex& obj1, Complex& obj2);
};

class Vector2D : public Complex {
public:
	Vector2D(int _re = 0, int _im = 0) : Complex(_re, _im) {};

	//���������� ��� ���� ���������
	//���������� ��������� ���������� ��� Vector2D � Complex
	//��� ���� ����� �������� ���������� ����: v3 = v1 + v2
	//����� ����� ����������� ������ ������ Complex
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

//��� �������� 1,3
Complex& operator+ (Complex& obj1, Complex& obj2) {
	obj1.re = obj1.re + obj2.re;
	obj1.im = obj1.im + obj2.im;
	return obj1;
}

//��� �������� 2
Complex operator++(Complex& obj, int)
{
	Complex temp(obj);
	obj.re++;
	obj.im++;
	return temp;
}

// ��� ������������
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