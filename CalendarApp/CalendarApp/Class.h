#pragma once
#ifndef CLASS_H
#define CLASS_H
#include <string>
#include <vector>


class EventLocation
{
private:
    std::string Country;
    std::string Town;
    std::string Street;
    std::string Number;
public:
    //Empty Location Object Constructor
    EventLocation();

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

class EventTime
{
public:
    // Prints Date or Time
    virtual void Print() = 0;

    // returns Year or Hour
    virtual int GetFirstValue() = 0;

    //returns Month or minute
    virtual int GetSecondValue() = 0;

    //returns Day
    virtual int GetThirdValue() = 0;
};


class Date: public EventTime
{
private:
    int Day;
    int Month;
    int Year;
public:
    //Empty Date Object Constructor
    Date();

    //Full Date Object Constructor
    Date(const int day, const int month, const int year);

    //Function which returns Date year
    int GetFirstValue() override;

    //Function which returns Date month
    int GetSecondValue() override;

    //Function which returns Date day
    int GetThirdValue() override;

    //Printing Date Object
    void Print() override;


   

};

class Clock : public EventTime
{
private: 
    int Hour;
    int Minute;
public:
    //Empty Time Constructor
    Clock();

    //Full Time Constructor
    Clock(int hour, int minute);

    //Function which returns Date hour
    int GetFirstValue() override;

    //Function which returns Date minute
    int GetSecondValue() override;
    

    int GetThirdValue() override;

    //Printing Clock Object
    void Print() override;
   
  
};


class Event
{
private:
    std::string EventName;
    std::vector<EventTime*> EventTimeVector;
    EventLocation* Location;
    bool Repetable;
public:
    
    //Empty Event Constructor
    Event();

    //No Location Event Constructor;
    Event(std::string eventname, std::vector<EventTime*>  eventTimeVector, const bool repetableEvent);

    //Full Event Constructor
    Event( std::string eventname, std::vector<EventTime*>  eventTimeVector, EventLocation* eventLocation, const bool repetableEvent);

    //Function to get Event Name
    std::string GetEventName();

    //Function to get Event Date
    std::vector<EventTime*> GetDate();

    //Function to get Event Location
    EventLocation* GetLocation();

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

    EventHolder(std::vector<Event> EventsVector);

    //Function to pushback() Event to EventHolder
    EventHolder operator+(Event event);

    //Function to access i value of EventHolder vector
    Event GetEvent(int EventNumber);

    //Function which returns EventHolder vector size
    int AllEventsSize();

    //Function which clears vector
    void ClearVector();
   
    //Function which removes given event
    void RemoveEvent(int &EventId);
};


#endif