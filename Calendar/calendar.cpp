/******************************************************************************
** File Name   : calendar.cpp
** Description : Source code example from CS121 project. Displays a calendar
**				 for a single month, populates appropriate weeks, days, and
**				 dates. Checks and accounts for leap years.
**
** Coded By	   : Jesse L Blum
** Created     : 10/22/2015
**
** Addit. Notes: The design requirements for this project are very similar to
**				 the Calendar application published in "Basic Computer Games,
**				 MicroComputer Edition" by David H. Ahl in 1978. The book and
**				 source were not known to me at the time, and the resulting
**				 code below was my own work. I've resisted the urge to clean
**				 this version up, and left it in its original state as an
**				 example of how, at the time,i solved such problems without
**				 knowledge beyond the c++ standard data types and console io.
******************************************************************************/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//function prototypes
bool inputYearMonth();
int firstDay();
int createCalendar();
int getOnlyIntegers(int, int);
bool checkLeapYear(int);
void printFile();
void loadPrintFile();

//global variables
string months[] = { " 1] January", " 2] February", " 3] March", " 4] April",
" 5] May\t", " 6] June", " 7] July", " 8] August", " 9] September",
"10] October", "11] November", "12] December" };
string days[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
int currentMonth = 0;
int currentYear = 0;
int firstOfMonth = 0;
int firstOfYear = 0;
int dayOfWeekCounter = 0;
bool leapYear = false;
int maxDays[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int daysThisYear[] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

ifstream in_file;

//*****************************************************************************
// function main() - minimal code here, setup a while loop to allow program 
// to execute until user exits.
//*****************************************************************************

int main() {

	while (inputYearMonth()){
		firstDay();
		createCalendar();
		system("cls");			// Windows OS specific, should be updated here. J.B. - 2017
	}
}//End Function

//****************************************************************************
// function inputYearMonth() - Displays the main menu, then prompts for input
// of the month and year values.
//****************************************************************************

bool inputYearMonth(){
	//display menu header image
	loadPrintFile();
	cout << "   _____________________________________________\n" << endl;
	for (int i = 0; i<12; i++){
		cout << "   " << months[i] << "\t" << months[i + 1] << "\t" <<
			months[i + 2] << "\t" << endl;
		i = i + 2;

	}
	cout << "   _____________________________________________\n" << endl;
	cout << "                [13]Exit program				  " << endl;
	cout << "   _____________________________________________" << endl;
	cout << "   Please make a menu selection [1-12,or 13] : ";
	currentMonth = getOnlyIntegers(1, 13);
	if (currentMonth == 13)
		return 0;


	cout << "   Please enter a calendar year : ";
	currentYear = getOnlyIntegers(1600, 2400);

}//End Function

//****************************************************************************
// function firstDay() - Calculate the first day of the year, and months to be
// used in display of dates according to weekdays(sun,mon,tues,etc).
// Sets the number of days to 28 or 29 for February according to leap year,
// or not leap year. Adds days to the running total of days if appropriate.
//****************************************************************************

int firstDay(){

	//Formula provided with project, to find the first day of the year.
	//I've broken it into seperate variables, chunks, so as easier to keep track of whats
	//going on here.
	//calculates starting day of year, 0-6 sun-sat
	int floorVal1 = ((currentYear - 1) / 4);
	int floorVal2 = ((currentYear - 1) / 100);
	int floorVal3 = ((currentYear - 1) / 400);
	firstOfYear = ((((currentYear - 1) * 365) + floorVal1 - floorVal2 + floorVal3) + 1) % 7;


	dayOfWeekCounter = firstOfYear;


	for (int i = 0; i<daysThisYear[currentMonth - 1]; i++){

		if (dayOfWeekCounter == 6){
			dayOfWeekCounter = -1;
		}
		dayOfWeekCounter++;

	}

	//alternative formula... tested, does not seem to be accurate. Left here for future
	//reference and experimentation.
	//math to find the days of the year, based upon the user selected year, and all leap
	//years that ever were, since 1804.
	//firstOfWeek =(((currentYear-1800)*365)+3)+daysThisYear[currentMonth-1];

	//check the current year, if a leap year set the days in February accordingly. 
	//(28 or 29)
	if (checkLeapYear(currentYear)){
		maxDays[2] = 29;
	}
	else{
		maxDays[2] = 28;
	}

	return 0;
}//End Function

//****************************************************************************
// function createCalendar() - Format and display the months of the year,
// calendar days, and dates for the calendar results page. 
//****************************************************************************

int createCalendar(){

cout << "\n\n\n\n\n\n" << months[currentMonth - 1] << "\t\t\t\t\t\t" << currentYear
		<< endl;
cout << "_____________________________________________________________" << endl;
	
for (int i = 0; i<7; i++){
	cout << "  " << days[i] << "\t ";
}

cout << "\n_____________________________________________________________\n"
	 << endl;

int spc = 0;
if (currentMonth>2 && checkLeapYear(currentYear)){
		dayOfWeekCounter = dayOfWeekCounter + 1;
}

for (int j = 0; j<maxDays[currentMonth] + dayOfWeekCounter; j++){
										//cout the dates of the
										//current month in a format
		spc++;                          //that fits the calendar 
		if (j<dayOfWeekCounter){        //page.
			cout << "  **\t  ";
		}else{

		if (j<8 + dayOfWeekCounter + 1)
			cout << " ";
			cout << "  " << j - dayOfWeekCounter + 1 << "\t  ";

			if (!(spc % 7))	 //format days of the week by 7. No remainder?
				cout << endl;//use the endl;. No new line if remainder.
	}
}

cout << "\n\n\n [ Press ENTER key ]" << endl;//wait for the user.
//cin.ignore();
char ch = getchar();
cin.clear(); // clear buffer
cin.ignore(200, '\n'); // flush buffer. 
return 0;
}//End function

//*****************************************************************************
// Function checkLeapYear() - Test a parameter value (testyear) to see if it is 
// a leap year. 
//*****************************************************************************

bool checkLeapYear(int testyear){
	return(!(testyear % 4) && (testyear % 100)) || !(testyear % 400);

}//End function

//*****************************************************************************
// Function getOnlyIntegers() - Function accepts a minimum and maximum integer
// value as parameters. cin to gather input, Error checking performed, must be
// an integer or rejected. Must be within range of two parameters, or rejected.
//*****************************************************************************

int getOnlyIntegers(int min, int max){
int someNumber;

while ((!(cin >> someNumber)) || (someNumber>max) || (someNumber<min)){
	cout << "Invalid Selection. Please try again :";
	cin.clear();		   // clear buffer
	cin.ignore(200, '\n'); // flush buffer. 
}
return someNumber;
}//End function 

//*****************************************************************************
// Function loadPrintFile() - Used to load an ascii text file for main menu 
//              header display,and cout to screen. Includes check for file load 
//				error, if file goes missing the program executes anyways with a 
//				warning msg.
//*****************************************************************************

void loadPrintFile(){

ifstream in_file;
in_file.open("menuimage.asc");//loads an image created in ascii with TheDraw.

if (!in_file.fail()){		  //Why? Because old SysOp habits die hard, and
							  //when am i ever going to get to use that again?
char c;						  //also, checks to see if the file loaded here.
string newLine;
in_file.get(c);					  //prime for loop. is this necessary?
	while (!in_file.eof()){			  //while not end of file, keep reading chars.
		cout << c;
		in_file.get(c);
	}
	cout << endl;
}else{							  //If the file doesn't load, no worries. Continue
								  //after a warning message.
	cout << "Error loading file header image file! Continuing without it.";
	cout << "\n[Press any key to continue]" << endl;
	char ch = getchar();
	}
	in_file.close();			//close the stream.
}//End function






