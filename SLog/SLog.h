#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include <sstream>
#include <iomanip>

//Type of log
enum LogType
{
	//Default type
	None, 
	//Type for Log
	Log,
	//Type for Thread
	Thread,
	//Type for ThreadException
	ThreadEx,
	//Type for Exception
	Exception,
	//Type for Handling Exception
	HandlingEx,
	//Type for Warnings
	Warning,
	//Type for Info
	Info
};

//https://stackoverflow.com/questions/25402017/changing-background-and-text-colour-in-a-windows-console-c
class ConsoleHelper
{
private:
	//Console 
	static CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;

	//Handler for standart output
	static HANDLE Hstdout;

	//Default font color
	static int SavedColors;

	//This Method get default console settings
	WORD GetConsoleTextAttribute(HANDLE hCon);

public:
	//Constructor
	ConsoleHelper();

	//This Method change font color in console
	static void ChangeColor(LogType Type);

	//This Method reset font color in console
	static void Reset();
};

class SLog
{
private:
//Properties
	//File name where log will be saved
	static std::string FileName;

	//Path to log file
	static std::string Path;

	//Handler for writing to file
	static std::ofstream LogWriter;

	//Number of received exception by SLog::Display
	static int NumberExceptions;

	//Flag that describe if SLog::Dispaly received at least one exception
	static bool Exceptions;

	//
	static std::vector<std::string> LogToAdd;

	//Flag that describe if log will be shown in console
	static bool ShowConsoleLog;

	//Flag that describe if log will not be saved in file
	static bool StopWriteToFile;

	//This object help with changing console settings
	static ConsoleHelper Console;

//Method
	//This Method change font color by LogType
	static void SetColor(LogType Type = None);

	//Thid Method reset font color to deafult settings
	static void ResetColor();

	//This Method return tag of Log
	static std::string SetTag(LogType Type = None);

	//This Method return Path to current directory where this code is executed
	static std::string GetCurrentWorkingDir();

	//This Method return Date/Time. If argument will be true return Date + Time in the oposite case return Time
	static std::string GetTime(bool Date = false);

	//TODO:
	//Add Loading data from xml file for sending log file via ftp
public:

	//Constructor
	SLog(std::string FileName, std::string Path ="");

	//This method show Message with spiecified Tag. Message will be transferred to Console and File according to the flags
	static void Display(std::string Message, LogType Type = None);

	//This method show Message and Exception with spiecified Tag. Message will be transferred to Console and File according to the flags
	static void Display(std::exception Ex, std::string Message, LogType Type = Exception);

	//This Method Set flag for ConsoleLog. If true then  the log will be shown in the console
	static void SetShowConsoleLog(bool Value);

	//This Method Set Flag for WriteToFile. If true then the log will not be saved to the file 
	static void SetStopWriteToFile(bool Value);

	//This Method return flag if SLog received at least one Exception
	static inline bool HasExceptions() { return Exceptions; }

	//This Method return number of Exception that SLog received
	static inline int NumberOfExceptions() { return NumberExceptions; }

	//This Method close all functionality! This Method is unsafe
	static void Abort();

	//Destructor
	~SLog();
};

