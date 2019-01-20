// WordCount.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include"cstdio"
#include "io.h"
#include "cstring"
#include "iostream"
#include "windows.h"
char para[200][200];
using namespace std;
//����ļ��Ƿ�����ҿ��Զ�ȡ
int check_file_name(char file_name[])
{
	if (access(file_name, 0))//�жϸ��ļ�/�ļ����Ƿ���ڣ�
		return -1;
	if (access(file_name, 2) != 0)//�жϸ��ļ�/�ļ����Ƿ��ж�Ȩ�ޣ�
		return -2;
	return 1;
}

//��������Ƿ���ȷ��������ȷ����1�����󷵻�-1.
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


//ͳ���ļ����ַ���
int count_char(char file[])
{
	int char_num = 0;
	char ch;
	freopen(file, "r", stdin);//�ض�������
	while ((ch = getchar()) != EOF)
	{
		//if (ch != ' '&&ch != '\n'&&ch != '\t')
		char_num++;
	}
	fclose(stdin);
	return char_num;
}

//ͳ���ļ��ĵ�����
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

//ͳ���ļ�������
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

//ͳ���ļ��Ŀ�����
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

//ͳ���ļ���ע�͵�����
int count_comment_line(char file[])
{
	//flag1��ע�Ϳ�ͷ�ı�־λ��current_line��¼��ǰ���ǵ���ע�ͣ�flag2�Ƕ���ע�Ϳ�ͷ�ı�־��line��¼����ע�͵�������flag3�Ƕ���ע�ͽ�β�ı�־
	int comment_line_num = 0, ch_num=0, flag1 = 0, flag2 = 0, flag3 = 0, line = 0, current_line = 0;
	char ch;
	freopen(file, "r", stdin);
	while ((ch = getchar()) != EOF)
	{
		if (ch == '\n')
		{
			if (line&&ch_num > 0)//��line>0���ַ�������0��ʾ��ǰ���Ƕ���ע���е�һ��
			{
				line++;
			}
			ch_num = flag1 = current_line = 0;
		}
		if (current_line == 1) continue;//��ǰ���ǵ���ע�ͣ�ֱ���������ַ����ж�ֱ���������з�
		if (ch != ' '&&ch != '\n'&&ch != '\t') 
			ch_num++;
		if (flag2)//��ǰ��������ע��
		{
			if (ch != ' '&&ch != '\n'&&ch != '\t')
				ch_num++;
			if (ch == '*')//��������ע�͵Ľ�β'*/'�ķ���'*'
				flag3 = 1;
			else if (ch == '/'&&flag3)//��������ע�ͽ�β��'/'������������'*'��'/'������flag3��0
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
			else if (flag1 = 1 && ch_num <= 3)//����ע�ͱ���������ȡ����'/',�ҵ�ǰ����ע��֮ǰ���ֻ��һ������ʾ�ַ�
			{
				comment_line_num++;
				current_line = 1;
			}
		}
		else if (ch == '*')//����ע�͵Ŀ�ͷ'/*'
		{
			if (flag1 == 1)
			{
				flag2 = 1;
				line = 1;//�������ע��
			}
		}
		else
			flag1 = 0;
	}
	fclose(stdin);
	return comment_line_num;
}

//ͳ���ļ��Ĵ�������
int count_code_line(char file[])
{
	int line = count_line(file);
	int blank_line = count_blank_line(file);
	int comment_line = count_comment_line(file);
	int code_line_num = line - blank_line - comment_line;
	return code_line_num;
}

//�����ӵ����ݣ�������/����/ע���У�
void complex_data(char file[])
{
	int code_line_num = count_code_line(file);
	int blank_line = count_blank_line(file);
	int comment_line = count_comment_line(file);
	printf("code lines: %d\n", code_line_num);
	printf("blank lines: %d\n", blank_line);
	printf("comment lines: %d\n", comment_line);
}

//��������ģ��
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

//wchar_t ת�� string 
void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte������
	char *psText;// psTextΪchar*����ʱ���飬��Ϊ��ֵ��std::string���м����
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte���ٴ�����
	szDst = psText;// std::string��ֵ
	delete[]psText;// psText�����
}

//�ݹ鴦���ļ�ģ��
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
			{  //��Ŀ¼
				cur = path + filefind.name + '\\';
				search_file(cur, idx);    //�ݹ鴦��
			}
			else //����Ŀ¼�����ļ�
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
	if (strcmp(argv[1], "-s") == 0) // �ݹ鴦��Ŀ¼�·����������ļ�  
	{		
		TCHAR szPath[MAX_PATH] = { 0 };
		if (GetModuleFileName(NULL, szPath, MAX_PATH))//ͨ������GetModuleFileName��ȡִ�г���ľ���·����
		{
			(_tcsrchr(szPath, _T('\\')))[1] = 0;//������Ҫ�õ�_tcsrchr����������ȡ����ִ�г���ľ���·���е�ִ�г��������ȥ��
		}
		string Path;
		Wchar_tToString(Path, szPath);
		for (int i = 0; i < argc; i++)
			strcpy(para[i], argv[i]);
		search_file(Path, argc - 1);
	}
	else if (strcmp(argv[1], "-x") == 0) //ͼ�ν��� 
	{	
		ShellExecuteA(NULL, "open", "GUI.exe", NULL, NULL, SW_SHOW);
	}
	else //�Ե���.c�ļ���ͳ�� 
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

