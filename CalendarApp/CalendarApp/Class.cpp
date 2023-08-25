#include "Class.h"
#include "function.h"
#include <iostream>
#include <vector>
#include <string>

#pragma region LoctionClass
EventLocation::EventLocation()
	: Country(), Town(), Street(), Number() {}
void EventLocation::SetLocation(const std::string country, const std::string town, const std::string street, const std::string number)
{
	Country = country;
	Town = town;
	Street = street;
	Number = number;
}

std::string EventLocation::GetCountry()
{
	return Country;
}

std::string EventLocation::GetTown()
{
	return Town;
}

std::string EventLocation::GetStreet()
{
	return Street;
}

std::string EventLocation::GetNumber()
{
	return Number;
}


void EventLocation::PrintLocation()
{
	std::cout << Country << " " << Town << " " << Street << " " << Number;
}
#pragma endregion

#pragma region DateClass
Date::Date() :
	Year(), Month(), Day() {}

Date::Date(const int day, const int month, const int year) : Day(day), Month(month), Year(year) {}

int Date::GetFirstValue()
{
	return Year;
}

int Date::GetSecondValue()
{
	return Month;
}

int Date::GetThirdValue()
{
	return Day;
}



void Date::Print()
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
	else
	{
		std::cout << "0000";
	}
	std::cout << " | ";
}
#pragma endregion

#pragma region ClockClass

Clock::Clock() :
	Hour(), Minute() {}

Clock::Clock(int hour, int minute) : Hour(hour), Minute(minute) {}

void Clock::Print()
{
	if (Hour < 10)
	{
		std::cout << "0" << Hour;
	}
	else {
		std::cout << Hour;
	}
	std::cout << ":";
	
	if (Minute < 10 && Minute != 0)
	{
		std::cout << "0" << Minute;
	}
	else if (Minute == 0)
	{
		std::cout << "00";
	}
	else
	{
		std::cout << Minute;
	}
	std::cout << " | ";
}

int Clock::GetFirstValue()
{
	return Hour;
}

int Clock::GetSecondValue() 
{
	return Minute;
}

int Clock::GetThirdValue()
{
	return 0;
}

#pragma endregion

#pragma region EventClass
Event::Event() :
	EventName(""), EventTimeVector(), Location(nullptr), Repetable(nullptr) {}

Event::Event(std::string eventName, std::vector<EventTime*> eventTimeVector, const bool repetableEvent) :
	EventName(eventName), EventTimeVector(eventTimeVector), Location(nullptr), Repetable(repetableEvent) {}

Event::Event( std::string eventName, std::vector<EventTime*> eventTimeVector, EventLocation* eventLocation, const bool repetableEvent) :
	EventName(eventName), EventTimeVector(eventTimeVector), Location(eventLocation), Repetable(repetableEvent) {}


std::string Event::GetEventName()
{
	return EventName;
}

std::vector<EventTime*> Event::GetDate()
{
	return EventTimeVector;
}

EventLocation* Event::GetLocation()
{
	return Location;
}

bool Event::GetRepetable()
{
	return Repetable;
}

void Event::PresentEvent()
{
	std::cout << EventName << " ";
	EventTimeVector[0]->Print();
	std::cout << " ";
	EventTimeVector[1]->Print();
	std::cout << " ";
	Location->PrintLocation();
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

EventHolder::EventHolder(std::vector<Event> EventsVector): AllEvents(EventsVector) {}

EventHolder EventHolder::operator+(Event event) {

	AllEvents.push_back(event);
	
	return EventHolder(AllEvents);
}

Event EventHolder::GetEvent(int EventNumber)
{
	return AllEvents[EventNumber];
}

int EventHolder::AllEventsSize()
{
	return AllEvents.size();
}
void EventHolder::ClearVector()
{
	   AllEvents.clear();
}

void EventHolder::RemoveEvent(int& EventId)
{
	AllEvents.erase(AllEvents.begin() + EventId);;
}
#pragma endregion