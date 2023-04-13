#pragma once
#ifndef CLASS_H
#define CLASS_H
#include <string>



class Location
{
private:
    std::string Country;
    std::string Town;
    std::string Street;
    std::string Number;
public:
    Location();
    void SetLocation(const std::string country, const std::string town, const std::string street, const std::string number);
    void PrintLocation();
};

class Date
{
private:
    int Day;
    int Month;
    int Year;
public:
    Date();
    void SetDate(const int day, const int month, const int year);
    void PrintDate();
};

class Event
{
private:
    std::string Event_Name;
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

    //Printing Event Information.
    void PresentEvent();
};




#endif