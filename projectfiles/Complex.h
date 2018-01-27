#pragma once
#include <iostream>
#include <string>


using namespace std;

class CComplex
{
public:
	double R;
	double I;
	CComplex();
	~CComplex();
	CComplex(double r , double i);
	CComplex(string s);
	CComplex(CComplex& C);
	void copy(CComplex& C);
	string getString();
	double magnitude();
	double angle();
	void negative();
	double real();
	double imaginary();
	static CComplex addComplex(CComplex& A, CComplex& B);
	void add(CComplex& C);
	CComplex operator=(CComplex& C);
	CComplex operator=(double D);
	void operator+=(CComplex& C);
	void operator+=(double D);
	CComplex operator+(CComplex& C);
	CComplex operator+(double D);
	CComplex operator-(); //Negative
	operator const string(); //Cast
	friend istream& operator >> (istream &is, CComplex& C); //Stream
	friend ostream& operator << (ostream &os, CComplex& C); //Stream
	CComplex operator++(); //Pre Increment
	CComplex operator++(int); //Post Increment, int is not used
	double operator[](string name); //Index
	double operator()(string name, string info = ""); //Argument
//	CComplex operator*(CComplex& A, CComplex& B);
	static CComplex mulComplex(CComplex& A, CComplex& B);
	void mul(CComplex& C);
	void operator*=(CComplex& C);
	void operator*=(double D);
	CComplex operator*(CComplex& C);
	CComplex operator*(double D);
	static CComplex subComplex(CComplex& A, CComplex& B);
	void sub(CComplex& C);
	void operator-=(CComplex& C);
	void operator-=(double D);
	CComplex operator-(CComplex& C);
	CComplex operator-(double D);
	static CComplex divComplex(CComplex& A, CComplex& B);
	void div(CComplex& C);
	void operator/=(CComplex& C);
	void operator/=(double D);
	CComplex operator/(CComplex& C);
	CComplex operator/(double D);




};

