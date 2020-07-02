#pragma once 
#include "preProcess.h"

int main()
{
	char resourceproject[10000];
	char token[20] = { 0 };
	int syn=-1;
	int pProject=0;
	FILE* fp;
	if ((fp = fopen("d://text_cf.txt", "r")) == NULL)
	{
		cout << "can't open this file";
		exit(0);
	}
	pProject = 0;
	resourceproject[pProject] = fgetc(fp);
	while (resourceproject[pProject] != '$')
	{//将源程序读入resourceproject数组中
		pProject++;
		resourceproject[pProject] = fgetc(fp);
	}
	resourceproject[++pProject] = '\0';
	fclose(fp);
	cout << "源程序为：" << endl;
	cout << resourceproject << endl;
	//取出无用字符
	preresource(resourceproject, pProject);
	cout << endl << "取出无用字符后" << endl;
	cout << resourceproject << endl;
	while (syn != 0)
	{
		scanner(syn, resourceproject, token, pProject);
	}
	return 0;
}