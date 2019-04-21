#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Глобальные настройки приложения
#pragma region Global settings

char *path = nullptr;
char *input = new char[9]{'i', 'n', 'p', 'u', 't', '.', 'c', 'p', 'p'};
char *output = new char[10]{'o', 'u', 't', 'p', 'u', 't', '.', 'c', 'p', 'p'};
char *cxxi = nullptr;
int tab = 4;
vector<char *> include;

#pragma endregion

struct rVariable
{
	string name = nullptr;
	string type = nullptr;
	string value = nullptr;

	rVariable(string Type, string Name, string Value = nullptr) : type(Type), name(Name), value(Value) {}
};

struct rConstructor
{
	vector<rVariable> args;
	string value = nullptr;

	rConstructor();
	rConstructor(string Value) : value(Value) {}
};

struct rVoid
{
	string name = nullptr;
	string type = nullptr;
	string value = nullptr;
	vector<rVariable> args;

	rVoid(string Type, string Name) : type(Type), name(Name) {}
	rVoid(string Type, string Name, string Value) : type(Type), name(Name), value(Value) {}
};

struct rStruct
{
	string name = nullptr;
	vector<rVariable> variables;
	vector<rConstructor> constructors;
	vector<rVoid> voids;

	rStruct(string Name) : name(Name) {}
};

struct rClass
{
	string name = nullptr;
	vector<rVariable> variables;
	vector<rConstructor> constructors;
	vector<rVoid> voids;

	rClass(string Name) : name(Name) {}
};

//Просмотр аргументов для анализа
#pragma region Args for analyze

const int enum_cato_size = 5;

char **enum_cato = new char *[enum_cato_size] {
	new char[3]{'-', 'i', 'n'},
		new char[4]{'-', 'o', 'u', 't'},
		new char[2]{'-', 'I'},
		new char[4]{'-', 't', 'a', 'b'},
		new char[4] { '-', 'd', 'l', 'l' }
};

void input_checker(vector<char *> s)
{
	input = s[1];
}

void output_checker(vector<char *> s)
{
	output = s[1];
}

void include_checker(vector<char *> s)
{
	s.erase(s.begin());
	include = s;
}

void tab_checker(vector<char *> s)
{
	tab = atoi(s[1]);
}

void cxxi_checker(vector<char *> s)
{
	cxxi = s[1];
}

void((*args_checkers[enum_cato_size]))(vector<char *> s) = {input_checker, output_checker, include_checker, tab_checker, cxxi_checker};

bool check_arg(vector<char *> s)
{
	for (int i = 0; i < enum_cato_size; i++)
		if (strcmp(s[0], enum_cato[i]) == 0)
		{
			args_checkers[i](s);
			return true;
		}
	return false;
}

vector<vector<char *>> to_check;

#pragma endregion

int main(int argc, char *argv[])
{

//Анализ аргументов
#pragma region Analyze args

	path = argv[0];
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
			to_check.resize(to_check.size() + 1);
		to_check[to_check.size() - 1].push_back(argv[i]);
	}
	for (int i = 0; i < to_check.size(); i++)
		check_arg(to_check[i]);

#pragma endregion

//Анализ кода
#pragma region Analize code

	try
	{
		//Открываем файл для чтения
		ifstream incpp(input);
		cout << "open " << input << " : ";
		if (!incpp.is_open())
			cout << "failure" << endl,
				throw new exception("error open input file");
		cout << "successfully" << endl;

		//Открываем файл(ы) для записи
		ofstream outcpp(output);
		cout << "open " << output << " : ";
		if (!outcpp.is_open())
			cout << "failure" << endl,
				throw new exception("error open output file");
		cout << "successfully" << endl;

#pragma region Closing files
		incpp.close();
		outcpp.close();
#pragma endregion
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
		return 1;
	}

#pragma endregion

	return 0;
}