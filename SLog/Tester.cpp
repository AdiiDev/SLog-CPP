// SLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SLog.h"
#include <iostream>
#include <cstdlib>
#include <exception>
int main()
{
	SLog Loger = SLog("nwm.txt");
	SLog::Display("Czesc!", Thread);
	SLog::Display(std::exception("Jakies tam ex"), "HAHA");

	system("pause");
    return 0;
}

