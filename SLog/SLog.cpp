#include "stdafx.h"
#include "SLog.h"
#include <direct.h>
#define GetCurrentDir _getcwd
 std::string SLog::FileName = "";
 std::string SLog::Path = "";
 std::ofstream SLog::LogWriter = std::ofstream("");
 int SLog::NumberExceptions = 0;
 bool SLog::Exceptions = false;
//ic std::vector<std::string> LogToAdd;
 bool SLog::ShowConsoleLog = true;
 bool SLog::StopWriteToFile = false;

void SLog::SetColor(TypeLog Type)
{

}

void SLog::ResetColor()
{

}

std::string SLog::SetTag(TypeLog Type)
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

SLog::SLog(std::string FileName, std::string Path)
{
	this->FileName = FileName;
	if (Path == "")
	{
		this->Path = SLog::GetCurrentWorkingDir();
	}
	else
		this->Path = Path;
	if (FileName.find(".txt") != std::string::npos)
		std::cout << std::endl;
	else
		this->FileName += ".txt";
	this->LogWriter = std::ofstream(FileName, std::ios::out);
	NumberExceptions = 0;
	Exceptions = false;
	ShowConsoleLog = true;
	StopWriteToFile = false;
}

void SLog::Display(std::string Message, TypeLog Type)
{
	std::string Output = SLog::SetTag(Type) + ": " + Message;
	//ChangeColor
	if (ShowConsoleLog)
	{
		//ChangeColor
		std::cout << Output << std::endl;
		//Reset Color
	}
	if (!StopWriteToFile)
	{
		LogWriter << Output << std::endl;
	}
}

void SLog::Display(std::exception Ex, std::string Message, TypeLog Type)
{
	std::string Output = SLog::SetTag(Type) + ": " + Ex.what() + " | " +  Message ;
	if (ShowConsoleLog)
	{
		//ChangeColor
		std::cout << Output << std::endl;
		//Reset Color
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
}

SLog::~SLog()
{
	LogWriter.close();
}
