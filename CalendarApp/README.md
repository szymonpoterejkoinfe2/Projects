# Calendar Console Application

This is a console-based calendar application developed as a programming project. It allows users to plan events, view calendars for specific years or intervals, and delete previously planned events. All data is managed using text files, ensuring that events are retained even after closing the program.

<p align="center">
  <img src="https://github.com/szymonpoterejkoinfe2/Projects/assets/115418017/bd7b27e5-b034-4f13-8967-51643f4e6b93" alt="CalendarApp" style="margin: 0 auto;">
</p>

## Table of Contents

- [User Interface and Functionality](#user-interface-and-functionality)
- [Classes and Functions](#classes-and-functions)
- [Testing](#testing)
- [Encountered Problems](#encountered-problems)
- [Learning Experience](#learning-experience)

## User Interface and Functionality

### Main Menu

The main menu displays the current date and provides four selection options:

1. **Check Calendar**: Displays options to view calendars.
2. **Add Event**: Allows users to plan events and save them.
3. **Delete Event**: Enables users to remove previously planned events.
4. **Exit Program**: Closes the application.

### Check Calendar Menu

This menu provides options to display calendars for specific years or year intervals. Users can:

1. Display a calendar for a specific year.
2. Display a calendar for a range of years.
3. Return to the main menu.

### Add Event Menu

Users can add events through this menu. They can input event details such as name, date, time, and location.

### Delete Event Menu

Allows users to delete events by specifying the year from which an event should be removed, followed by selecting the event ID to delete.

## Classes and Functions

The application is structured around several classes:

- **EventHolder**: Manages all event objects in a vector.
- **Event**: Represents individual events with details such as name, time, and location.
- **EventTime**: Abstract class for date and time elements of events.
- **Date**: Represents the date element of an event.
- **Clock**: Represents the time element of an event.
- **Location**: Represents the location element of an event.

Functions are implemented to handle various functionalities such as displaying menus, adding, deleting events, saving events to files, and retrieving events from files.

## Testing

The application includes testing for input validation, ensuring correctness in values such as year, month, day, hour, and minute. It also verifies logical inputs such as menu selections.

## Encountered Problems

The main challenge encountered was in efficiently saving and retrieving event data from text files. To address this, events are saved in separate files based on their year, improving performance for large datasets.

## Learning Experience

Developing this calendar application provided valuable learning experiences, especially in object-oriented programming concepts such as classes, inheritance, and polymorphism. Additionally, skills in file handling, pointer manipulation, and string conversions were enhanced.

---

This README provides an overview of the calendar console application, including its features, functionality, class structure, encountered challenges, and learning outcomes. For detailed implementation and usage instructions, please refer to the project documentation and source code.
