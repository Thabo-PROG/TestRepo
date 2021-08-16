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

	myScreen.reSize(16,16);
	myScreen.display();
	myScreen.clear(' ');

	myScreen.move(7,7);
	myScreen.set("BIG");
	myScreen.move(8,5);
	myScreen.set("SCREEN");
	myScreen.display();

	return 0;
}

