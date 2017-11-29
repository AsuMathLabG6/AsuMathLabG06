#include <iostream>
#include <stdio.h>
#include "CMatrix.h"
#include "stdarg.h"
#include <algorithm>
#include <string>
#include <fstream>
//F = A / B
using namespace std;

#define size 100

enum MI
{
	MI_ZEROS,
	MI_ONES,
	MI_EYE,
	MI_RAND,
	MI_VALUE
};
int num_elements = 0;

bool is_found(char c, char *array_chars);
void reserve(CMatrix *array_matrices, string x);
void insert_name(char *array_chars, char y);
int get_index(char *array_chars, char operand_name);
string operationg(CMatrix *array_matrices, char *array_chars, int size_array, char first_operand, string operation, char output, char second_operand, double d = 0);
void check_print(string output, bool is_semicolon);

int main(int argc, char *argv[])
{
	char array_chars[size];
	CMatrix array_matrices[size];
	if (argc == 2)
	{
		//"/home/mido/Downloads/drexample.m"
		ifstream infile(argv[1]);
		if (!infile.bad())
		{
			string get_input;
			string body_matrix;
			bool start_package, end_package, is_semicolon = false, start_operation = false;
			int end;
			char c;
			while (getline(infile, get_input))
			{
				is_semicolon = false;
				int length = get_input.length();
				if (get_input == "\r" || get_input == "")
				{
					continue;
				}
				end = get_input.find("]");
				if (get_input.find("[") != -1)
					start_package = true;
				else
					start_package = false;
				if (get_input.find("]") != -1)
				{
					end_package = true;
				}
				else
				{
					end_package = false;
				}
				if (start_package)
				{
					c = *((const char *)get_input.substr(0, 1).c_str());
					insert_name(array_chars, c);
				}
				if (end_package && start_package)
				{
					body_matrix = get_input.substr(4, end - 3);
					reserve(array_matrices, body_matrix);
					body_matrix.clear();
					if (get_input.substr(end + 1, 1) == ";")
						is_semicolon = true;
					if (!is_semicolon)
					{
						cout << array_matrices[get_index(array_chars, c)].getString() << endl;
					}
				}
				if (end_package && !start_package)
				{
					body_matrix += get_input.substr(0, end + 1);
					reserve(array_matrices, body_matrix);
					body_matrix.clear();
					if (get_input.substr(end + 1, 1) == ";")
						is_semicolon = true;
					if (!is_semicolon)
					{
						cout << array_matrices[get_index(array_chars, c)].getString();
					}
				}
				if (!end_package && !start_package && get_input.find("=") != -1)
				{
					start_operation = true;
					string req;
					char *g = (char *)get_input.c_str();
					char *spearators = " ";
					char *temp = strtok(g, spearators);
					while (temp)
					{
						req += string(temp);
						temp = strtok(NULL, spearators);
					}
					get_input = req;
					c = *((const char *)get_input.substr(0, 1).c_str());
					insert_name(array_chars, c);
					if (get_input.find("'") != -1)
					{
						if (get_input.find(";") == 4)
							is_semicolon = true;
						check_print(operationg(array_matrices, array_chars, num_elements, *((const char *)get_input.substr(2, 1).c_str()), get_input.substr(3, 1), c, 0), is_semicolon);
					}
					else if (get_input.find(".") == -1)
					{
						if (get_input.find(";") != -1)
							is_semicolon = true;
						check_print(operationg(array_matrices, array_chars, num_elements, *((const char *)get_input.substr(2, 1).c_str()), get_input.substr(3, 1), c, *((const char *)get_input.substr(4, 1).c_str())), is_semicolon);
					}
					else if ((*((const char *)get_input.substr(2, 1).c_str()) >= 'A' || *((const char *)get_input.substr(2, 1).c_str()) <= 'Z') && (*((const char *)get_input.substr(5, 1).c_str()) >= 'A' || *((const char *)get_input.substr(5, 1).c_str())) && get_input.substr(3, 1) == ".")
					{
						if (get_input.find(";") != -1)
							is_semicolon = true;
						check_print(operationg(array_matrices, array_chars, num_elements, *((const char *)get_input.substr(5, 1).c_str()), get_input.substr(3, 2), c, 0, atof(get_input.substr(2, 1).c_str())), is_semicolon);
					}
				}
				if (((!end_package && start_package) || (!end_package && !start_package)) && (!start_operation))
				{
					//&&get_input.substr(length-1,1)=="\n"
					if (get_input.substr(length - 1, 1) == "\r")
					{
						if (start_package)
							body_matrix += get_input.substr(4, length - 5);
						else
							body_matrix += get_input.substr(0, length - 1);
					}
				}
			}
			infile.close();
		}
		else
			cout << "File read failed." << endl;
	}
	return 0;
}

istream &operator>>(istream &is, CMatrix &m)
{
	string s;
	getline(is, s, ']');
	s += "]";
	CMatrix v(s);
	m = v;
	return is;
}
ostream &operator<<(ostream &os, CMatrix &m)
{
	os << m.getString();
	return os;
}
//to check if the character is found or not
bool is_found(char c, char *array_chars)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (c == array_chars[i])
			return false;
	}
	return true;
}
//give this function body of matrix [2 1, 4 5]
void reserve(CMatrix *array_matrices, string x)
{
	array_matrices[num_elements - 1] = x;
	//cout<<array_matrices[num_elements-1];
}
// reserve char in array which is the name of matrices
void insert_name(char *array_chars, char y)
{
	if (num_elements == 0)
	{
		array_chars[num_elements] = y;
		num_elements++;
	}
	if (is_found(y, array_chars))
	{
		array_chars[num_elements] = y;
		num_elements++;
	}
}
//array_chars is the dynamic array of characters
int get_index(char *array_chars, char operand_name)
{
	for (int i = 0; i < num_elements; i++)
	{
		if (array_chars[i] == operand_name)
			return i;
	}
}
//array_matrices is the dynamic array of matrices
string operationg(CMatrix *array_matrices, char *array_chars, int size_array, char first_operand, string operation, char output, char second_operand, double d)
{
	int index_first_operand, index_second_operand, index_output;
	index_first_operand = get_index(array_chars, first_operand);
	if (second_operand != 0)
		index_second_operand = get_index(array_chars, second_operand);
	index_output = get_index(array_chars, output);
	string required;

	if (operation == "+")
	{
		array_matrices[index_output] = array_matrices[index_first_operand] + array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
	}
	else if (operation == "-")
	{
		array_matrices[index_output] = array_matrices[index_first_operand] - array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
	}
	else if (operation == "*")
	{
		array_matrices[index_output] = array_matrices[index_first_operand] * array_matrices[index_second_operand];
		required = array_matrices[index_output].getString();
	}
	else if (operation == "/")
	{
		try
		{
			array_matrices[index_output] = array_matrices[index_first_operand] / array_matrices[index_second_operand];
			required = array_matrices[index_output].getString();
		}
		catch (string *fault)
		{
			cout << *(fault) << endl;
		}
	}
	else if (operation == "'")
	{
		array_matrices[index_output] = array_matrices[index_first_operand].getTranspose();
		required = array_matrices[index_output].getString();
	}
	else if (operation == "./")
	{
		array_matrices[index_output] = division_by_element(d, array_matrices[index_first_operand]);
		required = array_matrices[index_output].getString();
	}
	return required;
}
//to check to print or not
void check_print(string output, bool is_semicolon)
{
	if (!is_semicolon)
		cout << output << endl;
}
CMatrix &division_by_element(double d, CMatrix &X)
{
	static CMatrix output(X.nR, X.nC);
	for (int i = 0; i < X.nR; i++)
	{
		for (int j = 0; j < X.nC; j++)
		{
			double d1 = d / X.values[i][j];
			output.values[i][j] = d1;
		}
	}
	return output;
}
bool isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if ((!isdigit(s[i])) || s[i] == '.')
			return false;
	}
	return true;
}
//5.5 + 12 * sin(0.4) + 2.2^4; or ((CD .+ 4)./2.1 + sqrt(D))./C.^2
void handleInputNoMat(string *array)
{
	for (int i = 0; array[i] != "end"; i++)
	{
		if (isNumber(array[i]))
		{
			if (isNumber(array[i + 2]))
			{
			}
		}
	}
}
string *myTokenizer(string sample)
{
	string *array = new string[20];
	int posSpace, posStart, index = 0, posStartCurl, posEndCurl, noOfCurlyOpen = 0, noOfCurlyClose = 0;

	for (int i = 0; i < sample.length(); i++)
	{
		posStart = i;
		if (sample[i] == '(')
		{
			noOfCurlyOpen++;
			for (int j = i + 1; noOfCurlyOpen != 0; j++)
			{
				if (sample[j] == '(')
					noOfCurlyOpen++;
				else if (sample[j] == ')')
					noOfCurlyOpen--;
				i = j = posSpace;
			}
		}
		posSpace = sample.find(' ', posStart);
		array[index] = sample.substr(posStart, posSpace - posStart);
		index++;
	}
	array[index] = "end";
	return array;
}
