#pragma once 
#include "preProcess.h"

static char kt[32][20] = {
	"auto", "break", "case", "char", "const", "continue",
	"default", "do", "double", "else", "enum", "extern",
	"float", "for", "goto", "if", "int", "long",
	"register", "return", "short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union", "unsigned", "void",
	"mian", "while"
};//关键字kt
static char pt[40][5] = {
	"(",")","[","]","{","}","->",".","::","++","--","!","~","-","+","*","&","/","%","<<",
	">>","<","<=",">",">=","^","|","&&","||","?:","=","+=","-=","&="
	"|=",",",";","#",":",":="

};//界符pt
static char it[1000][20] = { "" };//标识表it
static char ct[1000] = { "" };//单字符表ct
static char st[1000][20] = { "" };//字符串表st
static char c[1000][20] = { "" };//常数表c
int num_it = 0;//it标识符表计数
int num_ct = 0;//单字符表ct计数
int num_st = 0;//字符串表st计数
int num_c = 0;//常数表c计数

//查找关键字kt
int searchkt(char kt[][20], char s[])
{
	for (int i = 0; i < 32; i++)
	{
		if (strcmp(kt[i], s) == 0)
		{
			return i + 1;//查找成功，返回syn
		}
		return -1;//查找失败，返回-1，即为标识符
	}
}
//查找某字符串是否在某表中出现（二维数组）
int searcht(char t[][20], char s[])
{
	for (int i = 0; t[i][0] != '/0'; i++)
	{
		if (strcmp(t[i], s) == 0)
		{
			return i + 1;//查找成功，返回syn
		}
		return -1;//查找失败，即此时该表中没有该字符
	}
}
//查找字符是否在字符表ct中出现
int searchct(char c[],char s)
{
	for (int i = 0; c[i] != '/0'; i++)
	{
		if (c[i]==s)
		{
			return i + 1;//查找成功，返回syn
		}
		return -1;//查找失败，即此时该表中没有该字符
	}
}
//判断是不是字母
bool isletter(char ch)
{
	if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//判断是不是数字
bool isdigit(char ch)
{
	if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}
//取出无用字符和注释
void preresource(char r[], int pProject)
{
	int num_afrer = 0;//after_resource下标
	char after_resource[10000];//存储预处理后的源程序
	for (int i = 0; i < pProject; i++)
	{
		if (r[i] != '\n' && r[i] != '\r' && r[i] != '\t' && r[i] != '\v')
		{/*当扫描到无用字符：
		   空格\n，回车\r，水平制表符\t，垂直制表符\v，则过滤*/
			after_resource[num_afrer++] = r[i];
		}
		if (r[i] == '/' && r[i + 1] == '/')
		{//这就是注释开头“//”,过滤注释
			while (r[i] != '\n')
			{//不为空就一直往后扫描
				i++;
			}
		}
		if (r[i] == '/' && r[i + 1] == '*')
		{//多行注释开头“/*........*/”
			i += 2;
			while (r[i] != '*' || r[i + 1] != '/')
			{//没有遇到多行注释结尾“*/”则一直往后扫描
				i++;
				if (r[i] == '$')//'$'文件结束符
				{
					cout << "注释错误" << endl;
					exit(0);//注释没有"*/",错误
				}
			}
			i += 2;//遇到“*/”，则+2
		}
	}
	after_resource[num_afrer] = '\0';
	strcpy(r, after_resource);
}
void scanner(int& syn, char resourceproject[], char token[], int& pProject)
{//syn在该表的顺序，resourceproject源程序，pProject指针
	FILE* fp1;
	if ((fp1 = fopen("d:\\text_cf1.txt", "at+")) == NULL)
	{
		cout << "can't open this file";
		exit(0);
	}
	int i, count = 0;//count用来做token[]指示器，搜集有用字符
	char ch='\0';//做判断
	ch == resourceproject[pProject];
	while (ch == ' ')
	{//过滤空格,防止识别空格而停止
		pProject++;
		ch == resourceproject[pProject];
	}
	for (i = 0; i < 20; i++)
	{//token收集前清零
		token[i] = '\n';
	}
	if (isletter(resourceproject[pProject]))
	{//如果开头为字母
		token[count++] = resourceproject[pProject];//记录
		pProject++;
		while (isletter(resourceproject[pProject]) || isdigit(resourceproject[pProject]))
		{//后面跟着字母或者数字
			token[count++] = resourceproject[pProject];//记录
			pProject++;
		}
		token[count] == '/0';
		syn = searchkt(kt, token);//判断是否为关键字，是则返回表中顺序
		if (syn == -1)
		{//不是关键字
			syn = searcht(it, token);//判断是否已存在标识符表中，存在则返回表中顺序，反之存入it中
			if (syn == -1)
			{
				strcpy(it[num_it++], token);//存入标识符表
				syn = num_it;
			}
			cout << "<" << "it" << "," << syn << "," << it[syn - 1] << ">" << endl;
			fprintf(fp1, "<it,%d,%s>\n", syn, it[syn - 1]);
		}
		if (syn != -1)
		{//是关键字
			cout << "<" << "kt" << "," << syn << "," << kt[syn - 1] << ">" << endl;
			fprintf(fp1, "<kt,%d,%s>\n", syn, kt[syn - 1]);
		}
	}
	else if (isdigit(resourceproject[pProject]))
	{//如果开头为数字
		while (isdigit(resourceproject[pProject]))
		{
			token[count++] = resourceproject[pProject];
			pProject++;
		}
		token[count] = '/0';
		syn = searcht(c, token);//查找常数表
		if (syn == -1)
		{//常数表c中没有该数字
			strcpy(c[num_c++], token);
			syn = num_c;
		}
		cout << "<" << "c" << "," << syn << "," << c[syn - 1] << ">" << endl;
		fprintf(fp1, "<c,%d,%s>\n", syn, c[syn - 1]);
	}
	else if (ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' 
			|| ch == '}' ||  ch == '.'|| ch == '!' || ch == '~' || ch == '*' 
			|| ch == '/'|| ch == '%' || ch == '^' || ch == '?' ||ch == ','
			|| ch == '='|| ch == ';' || ch == '#')
	{//如果开头为运算符或者是界符
		token[0] = resourceproject[pProject];
		token[1] = '\0';//形成单字符串
		for (i = 0; i < 46; i++)
		{
			if (strcmp(token, pt[i]) == 0)
			{
				syn = i + 1;//得到该符号在符号表pt中的顺序
				break;
			}
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '-')
	{// -> , - , -- , -=
		pProject++;
		if (resourceproject[pProject] == '>')
		{
			syn = 7;
		}
		else if (resourceproject[pProject] == '-')
		{
			syn = 11;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 33;
		}
		else
		{
			pProject--;
			syn = 14;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == ':')
	{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == ':')
		{
			syn = 9;
		 }
		else if (resourceproject[pProject] == '=')
		{
			syn = 40;
		}
		else
		{
			pProject--;
			syn = 39;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '+')
	{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '+')
		{
			syn = 10;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 32;
		}
		else
		{
			pProject--;
			syn = 15;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '&')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '&')
		{
			syn = 28;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 34;
		}
		else
		{
			pProject--;
			syn = 17;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
		}
	else if (resourceproject[pProject] == '<')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '<')
		{
			syn = 20;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 23;
		}
		else
		{
			pProject--;
			syn = 22;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '>')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '>')
		{
			syn = 21;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 25;
		}
		else
		{
			pProject--;
			syn = 24;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '|')
		{// : , :: ,:=
		pProject++;
		if (resourceproject[pProject] == '|')
		{
			syn = 29;
		}
		else if (resourceproject[pProject] == '=')
		{
			syn = 35;
		}
		else
		{
			pProject--;
			syn = 27;
		}
		cout << "<" << "pt" << "," << syn << "," << pt[syn - 1] << ">" << endl;
		fprintf(fp1, "<pt,%d,%s>\n", syn, pt[syn - 1]);
		pProject++;
	}
	else if (resourceproject[pProject] == '$')
	{//自定义$ 结束符
		syn = 0;
	}
	else
	{
		cout << "error:不能被识别 " << resourceproject[pProject] << endl;
		exit(0);
	}
	fclose(fp1);
}