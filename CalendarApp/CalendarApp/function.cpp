#include "function.h"
#include "Class.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>

void MainMenu()
{

#pragma region Variables
	EventHolder AllEventsVector;
	char UserSelection;
	bool LoopingCondition = true;
#pragma endregion

#pragma region GenerateMainMenu
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
			AddEventMenu(LoopingCondition, AllEventsVector);
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
#pragma endregion
}

void GetTodaysDate() {

#pragma region Variables
	// current date and time on the current system
	struct tm newtime;
	std::time_t now = time(0);
	localtime_s(&newtime, &now);
	int Month =1 + newtime.tm_mon;
	int Day =newtime.tm_mday;
	int Year = 1900 + newtime.tm_year;
#pragma endregion

#pragma region PrintTodaysDate
	std::cout << "Welcome to calendar application! " << "Today is ";
	std::cout << Day << ".";
	if (Month < 10)
	{
		std::cout<<"0";
	}
	std::cout<<Month << "." << Year;
#pragma endregion
}

void CheckCalendarMenu(bool &GoBack)
{
#pragma region Variables
	char UserSelection;
	bool WorkCondition = true;
	std::string UserInputYear[2];
	EventHolder FoundEvents;
#pragma endregion

#pragma region GenerateCalendarMenu
	std::cout << "If you want to see specific year enter 1. If you need year interval enter 2. If you want to go back enter 3: ";
	std::cin >> UserSelection;

	switch (UserSelection) {
	case '1':
		while (WorkCondition)
		{
			std::cout << "Enter year of your intrest: ";
			std::cin >> UserInputYear[0];
			ValidateInputYearData(UserInputYear[0],WorkCondition);
			UserInputYear[1] = UserInputYear[0];
			FoundEvents = FindEvents(UserInputYear);
			for (int year = stoi(UserInputYear[0]); year <= stoi(UserInputYear[1]); year++)
			{
				PrintCalendar(year, FoundEvents);
			}
			PresentAllEvents(FoundEvents);
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
			FoundEvents = FindEvents(UserInputYear);
			for(int year = stoi(UserInputYear[0]); year <= stoi(UserInputYear[1]); year++)
			{
				PrintCalendar(year, FoundEvents);
			}
		
			PresentAllEvents(FoundEvents);
		}
		break;
	case '3':
		GoBack = true;
		break;
	default:
		std::cout << "Wrong input selection! Enter option: 1 or 2!";
		break;
	}
#pragma endregion

}

bool ValidateInputYearData( const std::string& Year, bool &LoopBool) {

	//Loop to chcek if every character in year is digit
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

EventHolder FindEvents(std::string yearInterval[2]) {

	EventHolder FoundEvents;
	int BeginningOfInterval, EndOfInterval;
	BeginningOfInterval = stoi(yearInterval[0]);
	EndOfInterval = stoi(yearInterval[1]);

	for (int year = BeginningOfInterval; year <= EndOfInterval ; year++)
	{
		
		std::ifstream EventsFile(IntToString(year)+".txt");
		//std::cout << "Looking For Events in "<< IntToString(year)<< std::endl;
		if (EventsFile)
		{
			std::string EventName, country, town, street, number;
			int year, month, day;

			while (EventsFile >> EventName >> day >> month >> year >> country >> town >> street >> number)
			{
				
				bool isPeriodic = false;
				Date EventDate;
				EventDate.SetDate(day, month, year);
				Location EventLocation;
				EventLocation.SetLocation(country, town, street, number);

				Event NewEvent(EventName, new Date(EventDate), new Location(EventLocation), isPeriodic);
				FoundEvents.EventHolderPushBack(NewEvent);
			}
		}
		EventsFile.close();
	}

	std::ifstream PeriodicEventsFile("Periodic.txt");
	//std::cout << "Looking For Periodic Events"<< std::endl;
	std::string EventName, country, town, street, number;
	int year, month, day;

	if (PeriodicEventsFile)
	{
		
		while (PeriodicEventsFile >> EventName >> day >> month >> year >> country >> town >> street >> number)
		{
			bool isPeriodic = true;
			Date EventDate;
			EventDate.SetDate(day, month, year);
			Location EventLocation;
			EventLocation.SetLocation(country, town, street, number);

			Event NewEvent(EventName, new Date(EventDate), new Location(EventLocation), isPeriodic);
			FoundEvents.EventHolderPushBack(NewEvent);
		}
	}
	return FoundEvents;
}

void PresentAllEvents(EventHolder& FoundEvents)
{
	// if FoundEvents.yeaar = year of calendar
	std::cout << "---------------------- Events ----------------------" << std::endl;
	std::cout << "Id	EventName    Date     Location   Periodic " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	for (int EventId = 0; EventId < FoundEvents.AllEventsSize(); EventId++)
	{
		std::cout << EventId << ". ";
		FoundEvents.GetEvent(EventId).PresentEvent();
	}
	
	std::cout << "----------------------------------------------------" << std::endl;
}

void AddEventMenu(bool& GoBack, EventHolder &allEvents) {

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
				break;
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
			Event NewEvent(EventName, new Date(EventDate), new Location(EventLocation), isPeriodic);
			allEvents.EventHolderPushBack(NewEvent);
		}
		else
		{
			//Create Event Object
			Location EventLocation;
			EventLocation.SetLocation("No", "location", "to", "display");
			Event NewEvent(EventName, new Date(EventDate), new Location(EventLocation), isPeriodic);
			allEvents.EventHolderPushBack(NewEvent);
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
	
	//Saving Every Event in right file
	for (int EventNumber = 0; EventNumber < allEvents.AllEventsSize(); EventNumber++)
	{
		//allEvents.GetEvent(EventNumber).PresentEvent();
		SaveEventInFile(allEvents.GetEvent(EventNumber));
	}

	GoBack = true;
}

void SaveEventInFile(Event EventToSave)
{
	bool isPeriodic = EventToSave.GetRepetable();

	if (isPeriodic)
	{
		std::ofstream SaveFile("Periodic.txt", std::ofstream::app);
		if (SaveFile)
		{
			SaveFile << EventToSave.GetEventName() << " " << IntToString(EventToSave.GetDate()->GetDay()) << " " << IntToString(EventToSave.GetDate()->GetMonth())<<" 0000";
			SaveFile << " " << EventToSave.GetLocation()->GetCountry() << " " << EventToSave.GetLocation()->GetTown() << " " << EventToSave.GetLocation()->GetStreet() << " " << EventToSave.GetLocation()->GetNumber() << std::endl;
		}
		SaveFile.close();
	}
	else {
		std::ofstream SaveFile(IntToString(EventToSave.GetDate()->GetYear()) + ".txt", std::ofstream::app);
		if (SaveFile)
		{
			SaveFile << EventToSave.GetEventName() << " " << IntToString(EventToSave.GetDate()->GetDay()) << " " << IntToString(EventToSave.GetDate()->GetMonth()) << " " << IntToString(EventToSave.GetDate()->GetYear());
			SaveFile << " " << EventToSave.GetLocation()->GetCountry() << " " << EventToSave.GetLocation()->GetTown() << " " << EventToSave.GetLocation()->GetStreet() << " " << EventToSave.GetLocation()->GetNumber() << std::endl;
		}
		SaveFile.close();
	}
}

std::string IntToString(int Number)
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();;
}

void PrintCalendar(int &Year, EventHolder& allEvents)
{
	std::cout<<"----------- " << Year << " -----------"<<std::endl << std::endl;
	int days;

	// Index of the day from 0 to 6
	int current = DayNumber(1, 1, Year);

	// i --> Iterate through all the months
	// j --> Iterate through all the days of the
	//       month - i
	for (int month = 0; month < 12; month++)
	{
		days = numberOfDays(month, Year);
		bool notPrinted = true;

		// Print the current month name
		std::cout << "-----------" << getMonthName(month) << "-----------" << std::endl;

		// Print the columns
		std::cout<<" Su  Mo  Tu  We  Th  Fr  Sa\n";

		// Print appropriate spaces
		int Spaces;
		for (Spaces = 0; Spaces < current; Spaces++)
			std::cout<<"    ";

		for (int Day = 1; Day <= days; Day++)
		{
			for (int event = 0; event < allEvents.AllEventsSize(); event++)
			{
				if (allEvents.GetEvent(event).GetDate()->GetDay() == Day && allEvents.GetEvent(event).GetDate()->GetMonth() == (month+1) && (allEvents.GetEvent(event).GetDate()->GetYear() == Year || allEvents.GetEvent(event).GetDate()->GetYear() == 0))
				{
				
					std::cout << " [" << Day << "] ";
					notPrinted = false;
				}
				

			}
			if (notPrinted)
			{
				if (Day < 10)
				{
					std::cout << " 0" << Day << " ";
				}
				else std::cout << " " << Day << " ";
			}
			notPrinted = true;
			if (++Spaces > 6)
			{
				Spaces = 0;
				std::cout << std::endl;
			}
		}

		if (Spaces)
			std::cout<<std::endl;

		current = Spaces;
	}
	std::cout << "-----------------------------" << std::endl << std::endl;
	
}

int DayNumber(int day, int month, int year)
{
	static int t[] = { 0,3,2,5,0,3,5,1,4,6,2,4 };

	year -= month < 3;
	return (year + year / 4 - year / 100 +
		year / 400 + t[month - 1] + day) % 7;

}

std::string getMonthName(int monthNumber)
{
	std::string months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September","October", "November", "December"};

	return (months[monthNumber]);
}

int numberOfDays(int monthNumber, int year)
{
	// January
	if (monthNumber == 0)
		return (31);

	// February
	if (monthNumber == 1)
	{
		// If the year is leap then February has
		// 29 days
		if (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0))
			return (29);
		else
			return (28);
	}

	// March
	if (monthNumber == 2)
		return (31);

	// April
	if (monthNumber == 3)
		return (30);

	// May
	if (monthNumber == 4)
		return (31);

	// June
	if (monthNumber == 5)
		return (30);

	// July
	if (monthNumber == 6)
		return (31);

	// August
	if (monthNumber == 7)
		return (31);

	// September
	if (monthNumber == 8)
		return (30);

	// October
	if (monthNumber == 9)
		return (31);

	// November
	if (monthNumber == 10)
		return (30);

	// December
	if (monthNumber == 11)
		return (31);
}