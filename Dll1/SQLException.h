#pragma once
#include<exception>

class  __declspec(dllexport) SQLException :public std::exception
{
private:
	int errcode;

public:
	SQLException(const char* msg) :std::exception(msg) {
		errcode = 0;
	}

	SQLException(const char* msg, int err) :std::exception(msg), errcode(err) {

	}

	int geterrcode() const
	{
		return errcode;
	}
};