// Medical Store Managment
// Code By c361,C364,C367,C372

#include <iostream>
#include <ctime>
#include <windows.h> // header file for sleep function
#include <fstream>   //header file for file//fstream,ofstream,istream
static int count = 2, pass = 0;
static int id = 0; // static id is used
using namespace std;

class Customer_data // class to store customer data,bill record//ADT
{

public:
  int quant_stack[100];
  string name_stack[100];
  int price_stack[100];
  int top = -1;
  int ret_quant_stack;
  string ret_name_stack;
  int ret_price_stack;

  void push(int quant, string name, int price)
  {
    if (top == 99)
    {
      cout << "Max order limit exccedded\n";
    }
    else
    {
      top++;
      quant_stack[top] = quant;
      name_stack[top] = name;
      price_stack[top] = price;
    }
  }

  void pop()
  { //Customer_data obj1;
    if (top == -1)
    {
      cout << " No order is there\n";
    }
    else
    {
      ret_name_stack = name_stack[top];
      ret_quant_stack = quant_stack[top];
      ret_price_stack = price_stack[top];
      top--;
    }
  }

  void Pay_Bill(fstream &myfile)
  { // cout<<"problem iss here 1\n";
    // myfile.open("customer_database.txt",ios::app|ios::out);
    system("cls");
    int Total = 0;
    static int file_count = 1;

    if (top != -1)
    {
      myfile.open("customer_database.txt", ios::app | ios::out); //file open in append and write mode
      myfile << endl
             << " Customer No " << file_count << " data" << endl;
      myfile.close();
      cout << "\t\t\t\t\t\t\t==========================================================" << endl;
      cout << "\t\t\t\t\t\t\t|    Medicine Name    |  Quantity     |    Total Price |" << endl;
      cout << "\t\t\t\t\t\t\t==========================================================" << endl;
      while (top != -1) //print all data from stack till it get empty
      {
        Sleep(100);
        myfile.open("customer_database.txt", ios::app | ios::out);
        pop();
        cout << "\t\t\t\t\t\t\t\t" << ret_name_stack << "\t\t  " << ret_quant_stack << "\t\t   " << ret_price_stack << endl;

        myfile << endl
               << "Medicine name :" << ret_name_stack << "\nQuanity :" << ret_quant_stack << "\nAmount :" << ret_price_stack;
        Total += ret_price_stack; //calculationg total price
        myfile.close();
      }
      cout << "\t\t\t\t\t\t\t------------------------------------------------------------\n";
      cout << "\t\t\t\t\t\t\t\t\t\t\t   Total Amount = " << Total << endl;
      cout << "\t\t\t\t\t\t\t------------------------------------------------------------\n";
      myfile.open("customer_database.txt", ios::app | ios::out);
      myfile << endl
             << " Customer No " << file_count << " Total Amount: " << Total << endl;
      myfile.close();
      file_count++;
    }
    else
    {
      cout << "\n\t\t\t\t\t\t\tNo order has placed... Place Order First!!!\n";
    }
  }
};

class Medicne_data : public Customer_data // class to store medicne data inherited from Class Customer data
{
private:
  string name;
  int price;
  string date;
  int stock;
  string mf;
  int med_id;

public:
  int Buy(Medicne_data obj3[], int count)
  {
    if (pass != 1) //condition to chec whthere any medecien is presenyt ot not
    {
      cout << " \n\n\t\t\t\t\t\t\tNO any medicine   found.....Make sure you have added to medicine....\n";
      return 0;
    }

    int count_down = count; //to  search till count becomes 0
    int com = 0, cho;
    int quantity = 0;
    string temp; //stores temp name of medeciene
    Sleep(100);
    system("cls");
    cout << "\n\n\t\t\t\t\t\t\tBUY MEDICINE";
    cout << "\n\t\t\t\t\t\t\t--------------------------------------";
    cout << "\n\n\t\t\t\t\t\t\t1) Buy by Medicine Name \n\t\t\t\t\t\t\t2) Buy By Medicine ID\n";
    cout << "\n\t\t\t\t\t\t\tEnter Option :";
    cin >> cho;
    int res = 1;
    if (cho == 1) // buy by name section start from here
    {
      cout << "\n\n\t\t\t\t\t\t\tEnter Medicine name:";
      getline(cin, temp); //geting medeiene name from user
      getline(cin, temp);

      while (res != 0) //while loop to find entered name from avbailable medeicene
      {
        if (!temp.compare(obj3[count_down].name)) //compare fun check the user entered name and stored name are equal or not
        {

          res = 0; //gives permession to buy by name way
          break;
        }
        else if (count_down <= -1) //condition to displkay error message when med not found
        {
          cout << " \n\n\t\t\t\t\t\t\tmedicine not found.....Make sure you have added medicine....\n";
          return 0;
        }
        else
        {
          //  if(count_down<=0)
          //  {
          //    break;
          //  }
          count_down--; //decrements count_down from end till start
        }
        //  res=temp.compare(name);
      }

      if (res == 0)
      {
        cout << "\t\t\t\t\t\t\tmedicine  Name:" << obj3[count_down].name << "\n\t\t\t\t\t\t\tManufacturing comapny:" << obj3[count_down].mf << endl
             << "\t\t\t\t\t\t\tmedicine id:" << obj3[count_down].med_id << endl
             << "\t\t\t\t\t\t\tmedicine Expiray Date::" << obj3[count_down].date << endl
             << "\t\t\t\t\t\t\tmedicine Price:" << obj3[count_down].price << endl;

        if (obj3[count_down].stock == 0)
        {
          cout << "\n\n\t\t\t\t\t\t\tOpps...medicine is out of stock....\n";
          return 0;
        }
        else
        {
          cout << "\n\t\t\t\t\t\t\tEnter quantity To Buy:";
          cin >> quantity;
          if (quantity != 0)
          {
            obj3[count_down].stock = obj3[count_down].stock - quantity;
            push(quantity, temp, (obj3[count_down].price * quantity)); // order added to list
            cout << "\n\t\t\t\t\t\t\tmedicine is added to list\n";
            cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
          cout << "\t\t\t\t\t\t\tOrder Taken Successfully" << endl;
          cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
          cout << "\t\t\t\t\t\t\tGo to Reciept Menu to Pay The Bill" << endl;
          cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
          
          }
          else
            (cout << "\n\t\t\t\t\t\t\tEnter quantity greater than zero:\n");
        }
      }
      // else
      // {
      //     cout<<" \n\nmedicine  not found.....Make sure you have added to medicine....\n";
      //}
    }
    else if (cho == 2) // buy by id section start from here
    {
      int temp = 0;
      cout << "\n\n\t\t\t\t\t\t\tEnter medicine  id:";
      cin >> temp;
      while (res != 0) //while loop to find entered name from avbailable medeicene
      {
        if (temp == obj3[count_down].med_id) //compare fun check the user entered name and stored name are equal or not
        {

          res = 2; //gives permession to buy by name way
          break;
        }
        else if (count_down <= -1)
        {
          cout << " \n\n\t\t\t\t\t\t\tmedicine  not found.....Make sure you have added to medicine....\n";
          return 0;
        }
        else
        {
          count_down--; //decrements count_down from end till start
        }
      }
      if (res == 2 && (temp != 0))
      {
        cout << "\t\t\t\t\t\t\tmedicine  Name:" << obj3[count_down].name << "\n\t\t\t\t\t\t\tManufacturing comapny:" << obj3[count_down].mf << endl
             << "\t\t\t\t\t\t\tmedicine id:" << obj3[count_down].med_id << endl
             << "\t\t\t\t\t\t\tmedicine Expiray Date::" << obj3[count_down].date << endl
             << "\t\t\t\t\t\t\tmedicine Price:" << obj3[count_down].price << endl;

        if (obj3[count_down].stock == 0)
        {
          cout << "\n\t\t\t\t\t\t\tOpps...medicine is out of stock....\n";
        }
        else
        {
        cout << " \n\t\t\t\t\t\t\tEnter quantity To Buy:";
        cin >> quantity;
        if (quantity != 0)
        {
          stock = stock - quantity;
          push(quantity, obj3[count_down].name, (quantity * obj3[count_down].price));
          cout << "\n\t\t\t\t\t\t\tmedicine is added to list\n";
          cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
          cout << "\t\t\t\t\t\t\tOrder Taken Successfully" << endl;
          cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
          cout << "\t\t\t\t\t\t\tGo to Reciept Menu to Pay The Bill" << endl;
          cout << "\t\t\t\t\t\t\t===========================================================================" << endl;
         
        }
        else
          (cout << "\n\t\t\t\t\t\t\tEnter quantity greater than zero:\n");
       }
      }
    }
    else
    {
      cout << "\n\t\t\t\t\t\t\tWrong Choice...TRY AGAIN!!";
    }
  }
  void Add_stock(Medicne_data obj3[], int count) // add medidne  function  to store new medicne
  {
    system("cls");
    id++;
    pass = 1;
    cout << "\n\n\t\t\t\t\t\t\tADD MEDICINE IN STOCK\n";
    cout << "\t\t\t\t\t\t\t--------------------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\tEnter Medicine Name:\t";
    getline(cin, obj3[count].name);
    getline(cin, obj3[count].name);
    cout << "\n\t\t\t\t\t\t\tEnter Manufacturing Company of medicine:\t";
    getline(cin, obj3[count].mf);
    // getline(cin,obj3[count].mf);
    cout << " \n\t\t\t\t\t\t\tEnter Price Of Medicine:\t";
    cin >> obj3[count].price;
    cout << "\n\t\t\t\t\t\t\tEnter Expry Date(DD/MM/YYYY):\t";
    getline(cin, obj3[count].date);
    getline(cin, obj3[count].date);
    cout << "\n\t\t\t\t\t\t\tEnter quantity of medicine:\t";
    cin >> obj3[count].stock;
    //name="jaysing";stock=500;
    cout << "\n\t\t\t\t\t\t\tMedicine Systeam generated  Id is:" << id << endl;
    obj3[count].med_id = id; //giving medicien id as global id to seqarch it in buy function
    cout << "\n\n\t\t\t\t\t\t\tMedicine Added successfuly...........";
  }

  int Record(fstream &myfile) //call by rerfernce
  {
    myfile.open("customer_database.txt", ios::app | ios::in); //file is opened in append and read mode
    string line;
    if (myfile.is_open()) //is_open function
    {
      while (getline(myfile, line))
      {
        cout << line << endl;
      }
    }
    myfile.close();
    Sleep(5000);
  }

  int Check_Price(Medicne_data obj3[], int count)
  {
  	system("cls");
    if (pass != 1) //condition to chec whthere any medecien is presenyt ot not
    {
      cout << " \n\n NO medicine found.....Make sure you have added to medicine....\n";
      return 0;
    }
    int res = 1;
    int count_down = count;
    int temp = 0;
    cout <<"\n\n\t\t\t\t\t\t\tCHECK MEDICINE PRICE";
    cout <<"\n\t\t\t\t\t\t\t--------------------------------------";
    cout << "\n\n\t\t\t\t\t\t\tEnter medicine  id:";
    cin >> temp;
    while (res != 0) //while loop to find entered name from avbailable medeicene
    {
      if (temp == obj3[count_down].med_id) //compare fun check the user entered name and stored name are equal or not
      {
        res = 2; //gives permession to buy by name way
        break;
      }
      else if (count_down <= -1)
      {
        cout << " \n\n\t\t\t\t\t\t\tmedicine  not found.....Make sure you have added to medicine....\n";
        return 0;
      }
      else
      {
        count_down--; //decrements count_down from end till start
      }
    }
    if (res == 2 && (temp != 0))
    {
      cout <<"\n\t\t\t\t\t\t\t======================================";
      cout<< "\n\t\t\t\t\t\t\tMedicine Name \t   Price";
      cout <<"\n\t\t\t\t\t\t\t======================================";
      cout << "\n\t\t\t\t\t\t\t"<<obj3[count_down].name << "\t\t    " << obj3[count_down].price <<"\n\n";
    }
  }
};

int main() // main program
{
  fstream myfile; //file declaration
  int lim = 1;
  int choice;
  Medicne_data M1;
  Medicne_data M2[100]; // array object to store multiple medicen
                        // object of customer class
  while (1)
  {
    system("cls");
    cout << "\t\t\t\t\t\t\t--------------------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\t\tMEDICAL STORE MANAGMENT SYSTEAM\n\n";
    cout << "\t\t\t\t\t\t\t==================================================\n\n";
    time_t now = time(0);
    char *dt = ctime(&now);
    cout << "\t\t\t\t\t\t\t\t\t\t" << dt << endl;
    cout << "\t\t\t\t\t\t\t--------------------------------------------------\n";
    cout << "\n\t\t\t\t\t\t\t|| 1) Buy Medicne\t\t\t\t||\n";
    cout << "\n\t\t\t\t\t\t\t|| 2) Add Medicine Stock\t\t\t||\n";
    cout << "\n\t\t\t\t\t\t\t|| 3) Pay Bill\t\t\t\t\t||\n";
    cout << "\n\t\t\t\t\t\t\t|| 4) Check Price\t\t\t\t||\n";
    cout << "\n\t\t\t\t\t\t\t|| 5) Check Record\t\t\t\t||\n";
    cout << "\n\t\t\t\t\t\t\t|| 6) Exit\t\t\t\t\t||\n";
    cout << "\t\t\t\t\t\t\t--------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\tEnter Option :";
    cin >> choice;
    switch (choice)
    {
    case 1:
      for (int i = 0; i <= lim; i++)
      {
        char in;
        M1.Buy(&M2[count], count); //count++;
        cout << "\n\t\t\t\t\t\t\tWant to Buy more Medicien(y/n)?:";
        cin >> in;
        i = 2;
        if (in == 'y')
        {
          lim = 1;
          i = 0;
        }
      }

      break;

    case 2:
      for (int i = 0; i <= lim; i++) // for loop to get user choice
      {
        char in;
        M1.Add_stock(&M2[count], count);
        count++; // function call to add stock
        cout << "\n\n\t\t\t\t\t\t\tWant to Add more Medicien(y/n)?:";
        cin >> in;
        i = 2;
        if (in == 'y')
        {
          lim = 1;
          i = 0;
        }
      }
      break;

    case 3:
      M1.Pay_Bill(myfile); //file address send to pay bill function
      cout<<"\n\n\t\t\t\t\t\t\t";system("PAUSE");
      break;

    case 4:
      M1.Check_Price(&M2[count], count);
      cout<<"\n\n\t\t\t\t\t\t\t";system("PAUSE");
      break;
    case 5:
      system("cls");
      M1.Record(myfile);
      system("PAUSE");
      break;
    case 6:
      cout << "\n\n\t\t\t\t\t\t\tExiting ...";
      return 0;
      break;

    default:
      cout << "\n\n\t\t\t\t\t\t\tWrong Choice!!!! Try again\n";
    }
  }

  return 0;
}

