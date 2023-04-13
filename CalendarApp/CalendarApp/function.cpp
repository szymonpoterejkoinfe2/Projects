#include "function.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <ctime>



void MainMenu()
{
	char UserSelection;
	bool LoopingCondition = true;
	while (LoopingCondition)
	{

		std::cout << "Welcome to calendar application! " << "Today is ";
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
			AddEventMenu(LoopingCondition);
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
	for (int i = 0; i < Year.size(); i++)
	{
		
		if (!isdigit(Year[i]))
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

void AddEventMenu(bool& LoopBool) {
	std::string Country, Town, Street, Number,EventName;
	
	std::cout << "Name your Event: ";
	std::cin.ignore(1, '\n');
	getline(std::cin, EventName);

	std::cout << "Enter Country name: "; std::cin >> Country; std::cout << " Enter Town name: "; std::cin >> Town; std::cout << " Enter Street name: "; std::cin >> Street; std::cout << " Enter number: "; std::cin >> Number;
	Location EventLocation;
	EventLocation.SetLocation(Country,Town,Street,Number);
	EventLocation.PrintLocation();
	
}
