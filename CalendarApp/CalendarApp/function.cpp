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
	std::string UserSelection;
	bool WorkCondition = true,asking = true;
	std::string UserInputYear[2];
	EventHolder FoundEvents;
	bool looping = true;
#pragma endregion

#pragma region GenerateCalendarMenu
	
	while (asking)
	{
		//Action selection
		std::cout << "If you want to see specific year enter 1. If you need year interval enter 2. If you want to go back enter 3: ";
		std::cin >> UserSelection;

		switch (stoi(UserSelection)) {
		case 1:
			
			//Asking user for years to display and validating given data
			while (WorkCondition)
			{
				asking = false;
				std::cout << "Enter year of your intrest: ";
				std::cin >> UserInputYear[0];
				ValidateInputYearData(UserInputYear[0], WorkCondition);
				UserInputYear[1] = UserInputYear[0];
			}
			
			//Searching for Events in given Years
			FoundEvents = FindEvents(UserInputYear);

			//Printing calendar for given years
			for (int year = stoi(UserInputYear[0]); year <= stoi(UserInputYear[1]); year++)
			{
				PrintCalendar(year, FoundEvents);
			}

			//Printing all Events happening in given years
			PresentAllEvents(FoundEvents);
			

			//Returning to main menu after presentation of calendar
			while (looping)
			{
				char One;
				std::cout << "Press 1 to go back: ";
				std::cin >> One;
				if (One == '1')
				{
					looping = false;
					GoBack = true;
				}
			}
			break;

		case 2:
			
			//Asking user for years to display and validating given data
			while (WorkCondition)
			{
				asking = false;
				std::cout << "Enter beginning of the interval: ";
				std::cin >> UserInputYear[0];
				ValidateInputYearData(UserInputYear[0], WorkCondition);
				std::cout << "Enter end of the interval: ";
				std::cin >> UserInputYear[1];
				ValidateInputYearData(UserInputYear[1], WorkCondition);

				//Check if beginning < end (interval)
				if (stoi(UserInputYear[0]) > stoi(UserInputYear[1]))
				{
					std::cout << "Beginning of interval is greater than End! Try again \n";
					WorkCondition = true;
				}
			}

			//Searching for Events in given Years
			FoundEvents = FindEvents(UserInputYear);

			//Printing calendar for given years
			for (int year = stoi(UserInputYear[0]); year <= stoi(UserInputYear[1]); year++)
			{
				PrintCalendar(year, FoundEvents);
			}

			//Printing all Events happening in given years
			PresentAllEvents(FoundEvents);

			//Returning to main menu after presentation of calendar
			
			while (looping)
			{
				char One;
				std::cout << "Press 1 to go back: ";
				std::cin >> One;
				if (One == '1')
				{
					looping = false;
					GoBack = true;
				}
			}

			break;
		case 3:
			//Going back to main menu
			asking = false;
			GoBack = true;
			break;
		default:
			std::cout << "Wrong input selection! Enter option: 1 or 2!";
			break;
		}
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
	if (Yearint < 1)
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

	//For every year in given interval search for events
	for (int year = BeginningOfInterval; year <= EndOfInterval ; year++)
	{
		//Open file (if exists) named with searched year
		std::ifstream EventsFile(IntToString(year)+".txt");

		//If such file exists
		if (EventsFile)
		{
			std::string EventName, country, town, street, number;
			int year, month, day;

			// Extract all data and create Event object then push it to Eventholder object.
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

	//Searching for periodic events
	std::ifstream PeriodicEventsFile("Periodic.txt");
	std::string EventName, country, town, street, number;
	int year, month, day;

	//If periodic events file found
	if (PeriodicEventsFile)
	{
		//Extract all data and create Event Object
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
	PeriodicEventsFile.close();

	//Returning all found events for given interval
	return FoundEvents;
}

void PresentAllEvents(EventHolder& FoundEvents)
{
	// Printing Event Information
	std::cout << "---------------------- Events ----------------------" << std::endl;
	std::cout << "Id	EventName    Date     Location   Periodic " << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	for (int EventId = 0; EventId < FoundEvents.AllEventsSize(); EventId++)
	{
		//Presenting Event
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
		std::getline(std::cin,EventName);
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

	//Checking if event is periodic. If yes then seve to periodic file
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
	//Checking if event is periodic. If No then seve to file named with event year.
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
	//Print the current year
	std::cout<<"----------- " << Year << " -----------"<<std::endl << std::endl;
	int days;

	// Index of the day from 0 to 6
	int current = DayNumber(1, 1, Year);


	for (int month = 0; month < 12; month++)
	{
		days = numberOfDays(month, Year);


		// Print the current month name
		std::cout << "-----------" << getMonthName(month) << "-----------" << std::endl;

		// Print the columns
		std::cout<<" Su  Mo  Tu  We  Th  Fr  Sa\n";

		// Print appropriate spaces
		int Spaces;
		for (Spaces = 0; Spaces < current; Spaces++)
			std::cout<<"    ";

		//Print days of month
		for (int Day = 1; Day <= days; Day++)
		{

			bool DayAlreadyPrinted = false;
			for (int event = 0; event < allEvents.AllEventsSize(); event++)
			{
				if (DayAlreadyPrinted == false && allEvents.GetEvent(event).GetDate()->GetDay() == Day && allEvents.GetEvent(event).GetDate()->GetMonth() == (month+1) && (allEvents.GetEvent(event).GetDate()->GetYear() == Year || allEvents.GetEvent(event).GetDate()->GetYear() == 0))
				{
				   if(Day>10)
				   {
					   std::cout << "[" << Day << "]";
				   }else std::cout << "[0" << Day << "]";
					
					DayAlreadyPrinted = true;
				}
				

			}
			if (DayAlreadyPrinted == false)
			{
				if (Day < 10)
				{
					std::cout << " 0" << Day << " ";
				}
				else std::cout << " " << Day << " ";
			}
			
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
	switch (monthNumber)
	{case 0:
		return 31;
		break;
	case 1:
		if (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0))
			return 29;
		else
			return 28;
		break;
	case 2:
		return 31;
		break;
	case 3:
		return 30;
		break;
	case 4:
		return 31;
		break;
	case 5:
		return 30;
		break;
	case 6:
		return 31;
		break;
	case 7:
		return 31;
		break;
	case 8:
		return 30;
		break;
	case 9:
		return 31;
		break;
	case 10:
		return 30;
		break;
	case 11:
		return 31;
			break;
	default:
		std::cout << "No Such Month";
		return 0;
		break;
	}

}