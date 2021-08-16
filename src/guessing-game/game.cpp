#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// checks if User input is less than,greater than or equal to the secret number.
void inspect_condition(int &secret_num , int &user_num);
// Allows user to input a number
int User_Input(int &Input);
// prints a string
void printing(string String);
// generates a random secret number
int secret_num_generator( );

int main()
{
    // Guessing game Parameters and variables
    int Num_of_Attempts =0 , Secret_Num =0 , User_number =0 , Given_Attempts =5;

    Secret_Num = secret_num_generator();

    // Loop for running the guessing-game
    while( Num_of_Attempts < Given_Attempts )
    {
       printing("Enter any Number From 1 to 100: ");

       User_Input(User_number);   Num_of_Attempts++;

       inspect_condition( Secret_Num , User_number );

       if ( Secret_Num == User_number )
       { printing("You Win");  break;  }

       if ( Num_of_Attempts == Given_Attempts )
       { printing("You lose"); break;  }

    }

};

void printing(string String)
{
       cout<<String<<endl<<endl;
}

void inspect_condition(int &secret_num ,int &user_num)
{
       if( user_num > secret_num )
       { printing("Guess lower");    }

       else if( user_num < secret_num )
       { printing("Guess Higher");   }

}

int User_Input(int&Input)
{
       cin>>Input;
}

int secret_num_generator( )
{
       srand(time(0));  int secret_Number = rand()%101;
       return secret_Number;
}
