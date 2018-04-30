#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <windows.h>

enum TypeLog
{
	None,
	Log,
	Thread,
	ThreadEx,
	Exception,
	HandlingEx,
	Warning,
	Info
};

class ConsoleHelper
{
	static CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);


public:
	ConsoleHelper()
	{
		GetConsoleScreenBufferInfo(hstdout, &ConsoleInfo);

	}
};

class SLog
{
//private:
	static std::string FileName;
	static std::string Path;
	static std::ofstream LogWriter;
	static int NumberExceptions;
	static bool Exceptions;
	//static std::vector<std::string> LogToAdd;
	static bool ShowConsoleLog;
	static bool StopWriteToFile;

	static void SetColor(TypeLog Type = None);
	static void ResetColor();
	static std::string SetTag(TypeLog Type = None);
	static std::string GetCurrentWorkingDir();
	static ConsoleHelper Console;
	//TODO:
	//Add Loading data from xml file for sending log file via ftp
public:
	SLog(std::string FileName, std::string Path ="");
	static void Display(std::string Message, TypeLog Type = None);
	static void Display(std::exception Ex, std::string Message, TypeLog Type = Exception);
	static void SetShowConsoleLog(bool Value);
	static void SetStopWriteToFile(bool Value);
	static inline bool HasExceptions() { return Exceptions; }
	static inline int NumberOfExceptions() { return NumberExceptions; }
	static void Abort();
	~SLog();
};

