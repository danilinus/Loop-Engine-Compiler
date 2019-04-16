#include <algorithm>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

//Глобальные настройки приложения
#pragma region Global settings

char *path = nullptr;
char *input = "input.cpp";
char *output = "output.cpp";
int tab = 4;
vector<char *> include;

#pragma endregion

//Просмотр аргументов для анализа
#pragma region Args for analyze

const int enum_cato_size = 4;

char **enum_cato = new char *[enum_cato_size] {
	"-in",
		"-out",
		"-I",
		"-tab"
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

void((*args_checkers[enum_cato_size]))(vector<char *> s) = {input_checker, output_checker, include_checker, tab_checker};

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

	return 0;
}