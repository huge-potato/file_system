#include"header.h"

extern vector<cateLog> catelog;
extern vector<disk_Index> disk_index;;
extern vector<int> path;
extern i_node index[128];
void ifree(int block);
void free_disk_block(int inode);
extern vector<int> disk_stack;
extern disk_block disk[10240];
void delete_file(string command){
	stringstream command_stream(command);
	string command1, name;
	command_stream >> command1;
	command_stream >> name;
	int i = 0;
	int flag = 0;
	for (auto file : catelog[path.back()].addr.c_catelog)
	{
		if (name == file.name && catelog[file.id].info.type == 0)
		{
			flag = 1;
			for (auto block1 : disk_index[catelog[file.id].info.block].block)
				disk[block1].content = "";
			//�ͷŴ���i�ڵ�Ϊ����i�ڵ�
			ifree(catelog[file.id].addr.i_node);
			//�ͷŴ��̿�
			free_disk_block(index[catelog[file.id].addr.i_node].info.block);
			//����i�ڵ����
			index[catelog[file.id].addr.i_node].info.name = "";
			index[catelog[file.id].addr.i_node].info.type = -1;
			index[catelog[file.id].addr.i_node].info.block = -1;
			index[catelog[file.id].addr.i_node].info.create_time = "";
			index[catelog[file.id].addr.i_node].info.last_edit_time = "";
			index[catelog[file.id].addr.i_node].info.path.clear();
			index[catelog[file.id].addr.i_node].info.share = 0;
			index[catelog[file.id].addr.i_node].info.readable = 0;
			index[catelog[file.id].addr.i_node].info.writeable = 0;
			index[catelog[file.id].addr.i_node].info.size = 0;
			index[catelog[file.id].addr.i_node].info.user = -1;

			//ɾ��Ŀ¼�е���Ϣ
			vector<cateLog>::iterator it;
			it = catelog.begin() + file.id;
			catelog.erase(it);
			//ɾ�����ļ�Ŀ¼
			vector<child_catelog>::iterator it1;
			it1 = catelog[path.back()].addr.c_catelog.begin() + i;
			catelog[path.back()].addr.c_catelog.erase(it1);
			break;
		}
		i++;
	}

	if (!flag)
		cout << "file" << " \"" << name << "\" not exists" << endl;
}
void free_disk_block(int block)
{
	if (disk_stack.size() == 128)
	{
		cout << "no more size" << endl;
	}
	else
	{
		for (auto tmp : disk_index[block].block)
		{
			disk_stack.push_back(tmp);
		}
		vector<disk_Index>::iterator it;
		it = disk_index.begin() + block;
		disk_index.erase(it);
	}
}