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

// Function Convert IntToString
std::string IntToString(int a);
#endif