// SLog.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SLog.h"
#include <iostream>
#include <cstdlib>
#include <exception>

int main()
{
	//Tworzenie obiektu
	SLog Loger = SLog("Test.txt","C:\\Users\\Adii\\Desktop\\");  //Stworzenie pliku o nazwie Test.txt w sciezce C:\Users\Adii\Desktop\

	SLog::Display("Czesc!", Log); //Wyswietli tekst na konsoli i w pliku
	SLog::Display(std::exception("Blad krytyczny!"), "Blad w funkcji main!"); //Wysiwetli szczegoly wyjatku oraz wiadomosc Blad w funkcji main

	system("pause");
    return 0;
}

