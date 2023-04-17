#include "Class.h"
#include "function.h"
#include <iostream>
#include <vector>
#include <string>

#pragma region LoctionClass
Location::Location()
	: Country(), Town(), Street(), Number() {}
void Location::SetLocation(const std::string country, const std::string town, const std::string street, const std::string number)
{
	Country = country;
	Town = town;
	Street = street;
	Number = number;
}

std::string Location::GetCountry()
{
	return Country;
}

std::string Location::GetTown()
{
	return Town;
}

std::string Location::GetStreet()
{
	return Street;
}

std::string Location::GetNumber()
{
	return Number;
}
void Location::PrintLocation()
{
	std::cout << Country << " " << Town << " " << Street << " " << Number;
}
#pragma endregion

#pragma region DateClass
Date::Date() :
	Year(), Month(), Day() {}

void Date::SetDate(const int day, const int month, const int year)
{
	Day = day;
	Month = month;
	Year = year;
}

int Date::GetYear()
{
	return Year;
}

int Date::GetMonth()
{
	return Month;
}

int Date::GetDay()
{
	return Day;
}

void Date::PrintDate()
{

	std::cout<<" | " << Day << ".";
	if (Month < 10)
	{
		std::cout << "0" << Month;
	}else std::cout<< Month;
	std::cout << ".";
	if (Year != 0)
	{
		std::cout << Year;
	}
	std::cout << " | ";
}
#pragma endregion

#pragma region EventClass
Event::Event() :
	EventName(""), date(nullptr), location(nullptr), Repetable(nullptr) {}

Event::Event(std::string eventName, Date* eventDate, const bool repetableEvent) :
	EventName(eventName), date(eventDate), location(nullptr), Repetable(repetableEvent) {}

Event::Event( std::string eventName, Date* eventDate, Location* eventLocation, const bool repetableEvent) : 
	EventName(eventName), date(eventDate), location(eventLocation), Repetable(repetableEvent) {}


std::string Event::GetEventName()
{
	return EventName;
}

Date* Event::GetDate()
{
	return date;
}

Location* Event::GetLocation()
{
	return location;
}

bool Event::GetRepetable()
{
	return Repetable;
}

void Event::PresentEvent()
{
	std::cout << EventName << " ";
	date->PrintDate();
	std::cout << " ";
	location->PrintLocation();
	std::cout << " |";
	if (Repetable)
	{
		std::cout << " Yes";
	}else std::cout << " No";
	std::cout<<std::endl;

}
#pragma endregion

#pragma region EventHolderClass
EventHolder::EventHolder() {}

void EventHolder::EventHolderPushBack(Event event) {

	AllEvents.push_back(event);
}

Event EventHolder::GetEvent(int EventNumber)
{
	return AllEvents[EventNumber];
}

int EventHolder::AllEventsSize()
{
	return AllEvents.size();
}
#pragma endregion