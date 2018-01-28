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
string choose_type_operation (string line , CMatrix* array_matrices , char* array_chars,string& choose);
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
void ready(char* text,CMatrix& c ,CMatrix* array_matrices ,char* array_chars);
void combine (string matrix_inside,CMatrix& c,CMatrix* array_matrices,char* array_chars);
CMatrix& choose_type (string case1 , int x, CMatrix* array_matrices);
double do_this(string case1 ,double value);
void string_matrix (string result,CMatrix* array_matrices) ;
int is_erase(string text);
int no_item(string text,string item);
CMatrix& add_column_matrix(int no_rows);
string getstring (CMatrix& x , int choice);
string check_matrix_in (string matrix,CMatrix* array_matrices,char* array_chars);
string check_operation_in (string matrix);
CMatrix &power_matrix(CMatrix &matrix, int number);
CMatrix &sqrt_matrix(CMatrix &matrix);
CMatrix &unityMatrix(int num);
int main(int argc, char* argv[])
{
try{
char array_chars [size];
CMatrix* array_matrices = new CMatrix [size] ;

//if (argc == 2)
//{
//argv[1]
ifstream infile("/home/mido/Downloads/advexample(copy).m");
if (!infile.bad())
{
   string get_input , body_matrix , body_math , output , concatenate , decision , result1 ;
   bool open_bracket = false , close_bracket = false , is_semicolon;
   char c;
   int length , indicator1=0 , indicator2=0 ;
   while(getline(infile,get_input))
   {
    char* text1 = new char [get_input.length()+1] ;
    strcpy(text1,get_input.c_str());
    if(get_input=="\r"||get_input=="")
        continue;
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
                        reserve(array_matrices,"math",1,rand(nr,nc));
                }else if(get_input.find("eye",index+1)!=-1)
                {
                        trim (str2,2, nr ,nc );
                        reserve(array_matrices,"math",1,eye(nr,nc));
                }else if(get_input.find("zeros",index+1)!=-1)
                {
                        trim (str2,3, nr ,nc );
                        reserve(array_matrices,"math",1,zeros(nr,nc));
                }else if(get_input.find("ones",index+1)!=-1)
                {
                        trim (str2,4, nr ,nc );
                        reserve(array_matrices,"math",1,ones(nr,nc));
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
                result1 = choose_type_operation (str1 , array_matrices , array_chars,decision);
                if(decision=="math")
                {
                double d = atof(result1.c_str());
                CMatrix C(1,1,4,d);
                reserve(array_matrices, "math" , 1 ,C);
                }
            }
            else
            {
                string str1 ;
                str1 = get_input.substr(index+1,(get_input.find(";",0)-1)-index) ;
                result1 = choose_type_operation (str1 , array_matrices , array_chars,decision);
                if(decision=="math")
                {
                double d = atof(result1.c_str());
                CMatrix C(1,1,4,d);
                reserve(array_matrices, "math" , 1 ,C);
                }
            }
            int i = get_index(array_chars,c) ;
            if(decision=="math")
            output = array_matrices[i].getString();
            else if(decision=="matrix")
            output = result1 ;
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
        }else if ( (open_bracket&&close_bracket) || (open_bracket&&!close_bracket) || (!open_bracket&&!close_bracket) || (!open_bracket&&close_bracket) )
        {
            string s ;
            if(!indicator1&&!indicator2)
            {
            int index = get_input.find("=",0);
            for(int i = get_input.rfind("]")+1 ;i<get_input.length();i++)
            {
                if(get_input.substr(i,1)==";")
                {
                    is_semicolon = true ;
                    break ;
                }
                is_semicolon = false ;
            }
            c = trim (get_input.substr(0,index));
            insert_name(array_chars, c );
            s = get_input.substr(index+1,(length-1-index));
            }
            int no_open_brackets = 0 , no_closed_brackets = 0 ;
            for(int i=0;i<get_input.length();i++)
            {
                if(get_input.substr(i,1)=="[")
                    no_open_brackets++;
               else if(get_input.substr(i,1)=="]")
                    no_closed_brackets++;
            }
            if(no_open_brackets==1&&no_closed_brackets==1)
            {
                reserve(array_matrices, s );
                if(!is_semicolon)
            {
                string str3 ;
                int i = get_index(array_chars,c) ;
                str3 = array_matrices[i].getString();
                char text2[3];
                sprintf(text2,"%c=\n",array_chars[i]);
                check_print (string(text2)+" "+str3, is_semicolon);
            }
            }else if(no_open_brackets&&!no_closed_brackets)
            {
                if(!indicator1)
                {
                    concatenate += s;
                    indicator1 = 1;
                }

             }else if(!no_open_brackets&&!no_closed_brackets&&!indicator2)
             {
                if(indicator1)
                        concatenate += get_input;

             }else if(!no_open_brackets&&no_closed_brackets&&!indicator2)
             {
                if(indicator1)
                    {
                        concatenate += get_input;
                        indicator1 = 0 ;
                        reserve(array_matrices, concatenate );
                    if(get_input.find(";")==-1)
                    {
                        string str3 ;
                        int i = get_index(array_chars,c) ;
                        str3 = array_matrices[i].getString();
                        char text2[3];
                        sprintf(text2,"%c=\n\n",array_chars[i]);
                        check_print (string(text2)+" "+output, bool(get_input.find(";")==-1));
                    }
                    concatenate.clear();
                    }
             }else if(no_open_brackets>1&&no_closed_brackets>1&&no_open_brackets==no_closed_brackets)
             {
              s.erase(0,s.find("[")+1);
              s.erase(s.rfind("]"),s.length()-s.rfind("]"));
              int intially=0 , finally=0 ;
              int care = 0 ;
              string parsing ;
              string matrix_in_matrix ;
              CMatrix m;
              for(int i=0;i<s.length();i++)
              {
                if((s.substr(i,1)==";"||s.length()-1==i)&&!care)
                {
                  if(s.substr(i,1)==";")
                  finally=i;
                  else if(s.length()-1==i)
                  finally=i+1;
                  parsing = s.substr(intially,finally-intially);
                  char trans [parsing.length()+1];
                  strcpy(trans,parsing.c_str());
                  ready(trans,m,array_matrices,array_chars);
                  intially = finally+1;
                }else if(s.substr(i,1)=="[")
                    care = 1;
                 else if(s.substr(i,1)=="]"&&((s.length()-1)==i||s.substr(i+1,1)==";")&&((s.rfind(",",i)<i&&s.rfind(",",i)>intially)||(s.find(",",intially)==-1)))
                 {
                    finally = i+1 ;
                    matrix_in_matrix = s.substr(intially,finally-intially);
                    combine(matrix_in_matrix,m,array_matrices,array_chars);
                    intially = finally+1;
                    matrix_in_matrix.clear();
                    if(s.substr(i+1,1)==";")
                    {
                        i++;
                        care = 0 ;
                    }
                }
             }
             reserve(array_matrices,"math",1,m);
                if(!is_semicolon)
             {
                string str3 ;
                int i = get_index(array_chars,c) ;
                str3 = array_matrices[i].getString();
                char text2[3];
                sprintf(text2,"%c=\n",array_chars[i]);
                check_print (string(text2)+" "+str3, is_semicolon);
             }
        }
        else if(no_open_brackets>1&&no_closed_brackets>1||no_open_brackets!=no_closed_brackets)
        {
            if(!indicator2)
            {
                concatenate+=s;
                indicator2=1;
            }else if((indicator1||indicator2)&&no_open_brackets==no_closed_brackets)
                concatenate+=get_input;
             else if((indicator1||indicator2)&&no_closed_brackets>no_open_brackets)
             {
                concatenate+=get_input;
                concatenate.erase(0,concatenate.find("[")+1);
                concatenate.erase(concatenate.rfind("]"),concatenate.length()-concatenate.rfind("]"));
                int intially=0 , finally=0 ;
                int care = 0 ;
                string parsing ;
                string matrix_in_matrix ;
                CMatrix m;
                for(int i=0;i<concatenate.length();i++)
                {
                    if((concatenate.substr(i,1)==";"||concatenate.length()-1==i)&&!care)
                    {
                    if(concatenate.substr(i,1)==";")
                    finally=i;
                    else if(concatenate.length()-1==i)
                    finally=i+1;
                    parsing = concatenate.substr(intially,finally-intially);
                    char trans [parsing.length()+1];
                    strcpy(trans,parsing.c_str());
                    ready(trans,m,array_matrices,array_chars);
                    intially = finally+1;
                    }else if(concatenate.substr(i,1)=="[")
                    care = 1;
                    else if(concatenate.substr(i,1)=="]"&&((concatenate.length()-1)==i||concatenate.find(";",i)!=-1||concatenate.find("\r",i)==(i+1))&&((concatenate.rfind(",",i)<i&&concatenate.rfind(",",i)>intially)||(concatenate.find(",",intially)==-1)))
                    {
                    finally = i+1 ;
                    matrix_in_matrix = concatenate.substr(intially,finally-intially);
                    combine(matrix_in_matrix,m,array_matrices,array_chars);
                    intially = finally+1;
                    matrix_in_matrix.clear();
                    if(concatenate.substr(i+1,1)==";")
                    {
                        i++;
                        care = 0 ;
                    }else if(concatenate.find("\r",i)==(i+1))
                    {
                        i+=2;
                        care = 0 ;
                        intially++;
                    }
                }
             }
             reserve(array_matrices,"math",1,m);
                if(!is_semicolon)
             {
                string str3 ;
                int i = get_index(array_chars,c) ;
                str3 = array_matrices[i].getString();
                char text2[3];
                sprintf(text2,"%c=\n",array_chars[i]);
                check_print (string(text2)+" "+str3, is_semicolon);
             }
        }
    }
    }
    delete []text1;
}
}
infile.close();
//}else
//cout<<"File read failed."<<endl;
}

catch(char const* error){ cout<<"Error: "<<error<<endl; }
return 0;
}
/*bool is_end(char* text)
{
    bool found_exp = false ;
    for(int i=0;i<strlen(text);i++)
    {
        char c = text[i] ;
       if(c =='='||((c >='A'&&c <='Z')||(c >='a'&&c <='z'))|| c=='['||c==']'||c==','||c==';'||c>='0'||c<='9')
            found_exp = true;
    }
    return found_exp;
}*/
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
		{
		if(x=="math")
		array_matrices[num_elements-1]=c;
		else if(x=="matrix")
		array_matrices[num_elements-2]=c;
		}
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
	//try{
		array_matrices[index_output] = array_matrices[index_first_operand]/array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
	//	}
	//	catch(string* fault){cout<<*(fault)<<endl;}
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
    }else if(operation==".-")
	{
        array_matrices[index_first_operand]-=d2;
		array_matrices[index_output] = array_matrices[index_first_operand];
		required = array_matrices[index_output].getString();
    }else if(operation==".*")
	{
        array_matrices[index_first_operand]*=d2;
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
/*V2.0 Branch work*/
/*It multplies the matrix by itself n times
where n is the power of the matrix*/
CMatrix &power_matrix(CMatrix &matrix, int number)
{
  static CMatrix temp = matrix;
  if (number < 0)

		throw("Power must be positive Integer");
  if (number == 0)
    return unityMatrix(matrix.nR);
	if (number == 1)
		return matrix;
	else
	{
    for (int i = 1; i < number; i++)
			temp = temp*matrix;
	}
	return temp;
}
/* send the matrix as a parameter and it returns back the square root of the matrix which is a matrix too*/
CMatrix &sqrt_matrix(CMatrix &matrix)
{
	if (matrix.nC != matrix.nR)
		throw("Matrix must be square matrix (of equal dimensions)");
	else {
		static CMatrix Yprev = matrix;
    CMatrix Zprev = unityMatrix(matrix.nR)
           ,Ynext
           ,Znext
           ,unity = unityMatrix(matrix.nR);
		for (int i = 0; i < 10; i++)
		{

			Ynext = Yprev * 0.5 * (unity * 3.0 - Zprev * Yprev);
      Znext = Zprev * 0.5 * (unity * 3.0 - Zprev * Yprev);

      Yprev= Ynext;
      Zprev = Znext;
		}
		return Yprev;
	}
}
CMatrix &unityMatrix(int num)
{
	static CMatrix temp(num, num, CMatrix::MI_ZEROS,0);
	for (int i = 0; i < num; i++)
	{
		temp.values[i][i] = 1.0;
	}
	return temp;
}
// choose_type_operation is it on matrices or on numbers to handle if the operation will be done on matrices or on numbers and handle case 1x1 matrix
string choose_type_operation (string line , CMatrix* array_matrices , char* array_chars,string& choose)
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
           else if(array_matrices[get_index(array_chars,line[i])].getnC()>1&&array_matrices[get_index(array_chars,line[i])].getnR()>1)
            flag2 = 1;
        }
    }
    if(!flag1&&!flag2||flag1&&!flag2)
        {
        result = to_string(do_operation_line (line));
        choose = "math" ;
        }
    else if(flag1&&flag2||!flag1&&flag2)
        {
        result = do_operation_matrices (line , array_matrices , array_chars );
        choose = "matrix" ;
        }
    return result ;
}
//operations on matrices and get out matrix of the operation
string do_operation_matrices (string line , CMatrix* array_matrices , char* array_chars )
{
    string with_no_space;
    char* line1 = new char [line.length()+1];
    strcpy(line1,line.c_str());
    char* separators = " \r\n";
    char* token = strtok(line1,separators);
    while(token)
    {
        with_no_space+=string(token);
        token = strtok (NULL ,separators);
    }
    string c [11] = {"'","^",".^","/","./","*",".*","+",".+","-",".-"};
    while(with_no_space.find("sin")!=-1||with_no_space.find("cos")!=-1||with_no_space.find("tan")!=-1||with_no_space.find("sec")!=-1||with_no_space.find("csc")!=-1||with_no_space.find("cot")!=-1||with_no_space.find("arcsin")!=-1||with_no_space.find("arccos")!=-1||with_no_space.find("arctan")!=-1||with_no_space.find("arcsec")!=-1||with_no_space.find("arccsc")!=-1||with_no_space.find("arccot")!=-1||with_no_space.find("sqrt")!=-1||with_no_space.find("expm")!=-1||with_no_space.find("logm")!=-1)
    {
        CMatrix temp ;
        string rep ;
        int end1 , start1;
        string case1 ;
        case1 = (with_no_space.find("sin")!=-1)? "sin" : (with_no_space.find("cos")!=-1)? "cos" : (with_no_space.find("tan")!=-1)? "tan" : (with_no_space.find("sec")!=-1)? "sec" : (with_no_space.find("csc")!=-1)? "csc" : (with_no_space.find("cot")!=-1)? "cot" : (with_no_space.find("arcsin")!=-1)? "arctan" : (with_no_space.find("arccos")!=-1)? "arccos" : (with_no_space.find("arctan")!=-1)? "arctan" : (with_no_space.find("arcsec")!=-1)? "arcsec" : (with_no_space.find("arccsc")!=-1)? "arccsc" : (with_no_space.find("arccot")!=-1)? "arccot" : (with_no_space.find("sqrt")!=-1)? "sqrt" : (with_no_space.find("expm")!=-1)? "expm" : "logm" ;
        end1 = with_no_space.find(")",with_no_space.find(case1));
        start1 = with_no_space.find("(",with_no_space.find(case1));
        string inter = with_no_space.substr(start1+1,end1-(start1+1));
        if(inter.length()==1&&(inter[0]>='A'||inter[0]<='Z'||inter[0]>='a'||inter[0]<='z'))
           {
            int x = get_index(array_chars,*((const char*)inter.substr(0,1).c_str())) ;
            temp = choose_type (case1 , x , array_matrices);
           }else
           {
           string q = excute_matrices_ops(inter, get_num_ops_matrices (inter,c) , c , array_matrices , array_chars);
           int x = get_index(array_chars,*((const char*)q.substr(0,1).c_str())) ;
           temp = choose_type (case1 , x , array_matrices);
           }
           insert_name(array_chars,char(out+my_count));
           // cout<<temp.getString();
           string result;
           result = temp.getString();
           rep = char(out+my_count);
           int start = with_no_space.find(case1);
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
    result = array_matrices[get_index(array_chars,*((const char*)with_no_space.substr(0,1).c_str()))].getString() ;
    return result;
}
// to count no_operations on matrices in one line
int get_num_ops_matrices (string line , string operations [])
{
    int len = line.length();
    int no_operations = 0;
    for(int i=1;i<len;i++)
    {
        for(int j=0;j<11;j++)
        {
            if(line.find(".^",i)==i||line.find("./",i)==i||line.find(".*",i)==i||line.find(".+",i)==i||line.find(".-",i)==i)
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
            for(int h=0;h<11;h++)
                {
                    for(int i=1;i<line.length();i++)
                        {
                            if(line.substr(i,2)==".^"||line.substr(i,2)=="./"||line.substr(i,2)==".*"||line.substr(i,2)==".+"||line.substr(i,2)==".-")
                                {
                                    if(line.substr(i,2)== operations[h])
                                    {
                                        line = excute_matrix(line,line.substr(i,2),i,array_matrices,array_chars);
                                        no_operations--;
                                         i++;
                                    }
                                }
                            else if(line.substr(i,1)== operations[h]&&line.substr(i-1,1)!=".")
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
   int pos_begin_op = 0,pos_end_op = line.length()-1 ;
    for(int i=pos-1;i>=0;i--)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-"))
        {
            pos_begin_op = i+1;
            break;
        }
    }
    if(line.substr(pos,1)==".")
    {
      for(int i=pos+2;i<line.length();i++)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="."||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-"))
        {
            pos_end_op = i-1;
            break;
        }
    }
    }else
    {
    for(int i=pos+1;i<line.length();i++)
    {
        if((line.substr(i,1)=="^"||line.substr(i,1)=="."||line.substr(i,1)=="/"||line.substr(i,1)=="*"||line.substr(i,1)=="+"||line.substr(i,1)=="-"))
        {
            pos_end_op = i-1;
            break;
        }
    }
    }
    string rep ;
    if(op=="'")
    {
        char first_operand = line[pos_begin_op];
        insert_name(array_chars,char(out+my_count));
        string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , 0) ;
        rep = char(out+my_count);
        line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
        string_matrix(result,array_matrices);
    }
    else if(op=="^")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op==".^")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op=="/")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op=="./")
    {
    char* line1 = new char [line.length()+1];
    strcpy(line1,line.c_str());
    if((line1[pos_begin_op]>='A'&&line1[pos_begin_op]<='Z')||(line1[pos_begin_op]>='a'&&line1[pos_begin_op]<='z'))
    {
    char first_operand = line1[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }
    if(line1[pos_end_op]>='A'||line1[pos_end_op]<='Z'||line1[pos_end_op]>='a'||line1[pos_end_op]<='z')
    {
    char second_operand = line[pos_end_op];
    double d1 = atof(line.substr(pos_begin_op,pos-pos_begin_op).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,second_operand, op , char(out+my_count) , 0 , d1 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }
    }else if(op=="*")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op==".*")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op=="+")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op==".+")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op=="-")
    {
    char first_operand = line[pos_begin_op];
    char second_operand = line[pos_end_op];
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , second_operand , 0 , 0) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }else if(op==".-")
    {
    char first_operand = line[pos_begin_op];
    double d2 = atof(line.substr(pos+1,pos_end_op-pos).c_str());
    insert_name(array_chars,char(out+my_count));
    string result = operationg(array_matrices,array_chars,first_operand, op , char(out+my_count) , 0 , 0 , d2) ;
    rep = char(out+my_count);
    line.replace(pos_begin_op,(pos_end_op+1)-pos_begin_op,rep);
    string_matrix(result,array_matrices);
    }
my_count++;
return line ;
}
//to take line like that " 5.5 + 12 * sin(0.4) + 2.2^4 " and get it's output
double do_operation_line (string line)
{
    string with_no_space;
   string seperators = " \r\n";
    for(int o=0;o<line.length();o++)
    {
         for(int u=0;u<3;u++)
        {
        if(line.substr(o,1)==seperators.substr(u,1))
            line.erase(o,1);
        }
        if(line.find(".+")==o||line.find(".-")==o||line.find(".*")==o||line.find("./")==o||line.find(".^")==o)
            line.erase(o,1);
    }
    with_no_space = line;
    string c ="^/*+-";
    while(with_no_space.find("sin")!=-1||with_no_space.find("cos")!=-1||with_no_space.find("tan")!=-1||with_no_space.find("sec")!=-1||with_no_space.find("csc")!=-1||with_no_space.find("cot")!=-1||with_no_space.find("arcsin")!=-1||with_no_space.find("arccos")!=-1||with_no_space.find("arctan")!=-1||with_no_space.find("arcsec")!=-1||with_no_space.find("arccsc")!=-1||with_no_space.find("arccot")!=-1||with_no_space.find("sqrt")!=-1||with_no_space.find("exp")!=-1||with_no_space.find("log")!=-1)
    {
        int end1 , start1;
        string case1 ;
        case1 = (with_no_space.find("sin")!=-1)? "sin" : (with_no_space.find("cos")!=-1)? "cos" : (with_no_space.find("tan")!=-1)? "tan" : (with_no_space.find("sec")!=-1)? "sec" : (with_no_space.find("csc")!=-1)? "csc" : (with_no_space.find("cot")!=-1)? "cot" : (with_no_space.find("arcsin")!=-1)? "arctan" : (with_no_space.find("arccos")!=-1)? "arccos" : (with_no_space.find("arctan")!=-1)? "arctan" : (with_no_space.find("arcsec")!=-1)? "arcsec" : (with_no_space.find("arccsc")!=-1)? "arccsc" : (with_no_space.find("arccot")!=-1)? "arccot" : (with_no_space.find("sqrt")!=-1)? "sqrt" : (with_no_space.find("exp")!=-1)? "exp" : "log" ;
        end1 = with_no_space.find(")",with_no_space.find(case1));
        start1 = with_no_space.find("(",with_no_space.find(case1));
        double val = atof(with_no_space.substr(start1+1,end1-(start1+1)).c_str());
        double res = do_this(case1,val);
        int start = with_no_space.find("sin");
        with_no_space.replace (start,(end1+1-start),to_string(res));
    }
    while(with_no_space.find("(")!=-1&&with_no_space.find(")")!=-1)
    {
	int from ;
        int start1 = with_no_space.find("(");
        int end1 = with_no_space.find(")");
        from = start1 ;
        while(with_no_space.find("(",from+1)!=-1)
        {
        int start2 = with_no_space.find("(",from+1);
        int end2 = with_no_space.find(")",start2+1);
        if(end2>end1&&end2==with_no_space.length()-1)
            break;
	else if(with_no_space.rfind("(",end2)!=start2)
            from = start2 + 1 ;
        else if(with_no_space.rfind("(",end2)==start2)
        {
        string internal_line = with_no_space.substr(start2+1,(end2-(start2+1)));
        int no_ops = get_num_ops(internal_line,c);
        internal_line = handle_excute(internal_line,c,no_ops);
        with_no_space.replace(start2,(end2+1)-start2,internal_line);
	from = with_no_space.rfind("(",start2)-1;
        if(from<0)
            from = start1 + 1 ;
	}
    	}
        end1 = with_no_space.find(")");
        string internal_line = with_no_space.substr(start1+1,(end1-(start1+1)));
         int n ;
         n = get_num_ops(internal_line,c);
        internal_line = handle_excute(internal_line,c,n);
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
void ready(char* text,CMatrix& c ,CMatrix* array_matrices ,char* array_chars)
{
    char* sperators = " [];";
    char* token = strtok(text,sperators);
    string s = "[ ";
    while (token)
    {
        string temp;
        if((token[0]>='A'&&token[0]<='Z')&&strlen(token)==1)
        {
            temp=to_string(array_matrices[get_index(array_chars,token[0])].get_values(0,0));
            s+=temp;
            s+=" ";
        }else if(strchr(token,'+')>0||strchr(token,'-')>0||strchr(token,'*')>0||strchr(token,'/')>0|strchr(token,'^')>0)
        {
            temp=to_string(do_operation_line (string(token)));
            s+=temp;
            s+=" ";
        }else
        {
           s+=token;
            s+=" ";
        }
        token = strtok(NULL,sperators);
    }
    s+="]";
    CMatrix row (s);
    c.addRow(row);
}
int is_erase(string text)
{
    int accum = 0 ;
    for(int i=0;i<text.length();i++)
    {
        if(text.substr(i,1)=="[")
            accum++;
        else if(text.substr(i,1)=="]")
            accum--;
    }
    return accum ;
}
int no_item(string text,string item)
{
    int accum = 0 ;
    for(int i=0;i<text.length();i++)
    {
        if(text.substr(i,1)==item)
            accum++;
    }
    return accum ;
}
CMatrix& add_column_matrix(int no_rows)
{
    static CMatrix mat (no_rows,1);
    return mat ;
}
//void setSubMatrix(int iR, int iC, CMatrix& m);
void combine (string matrix_inside,CMatrix& c,CMatrix* array_matrices,char* array_chars )
{
    int r = c.getnR();
    int c1 = 0 ;
    int alarm ;
    matrix_inside = check_matrix_in (matrix_inside,array_matrices,array_chars);
    int no_commas = no_item(matrix_inside,",");
    int first1 =0 , first2=0;
    string operate_on ;
    char* text = new char [matrix_inside.length()+1];
    strcpy(text,matrix_inside.c_str());
    char* seperators = "," ;
    char* token = strtok(text,seperators);
    operate_on = string(token);
    alarm=is_erase(operate_on);
    if(alarm==1)
        first1 = 1;
    else if(alarm==0)
        first2 = 1;
    while(token)
    {
        operate_on = string(token);
        alarm=is_erase(operate_on);
        if(alarm==1)
        {
            operate_on.erase(operate_on.find("["),1);
            CMatrix matrix (operate_on);
            if(first1)
            {
            c.addRow(matrix);
            first1 = 0;
            if(c1==0&&r==0)
            {
            CMatrix mat (add_column_matrix(matrix.getnR()));
            c.addColumn(mat);
            }
            c1=matrix.getnC()-1;
            }
            else
            c.setSubMatrix(r,c1,matrix);
            c1++;
            no_commas--;
        }else if(alarm==0)
        {
            CMatrix matrix (operate_on);
            if(first2)
            {
            c.addRow(matrix);
            first2 = 0;
            if(!c1&&!r)
            {
            CMatrix mat (add_column_matrix(matrix.getnR()));
            c.addColumn(mat);
            }
            c1=matrix.getnC()-1;
            }
            else
            c.setSubMatrix(r,c1,matrix);
            c1++;
            no_commas--;
        }else if(alarm==-1)
        {
            operate_on.erase(operate_on.rfind("]"),1);
            CMatrix matrix (operate_on);
            c.setSubMatrix(r,c1,matrix);
            if(no_commas>0)
                c1++;
        }
        token = strtok(NULL,seperators);
    }
    delete[]text;
}
string check_matrix_in (string matrix,CMatrix* array_matrices,char* array_chars)
{
    int add_comma ;
    int grow_by = 0 ;
    string temp ;
    char* text = new char [matrix.length()+1];
    strcpy(text,matrix.c_str());
    for(int i=0;i<strlen(text);i++)
    {
        if(text[i]>='A'&&text[i]<='Z')
        {
           if(array_matrices[get_index(array_chars,text[i])].getnC()==1&&array_matrices[get_index(array_chars,text[i])].getnR()==1)
            {
                temp = to_string(array_matrices[get_index(array_chars,text[i])].get_values(0,0)) ;
                matrix.replace(i+grow_by,1,temp);
                grow_by = temp.length()-1;
                temp.clear();
            }else
            {
                if(matrix.find("]",i+1)<matrix.find("[",i+1))
                   add_comma = 0 ;
                else if(matrix.find("]",i+1) > matrix.find("[",i+1))
                    add_comma = 1 ;
                temp = getstring(array_matrices[get_index(array_chars,text[i])],add_comma) ;
                matrix.replace(i+grow_by,1,temp);
                grow_by = temp.length()-1;
                temp.clear();
            }
        }
    }
    matrix = check_operation_in (matrix);
    delete[]text;
    return matrix ;
}
CMatrix& choose_type (string case1 , int x , CMatrix* array_matrices)
{
   static CMatrix temp ;
            if(case1=="sin")
            temp = array_matrices[x].sin_matrix();
            else if(case1=="cos")
            temp = array_matrices[x].cos_matrix();
            else if(case1=="tan")
            temp = array_matrices[x].tan_matrix();
            else if(case1=="sec")
            temp = array_matrices[x].sec_matrix();
            else if(case1=="csc")
            temp = array_matrices[x].csc_matrix();
            else if(case1=="cot")
            temp = array_matrices[x].cot_matrix();
            else if(case1=="arcsin")
            temp = array_matrices[x].asin_matrix();
            else if(case1=="arccos")
            temp = array_matrices[x].acos_matrix();
            else if(case1=="arctan")
            temp = array_matrices[x].atan_matrix();
            else if(case1=="arcsec")
            temp = array_matrices[x].asec_matrix();
            else if(case1=="arccsc")
            temp = array_matrices[x].acsc_matrix();
            else if(case1=="arccot")
            temp = array_matrices[x].acot_matrix();
            else if(case1=="sqrt")
            temp = sqrt_matrix(array_matrices[x]);
            else if(case1=="expm")
            temp = array_matrices[x].exp_matrix();
            else if(case1=="logm")
            temp = array_matrices[x].log_matrix();
    return temp ;
}
double do_this(string case1 ,double value)
{
    double result ;
            if(case1=="sin")
            result = sin(value);
            else if(case1=="cos")
            result = cos(value);
            else if(case1=="tan")
            result = tan(value);
            else if(case1=="sec")
            result = 1/cos(value);
            else if(case1=="csc")
            result = 1/sin(value);
            else if(case1=="cot")
            result = 1/tan(value);
            else if(case1=="arcsin")
            result = asin(value);
            else if(case1=="arccos")
            result = acos(value);
            else if(case1=="arctan")
            result = atan(value);
            else if(case1=="arcsec")
            result = acos(1/value);
            else if(case1=="arccsc")
            result = asin(1/value);
            else if(case1=="arccot")
            result = atan(1/value);
            else if(case1=="sqrt")
            result = sqrt(value);
            else if(case1=="exp")
            result = exp(value);
            else if(case1=="log")
            result = log(value);
    return result ;
}
void string_matrix (string result , CMatrix* array_matrices)
{
    CMatrix c;
                        char* text = new char [result.length()+1];
                        strcpy(text,result.c_str());
                        char* first_parsing ;
                        char* separators1 = "\r\n";
                        char* token1 = strtok_r(text,separators1,&first_parsing);
                        while(token1)
                        {
                            CMatrix row ;
                            char* separators2 = "\t";
                            char* second_parsing ;
                            char* token2 = strtok_r(token1,separators2,&second_parsing);
                            while(token2)
                            {
                                CMatrix item(atof(token2));
                                row.addColumn(item);
                                token2 = strtok_r(NULL,separators2,&second_parsing);
                            }
                            c.addRow(row);
                            token1 = strtok_r(NULL,separators1,&first_parsing);
                        }
                        reserve(array_matrices, "matrix" , 1 ,c);
                        delete[]text;
}
string getstring (CMatrix& x , int choice )
{
    string s ;
    s+="[ ";
    for(int i=0;i<x.getnR();i++)
    {
        for(int j=0;j<x.getnC();j++)
        {
            s+=to_string(x.get_values(i,j));
            if(j!=x.getnC()-1)
            s+=" ";
            else if(j==x.getnC()-1&&i<x.getnR()-1)
            s+=" ; ";
            else if(j==x.getnC()-1&&i==x.getnR()-1)
            s+=" ]";
        }
    }
    if(choice)
    s+=",";
    return s ;
}
string check_operation_in (string matrix)
{
    int begineer , ender ;
    char* text = new char [matrix.length()+1];
    strcpy(text,matrix.c_str());
    for(int i=0;i<strlen(text);i++)
    {
        if(text[i]=='+'||text[i]=='-'||text[i]=='*'||text[i]=='/'||text[i]=='^'||matrix.find("sin")!=-1||matrix.find("cos")!=-1||matrix.find("tan")!=-1||matrix.find("sec")!=-1||matrix.find("csc")!=-1||matrix.find("cot")!=-1||matrix.find("arcsin")!=-1||matrix.find("arccos")!=-1||matrix.find("arctan")!=-1||matrix.find("arcsec")!=-1||matrix.find("arccsc")!=-1||matrix.find("arccot")!=-1||matrix.find("sqrt")!=-1||matrix.find("exp")!=-1||matrix.find("log")!=-1)
        {
            for(int h=i-1;h>=0;h--)
            {
                if(text[h]==' '||text[h]==';'||text[h]=='[')
                {
                    begineer = h+1 ;
                    break ;
                }
            }
            for(int g=i+1;g<matrix.length();g++)
            {
                if(text[g]==' '||text[g]==';'||text[g]==']')
                {
                    ender = g ;
                    break ;
                }
            }
            matrix.replace(begineer,ender-begineer,to_string(do_operation_line(matrix.substr(begineer,(ender-begineer)))));
        }
    }
    delete[]text;
    return matrix ;
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
