#include "Complex.h"
#define PI 3.14159

CComplex::CComplex()
{
	R = 0.0;
	I = 0.0;
}


CComplex::~CComplex()
{
	R = 0.0;
	I = 0.0;
}


CComplex::CComplex(double r , double i)
{
	this->R = r;
	this->I = i;
}



CComplex::CComplex(string s)
{
	R=0.0,I=0.0;
	int n=0;
	int flag1=0,flag2=0,flag3=0;
	if(s[0]=='-')
		flag1=1;
	for(int j=1;j<s.length();j++)
	{
		if(s[j]=='-')
			flag2=1;
	}
	for(int j=0;j<s.length();j++)
	{
		if(s[j]=='i')
			flag3=1;
	}
	char* buffer = new char[s.length()+1];
	strcpy(buffer, s.c_str());
	char* lineContext;
	char* lineSeparators = " -+iI";
	char* line = strtok_s(buffer, lineSeparators, &lineContext);
	while(line)
	{
		if(n==0)
		{
			if(flag3==0||(flag3==1&&strlen(lineContext) != 0))
			{
				R=atof(line);
				I=0;
				if (flag1==1)
					R=-R;
			}
			else if(flag3==1&&strlen(lineContext) == 0)
			{
				R = 0;
				I=atof(line);
				if (flag1==1)
					I=-I;
			}
		}
		
		else if (n==1)
		{
			I=atof(line);
			if (flag2==1)
				I=-I;
		}
		n++;
		line = strtok_s(NULL, lineSeparators, &lineContext);
	}
}




CComplex::CComplex(CComplex& C)
{
copy(C);
}



void CComplex::copy(CComplex& C)
{
R = C.R; I = C.I;
} 



string CComplex::getString()
{
char text[100];
if(I==0)sprintf(text, "%g", R);
else if(R==0)sprintf(text, "%g * i", I);
else if(I>0)sprintf(text, "%g + %g * i", R, I);
else if(I<0)sprintf(text, "%g - %g * i", R, -I);
return string(text);
}


double CComplex::magnitude()
{
return sqrt(R*R+I*I);
}


double CComplex::angle()
{
return atan2(I, R);
}


void CComplex::negative()
{
R*=-1; I*=-1;
} 


double CComplex::real()
{
return R;
} 


double CComplex::imaginary()
{
return I;
} 



CComplex CComplex::addComplex(CComplex& A, CComplex& B)
{
CComplex C;
C.R = A.R + B.R;
C.I = A.I + B.I;
return C;
}


void CComplex::add(CComplex& C)
{
R += C.R;
I += C.I;
}


CComplex CComplex::operator=(CComplex& C)
{
copy(C);
return *this;
} 


CComplex CComplex::operator=(double D)
{
R = D; I = 0;
return *this;
} 


void CComplex::operator+=(CComplex& C)
{
add(C);
} 


void CComplex::operator+=(double D)
{
R += D;
} 


CComplex CComplex::operator+(CComplex& C)
{
return addComplex(*this, C);
} 


CComplex CComplex::operator+(double D)
{
return addComplex(*this, CComplex(D, 0));
}



CComplex CComplex::operator-()
{
return CComplex(-R, -I);
} 


CComplex::operator const string()
{
return getString();
} 


istream& operator >> (istream& is, CComplex& C)
{
is>>C.R;
is>>C.I;
return is;
} 


ostream& operator << (ostream& os, CComplex& C)
{
os<<C.getString();
return os;
}



CComplex CComplex::operator++()
{
R++;
return *this;
} 


CComplex CComplex::operator++(int)
{
CComplex C = *this;
R+=1;
return C;
} 

double CComplex::operator[](string name)
{
if(name=="magnitude")return magnitude();
if(name=="angle")return angle();
if(name=="real")return real();
if(name=="imaginary")return imaginary();
return 0.0;
} 


double CComplex::operator()(string name, string info)
{
if(name=="angle")
{
if(info=="degree")return angle()*180.0/PI;
if(info=="radian" || info.length()==0)return angle();
} 
return (*this)[name];
}



/*
CComplex CComplex::operator*(CComplex& A, CComplex& B)
{
double R = A.real()*B.real() - A.imaginary()*B.imaginary();
double I = A.real()*B.imaginary() + A.imaginary()*B.real();
return CComplex(R, I);
}
*/


CComplex CComplex::mulComplex(CComplex& A, CComplex& B)
{
CComplex C;
C.R = A.real()*B.real() - A.imaginary()*B.imaginary();
C.I = A.real()*B.imaginary() + A.imaginary()*B.real();
return C;
}
void CComplex::mul(CComplex& C)
{
R = R*C.real() - I*C.imaginary();
I = R*C.imaginary() + I*C.real();
}
void CComplex::operator*=(CComplex& C)
{
	mul(C);
}
void CComplex::operator*=(double D)
{
	R*=D;
	I*=D;
}
CComplex CComplex::operator*(CComplex& C)
{
	return mulComplex(*this, C);
}
CComplex CComplex::operator*(double D)
{
	return subComplex(*this, CComplex(D, 0));
}
CComplex CComplex::subComplex(CComplex& A, CComplex& B)
{
CComplex C;
C.R = A.R - B.R;
C.I = A.I - B.I;
return C;
}
void CComplex::sub(CComplex& C)
{
	R -= C.R;
	I -= C.I;
}
void CComplex::operator-=(CComplex& C)
{
	sub(C);
}
void CComplex::operator-=(double D)
{
	R -= D;
}
CComplex CComplex::operator-(CComplex& C)
{
	return subComplex(*this, C);
}
CComplex CComplex::operator-(double D)
{
	return subComplex(*this, CComplex(D, 0));
}
CComplex CComplex::divComplex(CComplex& A, CComplex& B)
{
double dom=pow(B.real(),2)+pow(B.imaginary(),2);
CComplex C;
C.R=(A.real()*B.real())+(A.imaginary()*(-1*B.imaginary()))/dom;
C.I=(A.imaginary()*B.real())+(A.real()*(-1*B.imaginary()))/dom;
return C;
}
void CComplex::div(CComplex& C)
{
	double dom=pow(C.real(),2)+pow(C.imaginary(),2);
	R=(R*C.real())+(I*(-1*C.imaginary()))/dom;
	I=(I*C.real())+(R*(-1*C.imaginary()))/dom;
}
void CComplex::operator/=(CComplex& C)
{
	div(C);
}
void CComplex::operator/=(double D)
{
	R/=D;
	I/=D;
}
CComplex CComplex::operator/(CComplex& C)
{
	return divComplex(*this, C);
}
CComplex CComplex::operator/(double D)
{
	return divComplex(*this, CComplex(D, 0));
}

