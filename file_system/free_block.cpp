#include "header.h"
extern vector<int> i_stack;		//����i�ڵ�,0�Ŵ��С
extern vector<int> disk_stack;		//���д��̿�
extern i_node index[128];
extern information file_info;
extern vector<cataLog> catalog;
extern i_node index[128];
extern vector<int> path;
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
void ifree(int block)			//		���տ���i�ڵ�
{
	if (i_stack.size() == 128)
	{
		cout << "no more size" << endl;
	}
	else
	{
		i_stack.push_back(block);
	}
}