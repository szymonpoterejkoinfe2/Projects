#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include "Class.h"

// Function which displays and manage main menu.
void MainMenu();

// Function which takes today's date from user device.
void GetTodaysDate();

// Function which displays and manage calendar menu.
void CheckCalendarMenu(bool &GoBack);

//Function which evaluate corectness of input year value.
bool ValidateInputYearData( const std::string &Year, bool &LoopBool);

// Function which displays and manage event addition menu.
void AddEventMenu(bool& GoBack,EventHolder &allEvents);

// Fonction which saves Event to text file.
void SaveEventInFile(Event EventToSave);

// Function Convert IntToString.
std::string IntToString(int Number);

//Function which reads all events for given year interval.
EventHolder FindEvents(std::string yearInterval[2]);

//Function which prints all events for given year interval.
void PresentAllEvents(EventHolder& FoundEvents);

// Function which prints calendar of given year to console.
void PrintCalendar(int &Year, EventHolder& allEvents);

//function which returns the position of first day in month.
int DayNumber(int day, int month, int year);

// Function which returns name of month from numerical form.
std::string getMonthName(int monthNumber);

//Function which returns number of days in given month.
int numberOfDays(int monthNumber, int year);
#endif