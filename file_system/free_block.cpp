#include "header.h"
//���д��̿����
extern vector<int> i_stack;		//����i�ڵ�,0�Ŵ��С
extern vector<int> disk_stack;		//���д��̿�
extern i_node index[128];
extern information file_info;
extern int free_i;
int ialloc()	//�������i�ڵ�
{
	if (i_stack.size() == 0)
	{
		cout << "no more free blocks" << endl;
		return -1;
	}
	else
	{
		free_i = i_stack[i_stack.back()];
		i_stack.pop_back();
		return free_i;
	}
}
