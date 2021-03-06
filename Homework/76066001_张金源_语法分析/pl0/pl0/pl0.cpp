#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

//#define CODE "C:\\Users\\Michael Octavianus K\\Desktop\\pl0\\Debug\\76066001_test.txt"
//#define RESULT "H:\\GitHub\\Compiler\\Homework\\ConsoleApplication1\\Debug\\76066001_res3.txt"

char *prog, token[10]; //source program input (prog), word storage (token)
char ch, ch2;
char sym[10], sign[30];
char token_gram[10], sym_gram[10]; //grammar
//syn word number
int syn, syn2, p, p2, m = 0, m2 = 0, n, line, line2, sum = 0, sum2 = 0;

//rwtab is keyword list
const char *rwtab1[10] = { "begin","if","then","while","do","end", "read","write"}; //语句
const char *rwtab2[5] = { "const","var","procedure","call", "odd" }; //说明
//const char *header[] = { "program" };

void scaner()
{
	//function for scan the file
	for (n = 0; n < 10; n++)
		//token store the word
		token[n] = NULL;
	ch = prog[p++];

	//remove space
	/*while (ch == ' ')
	{
		ch = prog[p];
		p++;
	}*/

	if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))  //must alphabeth because this is The Header
	{
		m = 0;
		//after Header can be number / alphabeth
		while ((ch >= '0'&&ch <= '9') || (ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z'))
		{ 
			token[m++] = ch;
			ch = prog[p++];
		}
		//Identity
		token[m++] = '\0';
		p--;
		syn = 10;
		strcpy(sym, "IDEN");

		//declare is a keyword or a label
		for (n = 0; n < 6; n++)
			if (strcmp(token, rwtab1[n]) == 0)
			{
				syn = n + 1;
				strcpy(sym, "TKN");
				break;
			}
		for (n = 0; n < 5; n++)
		{
			if (strcmp(token, rwtab2[n]) == 0)
			{
				syn = n + 31;
				strcpy(sym, "TKN");
				break;
			}
		}
	}
	else if ((ch >= '0'&&ch <= '9'))  //if number put in sum
	{
		sum = 0;
		while ((ch >= '0'&&ch <= '9'))
		{
			//Process decimal Number (整数)
			sum = sum * 10 + ch - '0';
			ch = prog[p++];
		}
		p--;
		syn = 11;
		strcpy(sym, "NUM");
		//If greater than 32767 will error
		if (sum > 32767)
			syn = -1;
	}
	else switch (ch)   //Another symbol
	{
	case '<':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '>')
		{
			//Is Not Same
			syn = 21;
			strcpy(sym, "NEQ");
			token[m++] = ch;
		}
		else if (ch == '=')
		{
			//Less Equal
			syn = 22;
			strcpy(sym, "LEQ");
			token[m++] = ch;
		}
		else
		{
			//Is Less Than
			syn = 23;
			strcpy(sym, "LSS");
			p--;
		}
		break;
	case '>':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			//greater equal
			syn = 24;
			//strcpy(sym, "GEQ");
			token[m++] = ch;
		}
		else
		{
			//greater than
			syn = 20;
			//strcpy(sym, "GTR"); 
			p--;
		}
		break;
	case ':':
		m = 0;
		token[m++] = ch;
		ch = prog[p++];
		if (ch == '=')
		{
			//Is Becomes (:=)
			syn = 18;
			//strcpy(sym, "BECOMES");
			token[m++] = ch;
		}
		else
		{
			//Is Colon (:)
			syn = 17;
			//strcpy(sym, "COLON");
			p--;
		}
		break;
	case '*':
		syn = 13;
		//strcpy(sym, "MULTI");
		token[0] = ch;
		break;
	case '/':
		syn = 14;
		//strcpy(sym, "DIVIDE");
		token[0] = ch;
		break;
	case '+':
		syn = 15;
		strcpy(sym, "PLUS");
		token[0] = ch;
		break;
	case '-':
		syn = 16;
		strcpy(sym, "MINUS");
		token[0] = ch;
		break;
	case '=':
		syn = 25;
		strcpy(sym, "SYMBOL");
		token[0] = ch;
		break;
	case ';':
		syn = 26;
		strcpy(sym, "SEMICOLON");
		token[0] = ch;
		break;
	case '(':
		syn = 27;
		strcpy(sym, "LPAREN");
		token[0] = ch;
		break;
	case ')':
		syn = 28;
		strcpy(sym, "RPAREN");
		token[0] = ch;
		break;
	case ',':
		syn = 29;
		strcpy(sym, "COMMA");
		token[0] = ch;
		break;
	case '!':
		syn = 30;
		strcpy(sym, "SYMBOL");
		token[0] = ch;
		break;
	case '.':
		//if 
		syn = 0;
		strcpy(sym, "PERIOD");
		token[0] = ch;
		break;
	/*case '\'':
		syn = 31;
		strcpy(sym, "QUOTATION");
		token[0] = ch;
		break;*/
	case '\n':
		//if new line , line + 1, syn = -2
		syn = -2;
		break;
	default:
		//if not symbol / anything will error
		syn = -1;
		break;
	}
}

void grammar()
{
	//function for scan the file
	for (n = 0; n < 10; n++)
	{ 
		//token store the word
		token_gram[n] = NULL;
		sym_gram[n] = NULL;
	}
	for (n = 0; n < 30; n++)
	{
		//token store the word
		sign[n] = NULL;
	}
	ch2 = prog[p2++];

	//remove space
	while (ch2 == ' ')
	{
		ch2 = prog[p2];
		p2++;
	}

	if ((ch2 >= 'a'&& ch2 <= 'z') || (ch2 >= 'A'&& ch2 <= 'Z'))  //must alphabeth because this is The Header
	{
		m2 = 0;
		//after Header can be number / alphabeth
		while ((ch2 >= '0'&& ch2 <= '9') || (ch2 >= 'a'&& ch2 <= 'z') || (ch2 >= 'A'&& ch2 <= 'Z'))
		{
			token_gram[m2++] = ch2;
			ch2 = prog[p2++];
		}
		//Identity
		token_gram[m2++] = '\0';
		p2--;
		syn2 = 10;
		//strcpy(sym, "IDEN");
		
		
		if (strcmp(token_gram, rwtab1[0]) == 0)
			{
			syn2 = 0 + 1; 
			//strcpy(sym, "TKN");
			strcpy(sign, ">>Begin Statement Declare<<");
			//break;
		}
		else if (strcmp(token_gram, rwtab1[1]) == 0)
		{
			syn2 = 1 + 1;
			//strcpy(sym, "TKN");
			strcpy(sign, ">>If Statement Declare<<");
			//break;
		}
		else if (strcmp(token_gram, rwtab1[2]) == 0)
		{
			syn2 = 2 + 1;
			strcpy(sign, ">>Then Statement Declare<<");

		}
		else if (strcmp(token_gram, rwtab1[3]) == 0)
		{
			syn2 = 3 + 1;
			strcpy(sign, ">>While Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab1[4]) == 0)
		{
			syn2 =  4+ 1;
			strcpy(sign, ">>Do Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab1[5]) == 0)
		{
			syn2 = 5 + 1;
			strcpy(sign, ">>End Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab1[6]) == 0)
		{
			syn2 = 6 + 1;
			strcpy(sign, ">>Read Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab1[7]) == 0)
		{
			syn2 = 7 + 1;
			strcpy(sign, ">>Write Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab2[0]) == 0)
		{
			syn2 = 0 + 31;
			strcpy(sign, ">>Const Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab2[1]) == 0)
		{
			syn2 = 1 + 31;
			strcpy(sign, ">>Var Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab2[2]) == 0)
		{
			syn2 = 2 + 31;
			strcpy(sign, ">>Procedure Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab2[3]) == 0)
		{
			syn2 = 3 + 31;
			strcpy(sign, ">>Call Statement Declare<<");
		}
		else if (strcmp(token_gram, rwtab2[4]) == 0)
		{
			syn2 = 4 + 31;
			strcpy(sign, " >>Odd Statement Declare<<");		
		}
		else
		{
			//syn2 = -1;
		}
}
	else if ((ch2 >= '0'&& ch2 <= '9'))  //if number put in sum
	{
		sum2 = 0;
		while ((ch2 >= '0'&& ch2 <= '9'))
		{
			//Process decimal Number (整数)
			sum2 = sum2 * 10 + ch2 - '0';
			ch2 = prog[p2++];
		}
		p2--;
		syn2 = 11;
		//If greater than 32767 will error
		if (sum2 > 32767)
			syn2 = -1;
	}
	else switch (ch2)   //Another symbol
	{
	case '<':
		m2 = 0;
		sym_gram[m2++] = ch2;
		ch2 = prog[p2++];
		if (ch2 == '>')
		{
			//Is Not Same
			syn2 = 21;
			//strcpy(sym, "NEQ");
			sym_gram[m2++] = ch2;
		}
		else if (ch2 == '=')
		{
			//Less Equal
			syn2 = 22;
			//strcpy(sym, "LEQ");
			sym_gram[m++] = ch2;
		}
		else
		{
			//Is Less Than
			syn2 = 23;
			//strcpy(sym, "LSS");
			p2--;
		}
		break;
	case '>':
		m2 = 0;
		sym_gram[m2++] = ch2;
		ch2 = prog[p2++];
		if (ch2 == '=')
		{
			//greater equal
			syn2 = 24;
			//strcpy(sym, "GEQ");
			sym_gram[m2++] = ch2;
		}
		else
		{
			//greater than
			syn2 = 20;
			//strcpy(sym, "GTR");
			p2--;
		}
		break;
	case ':':
		m2 = 0;
		sym_gram[m2++] = ch2;
		ch2 = prog[p2++];
		if (ch2 == '=')
		{
			//Is Becomes (:=)
			syn = 18;
			//strcpy(sym, "BECOMES");
			sym_gram[m2++] = ch2;
		}
		else
		{
			//Is Colon (:)
			syn2 = 17;
			//strcpy(sym, "COLON");
			p2--;
		}
		break;
	case '*':
		syn2 = 13;
		//strcpy(sym, "MULTI");
		sym_gram[0] = ch2;
		break;
	case '/':
		syn2 = 14;
		//strcpy(sym, "DIVIDE");
		sym_gram[0] = ch2;
		break;
	case '+':
		syn2 = 15;
		//strcpy(sym, "PLUS");
		sym_gram[0] = ch2;
		break;
	case '-':
		syn2 = 16;
		//strcpy(sym, "MINUS");
		sym_gram[0] = ch2;
		break;
	case '=':
		syn2 = 25;
		//strcpy(sym, "SYMBOL");
		sym_gram[0] = ch2;
		break;
	case ';':
		syn2 = 26;
		//strcpy(sym, "SEMICOLON");
		sym_gram[0] = ch2;
		//cout << "End Of analyse " << endl;
		break;
	case '(':
		syn2 = 27;
		//strcpy(sym, "LPAREN");
		sym_gram[0] = ch2;
		break;
	case ')':
		syn2 = 28;
		//strcpy(sym, "RPAREN");
		sym_gram[0] = ch2;
		break;
	case ',':
		syn2 = 29;
		//strcpy(sym, "COMMA");
		sym_gram[0] = ch2;
		break;
	case '!':
		syn2 = 30;
		//strcpy(sym, "SYMBOL");
		sym_gram[0] = ch2;
		break;
	case '.':
		//if 
		syn2 = 0;
		//strcpy(sym, "PERIOD");
		sym_gram[0] = ch2;
		//cout << "end of program";
		break;
	/*case '\'':
		syn = 31;
		strcpy(sym, "QUOTATION");
		token[0] = ch;
		break;*/
	case '\n':
		//if new line , line + 1, syn = -2
		syn2 = -2;
		sym_gram[0] = '\n';
		break;
	case ' ':
		sym_gram[0] = ch2;
		break;
	default:
		//if not symbol / anything will error
		syn2 = -1;
		break;
	}
}

//read the source file(.txt)

int read(char fname[])
{
	FILE *fp;
	fp = fopen(fname, "r");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		int file_size;
		file_size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		prog = (char *)malloc(file_size * sizeof(char));
		fread(prog, file_size, sizeof(char), fp);
		//close the file stream
		fclose(fp);
		return 1;
	}
	else
		return 0;
}

int main()
{
	int p = 0;
	int /*line = 1,*/ line2 = 1;
	char result[20], fname[20];
	cout << "Input your input and output file name (.txt)" << endl;
	cin >> fname;
	cout << "\n";
	//cin >> result;
	//cin >> result2;
	//ofstream outfile(result);
	//ofstream outfile(result2);

	cout << "loading......" << endl;
	//Sleep(3000);
	//read the source file

	if(read(fname))
	{
		/*p = 0;
		outfile << "Result of the analyse :" << endl;
		outfile << "line" << " " << "Code" << " " << "Category" << " " << "Value" << endl;
		outfile << "\n";
		do
		{
			scaner();
			switch (syn)
			{
			case 11:
				cout << line << " " << syn << ": " << sym << " " << sum << endl;
				outfile << line << " " << syn << ": " << sym << " " << sum << endl;
				break;
			case -1:
				cout << "Error in line" << " " << line << "!" << endl;
				outfile << "Error in line" << " " << line << "!" << endl;
				break;
			case -2:
				line = line++;
				break;
			default:
				cout << line << " " << syn << ": " << sym << " " << token << endl;
				outfile << line << " " << syn << ": " << sym << " " << token << endl;
				break;
			}
		} while (syn != 0);
		outfile.close();
		cout << "Analyse Complete, please check the result file" << endl;*/
		//line = 0;
		//if (read(fname))
		//{
		cout << "<<Grammar Analyse>>" << endl;
		p2 = 0;
			//outfile << "Result of the analyse :" << endl;
			//outfile << "\n";
		do
		{
			grammar();
			switch (syn2)
			{
				case 11:
					cout << sum2;
					//outfile << line << " " << syn << ": " << sym << " " << sum << endl;
					break;
				case -1:
					cout <<"\n";
					cout << "Error in line" << " " << line2 << "!" << endl;
					//outfile << "Error in line" << " " << line << "!" << endl;
					break;
				case -2:
					line2 = line2++;
					cout << sym_gram;
					break;
				default:
					cout << sign << " " << token_gram;
					cout << sym_gram;
					/*if(sym_gram[0] == ';')
						cout <<"\n";*/
					//outfile << line << " " << syn << ": " << sym << " " << token << endl;
					break;
			}
			//cout<<"\n";
		} while (syn2 != 0);
			//outfile.close();
		cout<<"\n";
		//cout << "Analyse Complete, please check the result file" << endl;
		//}
	}
	else
	{
		cout<< "\n" << "File Not Found" << endl;
	}
	system("pause");
	return 0;
}