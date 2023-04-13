#pragma once
#ifndef FUNCTION_H
#define FUNCTION_H
#include <string>
#include <ctime>


void MainMenu();
void GetTodaysDate();
void CheckCalendarMenu(bool &GoBack);
bool ValidateInputYearData( const std::string &Year, bool &LoopBool);
void AddEventMenu(bool& LoopBool);

#endif