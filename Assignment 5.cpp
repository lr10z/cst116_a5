//
// Assignment 5 - Leander Rodriguez
//
// CST 116 - C++ Programming I
//
// Due Date:  Sunday, December 2nd by 11:59pm
//


#include  <iostream>
#include  <iomanip>
#include  <fstream>
#include  <cstdlib>

using namespace std;


// Size of input limitations, constant value
#define MAX_NUM_OF_ENTRIES	15
#define FILE_NAME_SIZE		32

// Output column sizes, constant value
#define ANIMAL_NAME_SIZE	20
#define ANIMAL_TYPE_SIZE	10
#define ANIMAL_AGE_SIZE		3

// Menu choices
#define FORWARD_ORDER		'1'
#define REVERSE_ORDER		'2'
#define YOUNG_TO_OLD_ORDER	'3'
#define AVERAGE_AGE			'4'
#define DISPLAY_OLDEST		'5'
#define DISPLAY_YOUNGEST	'6'
#define QUIT				'q'


//
// Data brought in from file will be
// assigned into the following 3 categories
//
struct AnimalData
{
	char	name[ANIMAL_NAME_SIZE]; 
	char	type[ANIMAL_TYPE_SIZE];
	int		age;
};


//
// Chart heading is displayed for data clarity
//
void chartHeading()
{
	char  underlineName[]	=  "--------------------",
		  underlineType[]	=  "----------",
		  underlineAge[]	=  "---";

	cout.setf( ios::left ); // Allignment left justified
	cout  <<	endl
		  <<	setw( ANIMAL_NAME_SIZE ) //Width of NAME column
		  <<	"Name"
		  <<	"  " //Space between columns
		  <<	setw( ANIMAL_TYPE_SIZE )
		  <<	"Type"
		  <<	"  "
		  <<	setw( ANIMAL_AGE_SIZE )
		  <<	"Age"
		  <<	endl;

	cout  <<	setw( ANIMAL_NAME_SIZE )
		  <<	underlineName
		  <<	"  "
		  <<	setw( ANIMAL_TYPE_SIZE )
		  <<	underlineType
		  <<	"  "
		  <<	setw( ANIMAL_AGE_SIZE )
		  <<	underlineAge
		  <<	endl;
	cout.unsetf( ios::left );
}


//
// Choice menu is displayed for user
//
int displayMenu()
{
	char choice;

	cout  <<  endl
		  <<  "Menu:"													<<  endl
		  <<  "1 - display all animals in forward order"				<<  endl
		  <<  "2 - display all animals in reverse order"				<<  endl
		  <<  "3 - display all animals sorted by age (youngest first)"  <<  endl
		  <<  "4 - determine the average animal age"					<<  endl
		  <<  "5 - determine which animal is oldest"					<<  endl
		  <<  "6 - determine which animal is youngest"					<<  endl
		  <<  "q - quit the program"									<<  endl
		  <<  "Choose: ";
	cin  >>  choice;

	return choice;
}


//
// Using file data, the animals are displayed
// in the exact order as they are in the original file
//
void forwardOrder( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
	chartHeading();
	
	for( int count = 0; count < maxAnimals; ++count)
	{
		cout.setf( ios::left );
		cout  <<	setw( ANIMAL_NAME_SIZE )
			  <<	data[count].name
			  <<	"  "
			  <<	setw( ANIMAL_TYPE_SIZE )
			  <<	data[count].type
			  <<	"  "
			  <<	setw( ANIMAL_AGE_SIZE )
			  <<	data[count].age
			  <<	endl;
		cout.unsetf( ios::left );
	}	
}


//
// Using file data, the animals are displayed
// in reverse order than they are in the original file
//
void reverseOrder( AnimalData data[MAX_NUM_OF_ENTRIES] )
{
	chartHeading();

	for( int count = 5; count > -1; --count)
	{
		cout.setf( ios::left );
		cout  <<	setw( ANIMAL_NAME_SIZE )
			  <<	data[count].name
			  <<	"  "
			  <<	setw( ANIMAL_TYPE_SIZE )
			  <<	data[count].type
			  <<	"  "
			  <<	setw( ANIMAL_AGE_SIZE )
			  <<	data[count].age
			  <<	endl;
		cout.unsetf( ios::left );
	}
}


//
// Using file data, the average age of the animals
// is calculated and then displayed
//
void averageAGEcalc( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
	//Calculation will show a single decimal place
	cout <<  fixed  <<  setprecision(1); 

	double sumOFages = 0,
		   avgAge = 0;

	for( int count = 0; count < maxAnimals; ++ count )
	{
		sumOFages += data[count].age;

		avgAge = sumOFages/maxAnimals;

	}

	cout << endl
		 << "The average age is "
		 << avgAge
		 <<	" years."
		 <<	endl;
}


//
// Using file data, the oldest animal is determined and returned
//
int calcOldest( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
		int oldestAnimal = 0;
	
		for( int count = 0; count < maxAnimals; ++count )
		{
			if( data[count].age > data[oldestAnimal].age )

			oldestAnimal = count;
		}
	
	return oldestAnimal;
}


//
// Using file data and returned value, the oldest animal is displayed
//
void displayOldest( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
	int oldestAnimal = calcOldest( data, maxAnimals );

	cout << endl
		 << data[oldestAnimal].name
		 << " is the oldest."
		 <<	endl;
}


//
// Using file data and returned value, the youngest animal is determined
// and displayed
//
void displayYoungest( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
	int youngestAnimal = calcOldest( data, maxAnimals);
	
	for( int count = 0; count < maxAnimals; ++count )
	{
		if( data[count].age < data[youngestAnimal].age  &&  
			data[count].age != data[youngestAnimal].age )

			youngestAnimal = count;
	}

	cout << endl
		 << data[youngestAnimal].name
		 << " is the youngest."
		 <<	endl; 
}


//
// Using file data and returned value, 
// the next youngest animal is determined and returned
//
int getNEXTyoungest( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals, int newYoung )
{
	int nextYoungest = calcOldest( data, maxAnimals );
	
	for( int count = 0; count < maxAnimals; ++count )
	{
		
		if( data[count].age < data[nextYoungest].age )  
			{
				
				if( data[count].age > newYoung )
				{
					nextYoungest = count; 
				}

			}	

	}

	return nextYoungest;
}


//
// Using file data and returned value, the animals are sorted
// and displayed from the youngest to the oldest
//
void displayYOUNGtoOLD( AnimalData data[MAX_NUM_OF_ENTRIES], int maxAnimals )
{
	chartHeading();

	int newYoung = -1;

	for( int count = 0; count < maxAnimals; ++count )
	{
		int aLITTLEolder = getNEXTyoungest( data, maxAnimals, newYoung );

		newYoung = data[aLITTLEolder].age;

		cout.setf( ios::left );
		cout  <<	setw( ANIMAL_NAME_SIZE )
			  <<	data[aLITTLEolder].name
			  <<	"  "
			  <<	setw( ANIMAL_TYPE_SIZE )
			  <<	data[aLITTLEolder].type
			  <<	"  "
			  <<	setw( ANIMAL_AGE_SIZE )
			  <<	data[aLITTLEolder].age
			  <<	endl;
		cout.unsetf( ios::left );
	}
}


//
// User is asked to enter the filename;
// if correct, file opens and reads in data
//
int promptFORfile( AnimalData data[MAX_NUM_OF_ENTRIES]  )
{
	ifstream in;

	int maxAnimals = 0;

	char filename[FILE_NAME_SIZE];


	cout  <<  "Enter file name: ";
	cin  >>  filename;

	//
	// File opens
	//
	in.open( filename, ios::in );


	//
	// Program checks to see if file is open,
	// if file is not open, it displays an error
	//
	if( ! in.is_open() )
	{
		cout  <<  "Error opening file '"
			  <<  filename
			  <<  "'"
			  <<  endl;
		return -1;
	}


	//
	//Program reads in data from file, until the end of the file
	//
	while( ! in.eof() )
	{
		in  >>	data[maxAnimals].name
			>>	data[maxAnimals].type
			>>	data[maxAnimals].age;

		++maxAnimals;
	}

	return maxAnimals;
}


//
// Main program
//
int main()
{

	AnimalData data[MAX_NUM_OF_ENTRIES];

	int maxAnimals;
	maxAnimals = promptFORfile( data );

	//
	// Program quits if file did not open
	//
	if( maxAnimals == -1 )
	{
		return 1;
	}


	//
	// From initial menu, the choices made by user
	// take the actions that are assigned to respective cases below
	//
	bool done = false;

	while( ! done )
	{
		switch( displayMenu () )
		{
			case FORWARD_ORDER		:	forwardOrder( data, maxAnimals );		break;
			case REVERSE_ORDER		:	reverseOrder( data );					break;
			case YOUNG_TO_OLD_ORDER	:	displayYOUNGtoOLD( data, maxAnimals );	break;
			case AVERAGE_AGE		:	averageAGEcalc( data, maxAnimals );		break;
			case DISPLAY_OLDEST		:	displayOldest( data, maxAnimals );		break;
			case DISPLAY_YOUNGEST	:	displayYoungest( data, maxAnimals );	break;
			case QUIT				:	done = true;							break;
			
			default					:	cout  <<  "*** Invalid choice ***"   <<  endl;  
											  
		}

	}
	
	return 0;
}