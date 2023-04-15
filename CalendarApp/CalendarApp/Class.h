#pragma once
#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>


class Location
{
private:
    std::string Country;
    std::string Town;
    std::string Street;
    std::string Number;
public:
    //Empty Location Object Constructor
    Location();

    //Full Location Object Constructor
    void SetLocation(const std::string country, const std::string town, const std::string street, const std::string number);

    //Function which returns Location Country
    std::string GetCountry();

    //Function which returns Location Town
    std::string GetTown();  

    //Function which returns Location Street
    std::string GetStreet();

    //Function which returns Location Number
    std::string GetNumber();

    //Printing Location Object
    void PrintLocation();
};

class Date
{
private:
    int Day;
    int Month;
    int Year;
public:
    //Empty Date Object Constructor
    Date();

    //Full Date Object Constructor
    void SetDate(const int day, const int month, const int year);

    //Function which returns Date year
    int GetYear();

    //Function which returns Date month
    int GetMonth();

    //Function which returns Date day
    int GetDay();

    //Printing Date Object
    void PrintDate();
};

class Event
{
private:
    std::string EventName;
    Date* date;
    Location* location;
    bool Repetable;
public:
    
    //Empty Event Constructor
    Event();

    //No Location Event Constructor;
    Event(std::string eventName, Date* eventDate, const bool repetableEvent);

    //Full Event Constructor
    Event( std::string eventName, Date* eventDate, Location* eventLocation, const bool repetableEvent);

    //Function to get Event Name
    std::string GetEventName();

    //Function to get Event Date
    Date* GetDate();

    //Function to get Event Location
    Location* GetLocation();

    //Function to get Event RepetableBool
    bool GetRepetable();

    //Printing Event Information.
    void PresentEvent();
};

class EventHolder
{
private:
    std::vector<Event> AllEvents;

public:

    //EventHolder Constructor
    EventHolder();

    //Function to pushback() Event to EventHolder
    void EventHolderPushBack(Event event);

    //Function to access i value of EventHolder vector
    Event GetEvent(int EventNumber);

    //Function which returns EventHolder vector size
    int AllEventsSize();
};


#endif