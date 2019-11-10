/*
	Make a "void printReciept" function:
  Expand this code.
upon input of x or X in accept Order
do the receipt generation process
1. Accept tip (from user)
   suggest 20% or more
2.Calculate
  Totaldue + tax + tip
3. Accept payment type
    Credit Card or Cash
4. Accept tender amount from user
   If(tender >= (Totaldue + tax + tip))
5. if cash calc change
6. if card process payment
7. Then generate receipt on screen void printReceipt(vector<MenuItem> &m)
8. next steps generate that same 
   reciept as an output HTML document
   webpage Wow Factor! Whaaat!!!
9. Loop program to start over for a 
  new user, until exit of the whole program. 
10 - Next, next steps, write this program
    in Object Oriented style vs. Struct style 
*/
#include <cstdlib>  // Provides EXIT_SUCCESS
#include <iostream>  // Provides cout, cerr, endl
//#include "Input_Validation_Extended.h" // Provides getValidatedInput<T>(), a header File with a Template Class
                              // Extended 2-11-2016 by Dr. McMillan to add validation methods by datatype
#include<string> //for string manipulation
#include<sstream> //for string manipulation and comparison
#include<iomanip>
#include<vector>// allows the use of Vectors*************
#include<unistd.h> //for sleep command
#include<fstream>


using namespace std;

struct MenuItem //Initialize Structure************
{
  string name;
  double itemCost;
  string desc;
  char addLetter;
  char removeLetter;
  int count;
};

//Function Definition **************************************
void populateMenu(vector<MenuItem> &entireMenu)//entireMenu becomes "wholeMenu" pass by "&"
{
  //put some default values inour MenuItem
  const int numItems = 7;
  MenuItem Item1; //Declares a Variable inside MenuItem Struct (see above)
  MenuItem Item2; //it will contain all items in MenuItem Struct.
  MenuItem Item3; //to get specific use 
  MenuItem Item4;
  MenuItem Item5;
  MenuItem Item6;
  MenuItem Item7;

  entireMenu.push_back(Item1); //add to the end of list the Item1
  entireMenu.push_back(Item2);
  entireMenu.push_back(Item3);
  entireMenu.push_back(Item4);
  entireMenu.push_back(Item5);
  entireMenu.push_back(Item6);
  entireMenu.push_back(Item7);
  
  vector<string> defaultMenuNames = {"Green Tea", "Tacos", "Steak",
  "Ribs",  "Pie", "Burger", "Burrito"}; //initailize vector
  vector<char> defaultaddLetters = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
  vector<char> defaultRemoveLetters =  {'a', 'b', 'c', 'd', 'e', 'f','g'};

  for(int i = 0; i < numItems; i++)
  {
    //add each item to the default list efficiently
    //"entireMenu" is the variable name inside the definition
    //"[i]" empty variable inside definition 
    entireMenu[i].name = defaultMenuNames[i]; //loop to store names  "i" open variable
    entireMenu[i].addLetter = defaultaddLetters[i];
    entireMenu[i].removeLetter = defaultRemoveLetters[i];
    entireMenu[i].itemCost = (3.00 + i); //set a random starter cost for each item.
    entireMenu[i].count = 0; //initialize all counts to 0
    entireMenu[i].desc = "delicous"; //set all default desc to "delicious"


  }
}

//define above showMenu, because show menu calls it
void printReceipt (vector<MenuItem> &m, double s)
{
  //process for calculating the Total w/ tax (accepting the tip)
  double tipAmount = 0.0, totalWithTax = 0.0;
  double taxAmount = 0.0, totalDue = 0.0, tenderAmount = 0.0, change = 0.0;
  double taxRate = 0.0862;
  int decision = 0;
  string cc = " ";
  ofstream myfile; //CREATING A FILE WITH THIS CODE***********!!!!!!!!!!!!
  myfile.open ("receipt.txt"); //FILE *********************************
 
  cout << "*************************YOUR RECEIPT**************************" << endl;
  cout << "\nSub Total Due: $" << s << endl;
  taxAmount = (s * .0825);
  cout << "\nSuggested Tip Amount (20%): $"
       << (s * .20) << endl;
  taxAmount = (s * .0825);
  cout << "Tax Amount $" << taxAmount << endl;
  totalWithTax = s + taxAmount;
  cout << "Total with Tax: " << (totalWithTax);
  //process for calc total with tax
  cout << "\nPlease enter a tip amount: $";
  cin >> tipAmount;

  totalDue = totalWithTax + tipAmount;
  cout << "Total Due $" << totalDue << endl;

  cout <<"\nHow would you like to pay? (1=cash, 2=credit card)";
  cin >> decision;
  if (decision == 1) //cash
  {
    cout <<"You have selected to pay cash." << endl;
    do
    {
      cout << "Please enter your tender amount: $";
      cin >> tenderAmount;
      
      if(tenderAmount < totalDue)
      {
        cout << "\nInsufficent funds (Try Again Please) " << endl;
      }
      
      if(tenderAmount > totalDue)
      {
        change = tenderAmount - totalDue; //show me the money !!! CHANGE !!!!
        cout << "\nChange Amount: $" << change << endl;
      }


    }while(tenderAmount < totalDue); // loop until tender amount >= totalDue 

  }
  else if ( decision == 2)
  {
    cout << "\nYou have selected to pay with Credit Card: ";
    cout << "\nPlease enter your credit card number: ";
    cin >> cc; 
    sleep(5);
    cout << "Approved!!!!!" << endl;
  }
  
  cout << "\n"<<endl;
  myfile << "*****************RECEIPT************************\n" << endl;
  myfile << "Items Purchased RECEIPT: ";
  for(int i = 0; i < m.size(); i++)
  {
    //print on the receipt if count > 0
    if(m[i].count > 0)
    {
      cout << m[i].name << setw(5) << " @$ " << m[i].itemCost << "\t$"
      << (m[i].count * m[i].itemCost) //Running Total*************
      << endl;
    }
  }

  myfile << "\nSubtotal: $" << s << endl;
  myfile << "Tax Rate: $" << (taxRate * 100) << "%" << endl;
  myfile << "Tax Amount: " << taxAmount << endl;
  myfile << "Total with Tax: $" << totalWithTax << endl;
  myfile << "\nTip Amount: $" <<tipAmount << endl;
  myfile << "Total Due: $" << totalDue << endl;

  if (decision == 1)
  {
    myfile << "\nTender: " << tenderAmount << endl;
    myfile << "Change: $" << change << endl;
  } 
  else
  {
    myfile << "\nCredit Card: Approved. " << endl;
  }

  //print a text copy
  myfile.close(); //Closes the file and then adds all "myfile" lines to a txt.file
  
}

void showMenu(vector<MenuItem> &m) //output Menu for Item Values and input
{
  cout << fixed << setprecision(2); //set 2 decimal places for $
  cout << "\n**************David's Efficent Menu***********\n " << endl;
  cout << "ADD \tNAME \tCOST \tREMOVE \tCOUNT \tDESC " << endl;
  for(int i = 0; i < m.size(); i++)
  {
    // "setw() will provide spaces between inputs"******
    cout << m[i].addLetter << ")" << setw(10) << m[i].name 
    << setw(5)<< "$" << m[i].itemCost << setw(5) << m[i].removeLetter 
    << ")" <<  setw(7) << m[i].count << setw(10) << m[i].desc << endl;
  }
}



void acceptOrder(vector<MenuItem> &m)//Inputting Customers order **********
{
  char option = '\0'; //the user-selected menu item
  double subtotal = 0.0;

  do
  {
    cout << "\nPlease choose an item (x to Exit): ";
    cin >> option;
    
    for(int i = 0; i < m.size(); i++)//for loop for picking options(Validates Input also)
    {     //Add Item *************
      if(option == m[i].addLetter) //addLetter Vector  [i] = specific letter*******
      {
          cout << "\nMenu Item " << m[i].addLetter << " selected.";
          m[i].count++; //Increment the "count of items" by 1**********
          cout << "\033[2J\033[1;1H"; // clear screen **********
          cout << "\n1 UP on " << m[i].name << endl;//shown about Menu*****
          subtotal += m[i].itemCost; //increment the subtotal by the cost of the item.******
          showMenu(m); // Refreshesh the Menu again *********************
          cout << "\nSubtotal: $ " << subtotal << endl;
      }
      else if(option == m[i].removeLetter) //Remove Item *****same code as above*****
      {
          cout << "\nRemove Item " << m[i].removeLetter << " selected. ";
          if(m[i].count > 0) //subtract if and only if the count is > 0 ********
          {
            m[i].count--;
            cout << "\033[2J\033[1;1H"; // clear screen **********
            cout << "\n1 Down on " << m[i].name << endl;
            subtotal -= m[i].itemCost; // updates the subtotal********
            showMenu(m);
            cout << "\nSubtotal: " << subtotal << endl;// Total *************
          }
          
          else //tell user why you blocked item removal ***********
          {
          cout << "\nItem count must be > 0 to remove. " << endl;
          }
        
      }
      else if(option != m[i].addLetter && option != m[i].removeLetter &&
              option != 'x' && option != 'X') //test for 11 of my valid inputs******
              {
                if( i ==0)//This prevents a multiple "Invalid Input" message *********
                {
                cout << "Invalid Input";
                }
              }

              
    }
            
  }while(option != 'x' && option != 'X');
  cout << "\nThank you for placing your order." << endl;
  //handle the tip process header
  //handle recipet generation header
  printReceipt (m, subtotal);
}


// *****************MAIN PROGRAM FUNCTION********************************

int main()
{
        //DataType  Variable    
  vector<MenuItem> wholeMenu; //Declared the "wholeMenu" variable
  string decision = " ";
  populateMenu(wholeMenu); //put some default values in the menu
  int programCount = 0;

  showMenu(wholeMenu);
 
  do
  {
   acceptOrder(wholeMenu);
   cout << "\nWould you like to order again. Type \"exit\", otherwise: ";
   cin >> decision;
   if (decision != "exit")
   {
     cout << "\033[2J\033[1;1H"; //clear screen
     cout << "\nWELCOM BACK: " << endl;
     cout << "Place New Order " << endl;
     for (int i = 0; i < wholeMenu.size(); i++)
     {
       wholeMenu[i].count = 0;
     }
     showMenu(wholeMenu);
     
   }

  programCount++;
  

  }while (decision != "exit");

  cout << "Have a Nice Day!!" << endl;
  cout << "Program Ran: " << programCount << endl;

  
 






   
    return 0;
}
