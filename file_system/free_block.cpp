#include "header.h"
//���д��̿����
extern vector<int> i_stack;		//����i�ڵ�,0�Ŵ��С
extern vector<int> disk_stack;		//���д��̿�
extern i_node index[128];
extern int free_i;
extern information file_info;
int ialloc()	//�������i�ڵ�
{
	if (i_stack.size() == 128)
	{
		cout << "no more free blocks" << endl;
		return 0;
	}
	else
	{
		free_i = i_stack[i_stack.size() - 1];
		i_stack.pop_back();
		return free_i;
	}
}
