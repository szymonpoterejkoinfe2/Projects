#include "Class.h"
#include "function.h"
#include <iostream>


//void Day:: presentDay()
//{
//    cout << "Today is: " << this->Number_Of_Day << " " << this->Day_Name << endl;
//}
//
//Day :: Day(const Day& other)
//{
//    this->Number_Of_Day = other.getNumber_Of_Day();
//    this->Day_Name = other.getDay_Name();
//}

Location::Location()
	: Country(), Town(), Street(), Number() {}
void Location::SetLocation(const std::string country, const std::string town, const std::string street, const std::string number)
{
	Country = country;
	Town = town;
	Street = street;
	Number = number;
}
void Location::PrintLocation()
{
	std::cout << Country << " " << Town << " " << Street << " " << Number;
}


Date::Date() :
	Year(), Month(), Day() {}
void Date::SetDate(const int day, const int month, const int year)
{
	Day = day;
	Month = month;
	Year = year;
}
void Date::PrintDate()
{
	std::cout << Day << " " << Month << " " << Year;
}

Event::Event() :
	Event_Name(nullptr), date(nullptr), location(nullptr),Repetable(nullptr) {}

Event::Event(const std::string eventName, Date* eventDate, Location* eventLocation, const bool repetableEvent) : 
	Event_Name(eventName), date(eventDate), location(eventLocation), Repetable(repetableEvent) {}

