#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

const int CASE_SIZE = 100;
const int WORD_SIZE = 127 + 1;
const int BUFFER_SIZE = 1023 + 1;

struct DateTime {
    int minutes;
    int hour;
    int day;
    int month;
    int year;
};

struct Case 
{
	char* name;
    int priority;
	char* description{};
    DateTime exicutionTime;
};

Case* craeteNewCase(const char name[WORD_SIZE], int priority, const char description[WORD_SIZE], DateTime exicutionTime);

void freeMemoryCase(Case* caseN);

Case** inicializeCases();

void printCases(Case* caseN);

bool datePredicate(Case* caseN, DateTime dateTime);

bool priorityPredicate(Case* caseN, int priority);

bool descriptionPredicate(Case* caseN, char* description);

bool namePredicate(Case* caseN, char* name);

bool datePredicateForMonth(Case* caseN, DateTime dateTime);

bool datePredicateForDay(Case* caseN, DateTime dateTime);

template <typename T>
void printSelectedCase(Case** cases, int caseSize, T field, bool(predicate)(Case* caseN, T));

template <typename T>
bool isCaseExists(Case** cases, int caseSize, T field, bool(predicate)(Case* caseN, T));

char* requestString(const char  message[WORD_SIZE]);

int requestInt(const char message[BUFFER_SIZE]);

int requestPriority();

DateTime requestExicutionDateTimeForDay();

DateTime requestExicutionDateTimeForMonth();

DateTime requestExicutionDateTime();

void editName(Case* caseN, char* newName);

void editDescription(Case* caseN, char* newDescription);

void editPriority(Case* caseN, int newPriority);

void editDate(Case* caseN, DateTime newExicutionTime);

template <typename T>
void edit(Case** cases, int caseSize, char* name, T newField, void (func)(Case* caseN, T));

int compairPriority(Case* caseOne, Case* caseTwo);

int compairByExicutionDate(Case* caseOne, Case* caseTwo);

void sorting(Case** cases, int sizeCase, int (compair)(Case* caseOne, Case* caseTwo));

void printAllCases(Case** cases, int sizeCase);

void addNewCase(Case** cases, int sizeCase, Case* newCase);

void deleteCase(Case** cases, int caseSize, char* name);

int main()
{
	Case** cases = inicializeCases();	
	
	std::cout << "LIST OF CASES:\n";
	std::cout << "Select the menu item:\n";
	std::cout <<
		"1 - add a case;\n"
		"2 - delete the case;\n"
		"3 - editing a case;\n"
		"4 - search for cases;\n" 
		"5 - display of case;\n"
		"0 - out;\n";

	int menuItem;

	while (true) {

		menuItem = requestInt("\nEnter the menu item: ");

		if (menuItem == 1) {
			std::cout << "Add a case:\n";
			char* name = requestString("Enter name of the case:");
			int priority = requestPriority();
			char* description = requestString("Describe the case: ");
			DateTime newDateTime = requestExicutionDateTime();

			Case* newCase = craeteNewCase(name, priority, description, newDateTime);

			addNewCase(cases, CASE_SIZE, newCase);
			printAllCases(cases, CASE_SIZE);

			delete[] name, description, newCase;
		}
		else if (menuItem == 2) {
			std::cout << "Delete the case:\n";
			char* name = requestString("Enter name of the case:");
			deleteCase(cases, CASE_SIZE, name);
			delete[] name;
			printAllCases(cases, CASE_SIZE);
		}
		else if (menuItem == 3) {
			std::cout << "Editing a case:\n";
			char* name = requestString("Enter the name of case you want to change: ");

			if (isCaseExists(cases, CASE_SIZE, name, namePredicate)) {
				std::cout << "\nHow do you want to edit the case?:\n"
					"1 - edit name;\n"
					"2 - edit priority;\n"
					"3 - edit description;\n"
					"4 - edit date execution;\n"
					"over - exit from editing.\n";

				int editMenu = requestInt("Enter the edit menu item:");

				if (editMenu == 1) {
					char* newName = requestString("Enter new name: ");
					edit(cases, CASE_SIZE, name, newName, editName);
					delete[] newName;
				}
				else if (editMenu == 2) {

					int newPriority = requestPriority();
					edit(cases, CASE_SIZE, name, newPriority, editPriority);
				}
				else if (editMenu == 3) {

					char* newDescription = requestString("Enter new description: ");
					edit(cases, CASE_SIZE, name, newDescription, editDescription);
					delete[] newDescription;
				}
				else if (editMenu == 4) {

					DateTime newDateTime = requestExicutionDateTime();
					edit(cases, CASE_SIZE, name, newDateTime, editDate);
				}
				else {
					std::cout << "Exit from editing:\n";
				}
			}
			else
				std::cout << "Case was not found!";

			delete[] name;
		}
		else if (menuItem == 4) {
			std::cout << "Search a case:\n";
			std::cout << "\nHow do you want to search the case?:\n"
				"1 - by name;\n"
				"2 - by priority;\n"
				"3 - by description;\n"
				"4 - by date execution;\n"
				"over - exit from editing.\n";

			int editMenu = requestInt("Enter the search menu item:");

			if (editMenu == 1) {
				char* name = requestString("Enter name: ");
				printSelectedCase(cases, CASE_SIZE, name, namePredicate);
				delete[] name;
			}
			else if (editMenu == 2) {
				int priority = requestPriority();
				printSelectedCase(cases, CASE_SIZE, priority, priorityPredicate);
			}
			else if (editMenu == 3) {
				char* description = requestString("Enter description: ");
				printSelectedCase(cases, CASE_SIZE, description, descriptionPredicate);
				delete[] description;
			}
			else if (editMenu == 4) {
				DateTime dateTime = requestExicutionDateTime();
				printSelectedCase(cases, CASE_SIZE, dateTime, datePredicate);
			}
			else {
				std::cout << "Exit from searching:\n";
			}
		}

		else if (menuItem == 5) {
			std::cout << "Display of case:\n";
			std::cout << "\nHow do you want to display of case?:\n"
				"1 - for day;\n"
				"2 - for month;\n"
				"over - incorrect menu selection\n";
			int selectMenuDisplay = requestInt("Enter the search menu display item:");

			std::cout << "\nHow do you want sorting your case?:\n"
				"1 -  by priority;\n"
				"2 -  by date execution;\n"
				"over - incorrect menu selection\n";
			int selectMenuSort = requestInt("Enter the search menu sorting item:");

			if (selectMenuDisplay == 1 && selectMenuSort == 1) {

				sorting(cases, CASE_SIZE, compairPriority);
				DateTime dateTime = requestExicutionDateTimeForDay();
				printSelectedCase(cases, CASE_SIZE, dateTime, datePredicateForDay);

			}
			else if (selectMenuDisplay == 1 && selectMenuSort == 2) {

				sorting(cases, CASE_SIZE, compairByExicutionDate);
				DateTime dateTime = requestExicutionDateTimeForDay();
				printSelectedCase(cases, CASE_SIZE, dateTime, datePredicateForDay);

			}
			else if (selectMenuDisplay == 2 && selectMenuSort == 1) {

				sorting(cases, CASE_SIZE, compairPriority);
				DateTime dateTime = requestExicutionDateTimeForMonth();
				printSelectedCase(cases, CASE_SIZE, dateTime, datePredicateForMonth);

			}
			else if (selectMenuDisplay == 2 && selectMenuSort == 2) {

				sorting(cases, CASE_SIZE, compairByExicutionDate);
				DateTime dateTime = requestExicutionDateTimeForMonth();
				printSelectedCase(cases, CASE_SIZE, dateTime, datePredicateForMonth);

			}
			else
				std::cout << "Exit from sorting and dysplay menu!\n";
		}

		else if (menuItem == 0)
		{
			std::cout << "\nYou have left the program!";
			break;
		}

		if (menuItem < 1 || menuItem > 6) {
			std::cout << "\nYou have entered the wrong menu item!";
			continue;
		}
	}
}

Case* craeteNewCase(const char name[WORD_SIZE], int priority, const char description[WORD_SIZE], DateTime exicutionTime) {

	Case* newCase = new Case;
	newCase->name = new char[WORD_SIZE];

	strcpy(newCase->name, name);
	newCase->priority = priority;

	newCase->description = new char[WORD_SIZE];
	strcpy(newCase->description, description);

	newCase->exicutionTime = exicutionTime;

	return newCase;
}

void freeMemoryCase(Case* caseN) {

	delete[] caseN->name, caseN->description;
	delete caseN;
}

Case** inicializeCases() {

	Case** cases = new Case * [CASE_SIZE];

	for (int ii = 0; ii < CASE_SIZE; ii++)
		cases[ii] = nullptr;

	cases[0] = craeteNewCase("home", 3, "wash the dishes", { 20, 0, 13, 10, 2023 });
	cases[1] = craeteNewCase("work", 3, "take the documents", { 0, 10, 11, 5, 2023 });
	cases[2] = craeteNewCase("freands", 2, "go to walk", { 0, 1, 13, 10, 2023 });
	cases[3] = craeteNewCase("pet", 4, "by the food", { 0, 1, 15, 6, 2023 });
	cases[4] = craeteNewCase("perents", 1, "go to visit", { 0, 1, 15, 6, 2023 });
	cases[5] = craeteNewCase("hobby", 5, "to drow", { 0, 2, 24, 11, 2024 });
	cases[6] = craeteNewCase("sport", 2, "volleyball", { 0, 2, 28, 10, 2023 });
	return cases;

}


void printCases(Case* caseN) {

	std::cout << "\n*****************************\n";
	std::cout << "Name of the case: " << caseN->name << '\n';
	std::cout << "Priority: " << caseN->priority << '\n';
	std::cout << "Describe the case: " << caseN->description << '\n';
	std::cout << "Execution date: " << caseN->exicutionTime.hour << ":" << caseN->exicutionTime.minutes << " "
		<< caseN->exicutionTime.day << '.' << caseN->exicutionTime.month << '.' << caseN->exicutionTime.year;
}

void printAllCases(Case** cases, int sizeCase)
{
	for (int ii = 0; ii < sizeCase; ii++) {
		if (cases[ii] != NULL)
			printCases(cases[ii]);
	}
}

bool datePredicate(Case* caseN, DateTime dateTime)
{
	DateTime caseDateTime = caseN->exicutionTime;

	if (caseDateTime.minutes == dateTime.minutes
		&& caseDateTime.hour == dateTime.hour
		&& caseDateTime.day == dateTime.day
		&& caseDateTime.month == dateTime.month
		&& caseDateTime.year == dateTime.year)
		return true;
	else
		return false;
}


bool priorityPredicate(Case* caseN, int priority)
{
	return caseN->priority == priority;
}

bool descriptionPredicate(Case* caseN, char* description)
{
	return strcmp(caseN->description, description) == 0;
}

bool namePredicate(Case* caseN, char* name)
{
	return strcmp(caseN->name, name) == 0;
}

bool datePredicateForMonth(Case* caseN, DateTime dateTime)
{
	DateTime caseDateTime = caseN->exicutionTime;

	if (caseDateTime.month == dateTime.month
		&& caseDateTime.year == dateTime.year)
		return true;
	else
		return false;
}

bool datePredicateForDay(Case* caseN, DateTime dateTime)
{
	DateTime caseDateTime = caseN->exicutionTime;

	if (caseDateTime.day == dateTime.day
		&& caseDateTime.month == dateTime.month
		&& caseDateTime.year == dateTime.year)
		return true;
	else
		return false;
}

template <typename T>
void printSelectedCase(Case** cases, int caseSize, T field, bool(predicate)(Case* caseN, T)) {
	bool isFound = false;

	for (int ii = 0; ii < caseSize; ii++) {
		if (cases[ii] != NULL && predicate(cases[ii], field)) {
			isFound = true;
			printCases(cases[ii]);
		}
	}
	if (!isFound)
		std::cout << "\nCases are not found!\n";
}

template <typename T>
bool isCaseExists(Case** cases, int caseSize, T field, bool(predicate)(Case* caseN, T)) {
	for (int ii = 0; ii < caseSize; ii++) {
		if (cases[ii] != NULL && predicate(cases[ii], field)) {
			return true;
		}
	}
	return false;
}

char* requestString(const char  message[WORD_SIZE]) {
	std::cout << message << "\n";
	char* string = new char[BUFFER_SIZE];
	std::cin.getline(string, BUFFER_SIZE);
	return string;
}

int requestInt(const char message[BUFFER_SIZE]) {
	std::cout << message << "\n";
	int integer;
	std::cin >> integer;
	std::cin.ignore();
	return integer;
}

int requestPriority() {
	int priority;
	do {
		priority = requestInt("Enter priority from 1 to 5 where"
			" 1 is the most important");
	} while (!(priority >= 1 && priority <= 5));

	return priority;
}

DateTime requestExicutionDateTimeForDay() {

	std::cout << "Enter day, month and year:\n";

	int day;
	int month;
	int year;

	bool correctDate = false;
	do {

		correctDate = true;

		day = requestInt("enter the day for the case (1 - 30):");
		month = requestInt("enter the month for the case (1 - 12):");
		year = requestInt("enter the year for the case (2023 - 2123):");

		if (month % 2 == 0 && (day < 1 || day > 30)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
		}
		else if (month % 2 != 0 && (day < 1 || day > 31)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
		}
		else if ((month == 2 && year % 4 == 0) && (day < 1 || day > 28)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
			std::cout << "Enter the day 1 - 28:";
		}
		else if ((month == 2 && year % 4 != 0) && (day < 1 || day > 29)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
			std::cout << "Enter the day 1 - 29:";
		}
		if (month < 1 && month > 12) {
			correctDate = false;
			std::cout << "You enter incorrect month!\n";
		}
		if (year < 2023) {
			correctDate = false;
			std::cout << "You enter incorrect year!\n";
		}

	} while (!correctDate);

	return { 0, 0, day, month, year };
}

DateTime requestExicutionDateTimeForMonth() {

	std::cout << "Enter month and year:\n";
	int month;
	int year;

	bool correctDate = false;

	do {
		month = requestInt("enter the month for the case (1 - 12):");
		year = requestInt("enter the year for the case (2023 - 2123):");

		correctDate = true;

		if (month < 1 && month > 12) {
			correctDate = false;
			std::cout << "You enter incorrect month!\n";
		}
		if (year < 2023) {
			correctDate = false;
			std::cout << "You enter incorrect year!\n";
		}
	} while (!correctDate);


	return { 0, 0, 0, month, year };
}

DateTime requestExicutionDateTime() {

	std::cout << "Enter date and time of execution:\n";

	int minutes;
	int hour;
	int day;
	int month;
	int year;

	bool correctDate = false;
	do {

		correctDate = true;

		minutes = requestInt("enter the minutes for the case (0 - 60):");
		hour = requestInt("enter the hour for the case (0 - 24):");
		day = requestInt("enter the day for the case (1 - 30):");
		month = requestInt("enter the month for the case (1 - 12):");
		year = requestInt("enter the year for the case (2023 - 2123):");

		if (minutes < 0 || minutes > 59) {
			correctDate = false;
			std::cout << "You enter incorrect minutes!\n";
		}
		if (hour < 0 || hour > 23) {
			correctDate = false;
			std::cout << "You enter incorrect hour!\n";
		}
		if (month % 2 == 0 && (day < 1 || day > 30)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
		}
		else if (month % 2 != 0 && (day < 1 || day > 31)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
		}
		else if ((month == 2 && year % 4 == 0) && (day < 1 || day > 28)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
			std::cout << "Enter the day 1 - 28:";
		}
		else if ((month == 2 && year % 4 != 0) && (day < 1 || day > 29)) {
			correctDate = false;
			std::cout << "You enter incorrect day!\n";
			std::cout << "Enter the day 1 - 29:";
		}
		if (month < 1 && month > 12) {
			correctDate = false;
			std::cout << "You enter incorrect month!\n";
		}
		if (year < 2023) {
			correctDate = false;
			std::cout << "You enter incorrect year!\n";
		}

	} while (!correctDate);

	return { minutes, hour, day, month, year };
}

void editName(Case* caseN, char* newName)
{
	strcpy(caseN->name, newName);
}

void editDescription(Case* caseN, char* newDescription)
{
	strcpy(caseN->description, newDescription);
}

void editPriority(Case* caseN, int newPriority)
{
	caseN->priority = newPriority;
}

void editDate(Case* caseN, DateTime newExicutionTime)
{
	caseN->exicutionTime = newExicutionTime;
}

template <typename T>
void edit(Case** cases, int caseSize, char* name, T newField, void (func)(Case* caseN, T)) {

	std::cout << "Selected case:\n";
	printSelectedCase(cases, caseSize, name, namePredicate);
	bool isFound = false;

	for (int ii = 0; ii < caseSize; ii++) {

		if (cases[ii] != NULL && namePredicate(cases[ii], name)) {
			func(cases[ii], newField);
			std::cout << "\nEdited case:\n";
			printCases(cases[ii]);
			isFound = true;
		}
	}
	if (!isFound)
		std::cout << "\nNo case with this name has been found!";
}

int compairPriority(Case* caseOne, Case* caseTwo) {
	if (caseOne == NULL && caseTwo == NULL)
		return 0;

	if (caseOne != NULL && caseTwo == NULL)
		return -1;

	if (caseOne == NULL && caseTwo != NULL)
		return 1;
	return caseOne->priority - caseTwo->priority;
}

int compairByExicutionDate(Case* caseOne, Case* caseTwo) {

	if (caseOne == NULL && caseTwo == NULL)
		return 0;

	if (caseOne != NULL && caseTwo == NULL)
		return -1;

	if (caseOne == NULL && caseTwo != NULL)
		return 1;

	if (caseOne->exicutionTime.year - caseTwo->exicutionTime.year != 0)
		return caseOne->exicutionTime.year - caseTwo->exicutionTime.year;

	if (caseOne->exicutionTime.month - caseTwo->exicutionTime.month != 0)
		return caseOne->exicutionTime.month - caseTwo->exicutionTime.month;

	if (caseOne->exicutionTime.day - caseTwo->exicutionTime.day != 0)
		return caseOne->exicutionTime.day - caseTwo->exicutionTime.day;

	if (caseOne->exicutionTime.hour - caseTwo->exicutionTime.hour != 0)
		return caseOne->exicutionTime.hour - caseTwo->exicutionTime.hour;

	if (caseOne->exicutionTime.minutes - caseTwo->exicutionTime.minutes != 0)
		return caseOne->exicutionTime.minutes - caseTwo->exicutionTime.minutes;

	return 0;
}

void sorting(Case** cases, int sizeCase, int (compair)(Case* caseOne, Case* caseTwo)) {
	for (int ii = 0; ii < sizeCase - 1; ii++) {
		for (int jj = 0; jj < sizeCase - ii - 1; jj++) {
			if (compair(cases[jj], cases[jj + 1]) > 0) {
				Case* temp = cases[jj];
				cases[jj] = cases[jj + 1];
				cases[jj + 1] = temp;
			}
		}
	}
}

void addNewCase(Case** cases, int sizeCase, Case* newCase) {

	for (int ii = 0; ii < sizeCase; ii++) {
		if (cases[ii] == NULL) {
			cases[ii] = newCase;
			break;
		}
	}
}

void deleteCase(Case** cases, int caseSize, char* name) {

	bool isCaseFound = false;
	for (int ii = 0; ii < caseSize; ii++) {
		if (cases[ii] != NULL && namePredicate(cases[ii], name)) {
			isCaseFound = true;
			freeMemoryCase(cases[ii]);
			cases[ii] = nullptr;

			std::cout << "\nYou have successfully deleted a case called \"" << name << "\" \n";
		}
	}
	if (!isCaseFound)
		std::cout << "\nNo case with this name has been found!";
}


