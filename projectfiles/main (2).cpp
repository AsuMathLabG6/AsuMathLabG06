#include <iostream>
#include <stdio.h>
#include "CMatrix.h"
#include "stdarg.h"
#include <algorithm>
#include <math.h>
#include <string>
#include <fstream>
using namespace std;
#define size 100
//enum MI{ MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE };
CMatrix& eye(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,2);
w=temp;
return w;
}
CMatrix& rand(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,3);
w=temp;
return w;
}
CMatrix& zeros(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,0);
w=temp;
return w;
}
CMatrix& ones(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,1);
w=temp;
return w;
}
CMatrix init ;
int num_elements = 0;
char out = 'a';
int my_count = 0;
bool is_found(char c, char*  array_chars);
void reserve(CMatrix* array_matrices, string x , int type =0 , CMatrix& c = init);
void insert_name(char* array_chars, char y);
int get_index(char * array_chars, char operand_name);
string operationg(CMatrix* array_matrices, char* array_chars,char first_operand, string operation, char output,char second_operand,double d1=0,double d2=0);
void check_print (string output, bool is_semicolon);
string choose_type_operation (string line , CMatrix* array_matrices , char* array_chars);
string do_operation_matrices (string line , CMatrix* array_matrices , char* array_chars ) ;
double do_operation_line (string line);
int get_num_ops (string line , string operations);
string excute (string line , string operation , int position_operation);
string handle_excute (string line , string operations ,int no_operations);
int get_num_ops_matrices (string line , string operations []);
string excute_matrices_ops(string line , int no_operations , string * operations , CMatrix* array_matrices , char* array_chars);
string excute_matrix (string line , string op , int pos , CMatrix* array_matrices , char* array_chars );
char trim(string text);
bool is_end(char* text);
void trim (string text , int  type, int& nr ,int& nc );
void MatricesPos(int* openmatrix, int* closematrix,string str,char x ,char y);
int main(int argc, char* argv[])
{
char array_chars [size];
CMatrix* array_matrices = new CMatrix [size] ;

//if (argc == 2)
//{
//argv[1]
ifstream infile("/home/mido/Downloads/advexample.m");
if (!infile.bad())
{
   string get_input , body_matrix , body_math , output ;
   bool open_bracket = false , close_bracket = false , is_semicolon;
   char c;
   int length ;
   while(getline(infile,get_input))
   {
    char* text1 = new char [get_input.length()+1] ;
    strcpy(text1,get_input.c_str());
    if(is_end(text1))
    {
        length = get_input.length();
        open_bracket = (get_input.find("[",0)== -1 ) ? false : true ;
        close_bracket = (get_input.find("]",0)== -1 ) ? false : true ;
        if(!open_bracket&&!close_bracket)
        {
            int index = get_input.find("=",0);
            is_semicolon = (get_input.find(";",0)==-1)? false : true ;
            if(index!=-1)
            {
            c = trim (get_input.substr(0,index));
            insert_name(array_chars, c );
            if(get_input.find("rand",index+1)!=-1||get_input.find("eye",index+1)!=-1||get_input.find("zeros",index+1)!=-1||get_input.find("ones",index+1)!=-1)
            {
                string str2 = get_input.substr(index+1,(length-1)-(index+1));
                int nr , nc ;
                if(get_input.find("rand",index+1)!=-1)
                {
                        trim (str2,1, nr ,nc );
                        reserve(array_matrices,str2,1,rand(nr,nc));
                }else if(get_input.find("eye",index+1)!=-1)
                {
                        trim (str2,2, nr ,nc );
                        reserve(array_matrices,str2,1,eye(nr,nc));
                }else if(get_input.find("zeros",index+1)!=-1)
                {
                        trim (str2,3, nr ,nc );
                        reserve(array_matrices,str2,1,zeros(nr,nc));
                }else if(get_input.find("ones",index+1)!=-1)
                {
                        trim (str2,4, nr ,nc );
                        reserve(array_matrices,str2,1,ones(nr,nc));
                }
                int i = get_index(array_chars,c) ;
                output = array_matrices[i].getString();
                char text2[3];
                sprintf(text2,"%c=\n\n",array_chars[i]);
                check_print (string(text2)+output, is_semicolon);
            }else
            {
            if(!is_semicolon)
            {
                string str1 ;
                str1 = get_input.substr(index+1,(length-1)-index) ;
                double d = atof(choose_type_operation (str1 , array_matrices , array_chars).c_str());
                CMatrix C(1,1,4,d);
                reserve(array_matrices, str1 , 1 ,C);
            }
            else
            {
                string str1 ;
                str1 = get_input.substr(index+1,(get_input.find(";",0)-1)-index) ;
                double d = atof(choose_type_operation (str1 , array_matrices , array_chars).c_str());
                CMatrix C(1,1,4,d);
                reserve(array_matrices, get_input.substr(index+1,(length-1)-index) , 1 ,C);
            }
            int i = get_index(array_chars,c) ;
            output = array_matrices[i].getString();
            char text2[3];
            sprintf(text2,"%c=\n\n",array_chars[i]);
            check_print (string(text2)+" "+output, is_semicolon);
            }
            }else
            {
                c = trim(get_input);
                int i = get_index(array_chars,c) ;
                output = array_matrices[i].getString();
                char text2[3];
                sprintf(text2,"%c=\n\n",array_chars[i]);
                check_print (string(text2)+" "+output, is_semicolon);
            }
        }
    }
    delete []text1;
}
}
infile.close();
//}else
//cout<<"File read failed."<<endl;
return 0;
}
bool is_end(char* text)
{
    bool found_exp = false ;
    for(int i=0;i<strlen(text);i++)
    {
        char c = text[i] ;
       if(c =='='||((c >='A'&&c <='Z')||(c >='a'&&c <='z')))
            found_exp = true;
    }
    return found_exp;
}
char trim(string text)
{
    for(int i=0;i<text.length();i++)
        {
            if(text.substr(i,1)!=" ")
                return text[i] ;
        }
}
void trim (string text , int  type, int& nr ,int& nc )
{
    for(int i=0;i<text.length();i++)
        {
            if(text.substr(i,1)==" ")
                text.erase(i,1);
        }
        switch(type)
        {
            case 1 : nr = atof(text.substr(5,1).c_str());
                     nc = atof(text.substr(7,1).c_str());
                     break ;
            case 2 : nr = atof(text.substr(4,1).c_str());
                     nc = atof(text.substr(6,1).c_str());
                     break ;
            case 3 : nr = atof(text.substr(6,1).c_str());
                     nc = atof(text.substr(8,1).c_str());
                     break ;
            case 4 : nr = atof(text.substr(5,1).c_str());
                     nc = atof(text.substr(7,1).c_str());
                     break ;
            default : nr = 0 ;
                      nc = 0 ;
                      break ;
        }
}
istream& operator >> (istream &is, CMatrix& m)
{
	string s;
	getline(is, s, ']');
	s += "]";
    CMatrix v (s);
	m = v;
	return is;
}
ostream& operator << (ostream &os, CMatrix& m)
{
	os << m.getString();
	return os;
}
//to check if the character is found or not
bool is_found(char c, char*  array_chars)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (c == array_chars[i])
			return false;
	}
	return true;
}
//give this function body of matrix [2 1, 4 5]
void reserve(CMatrix* array_matrices, string x , int type , CMatrix& c )
{
        if(type==0)
		array_matrices[num_elements-1] = x;
		else if(type==1)
		array_matrices[num_elements-1]=c;
		//cout<<array_matrices[num_elements-1];
}
// reserve char in array which is the name of matrices
void insert_name(char* array_chars,char y)
{
	if (num_elements==0)
	{
		array_chars[num_elements] = y;
		num_elements++;
	}
	if (is_found(y,array_chars))
	{
		array_chars[num_elements] = y;
		num_elements++;
	}
}
//array_chars is the dynamic array of characters
int get_index(char * array_chars, char operand_name)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (array_chars[i] == operand_name)
			return i;
	}
}
//array_matrices is the dynamic array of matrices
string operationg(CMatrix* array_matrices, char* array_chars,char first_operand, string operation,char output, char second_operand,double d1,double d2)
{
	int index_first_operand, index_second_operand, index_output;
	index_first_operand = get_index(array_chars, first_operand);
	if(second_operand!=0)
	index_second_operand = get_index(array_chars, second_operand);
	index_output = get_index(array_chars, output);
	string required;

	if(operation=="+")
	{
		array_matrices[index_output] = array_matrices[index_first_operand] + array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
    }else if(operation=="-")
    {
		array_matrices[index_output] = array_matrices[index_first_operand]-array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
    }else if(operation=="*")
    {
		array_matrices[index_output] = array_matrices[index_first_operand]*array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
    }else if(operation=="/")
	{
	try{
		array_matrices[index_output] = array_matrices[index_first_operand]/array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
		}
		catch(string* fault){cout<<*(fault)<<endl;}
    }else if(operation=="'")
	{
		array_matrices[index_output] = array_matrices[index_first_operand].getTranspose();
		required = array_matrices[index_output].getString();
    }else if(operation=="./"&&d2==0)
	{
		array_matrices[index_output] = division_by_element(d1,array_matrices[index_first_operand]);
		required = array_matrices[index_output].getString();
    }else if(operation=="./"&&d1==0)
	{
		array_matrices[index_first_operand] /= d2;
		array_matrices[index_output] = array_matrices[index_first_operand];
		required = array_matrices[index_output].getString();
    }else if(operation==".+")
	{
        array_matrices[index_first_operand]+=d2;
		array_matrices[index_output] = array_matrices[index_first_operand];
		required = array_matrices[index_output].getString();
    }else if(operation=="^")
	{
		array_matrices[index_output] = power_matrix(array_matrices[index_first_operand],int(d2));
		required = array_matrices[index_output].getString();
    }else if(operation==".^")
	{
        array_matrices[index_output] = power_by_element(array_matrices[index_first_operand],d2);
		required = array_matrices[index_output].getString();
    }
	return required;
}
//to check to print or not
void check_print (string output, bool is_semicolon)
{
	if (!is_semicolon)
		cout << output<<endl;

}
 CMatrix& division_by_element(double d,CMatrix& X)
{
    static CMatrix output(X.nR, X.nC);
	for(int i=0;i<X.nR;i++)
    {
        for(int j=0;j<X.nC;j++)
        {
        double d1=d/X.values[i][j];
          output.values[i][j]=d1;
        }
    }
    return output;
}

CMatrix & power_by_element (CMatrix& l , double power)
{
    static CMatrix output(l.nR,l.nC) ;
    for(int i=0;i<l.nR;i++)
    {
        for(int j=0;j<l.nC;j++)
        {
                output.values[i][j] = pow(l.values[i][j],power);
        }
    }
    return output;
}
/*It multplies the matrix by itself n times
where n is the power of the matrix*/
CMatrix & power_matrix(CMatrix &matrix, int number)
{
	if (number <= 0)
		throw("Power must be positive Integer");
	if (number == 1)
		return matrix;
	else
	{
		return matrix * power_matrix(matrix, number - 1);
	}
}
CMatrix & unityMatrix(int num)
{
	static CMatrix temp(num, num, 0);
	for (int i = 0; i < num; i++)
	{
		temp.values[i][i] = 1.0;
	}
	return temp;
}
/* send the matrix as a parameter and it returns back the square root of the matrix which is a matrix too*/
CMatrix & sqrt_matrix(CMatrix &matrix)
{
	if (matrix.nC != matrix.nR)
		throw("Matrix must be square matrix (of equal dimensions)");
	double taw = getTrace(matrix), dtrm = matrix.getDeterminant();
	double s = sqrt(dtrm);
	float t = sqrt(2 * s + taw);
	return (matrix + (unityMatrix(matrix.nR) * s)) * (1.0 / t);
}

float getTrace(CMatrix &mat)
{
	float temp = 0;
	for (int i = 0; i < mat.nR; i++)
	{
		temp += mat.values[i][i];
	}
	return temp;
}
// choose_type_operation is it on matrices or on numbers to handle if the operation will be done on matrices or on numbers and handle case 1x1 matrix
string choose_type_operation (string line , CMatrix* array_matrices , char* array_chars)
{
    string result ;
    int flag1=0 , flag2=0 ;
    for(int i=0 ; i<line.length() ;i++)
    {
    if(line[i]>='A'||line[i]<='Z')
        {
           if(array_matrices[get_index(array_chars,line[i])].getnC()==1&&array_matrices[get_index(array_chars,line[i])].getnR()==1)
           {
                line.replace(i,1,to_string(array_matrices[get_index(array_chars,line[i])].get_values(0,0)));
                flag1 = 1 ;
           }
           else
            flag2 = 1;
        }
    }
    if(!flag1&&flag2||!flag1&&!flag2)
        result = to_string(do_operation_line (line));
    else if(flag1&&!flag2||flag1&&flag2)
        result = do_operation_matrices (line , array_matrices , array_chars );
    return result ;
}
//operations on matrices and get out matrix of the operation
string do_operation_matrices (string line , CMatrix* array_matrices , char* array_chars )
{
    string with_no_space;
    string seperators = " ";
    for(int o=0;o<line.length();o++)
    {
        if(line.substr(o,1)==seperators)
            line.erase(o,1);
    }
    with_no_space = line;
    string c [7] = {"^",".^","/","./","*","+","-"};
    while(with_no_space.find("sin")!=-1)
    {
        CMatrix temp ;
        string rep ;
        int end1 = with_no_space.find(")",with_no_space.find("sin"));
        string inter = with_no_space.substr(with_no_space.find("sin")+4,end1-with_no_space.find("sin")+4);
        if(inter.length()==1&&(inter[1]>='A'||inter[1]<='Z'||inter[1]>='a'||inter[1]<='z'))
           {
            int x = get_index(array_chars,*((const char*)inter.substr(1,1).c_str())) ;
            //temp = sqrt_matrix(array_matrices[x]) ;
            temp = array_matrices[x].sin_matrix();
           }else
           {
           string q = excute_matrices_ops(inter, get_num_ops_matrices (inter,c) , c , array_matrices , array_chars);
           int x = get_index(array_chars,*((const char*)q.substr(1,1).c_str())) ;
            //temp = sqrt_matrix(array_matrices[x]) ;
            temp = array_matrices[x].sin_matrix();
           }
           insert_name(array_chars,char(out+my_count));
           string result = temp.getString();
           rep = char(out+my_count);
           int start = with_no_space.find("sin");
           with_no_space.replace(start,(end1+1-start),rep);
           reserve(array_matrices, result);
           my_count++;
    }
    while(with_no_space.find("sqrt")!=-1)
    {
        CMatrix temp ;
        string rep ;
        int end1 = with_no_space.find(")",with_no_space.find("sqrt"));
        string inter = with_no_space.substr(with_no_space.find("sqrt")+5,end1-with_no_space.find("sqrt")+5);
        if(inter.length()==1&&(inter[1]>='A'||inter[1]<='Z'||inter[1]>='a'||inter[1]<='z'))
           {
            int x = get_index(array_chars,*((const char*)inter.substr(1,1).c_str())) ;
            temp = sqrt_matrix(array_matrices[x]) ;
            //temp = array_matrices[x].sin_matrix();
           }else
           {
           string q = excute_matrices_ops(inter, get_num_ops_matrices (inter,c) , c , array_matrices , array_chars);
           int x = get_index(array_chars,*((const char*)q.substr(1,1).c_str())) ;
           temp = sqrt_matrix(array_matrices[x]) ;
            //temp = array_matrices[x].sin_matrix();
           }
           insert_name(array_chars,char(out+my_count));
           string result = temp.getString();
           rep = char(out+my_count);
           int start = with_no_space.find("sqrt");
           with_no_space.replace(start,(end1+1-start),rep);
           reserve(array_matrices, result);
           my_count++;
    }
    while(with_no_space.find("(")!=-1&&with_no_space.find(")")!=-1)
    {
        int start1 = with_no_space.find("(");
        int end1 = with_no_space.find(")");
        while(with_no_space.find("(",start1+1)!=-1)
        {
        int start2 = with_no_space.find("(",start1+1);
        int end2 = with_no_space.find(")",start2+1);
        if(end2>end1)
            break;
        string internal_line = with_no_space.substr(start2+1,(end2-(start2+1)));
        int no_ops = get_num_ops_matrices(internal_line,c);
        internal_line = excute_matrices_ops(internal_line,no_ops,c, array_matrices , array_chars);
        with_no_space.replace(start2,(end2+1)-start2,internal_line);
        }
        end1 = with_no_space.find(")");
        string internal_line = with_no_space.substr(start1+1,(end1-(start1+1)));
        int no_ops = get_num_ops_matrices(internal_line,c);
        internal_line = excute_matrices_ops(internal_line,no_ops,c, array_matrices , array_chars);
        with_no_space.replace(start1,(end1+1)-start1,internal_line);
    }
    //int len = with_no_space.length();
    int no_operations = get_num_ops_matrices(with_no_space,c);
    with_no_space = excute_matrices_ops(with_no_space,no_operations,c, array_matrices , array_chars);
    string result;
    result = array_matrices[get_index(array_chars,*((const char*)with_no_space.substr(1,1).c_str()))].getString() ;
    return result;
}
// to count no_operations on matrices in one line
int get_num_ops_matrices (string line , string operations [])
{
    int len = line.length();
    int no_operations = 0;
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<7;j++)
        {
            if(line.find(".^",i)==i||line.find("./",i)==i)
            {
                if(line.substr(i,2)== operations[j])
                {
                    no_operations++;
                    i++;
                    break;
                }
            }
            else if(line.substr(i,1)== operations[j])
            {
                no_operations++;
                break;
            }
        }
    }
    return no_operations;
}
//handling operation and excuting them like in math
string excute_matrices_ops(string line , int no_operations , string * operations , CMatrix* array_matrices , char* array_chars)
{
        while(no_operations>0)
    {
            for(int h=0;h<7;h++)
                {
                    for(int i=1;i<line.length();i++)
                        {
                            if(line.find(".^",i)==i||line.find("./",i)==i)
                                {
                                    if(line.substr(i,2)== operations[h])
                                    {
                                        i++;
                                        line = excute_matrix(line,line.substr(i,1),i,array_matrices,array_chars);
                                        no_operations--;
                                    }
                                }
                            else if(line.substr(i,1)== operations[h])
                                {
                                    line = excute_matrix(line,line.substr(i,1),i,array_matrices,array_chars);
                                    no_operations--;
                                }
                        }
                }
    }
        return line ;
}
//test case of operations
string excute_matrix (string line , string op , int pos , CMatrix* array_matrices , char* array_chars )
{
   int pos_begin_op,pos_end_op;
    for(int i=pos-1;i>=0;i--)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-")||i==0)
        {
            pos_begin_op = i+1;
            break;
        }
    }
    for(int i=pos+1;i<line.length();i++)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="."||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-")||i==line.length()-1)
        {
            pos_end_op = i-1;
            break;
        }
    }
    string rep ;
    if(op=="^")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op==".^")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op=="/")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op=="./")
    {
    if(line.substr(pos_begin_op,1).length()==1&&(line[pos_begin_op]>='A'||line[pos_begin_op]<='Z'||line[pos_begin_op]>='a'||line[pos_begin_op]<='z'))
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }
    if(line.substr(pos_end_op,1).length()==1&&(line[pos_end_op]>='A'||line[pos_end_op]<='Z'||line[pos_end_op]>='a'||line[pos_end_op]<='z'))
    {
    char second_operand = line[pos_end_op];
    double d1 = atof(line.substr(pos_begin_op,pos-pos_begin_op).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,second_operand, op , char(out+my_count) , 0 , d1 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }
    }else if(op=="*")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op=="+")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op==".+")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }else if(op=="-")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    reserve(array_matrices, result);
    }
my_count++;
return line ;
}
//to take line like that " 5.5 + 12 * sin(0.4) + 2.2^4 " and get it's output
double do_operation_line (string line)
{
    string with_no_space;
    string seperators = " ";
    for(int o=0;o<line.length();o++)
    {
        if(line.substr(o,1)==seperators)
            line.erase(o,1);
    }
    with_no_space = line;
    string c ="^/*+-";
    while(with_no_space.find("sin")!=-1)
    {
        int end1 = with_no_space.find(")",with_no_space.find("sin"));
        double val = atof(with_no_space.substr(with_no_space.find("sin")+4,end1-with_no_space.find("sin")+4).c_str());
        double res = sin(val);
        int start = with_no_space.find("sin");
        with_no_space.replace (start,(end1+1-start),to_string(res));
    }
    while(with_no_space.find("(")!=-1&&with_no_space.find(")")!=-1)
    {
        int start1 = with_no_space.find("(");
        int end1 = with_no_space.find(")");
        while(with_no_space.find("(",start1+1)!=-1)
        {
        int start2 = with_no_space.find("(",start1+1);
        int end2 = with_no_space.find(")",start2+1);
        if(end2>end1)
            break;
        string internal_line = with_no_space.substr(start2+1,(end2-(start2+1)));
        int no_ops = get_num_ops(internal_line,c);
        internal_line = handle_excute(internal_line,c,no_ops);
        with_no_space.replace(start2,(end2+1)-start2,internal_line);
        }
        end1 = with_no_space.find(")");
        string internal_line = with_no_space.substr(start1+1,(end1-(start1+1)));
        int no_ops = get_num_ops(internal_line,c);
        internal_line = handle_excute(internal_line,c,no_ops);
        with_no_space.replace(start1,(end1+1)-start1,internal_line);
    }
    int len = with_no_space.length();
    int no_operations = get_num_ops(with_no_space,c);
    with_no_space = handle_excute(with_no_space,c,no_operations);
    double result;
    result = atof(with_no_space.c_str());
    return result;
}
//to get no of operations
int get_num_ops (string line , string operations)
{
    int len = line.length();
    int no_operations = 0;
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(line.substr(i,1)== operations.substr(j,1))
            {
                no_operations++;
                break;
            }
        }
    }
    return no_operations;
}
//to get operation excuted as arranged in math
string handle_excute (string line , string operations ,int no_operations)
{
    while(no_operations>0)
    {
            for(int h=0;h<5;h++)
                {
                    for(int i=1;i<line.length();i++)
                        {
                            if(line.substr(i,1)== operations.substr(h,1))
                            {
                                line = excute(line,line.substr(i,1),i);
                                no_operations--;
                            }
                        }
                }
    }
        return line ;
}
//excuting operation and replacing this operation with it's value in string "line".
string excute (string line , string operation , int position_operation)
{
    int pos_begin_op,pos_end_op;
    for(int i=position_operation-1;i>=0;i--)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-")||i==0)
        {
            pos_begin_op = i+1;
            if(i==0||line.substr(i,1)=="-")
               pos_begin_op = i;
            break;
        }
    }
    for(int i=position_operation+1;i<line.length();i++)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-")||i==line.length()-1)
        {
            pos_end_op = i-1;
            if(i==line.length()-1)
                pos_end_op = i;
            break;
        }
    }
    double first_operand , second_operand , result;
    string change ;
    first_operand = atof(line.substr(pos_begin_op,position_operation-pos_begin_op).c_str());
    second_operand = atof(line.substr(position_operation+1,(pos_end_op+1)-(position_operation+1)).c_str());
    if(operation=="^")
    {
    result = pow(first_operand,second_operand);
    change = to_string(result);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,change);
    }else if(operation=="/")
    {
    result = first_operand/second_operand;
    change = to_string(result);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,change);
    }else if(operation=="*")
    {
    result = first_operand*second_operand;
    change = to_string(result);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,change);
    }else if(operation=="+")
    {
    result = first_operand+second_operand;
    change = to_string(result);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,change);
    }else if(operation=="-")
    {
    result = first_operand-second_operand;
    change = to_string(result);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,change);
    }
    return line;
}


//useful function for phase 2

void MatricesPos(int* openmatrix, int* closematrix,string str,char x ,char y){

vector<int> positions; // holds all the positions that sub occurs within str
vector<int> positions2; // holds all the positions that sub occurs within str

int pos = str.find(y, 0);
while(pos != -1)
{
    positions.push_back(pos);
    pos = str.find(y,pos+1);
}



int pos2 = str.find(x, 0);
while(pos2 != -1)
{
    positions2.push_back(pos2);
    pos2 = str.find(x,pos2+1);
}

int myindex=0;


for(unsigned int i=0;i<positions.size();i++)
{
    for(unsigned int y=positions2.size()-1;y>=0;y--)
    {

        if(positions.at(i)>positions2.at(y))
        {
            openmatrix[myindex]=positions2.at(y);
            closematrix[myindex]=positions.at(i);
            positions2.erase(positions2.begin()+y);
            myindex++;
            break;

        }
    }
}
}



/*
#include <iostream>
#include "CMatrix.h"
#include "stdarg.h"
#include <algorithm>
using namespace std;
CMatrix& eye(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,2);
w=temp;
return w;
}
CMatrix& rand(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,3);
w=temp;
return w;
}
CMatrix& zeros(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,0);
w=temp;
return w;
}
CMatrix& ones(int nr,int nc)
{
static CMatrix w;
CMatrix temp(nr,nc,1);
w=temp;
return w;
}
int main()
{
    CMatrix A ;
    //A = "[1.2 3.4 5.6 7.8 1.0 3.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 1.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 17.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 1.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.4 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 4.4 2.3 2.4 2.6 2.7 1.2 3.4 5.6 2.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 1.8 9.0 1.2 2.1 2.3 2.4 8.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 5.1 4.3 12.4 2.6 2.7 1.2 3.4 5.6 97.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6; 2.7 1.2 3.4 5.6 7.5 9.0 2.2 2.1 3.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 5.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 8.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 6.6 2.7 1.2 3.4 5.6 2.8 9.0 1.2 2.1; 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 5.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 0.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 0.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0; 4.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.2 2.1 2.3 2.4 9.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 5.3 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.3; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 3.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 3.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 8.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 3.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 1.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2; 3.4 1.6 7.8 9.0 2.2 3.1 6.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7; 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 4.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 1.6; 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 1.2 3.4 9.6 7.8 9.0 2.2 2.1 2.3 2.4; 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 1.4 2.6 2.7 2.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3; 2.4 2.6 2.7 1.2 3.4 5.6 7.8 1.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 8.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 2.6 7.8 9.0 2.2 2.1; 7.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 3.6 1.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2; 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 7.2 3.4 5.6 7.8 9.0; 2.2 2.1 2.3 2.4 2.6 7.7 9.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.9 2.4 2.6 2.7 1.2 3.4 5.6 7.8; 9.0 2.2 2.1 2.3 2.4 2.6 7.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6; 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4; 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 2.7 1.2 3.4 5.6 7.8 9.0 2.2 2.1 2.3 2.4 2.6 5.7 9.3 3.4 5.6 3.8 9.0 2.2 5.1 2.3 2.4 2.6 2.7 1.2];";
   // cout<<A.FastestDeterminant()<<endl;
    //CMatrix B ;
   // A="[1 -1 0 2; 2 1 0 0; 1 1 2 2; 0 0 1 1];";
    //cout<<"\n"<<A;
    //cout<<"\n"<<B;
    //CMatrix C=A+B;
    //cout<<"\n"<<C;
    //C=A-B;
    //cout<<"\n"<<C;
    //C=A*B;
    //cout<<"\n"<<C;
    //C=A/B;
    //cout<<A.FastestDeterminant()<<endl;
    cout<<eye(4,4)<<"\n";
    cout<<rand(4,4)<<"\n";
    cout<<ones(4,4)<<"\n";
    cout<<zeros(4,4)<<"\n";
    A=ones(3,6);
    cout<<A.sin_matrix()<<"\n";
    return 0;
}
istream& operator >> (istream &is, CMatrix& m)
{
	string s;
	getline(is, s, ']');
	s += "]";
    CMatrix v (s);
	m = v;
	return is;
}
ostream& operator << (ostream &os, CMatrix& m)
{
	os << m.getString();
	return os;
}
/*string handling_operations(string s)
{
    string temp;
    while(s.length()==0)
    {
        if(s.find("(")!=0)
        {
        temp=s.substr(s.find("(")+1,s.find(")")-(s.find("(")+1));

        }
    }
}
string do_operation(string x)
{
    int length=x.length();
    string arr_op [5] = {"^","/","*","+","-"};
    for(int j=0;j<5;j++)
    {
        for(int i=0;i<length;i++)
            {

            }
    }
}
*/

/*	string get_input;
	string body_matrix;
	bool start_package,end_package,is_semicolon=false,start_operation=false;
	int end;
 	char c;
	while(getline(infile,get_input))
		{
	is_semicolon=false;
	int length=get_input.length();
	if(get_input=="\r"||get_input=="")
	{
        continue;
    }
	end=get_input.find("]");
	if(get_input.find("[")!=-1)
		start_package=true;
    else
        start_package=false;
	if(get_input.find("]")!=-1)
	{
		end_package=true;
	}else{
		end_package=false;
		}
	if(start_package)
	{
        c=*((const char*)get_input.substr(0,1).c_str());
		insert_name(array_chars,c);
	}
	if(end_package&&start_package)
	{
		body_matrix=get_input.substr(4,end-3);
		reserve(array_matrices, body_matrix);
		body_matrix.clear();
		if(get_input.substr(end+1,1)==";")
			is_semicolon=true;
		if(!is_semicolon)
		{
			cout<<array_matrices[get_index(array_chars,c)].getString()<<endl;
		}
	}
	if(end_package&&!start_package)
	{
		body_matrix+=get_input.substr(0,end+1);
		reserve(array_matrices, body_matrix);
		body_matrix.clear();
		if(get_input.substr(end+1,1)==";")
			is_semicolon=true;
		if(!is_semicolon)
		{
			cout<<array_matrices[get_index(array_chars,c)].getString();
		}
	}
	if(!end_package&&!start_package&&get_input.find("=")!=-1)
		{
		start_operation = true;
		string req;
		char* g = (char*)get_input.c_str();
		char* spearators = " ";
		char* temp = strtok(g,spearators);
		while(temp)
		{
            req += string(temp);
            temp = strtok(NULL,spearators);
		}
		get_input = req;
		c=*((const char*)get_input.substr(0,1).c_str());
		insert_name(array_chars, c);
		if(get_input.find("'")!=-1)
		{
		if(get_input.find(";")==4)
			is_semicolon=true;
		check_print(operationg(array_matrices,array_chars,num_elements,*((const char*)get_input.substr(2,1).c_str()),get_input.substr(3,1),c,0,0),is_semicolon);
		}else if(get_input.find(".")==-1)
		{
		if(get_input.find(";")!=-1)
			is_semicolon=true;
		check_print(operationg(array_matrices,array_chars,num_elements,*((const char*)get_input.substr(2,1).c_str()),get_input.substr(3,1),c,*((const char*)get_input.substr(4,1).c_str())),is_semicolon);
		}else if((*((const char*)get_input.substr(2,1).c_str())>='A'||*((const char*)get_input.substr(2,1).c_str())<='Z')&&(*((const char*)get_input.substr(5,1).c_str())>='A'||*((const char*)get_input.substr(5,1).c_str()))&&get_input.substr(3,1)==".")
		{
		if(get_input.find(";")!=-1)
			is_semicolon=true;
		check_print(operationg(array_matrices,array_chars,num_elements,*((const char*)get_input.substr(5,1).c_str()),get_input.substr(3,2),c,0,atof(get_input.substr(2,1).c_str())),is_semicolon);
		}
		}
		if (((!end_package&&start_package)||(!end_package&&!start_package))&&(!start_operation))
	{
	//&&get_input.substr(length-1,1)=="\n"
		if(get_input.substr(length-1,1)=="\r")
		{
            if(start_package)
			body_matrix+=get_input.substr(4,length-5);
			else
			body_matrix+=get_input.substr(0,length-1);
		}
	}*/
