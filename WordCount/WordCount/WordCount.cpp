// WordCount.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"cstdio"
#include "io.h"
#include "cstring"
#include "iostream"
#include "windows.h"
char para[200][200];
using namespace std;
//检查文件是否存在且可以读取
int check_file_name(char file_name[])
{
	if (access(file_name, 0))//判断该文件/文件夹是否存在；
		return -1;
	if (access(file_name, 2) != 0)//判断该文件/文件夹是否有读权限；
		return -2;
	return 1;
}

//检查命令是否正确，命令正确返回1，错误返回-1.
int check_command(char command[])
{
	int len = strlen(command);
	if (len != 2 || command[0] != '-')
		return -1;
	if (command[1] == 'c' || command[1] == 'w' || command[1] == 'l' || command[1] == 'a') 
		return 1;
	else 
		return -1;
}


//统计文件的字符数
int count_char(char file[])
{
	int char_num = 0;
	char ch;
	freopen(file, "r", stdin);//重定向输入
	while ((ch = getchar()) != EOF)
	{
		//if (ch != ' '&&ch != '\n'&&ch != '\t')
		char_num++;
	}
	fclose(stdin);
	return char_num;
}

//统计文件的单词数
int count_word(char file[])
{
	int word_num = 0, flag = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF)
	{
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || ch == '_') flag = 1;
		else
		{
			if (flag)
			{
				word_num++;
				flag = 0;
			}
		}
	}
	fclose(stdin);
	return word_num;
}

//统计文件的行数
int count_line(char file[])
{
	int line_num = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n')
		{
			line_num++;
		}
	}
	fclose(stdin);
	return line_num;
}

//统计文件的空行数
int count_blank_line(char file[])
{
	int blank_line_num = 0, ch_num = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n')
		{
			if (ch_num <= 1)
			{
				blank_line_num++;	
			}
			ch_num = 0;
		}
		else if (ch != ' '&&ch != '\t')
			ch_num++;
	}
	fclose(stdin);
	return blank_line_num;
}

//统计文件的注释的行数
int count_comment_line(char file[])
{
	//flag1是注释开头的标志位，current_line记录当前行是单行注释，flag2是多行注释开头的标志，line记录多行注释的行数，flag3是多行注释结尾的标志
	int comment_line_num = 0, ch_num=0, flag1 = 0, flag2 = 0, flag3 = 0, line = 0, current_line = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n')
		{
			if (line&&ch_num > 0)//若line>0且字符数大于0表示当前行是多行注释中的一行
			{
				line++;
			}
			ch_num = flag1 = current_line = 0;
		}
		if (current_line == 1) continue;//当前行是单行注释，直接跳过对字符的判断直到读到换行符
		if (ch != ' '&&ch != '\n'&&ch != '\t') 
			ch_num++;
		if (flag2)//当前读到多行注释
		{
			if (ch != ' '&&ch != '\n'&&ch != '\t')
				ch_num++;
			if (ch == '*')//读到多行注释的结尾'*/'的符号'*'
				flag3 = 1;
			else if (ch == '/'&&flag3)//读到多行注释结尾的'/'，必须连续读'*'和'/'，否则flag3置0
			{
				comment_line_num += line;
				line = 0;
				flag2 = flag3 = 0;
				current_line = 1;
			}
			else
				flag3 = 0;
		}
		else if (ch == '/')
		{
			if (flag1 == 0)
				flag1 = 1;
			else if (flag1 = 1 && ch_num <= 3)//单行注释必须连续读取两个'/',且当前行在注释之前最多只有一个可显示字符
			{
				comment_line_num++;
				current_line = 1;
			}
		}
		else if (ch == '*')//多行注释的开头'/*'
		{
			if (flag1 == 1)
			{
				flag2 = 1;
				line = 1;//进入多行注释
			}
		}
		else
			flag1 = 0;
	}
	fclose(stdin);
	return comment_line_num;
}

//统计文件的代码行数
int count_code_line(char file[])
{
	int line = count_line(file);
	int blank_line = count_blank_line(file);
	int comment_line = count_comment_line(file);
	int code_line_num = line - blank_line - comment_line;
	return code_line_num;
}

//更复杂的数据（代码行/空行/注释行）
void complex_data(char file[])
{
	int code_line_num = count_code_line(file);
	int blank_line = count_blank_line(file);
	int comment_line = count_comment_line(file);
	printf("code lines: %d\n", code_line_num);
	printf("blank lines: %d\n", blank_line);
	printf("comment lines: %d\n", comment_line);
}

//基本功能模块
void basic_command(char order[], char filename[])
{
	switch (order[1]) {
	case 'c':
		printf("characters: %d\n", count_char(filename));
		break;
	case 'w':
		printf("words: %d\n", count_word(filename));
		break;
	case 'l':
		printf("lines: %d\n", count_line(filename));
		break;
	case 'a':
		complex_data(filename);
		break;
	}
}

//wchar_t 转换 string 
void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;// psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

//递归处理文件模块
void search_file(string path, int idx)
{
	struct _finddata_t filefind;
	string cur = path + "*.*";
	int done = 0, handle;
	if ((handle = _findfirst(cur.c_str(), &filefind)) != -1)
	{
		while (!(done = _findnext(handle, &filefind)))
		{
			if (strcmp(filefind.name, "..") == 0)
				continue;
			if ((_A_SUBDIR == filefind.attrib)) 
			{  //是目录
				cur = path + filefind.name + '\\';
				search_file(cur, idx);    //递归处理
			}
			else //不是目录，是文件
			{
				int len = strlen(filefind.name);
				for (int i = 0; i < len; i++) 
				{
					if (filefind.name[i] == '.') 
					{
						len = i;
						break;
					}
				}
				if (strcmp(filefind.name + len, para[idx] + 1) == 0) 
				{
					cur = path + filefind.name;
					printf("%s:\n", filefind.name);
					for (int i = 1; i < idx; i++)
						basic_command(para[i], &cur[0]);
				}
			}
		}
		_findclose(handle);
	}
}

int main(int argc, char* argv[])
{
	if (strcmp(argv[1], "-s") == 0) // 递归处理目录下符合条件的文件  
	{		
		TCHAR szPath[MAX_PATH] = { 0 };
		if (GetModuleFileName(NULL, szPath, MAX_PATH))//通过函数GetModuleFileName获取执行程序的绝对路径。
		{
			(_tcsrchr(szPath, _T('\\')))[1] = 0;//这里需要用到_tcsrchr函数来将获取到的执行程序的绝对路径中的执行程序的名称去掉
		}
		string Path;
		Wchar_tToString(Path, szPath);
		for (int i = 0; i < argc; i++)
			strcpy(para[i], argv[i]);
		search_file(Path, argc - 1);
	}
	else if (strcmp(argv[1], "-x") == 0) //图形界面 
	{	
		ShellExecuteA(NULL, "open", "GUI.exe", NULL, NULL, SW_SHOW);
	}
	else //对单个.c文件的统计 
	{									
		int num_para;
		for (num_para = argc - 1; num_para > 1; num_para--) 
		{
			if (strcmp(argv[num_para], "-s") == 0 || strcmp(argv[num_para], "-x") == 0
				|| strcmp(argv[num_para], "-c") == 0 || strcmp(argv[num_para], "-w") == 0
				|| strcmp(argv[num_para], "-l") == 0 || strcmp(argv[num_para], "-a") == 0)
			{
				break;
			}
		}
		char  filename[500] = { 0 };
		strcat(filename, argv[num_para + 1]);
		for (int i = num_para + 2; i < argc; i++) 
		{
			strcat(filename, " ");
			strcat(filename, argv[i]);
		}
		int flag_3 = check_file_name(filename);
		if (flag_3 == -1) 
		{
			printf("Error:The file does not exist !\n");
			return 0;
		}
		else if (flag_3 == -2) 
		{
			printf("Error:The file has no read permissions !\n");
			return 0;
		}
		printf("%s:\n", filename);
		for (int i = 1; i <= num_para; i++) 
		{
			if (check_command(argv[i]) == 1)
				basic_command(argv[i], filename);
			else
				printf("Command parameter error !\n");
		}
	}
	return 0;
}

