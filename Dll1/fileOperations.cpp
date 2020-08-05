#include "pch.h"
#include "fileOperations.h"



void fileOperations::readData(UserDataList & dataList)
{
	std::fstream f("C:\\DataBase\\names.txt", std::ios::in);
	d.number = 1;
	if (!f.is_open())
	{
		throw SQLException("couldn`t open file");
	}
	while (!f.eof())
	{
		f >> d.name >> d.birthday;
		d.number++;
		dataList.push_back(d);
	}
	f.close();
}

void fileOperations::inputData(UserDataList & dataList)
{
	while (true)
	{
		std::cout << "name: " << std::endl;

		std::getline(std::cin, name);
		if (name.empty())
		{
			std::cout << "Name error" << std::endl;
			throw SQLException("name error");
			break;
		}
	again:
		std::cout << "birthday : ";
		std::getline(std::cin, birthdayStr);

		if (birthdayStr.empty())
		{
			break;
		}

		birthday = atoi(birthdayStr.c_str());
		if (birthday == 0) {
			std::cout << "Not valid, try again" << std::endl;
			goto again;
		}

		userData d;
		d.name = name;
		d.birthday = birthday;
		dataList.push_back(d);

	}
}
