#include "XmlSerialization.h"
#include "pugixml.hpp"
#include "SQLException.h"

bool ToXml(const std::wstring& filePath, std::list<userData>& dataList)
{
	pugi::xml_document doc;

	pugi::xml_node data = doc.append_child("data");

	for (auto it = dataList.begin(); it != dataList.end(); it++) 
	{
		pugi::xml_node person = data.append_child("person");
		person.append_child("number").text() = it->number;
		person.append_child("name").text() = it->name.c_str();
		person.append_child("birthday").text() = it->birthday;
	}

	doc.save_file(filePath.c_str());
	if (!doc.save_file(filePath.c_str())) {
		throw SQLException("save file error");
		return false;
	}

	return true;
}

bool FromXml(const std::wstring& filePath, std::list<userData>& data)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(filePath.c_str());

	if (!result)
	{
		throw SQLException("load file error", result);
		return false;
	}
	
	pugi::xpath_query person_query("/data/person");

	pugi::xpath_query number_query("number/text()");
	pugi::xpath_query name_query("name/text()");
	pugi::xpath_query birthday_query("birthday/text()");

	pugi::xpath_node_set xpath_people = doc.select_nodes(person_query);

	for (auto it = xpath_people.begin(); it != xpath_people.end(); it++)
	{
		pugi::xml_node person = it->node();

		pugi::xml_node number = person.select_node(number_query).node();
		pugi::xml_node name = person.select_node(name_query).node();
		pugi::xml_node birthday = person.select_node(birthday_query).node();


		userData e;
		e.number = atoi(number.value());
		e.name = name.value();
		e.birthday = atoi(birthday.value());
		data.push_back(e);
	}

	return true;
}
