//  Calculator
//
//  Program By: Daniel Eisterhold
//

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

//Variables to hold data
char input;
double number;
double result = 0.0;

int main()
{
	//Tell the user the commands that are available
    cout<<"The Simple Calculator"<<endl;
    cout<<"The following commands are available"<<endl;
    cout<<"c"<<endl;
    cout<<"+ <number>"<<endl;
    cout<<"- <number>"<<endl;
    cout<<"* <number>"<<endl;
    cout<<"/ <number>"<<endl;
	cout<<"s <number> (Square a number)"<<endl;
	cout<<"p <number> (total to the n power)"<<endl;
    cout<<"q"<<endl;
	cout<<"Total: "<<result<<endl;
    do {
		cin.clear();
		cout<<"Input: ";
	//Read in what the user wishes to do
        cin>>input;

	//Operate based upon that input
        switch (input) {
        case '+':
	//Add number to current total
            cin>>number;
			cout<<result<<" "<<input<<" "<<number<<endl;
            result += number;
            cout<<"Total: "<<(result)<<endl;
            cin.clear();
			break;
        case '-':
	//Subtract number from current total
            cin>>number;
            cout<<result<<" "<<input<<" "<<number<<endl;
            result -= number;
            cout<<"Total: "<<result<<endl;
            cin.clear();
            break;
        case '*':
	//Multiply number by current total
            cin>>number;
            cout<<result<<" "<<input<<" "<<number<<endl;
            result *= number;
            cout<<"Total: "<<result<<endl;
            cin.clear();
            break;
        case '/':
	//Divide the current total by number
	//Unless the number is zero
            cin>>number;
            cout<<result<<" "<<input<<" "<<number<<endl;
            if (number != 0)
            {
                result /= number;
                cout<<"Total: "<<result<<endl;
            }
            else
            {
                cout<<"Cannot divide by Zero"<<endl;
                cout<<"Total: "<<result;
            }
            cin.clear();
            break;
		case 's':
		case 'S':
			cout<<result<<" * "<<result<<endl;
            result = result*result;
            cout<<"Total: "<<result<<endl;
            cin.clear();
            break;
		case 'p':
		case 'P':
	//Put the current total to the power
	//of what was input
			cin>>number;
			cout<<result<<" ^ "<<input<<endl;
            result = pow(result,number);
            cout<<"Total: "<<result<<endl;
            break;
        case 'c':
        case 'C':
	//Clear the current total
            cin.clear();
            result = 0.0;
            cout<<"Total: "<<result<<endl;
            break;
        case 'q':
        case 'Q':
	//Quit the program
            cout<<"The Simple Calculator is ending"<<endl;
            return 0;
            break;
        default:
	/*If input was invalid tell the user
	And redisplay the available commands*/
            cout<<"Invalid Input"<<endl;
            cout<<"The following commands are available"<<endl;
            cout<<"c"<<endl;
            cout<<"+ <number>"<<endl;
            cout<<"- <number>"<<endl;
            cout<<"* <number>"<<endl;
            cout<<"/ <number>"<<endl;
            cout<<"s <number> (Square a number)"<<endl;
			cout<<"p <number> (total to the n power)"<<endl;
			cout<<"q"<<endl;
			cout<<"Total: "<<result<<endl;
			cout<<"Input: ";
            cin.clear();
            cin.ignore(1000,'\n');
            break;
        }
        //Repeat all of this until the user chooses to quit.
    } while (input != 'q' && input != 'Q');
    
    return 0;
}

