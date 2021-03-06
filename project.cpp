// ENGG 1340 course project - Financial system.
// The program includes the following functions:
// add, view, print statement, edit, show wealth allocation, set budget.
#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

ofstream fout, fout_i, fout_e, fout_tmp;  //For income and expense files.
ifstream fin, fin_i, fin_e, fin_tmp;  //For income and expense files.

struct data
{
  double amount; // Amount of money.
  string date, type; // Date and type.
};
// So the input format should be: transaction amount date type
// e.g. E 200 2019-APR-23 entertainment

void renewBudget()
{
  ifstream fin("renewBudget.txt");
  ofstream fout("budget.txt");
  string copyFile;
  while(getline(fin , copyFile))
 {
   fout << copyFile << endl;
 }
 fin.close();
 fout.close();
}

void recoverBudget(string date, string type, int amount)
{
  date = date.substr(0,date.length()-3);
  cout << date;
  string lineDate,lineType;
  int lineAmount;
  ifstream fin("budget.txt");
  ofstream fout("renewBudget.txt");
  while(fin >> lineDate >> lineType >> lineAmount)
  {
    if (lineDate == date && lineType == type)
    {
      lineAmount += amount;
    }
    if (lineDate == date && lineType == "ALL")
    {
      lineAmount += amount;
    }
    fout << lineDate << " " << lineType << " "<< lineAmount << endl;
    cout << "Recovered budget: "<<lineDate << " " << lineType << " +$"<< lineAmount<<endl;
  }
  fin.close();
  fout.close();
  renewBudget();
}


// function of calculating the remaining budget

void budgetChecker(int amount, string date, string type)
{
 ifstream fin("budget.txt");
 ofstream fout("renewBudget.txt");
 string x,y;
 int z;
 int tempamount;
 date = date.substr(0,date.length()-3);
 while(fin >> x >> y >> z)
 {
   if (x == date && y == type)
   {
     z = z - amount;
     if (z < 0)
     {
       cout << "Alert: Using on " << y << " within the period of " << x << " was over budget!!!" << endl;
       cout << "Do you want to delete this alert? (Y/N) : ";
       string yesno;
       cin >> yesno;
       if (yesno == "Y")
       {
         y = "NULL";
         cout << "Deleted this budget alert!" << endl;
       }
       else
       {
         cout << "We will remind you if you use this budget next time!" << endl;
       }
     }
     else
     {
       cout <<"Alert: The remaining budget using on " << y << " within the period of " << x << " is $" << z << endl;
    }
   }
   if (x == date && y == "ALL")
   {
     z = z - amount;
     if (z < 0)
     {
       cout << "Alert: Using on " << y << " within the period of " << x << " was over budget!!!" << endl;
       cout << "Do you want to delete this alert? (Y/N) : ";
       string yesno;
       cin >> yesno;
       if (yesno == "Y")
       {
         y = "NULL";
         cout << "Deleted this budget alert!" << endl;
       }
       else
       {
         cout << "We will remind you if you use this budget next time!" << endl;
       }
     }
     else
     {
       cout <<"Alert: The remaining budget using on " << y << " within the period of " << x << " is $" << z << endl;
     }
   }
   fout << x << " "<< y << " "<< z << endl;
 }
 fin.close();
 fout.close();
 renewBudget();

}


//function of set budget
void makeBudget(string month, string category, int budget)
{
  ofstream fout("budget.txt", ios::app);
  fout << month << " " << category << " " << budget << endl;
  fout.close();
}

void add(int n)
{
  fout_i.open("income.txt", ios::app);
  fout_e.open("expense.txt", ios::app);

  char transaction;
  data * data_ptr = new data[n] ();
  for(int i = 1; i <= n; i++)
  {
    cout << '(' << i << ')' << "\nIncome(I) or Expense(E) : ";
    cin >> transaction;

    cout << "Amount of money : ";
    cin >> data_ptr[i].amount;

    cout << "The format of input date : YYYY-MMM-DD.  e.g 2019-APR-27, 2019-APR-DD(no exact day)." << endl;
    cout << "Date : ";
    cin >> data_ptr[i].date;

    cout << "All the input letters should be in upppercase. And the space should be replaced by '-' if necessary." << endl;
    cout << "e.g. FOOD" << endl;
    cout << "Type : ";
    cin >> data_ptr[i].type;

    if(transaction == 'E')
    {
      fout_e << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
      budgetChecker(data_ptr[i].amount,data_ptr[i].date,data_ptr[i].type);
    }
    else if(transaction == 'I')
      fout_i << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
  }

  fout_i.close();
  fout_e.close();
  delete [] data_ptr;
}

int view_in_categories(char transaction, string date, string type)
{
  string filename;
  if(transaction != 'I' && transaction != 'E')
    cout << "\nInvalid input." << endl;
  else if(transaction == 'I')
    filename = "income.txt";
  else if(transaction == 'E')
    filename = "expense.txt";

  fin.open(filename.c_str());
  if(fin.fail())
  {
    cout << "\nFail to open file.\n";
    return 0;
  }
  else
  {
    if(date == "NA")  // Do not limites by date. Any date will do.
      date  = "-";
    else if(date.length() != 11)
      date = date + "-"; // Prevent the situation that if user input year 2019, and there is a record of $2019.

    if(type == "NA")  // Do not limited by type. Any type will do.
      type = " ";

    string data;
    int counter = 1;
    cout << endl << filename.erase(filename.length()-4, 4) << " record : " << endl;
    while( getline(fin, data) )
    {
      if(data.find(date) != -1 && data.find(type) != -1)
      {
        cout << counter << ". " << data << endl;
        counter++;
      }
    }
    if(counter == 1)
      cout << "No " << filename.erase(filename.length()-4, 4)<< " record found!";
    fin.close();
    return 1;
  }
}

int make_statement(string month)
{
  double sum = 0;
  data d;
  fin_e.open("expense.txt");
  fin_i.open("income.txt");
  if(fin_e.fail() || fin_i.fail())
  {
    cout << "Fail to open file." << endl;
    return 0;
  }
  else
  {
    int counter = 1;
    while(fin_i >> d.amount >> d.date >> d.type)
    {
      if((d.date).find(month) != -1)
      {
        sum += d.amount;
        cout << counter << ". " << d.date << "   +" << d.amount << endl;
        counter++;
      }
    }
    while(fin_e >> d.amount >> d.date >> d.type)
    {
      if((d.date).find(month) != -1)
      {
        sum -= d.amount;
        cout << counter << ". " << d.date << "   -" << d.amount << endl;
        counter++;
      }
    }
    cout << "\nNet Position :   " << sum << "\n" << endl;
  }
  fin_i.close();
  fin_e.close();
  return 1;
}

void delBudget()
{
  ifstream fin_bud("budget.txt");
  ofstream fout("renewBudget.txt");
  string x,y;
  int z, counter = 0;
  while(fin_bud >> x >> y >> z)
  {
    counter++;
    cout << counter << ". " << x << " " << y << " " << z << endl;
  }
  cout << "Enter the no. of the record to be deleted : ";
  int deletedLine;
  cin >> deletedLine;
  fin_bud.close();


  int counter2 = 1;
  ifstream fin_bud2("budget.txt");
  for (int i = 1; i <= counter; i++)
  {
    fin_bud2 >> x >> y >> z;

    if (i != deletedLine)
      fout << x << " " << y << " " << z << endl;
    counter2++;
  }
  fout.close();
  fin_bud2.close();
  renewBudget();
}


int del_record()
{
  char t;
  data d;
  string filename;
  cout << "\nDelete a record of Income(I) / Expense(E) / Budget(B): ";
  cin >> t;
  if(t == 'I')  //Delete an income
    filename = "income.txt";
  else if(t == 'E')
    filename = "expense.txt";
  else if(t == 'B')
  {
    delBudget();
    return 0;
  }

  view_in_categories(t, "NA", "NA");
  cout << "\nEnter the no. of the record to be deleted : ";
  int n, counter = 0;
  cin >> n; // the target record's no.

  fin.open(filename.c_str());
  fout_tmp.open("temp.txt");
  while(fin >> d.amount >> d.date >> d.type)
  {
    counter++;
    if(counter == n)  // when it comes to the target record.
    {
    if(n > 0 && t == 'E')
    {
      recoverBudget(d.date, d.type, d.amount);
    }
      continue;
    }
    fout_tmp << d.amount << " " << d.date << " " << d.type << endl;
  }  // output all the records except the target record to a temporary file.
  fin.close();
  fout_tmp.close();

  fin_tmp.open("temp.txt"); //get data from temp.txt
  fout.open(filename.c_str());  //open income.txt/expense.txt with no previos records.
  while(fin_tmp >> d.amount >> d.date >> d.type)
    fout << d.amount << " " << d.date << " " << d.type << endl;
   // output records in temp.txt to income.txt/expense.txt. The target will be removed.
  fin_tmp.close();
  fout.close();
  return 0;
}

void change_info(char t)  // Function to edit record's infomation.
{
  string filename;
  int n, info_type, counter = 1;
  data d;
  if(t == 'I')  //Edit an income
    filename = "income.txt";
  else if(t == 'E')
    filename = "expense.txt";

  view_in_categories(t, "NA", "NA"); // First print out all records.
  cout << "\nWhich record would you like to edit (Enter the no.) : ";  // Let the user choose which one to edit.
  cin >> n;
  cout << "What would you like to edit : \n1. Amount\n2. Date\n3. Type\n4. All (Replace)\nYour option : ";
  cin >> info_type; // Choose the which information to edit. It can be amount, date, type or all.

  fin.open(filename.c_str());
  fout_tmp.open("temp.txt");

  while(fin >> d.amount >> d.date >> d.type)
  {
    if(counter == n)  // Editing the information of the target record.
    {
      switch(info_type)
      {
        case 1:
        {
          cout << "Current amount : " << d.amount << "  New amount : ";
          cin >> d.amount;
          cout << "New record : " << d.amount << " " << d.date << " " << d.type << endl;
          break;
        }
        case 2:
        {
          cout << "Current date : " << d.date << "  New date : ";
          cin >> d.date;
          cout << "New record : " << d.amount << " " << d.date << " " << d.type << endl;
          break;
        }
        case 3:
        {
          cout << "Current type : " << d.type << "  New type : ";
          cin >> d.type;
          cout << "New record : " << d.amount << " " << d.date << " " << d.type << endl;
          break;
        }
        case 4:
        {
          cout << "Current record : " << d.amount << " " << d.date << " " << d.type << "  New record : ";
          cin >> d.amount >> d.date >> d.type;
          cout << "New record : " << d.amount << " " << d.date << " " << d.type << endl;
          break;
        }
      }
    }
    counter++;
    fout_tmp << d.amount << " " << d.date << " " << d.type << endl;  // Output each record to the temporary file.
  }
  fin.close();
  fout_tmp.close();

  fout.open(filename.c_str());
  fin_tmp.open("temp.txt");
  while(fin_tmp >> d.amount >> d.date >> d.type)    // Output the temp.txt to income/expense.txt. Edit is done.
    fout << d.amount << " " << d.date << " " << d.type << endl;

  fout.close();
  fin_tmp.close();
}

int wealth_allocation()  //View by Percentage.
{
  cout << "\nThis function can show you the proportion of your income / expense of each type." << endl;
  string type, filename;
  char t;
  data d;
  double total = 0, sum = 0;
  cout << "Enter the type (In uppercase) : ";
  cin >> type;
  cout << "Proportion of " << type << " in Income / Expense ? (I/E) : ";
  cin >> t;

  if(t == 'I')
    filename = "income.txt";
  else if(t == 'E')
    filename = "expense.txt";

  fin.open(filename.c_str());
  if( fin.fail() )
  {
    cout << "Fail to open file. " << endl;
    return 0;
  }
  else
  {
    int i = 1;
    cout << endl;
    while(fin >> d.amount >> d.date >> d.type)
    {
      total += d.amount;
      if(d.type == type)
        sum += d.amount;
      cout << i << "." << " " << d.amount << " " << d.date << " " << d.type << endl;
      i++;
    }
    cout << "\nPercentage of " << type << " in your " << filename.erase(filename.length() - 4, 4) << " : ";
    cout << fixed << setprecision(2) << (sum/total)*100 << "%" << endl;
  }
  fin.close();
  return 1;
}


int main() {
  int option;  //Option can be add, view etc.
  cout << "Financial System" << endl;
  cout << "1. Add\n" << "2. View in categories\n" << "3. Print statement\n";
  cout << "4. Edit\n" << "5. Set budget\n" << "6. Wealth allocation\n" << "0. Exit"<< endl;
  cout << "Choose your option: ";
  cin >> option;
  while( cin.fail() )
  {
    cin.clear();
    cout << "Invalid input type. Please try again : " << endl;
    cin.ignore(100, '\n');
    cin >> option;
  }

  while(option != 0)
  {
    switch (option)
    {
      case 1: //Add records
      {
        int n;
        cout << "How many records would you like to add: ";
        cin >> n;
        add(n);
        cout << endl;
        break;
      }
      case 2: //View in categories
      {
        cout << "\n******View in categories******" << endl;
        char transaction;
        string date, type;

        cout << "Income(I) / Expense(E) / Both(B) : ";
        cin >> transaction;
        cout << "Time period (e.g. 2019-APR) : ";
        cin >> date;
        cout << "Type: ";
        cin >> type;
        if(transaction == 'B')
        {
          view_in_categories('I', date, type);
          view_in_categories('E', date, type);
        }
        else
          view_in_categories(transaction, date, type);
        break;
      }
      case 3: //Statement
      {
        cout << "******Print Statement******\nEnter month (e.g. 2019-APR) : ";
        string month;
        cin >> month;
        make_statement(month);
        break;
      }
      case 4: //Edit record
      {
        cout << "******Edit records******\n";
        cout << "You may choose to : \n1. Delete\n2. Change information\nEnter your option : ";
        int c;
        cin >> c;
        if(c == 1)
        {
          del_record();
        }
        else if(c == 2)
        {
          char t;
          cout << "Edit an income(I) / expense(E) record : ";
          cin >> t;
          change_info(t);
        }
        else
          cout << "Invalid option. " << endl;
        break;
      }
      case 5:
      {
        cout << "******Budget Alert Setting******\nEnter month (YYYY-MMM e.g. 2019-MAY) : ";
        string month;
        cin >> month;
        while (month.length() != 8)
        {
          cout << "Wrong format!!!\nEnter month (YYYY-MMM e.g. 2019-MAY) :";
          cin >> month;
        }
        cout << "Enter a category (Type 'ALL' for all categories) :";
        string category;
        cin >> category;
        cout << "Enter amont of budget : ";
        int budget;
        cin >> budget;
        cout << "Budget alert will remind you if you use over $ " << budget << " in " << category << " within the period of " << month << endl;
        makeBudget(month, category, budget);
        break;
      }
      case 6:
      {
        wealth_allocation();
        break;
      }

    }
    cout << "\n\n1. Add\n" << "2. View in categories\n" << "3. Print statement\n";
    cout << "4. Edit\n" << "5. Set budget\n" << "6. Wealth allocation\n" << "0. Exit"<< endl;
    cout << "Choose your option: ";
    cin >> option;
  }

  cout << "End of program. Bye." << endl;
  return 0;
}
