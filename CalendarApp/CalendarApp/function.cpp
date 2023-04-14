#include "function.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>


void MainMenu()
{
	std::vector<Event> AllEvents;
	char UserSelection;
	bool LoopingCondition = true;
	while (LoopingCondition)
	{
		GetTodaysDate();
		std::cout << " Chose what you want to do:" << std::endl << "1. Check calendar" << std::endl << "2. Add event" << std::endl << "3. Exit program" << std::endl << "Enter your choice: ";
		std::cin >> UserSelection;

		switch (UserSelection) {
		case '1':
			
			LoopingCondition = false;
			CheckCalendarMenu(LoopingCondition);
			break;
		case '2':
		
			LoopingCondition = false;
			AddEventMenu(LoopingCondition, AllEvents);
			break;
		case '3':
			std::cout << "Exit Application";
			LoopingCondition = false;
			break;
		default:
			std::cout << "Wrong input selection! Enter option: 1,2 or 3!";
			break;
		}

	}
}

void GetTodaysDate() {


	// current date and time on the current system
	struct tm newtime;
	std::time_t now = time(0);
	localtime_s(&newtime, &now);
	int Month =1 + newtime.tm_mon;
	int Day =newtime.tm_mday;
	int Year = 1900 + newtime.tm_year;

	std::cout << "Welcome to calendar application! " << "Today is ";
	std::cout << Day << ".";
	if (Month < 10)
	{
		std::cout<<"0";
	}
	std::cout<<Month << "." << Year;

}

void CheckCalendarMenu(bool &GoBack)
{
	char UserSelection;
	bool WorkCondition = true;
	std::string UserInputYear[2];
	std::cout << "If you want to see specific year enter 1. If you need year interval enter 2. If you want to go back enter 3: ";
	std::cin >> UserSelection;

	switch (UserSelection) {
	case '1':
		while (WorkCondition)
		{
			std::cout << "Enter year of your intrest: ";
			std::cin >> UserInputYear[0];
			ValidateInputYearData(UserInputYear[0],WorkCondition);
		}
		break;
	case '2':
		while (WorkCondition)
		{
			std::cout << "Enter beginning of the interval: ";
			std::cin >> UserInputYear[0];
			ValidateInputYearData(UserInputYear[0],WorkCondition);
			std::cout << "Enter end of the interval: ";
			std::cin >> UserInputYear[1];
			ValidateInputYearData(UserInputYear[1],WorkCondition);
		}
		break;
	case '3':
		GoBack = true;
		break;
	default:
		std::cout << "Wrong input selection! Enter option: 1 or 2!";
		break;
	}


}

bool ValidateInputYearData( const std::string& Year, bool &LoopBool) {

	//std::cout << Year;
	for (int YearDigit = 0; YearDigit < Year.size(); YearDigit++)
	{
		
		if (!isdigit(Year[YearDigit]))
		{
			//std::cout << "improper input provided";
			return false;
		}
		
	}
	int Yearint = stoi(Year);
	if (Yearint < 0)
	{
		return false;
		//std::cout << "improper input provided";
	}
	//std::cout << "proper input provided";
	LoopBool = false;
	return true;
}

void AddEventMenu(bool& GoBack, std::vector<Event> allEvents) {

	bool workCondition = true;

	while (workCondition)
	{
	#pragma region Variables
		std::string Country, Town, Street, Number, EventName, Day, Month, Year;
		char PeriodicQuestion, LocationQuestion, AddMoreEventsQuestion;
		bool isPeriodic = false, haveLocation = false;
	#pragma endregion

		// Naming Event
		std::cout << "Name your Event: ";
		std::cin.ignore(1, '\n');
		getline(std::cin, EventName);
		std::cin.clear();

	#pragma region MakeDateObject

		//Specifying Event Date
		std::cout << "Enter event date year: "; std::cin >> Year; std::cout << " Enter event date month: "; std::cin >> Month; std::cout << " Enter event date day: "; std::cin >> Day; 


		//Set isPeriodic Bool
		bool WaitingForPeriodicInput = true;
		while (WaitingForPeriodicInput)// Continue to ask if input != n || != y
		{
			std::cout << " Is event periodic? Enter y if YES; Enter n if NO: "; std::cin >> PeriodicQuestion;
			switch (PeriodicQuestion)
			{
			case 'n':
				isPeriodic = false;
				WaitingForPeriodicInput = false;
				break;
			case 'y':
				isPeriodic = true;
				WaitingForPeriodicInput = false;
			default:
				std::cout << "Wrong input! Try again"<<std::endl;
				break;
			}
		}
	

		//Convert string to int
		int year, month, day;
		year = stoi(Year);
		month = stoi(Month);
		day = stoi(Day);


		//Create EventDate Object
		Date EventDate;
		EventDate.SetDate(day, month, year);
#pragma endregion
		

	#pragma region MakeLocationObject
		//Set haveLocation Bool
		bool WaitingForLocationInput = true;
		while (WaitingForLocationInput)// Continue to ask if input != n || != y
		{
			std::cout << " Does the event have location? Enter y if YES; Enter n if NO: "; std::cin >> LocationQuestion;

			switch (LocationQuestion)
			{
			case 'n':
				haveLocation = false;
				WaitingForLocationInput = false;
				break;
			case 'y':
				haveLocation = true;
				WaitingForLocationInput = false;
				break;
			default:
				std::cout << "Wrong input! Try Again"<<std::endl;
				break;
			}
		}
		

		//Specifying Event Location
		if (haveLocation)
		{
			std::cout << "Enter Country name: "; std::cin >> Country; std::cout << " Enter Town name: "; std::cin >> Town; std::cout << " Enter Street name: "; std::cin >> Street; std::cout << " Enter number: "; std::cin >> Number;
			Location EventLocation;
			EventLocation.SetLocation(Country, Town, Street, Number);

			//Create Event Object
			Event NewEvent(EventName, &EventDate, &EventLocation, isPeriodic);
			allEvents.push_back(NewEvent);
		}
		else
		{
			//Create Event Object
			Location EventLocation;
			EventLocation.SetLocation("", "", "", "");
			Event NewEvent(EventName, &EventDate, &EventLocation, isPeriodic);
			allEvents.push_back(NewEvent);
		}
#pragma endregion

		//Add Next Event
		bool WaitingForAddMorEventsInput = true;
		while (WaitingForAddMorEventsInput) // Continue to ask if input != n || != y
		{
			std::cout << " Do you want to Add More Events? Enter y if YES; Enter n if NO: "; std::cin >> AddMoreEventsQuestion;

			switch (AddMoreEventsQuestion)
			{case 'n':
				WaitingForAddMorEventsInput = false;
				workCondition = false;
				break;
			case 'y':
				WaitingForAddMorEventsInput = false;
				workCondition = true;
				break;
			default:
				std::cout << "Wrong input! Try Again" << std::endl;
				break;
			}

		}
	}
	
	for (Event event : allEvents)
	{
		event.PresentEvent();
	}

	GoBack = true;
}
