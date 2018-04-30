# SLog
Mniejsza biblioteka do wypisywania logow w konsoli oraz do pliku.
Do swojego projektu wystarczy dolaczyc plik SLog.h oraz SLog.cpp
W pliku z funkcja <code>main</code> dodac <code>#include "SLog.h"</code> i stworzyc instancje obiektu.
## Typy logow

Typ | Przeznaczenie
----|--------------
None | -
Log | Wazna informacja
Exception | Informacja o wyjątku
HandlingEx | Informacja o obsludze wyjatku
Thread | Informacja o wątku
ThreadEx | Informacje o wyjatku watku
Warning | Ostrzezenie
Info | Informacja

## Metody publiczne
```c++
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
```
## Przyklady wykorzystania metod
```c++
//Tworzenie obiektu
SLog Loger = SLog("TestTworzeniaLogu","C:\\Users\\Adii\\Desktop\\"); //Stworzenie obiektu SLog. Wystarczy stworzyc jeden obiekt na caly projekt
SLog Loger2 = SLog("Test"); //Stworzy plik o nazwie Test.txt w folderze w ktorym wywolywany jest dany kod

//Metody Display
SLog::Display("Czesc!", Thread); //Wypisze do pliku oraz Konsoli "Czesc!" z Tagiem [THREAD] (w konsoli w kolorze zielonym)
SLog::Display(std::exception("Jakies tam ex"), "HAHA"); //Wypisze do pliku oraz konsoli szczegoly Exception z dodatkowa wiadomoscia "HAHA". (w konsoli w kolorze czerwonym)
SLog::Display("Tester kolorow"); //Wypisze do pliku oraz konsoli "Tester kolorow"

//Typy logow
SLog::Display("Thread", Thread);
SLog::Display("Log", Log);
SLog::Display("ThreadEx", ThreadEx);
SLog::Display("Exception", Exception);
SLog::Display("HandlingEx", HandlingEx);
SLog::Display("Warning", Warning);
SLog::Display("Info", Info);
SLog::Display("Koniec!");


SLog::SetShowConsoleLog(false); //Wylaczenie logow w konsoli
SLog::SetStopWriteToFile(true); //Zaprzestanie wypisywania logow do pliku
SLog::NumberOfExceptions(); //Zwroci ilosc przyjetych Exception przez metode Display
SLog::HasExceptions(); //Zwroci flage oznaczajaca czy metoda Display przyjela przynajmniej jedno exception
SLog::Abort(); //Metoda niebezpieczna. Przymusowe zamkniecie logow w konsoli i pliku. Po jej uzyciu nie mozna zrestartowac obiektu SLog.
```

# Przyklad

## Kod
```c++
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
```
## Output

### Konsola

    [Log] 14:08:06 ==> Czesc!

    [Exception] 14:08:06 ==> Blad krytyczny! | Blad w funkcji main!

--------------------------
### Plik Test.txt

    Start SLog: 30-04-2018 14:08:06

    [Log] 14:08:06 ==> Czesc!

    [Exception] 14:08:06 ==> Blad krytyczny! | Blad w funkcji main!