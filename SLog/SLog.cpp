#include "stdafx.h"
#include "SLog.h"
#include <direct.h>

#define GetCurrentDir _getcwd
#pragma warning(disable:4996)
//Static SLog properties
 std::string SLog::FileName = "";
 std::string SLog::Path = "";
 std::ofstream SLog::LogWriter;
 int SLog::NumberExceptions = 0;
 bool SLog::Exceptions = false;
 std::vector<std::string> LogToAdd;
 bool SLog::ShowConsoleLog = true;
 bool SLog::StopWriteToFile = false;
 ConsoleHelper SLog::Console;

 //Static ConsoleHelper properties
 CONSOLE_SCREEN_BUFFER_INFO ConsoleHelper::ConsoleInfo;
 HANDLE ConsoleHelper::Hstdout;
 int ConsoleHelper::SavedColors;

 //SLog method
void SLog::SetColor(LogType Type)
{
	ConsoleHelper::ChangeColor(Type);
}

void SLog::ResetColor()
{
	ConsoleHelper::Reset();
}

std::string SLog::SetTag(LogType Type)
{
	switch (Type)
	{
	case None:
		break;
	case Thread:
		return "[Thread]";
	case ThreadEx:
		return "[ThreadEx]";
	case Log:
		return "[Log]";
	case Exception:
		return "[Exception]";
	case HandlingEx:
		return "[HandlingEx]";
	case Warning:
		return "[Warning]";
	case Info:
		return "[Info]";
	default:
		break;
	}
	return "";
}

std::string SLog::GetCurrentWorkingDir()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

std::string SLog::GetTime(bool Date)
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	if(Date)
		oss << std::put_time(&tm, "%d-%m-%Y %H:%M:%S");
	else
		oss << std::put_time(&tm, "%H:%M:%S");
	return oss.str();
}

SLog::SLog(std::string FileName, std::string Path)
{
	this->FileName = FileName;
	if (Path == "")
	{
		this->Path = SLog::GetCurrentWorkingDir();
	}
	else
		this->Path = Path;
	if (this->FileName.find(".txt") == std::string::npos)
		this->FileName += ".txt";
	else
		std::cout << std::endl;
	this->LogWriter = std::ofstream(this->Path + this->FileName, std::ios::out);
	this->LogWriter << "Start SLog: " << this->GetTime(true) << std::endl;
	NumberExceptions = 0;
	Exceptions = false;
	ShowConsoleLog = true;
	StopWriteToFile = false;
}

void SLog::Display(std::string Message, LogType Type)
{
	std::string Output = SLog::SetTag(Type) + " " + GetTime() + " ==> " + Message;
	if (ShowConsoleLog)
	{
		ConsoleHelper::ChangeColor(Type);
		std::cout << Output << std::endl;
		ConsoleHelper::Reset();
	}
	if (!StopWriteToFile)
	{
		LogWriter << Output << std::endl;
	}
}

void SLog::Display(std::exception Ex, std::string Message, LogType Type)
{
	std::string Output = SLog::SetTag(Type) + " " + GetTime() +  " ==> " + Ex.what() + " | " +  Message ;
	if (ShowConsoleLog)
	{
		ConsoleHelper::ChangeColor(Type);
		std::cout << Output << std::endl;
		ConsoleHelper::Reset();
	}
	if (!StopWriteToFile)
	{
		LogWriter << Output << std::endl;
	}
}

void SLog::SetShowConsoleLog(bool Value)
{
	ShowConsoleLog = Value;
}

void SLog::SetStopWriteToFile(bool Value)
{
	StopWriteToFile = Value;
}

void SLog::Abort()
{
	LogWriter.close();
	ShowConsoleLog = false;
	StopWriteToFile = true;
}

SLog::~SLog()
{
	LogWriter.close();
}

//ConsoleHelper Method

WORD ConsoleHelper::GetConsoleTextAttribute(HANDLE hCon)
{
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);

	return con_info.wAttributes;
}

ConsoleHelper::ConsoleHelper()
{
	Hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(Hstdout, &ConsoleInfo);
	SavedColors = GetConsoleTextAttribute(Hstdout);
	
}

void ConsoleHelper::ChangeColor(LogType Type)
{

	switch (Type)
	{
	case None:
		break;
	case Thread:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		break;
	case ThreadEx:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case Log:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		break;
	case Exception:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
		break;
	case HandlingEx:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_GREEN | FOREGROUND_RED);
		break;
	case Warning:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_GREEN | FOREGROUND_RED |FOREGROUND_INTENSITY);
		break;
	case Info:
		SetConsoleTextAttribute(ConsoleHelper::Hstdout, FOREGROUND_GREEN);
		break;
	default:
		break;
	}
}

void ConsoleHelper::Reset()
{
	SetConsoleTextAttribute(ConsoleHelper::Hstdout, ConsoleHelper::SavedColors);
}
