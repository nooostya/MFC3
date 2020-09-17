#pragma once
#include <list>
#include<string>
#include "userData.h"

bool ToXml(const std::wstring& filePath, std::list<userData>& data);
bool FromXml(const std::wstring& filePath, std::list<userData>& data);


