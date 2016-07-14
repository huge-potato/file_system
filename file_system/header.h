#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<conio.h>
#include<sstream>
#include<time.h>
#include<windows.h>
#include<shellapi.h>
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<tchar.h>
#include<cstdlib>
#include<iomanip>
#include<windowsx.h>

using namespace std;

#define BLOCKSIZ 512
#define DIRNUM 128
#define MAXBLK 512

typedef struct{		//���ļ�Ŀ¼
	string name;
	int id;
}child_catalog;

typedef struct{		//�ļ�Ŀ¼�е�ַ
	int flag;
	vector<child_catalog> c_catalog;
	int i_node;
}address;

typedef struct{		//�ļ���Ϣ
	string name;
	int type;
	string ftype;
	int user;
	string create_time;
	string last_edit_time;
	int share;
	int readable;
	int writeable;
	int size;
	int block;
	vector<int> path;
}information;

typedef struct{		//�ļ�Ŀ¼
	int id;
	address addr;
	information info;
}cataLog;

typedef struct{		//����i�ڵ�
	information info;
}i_node;

typedef struct{		//�ڴ�i�ڵ�
	information info;
	vector<int> user;
	int         id;//��Ӧ����i�ڵ��id
	string      open_time;
}i_node_memory;

typedef struct{		//���̿�
	string content;
}disk_block;

typedef struct{		//���̿�����
	vector<int> block;
}disk_Index;

typedef struct{
    string name;
    int    id;
}INAMEindex;
typedef struct{
    string date;
    int    id;
}IDATEindex;
typedef struct{
    string type;
    int    id;
}ITYPEindex;
typedef struct{
    int    id;
    string username;
    string password;
}User;
