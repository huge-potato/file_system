#include"header.h"
vector<int> i_stack;
vector<int> disk_stack;
disk_block disk[10240];
i_node index[128];
vector<i_node_memory> i_node_mem;
vector<cataLog> catalog;
vector<disk_Index> disk_index;
vector<int>disk_index_free;
vector<INAMEindex> inameindex;   //i�ڵ�����
vector<IDATEindex> idateindex;
vector<ITYPEindex> itypeindex;
vector<int> path;
vector<User> user;
vector<int> catalog_free;
int username_id;
int free_i;						//����i�ڵ��
void load_user();
void init();
void create_folder(string command);
void change_path(string command);
void show_folder(string  command);
void create(string command);
void delete_file(string command);
void edit(string a);            //�༭
void search_file(string command);
void open_file(string command);
bool compare_arry(vector<int> a, vector<int> b);
int find_block(string name);
void close_file(string command);
void save();
void copy(string command);
void move(string command);
void rename(string name);
void backstage();
void l();
void info();
void format();
void add_user(string command);
int check_user(string username, string password);
void delete_user(string command);
void change_password(string command);

int main()
{
	string username;
	string password;
	string command;
	string subcommand;
	string temp_path;
	char t;
	load_user();
	init();
	save();
	while (1)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
		cout << "welcome to system" << endl;
		cout << "please login" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		while (1)
		{
			username = "";
			password = "";
			cout << "username:";
			cin >> username;
			cout << "password:";
			while ((t = _getch()) != '\r')
			{
				if (t == '\b')
				{
					password = password.substr(0, password.length() - 1);
				}
				else
					password += t;
			}
			if (check_user(username, password))
			{
				break;
			}
			else{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << endl << "username or password error" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
		}
		system("cls");
		getline(cin, command);
		while (1)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
			cout << username;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED);
			cout << "@filesystem ";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
			if (path.size() == 1)
				cout << "/";
			else
			{
				for (auto p : path)
				{
					if (p == 0)
						continue;
					cout << "/" << catalog[p].info.name;
				}
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			cout << endl << ">";
			getline(cin, command);
			stringstream command_stream(command);
			command_stream >> subcommand;
			if (subcommand == "")
			{

			}
			else if (subcommand == "cd")
			{
				change_path(command);
			}
			else if (subcommand == "ls")
			{
				show_folder(command);
			}
			else if (subcommand == "create")
			{
				create(command);
			}
			else if (subcommand == "mkdir")
			{
				create_folder(command);
			}
			else if (subcommand == "delete")
			{
				delete_file(command);
			}
			else if (subcommand == "edit")
			{
				edit(command);
			}
			else if (subcommand == "search")
			{
				search_file(command);
			}
			else if (subcommand == "open")
			{
				open_file(command);
			}
			else if (subcommand == "close")
			{
				close_file(command);
			}
			else if (subcommand == "cp")
			{
				copy(command);
			}
			else if (subcommand == "mv")
			{
				move(command);
			}
			else if (subcommand == "bs"){
				backstage();
			}
			else if (subcommand == "l"){
				l();
			}
			else if (subcommand == "info"){
				info();
			}
			else if (subcommand == "format")
			{
				char c;
				cout << "Are you sure you want to format the disk?(y/N)";
				c = _getch();
				if (c == 'n' || c == 'N' || c == '\r')
				{
					cout << c << endl;
					continue;
				}
				else if (c == 'y' || c == 'Y')
				{
					remove("disk.txt");
					remove("diskdata.txt");
					init();
					cout << c << "\nformat complete" << endl;
				}
			}
			else if (subcommand == "useradd")
			{
				add_user(command);
			}
			else if (subcommand == "userdelete")
			{
				delete_user(command);
			}
			else if (subcommand == "passwd")
			{
				change_password(command);
			}
			else if (subcommand == "clear")
			{
				system("cls");
			}
			else if (subcommand == "exit")
			{
				system("cls");
				break;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
				cout << "command not found" << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			}
			cout << endl;
			save();
			command = "";
			subcommand = "";
		}
	}
}