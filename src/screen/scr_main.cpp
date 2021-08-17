// Exercising the Screen class
#include "screen.h"
#include <iostream>

using namespace std;

int main()
{
	// Exercise 4.1
    // Writing/Drawing letter T on the screen
    auto NewScreen = Screen(6,6);
    NewScreen.clear(' ');
    NewScreen.set("******");
    NewScreen.move(1,3);

    int i=0;
    while(i<5)
    {
        NewScreen.down();
        NewScreen.set('*');
        i++;
    }

    NewScreen.display();
    cout<<endl;

	//Exercise 4.5
	auto myScreen = Screen{9,9};
	myScreen.clear(' ');
	myScreen.Empty_Square(4,4,4);
	myScreen.display();           // Display Empty Square
    cout << endl;

	myScreen.clear(' ');
	myScreen.Empty_Square(4,4,10);
	myScreen.display();           // Check for length error
	cout<<endl;

    myScreen.clear(' ');
	myScreen.Empty_Square(11,1,10);
	myScreen.display();           // Check for top-left corner co-ordinates error
    cout<<endl;

	return 0;
}

