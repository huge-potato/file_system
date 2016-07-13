#include "header.h"

extern vector<cataLog> catalog;
extern vector<int> disk_stack;		//���д��̿�
extern i_node index[128];
extern vector<int> path;
extern vector<disk_Index> disk_index;
extern vector<INAMEindex> inameindex;   //i�ڵ�����
extern vector<IDATEindex> idateindex;
extern vector<ITYPEindex> itypeindex;
extern vector<int> allocata(int size);
int check_file(string fname, int path);
int ialloc();
extern int free_i;

void create(string command)
{
	child_catalog child_file;
	information file_info;
	stringstream command_stream(command);
	string command1, name, size, share;
	command_stream >> command1;
	command_stream >> name;
	command_stream >> size;
	command_stream >> share;
	int zhengsize = 0;

	if (name == "")
	{
		cout << "Please input filename" << endl;
		return;
	}
	else
	{
		//�ж�����
		if (check_file(name, path.back()))
		{
			cout << "create: Cannot create file \"" << name << "\":file exists" << endl;
			return;
		}
		//д���ļ���Ϣ������i�ڵ���Ϣ
		file_info.name = name;
		file_info.type = 0;
		char date[255];
		time_t t = time(0);
		strftime(date, 255, "%Y-%m-%d %H:%M:%S", localtime(&t));
		file_info.last_edit_time = file_info.create_time = date;
		//cout << file_info.create_time << endl;
		file_info.user = 0;
		if (size == "")
		{
			zhengsize = 512;
		}
		else if ((size[(size.size() - 1)] == 'k') || size[(size.size() - 1)] == 'K')
		{
			for (int i = size.size() - 2; i >= 0; i--)
			{
				zhengsize = zhengsize + (size[i] - '0') * (int)pow(10, size.size() - 2 - i);
			}
		}

		else if ((size[(size.size() - 1)] == 'm') || size[(size.size() - 1)] == 'M')
		{
			for (int i = size.size() - 2; i >= 0; i--)
			{
				zhengsize += (size[i] - '0') * (int)pow(10, size.size() - 2 - i);
			}
			zhengsize = zhengsize * 1000;
		}
		else
		{
			cout << "size is illegal" << endl;
			return;
		}
		file_info.size = zhengsize;
		disk_Index new_disk_index;					//������̿�
		new_disk_index.block = allocata(file_info.size);
		if (new_disk_index.block.size() == 0)
		{	
			return;
		}
		if (share == "n")
		{
			file_info.share = 0;
			file_info.readable = 0;
			file_info.writeable = 0;
		}
		else if (share == "swr" || share == "srw" || share == "")
		{
			file_info.share = 1;
			file_info.readable = 1;
			file_info.writeable = 1;

		}
		else if (share == "sr")
		{
			file_info.share = 1;
			file_info.readable = 1;
			file_info.writeable = 0;
		}
		else{
			cout << "command is not exists" << endl;
			return;
		}
		free_i = ialloc();
		if (free_i == -1)
		{
			return;
		}
		//�ж��ļ����� string ftype
		unsigned int i;
		for (i = name.size(); i > 0; i--)
		{
			if (name[i] == '.')
			{
				unsigned int j = i;
				while (j < name.size() - 1)
				{
					file_info.ftype += file_info.name[++j];
				}
				break;
			}
		}
		if (i == 0)
			file_info.ftype = "file";
		//cout << file_info.ftype << endl;

		file_info.path = path;
		file_info.block = disk_index.size();
		index[free_i].info = file_info;

		INAMEindex new_inameindex;                       //�����ļ�������
		new_inameindex.id = free_i;
		new_inameindex.name = index[free_i].info.name;
		inameindex.push_back(new_inameindex);

		IDATEindex new_idateindex;                      //������������
		new_idateindex.id=free_i;
		new_idateindex.date=index[free_i].info.last_edit_time;
		idateindex.push_back(new_idateindex);

		ITYPEindex new_itypeindex;                      //������������
		new_itypeindex.id = free_i;
		new_itypeindex.type = index[free_i].info.ftype;
		itypeindex.push_back(new_itypeindex);

		cataLog new_catalog;
		new_catalog.id = catalog.size();
		new_catalog.info = file_info;
		new_catalog.addr.flag = 0;
		new_catalog.addr.i_node = free_i;
		catalog.push_back(new_catalog);
		child_file.id = new_catalog.id;
		child_file.name = name;
		catalog[path.back()].addr.c_catalog.push_back(child_file);
		disk_index.push_back(new_disk_index);		//����������������



	}

}

//������д��̿�
vector<int> allocata(int size)
{
	vector<int> free_block;
	unsigned int block_num = (unsigned int)ceil(size / BLOCKSIZ);
	if (disk_stack.size() < block_num)
	{
		cout << "no more free blocks" << endl;
		return free_block;
	}
	else
	{

		for (unsigned int i = 0; i < block_num; i++)
		{
			free_block.push_back(disk_stack.back());
			disk_stack.pop_back();
		}
		return free_block;
	}
}
//�������
int check_file(string fname, int path)
{
	for (auto file : catalog[path].addr.c_catalog)
	{
		if (fname == file.name && catalog[file.id].info.type == 0)
		{
			
			return file.id;
		}
	}
	return 0;
}
