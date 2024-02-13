Calendar Console Application
This is a console-based calendar application developed as a programming project. It allows users to plan events, view calendars for specific years or intervals, and delete previously planned events. All data is managed using text files, ensuring that events are retained even after closing the program.

User Interface and Functionality
Main Menu
The main menu displays the current date and provides four selection options:

Check Calendar: Displays options to view calendars.
Add Event: Allows users to plan events and save them.
Delete Event: Enables users to remove previously planned events.
Exit Program: Closes the application.
Check Calendar Menu
This menu provides options to display calendars for specific years or year intervals. Users can:

Display a calendar for a specific year.
Display a calendar for a range of years.
Return to the main menu.
Add Event Menu
Users can add events through this menu. They can input event details such as name, date, time, and location.

Delete Event Menu
Allows users to delete events by specifying the year from which an event should be removed, followed by selecting the event ID to delete.

Testing
The application includes testing for input validation, ensuring correctness in values such as year, month, day, hour, and minute. It also verifies logical inputs such as menu selections.

Description of Classes and Functions
The application is structured around several classes:

EventHolder: Manages all event objects in a vector.
Event: Represents individual events with details such as name, time, and location.
EventTime: Abstract class for date and time elements of events.
Date: Represents the date element of an event.
Clock: Represents the time element of an event.
Location: Represents the location element of an event.
Functions are implemented to handle various functionalities such as displaying menus, adding, deleting events, saving events to files, and retrieving events from files.

Encountered Problems
The main challenge encountered was in efficiently saving and retrieving event data from text files. To address this, events are saved in separate files based on their year, improving performance for large datasets.

Learning Experience
Developing this calendar application provided valuable learning experiences, especially in object-oriented programming concepts such as classes, inheritance, and polymorphism. Additionally, skills in file handling, pointer manipulation, and string conversions were enhanced.
