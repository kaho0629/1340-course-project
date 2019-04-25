// ENGG 1340 course project - Financial system.
// The program includes the following functions:
// add, view, print statement, edit, suggest wealth allocation, set budget.
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
// So the input format should be: transaction amount date to_int_type
// e.g. E 200 2019-Apr-23 entertainment

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

    cout << "Date (Format of date input, e.g. 2019-Apr-23. Put \"NA\" if not applicable) : \n";
    cin >> data_ptr[i].date;

    cout << "Type (e.g. Food, Entertainment, Salary, etc. Put \"NA\" if not applicable) : \n";
    cin >> data_ptr[i].type;

    if(transaction == 'E')
      fout_e << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;

    else if(transaction == 'I')
      fout_i << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
  }

  fout_i.close();
  fout_e.close();
  delete [] data_ptr;
}

void view_in_categories(char transaction, string date, string type)
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
    cout << "\nFail to open file.\n";
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
  }
}

void make_statement(string month)
{
  double sum = 0;
  data d;
  fin_e.open("expense.txt");
  fin_i.open("income.txt");
  if(fin_e.fail() || fin_i.fail())
    cout << "Fail to open file." << endl;
  else
  {
    int counter = 1;
    while(fin_i >> d.amount)
    {
      fin_i >> d.date >> d.type;
      if((d.date).find(month) != -1)
      {
        sum += d.amount;
        cout << counter << ". " << d.date << "   +" << d.amount << endl;
        counter++;
      }
    }
    while(fin_e >> d.amount)
    {
      fin_e >> d.date >> d.type;
      if((d.date).find(month) != -1)
      {
        sum -= d.amount;
        cout << counter << ". " << d.date << "   -" << d.amount << endl;
        counter++;
      }
    }
    cout << "\nNet Position :   " << sum  << "\n" << endl;
  }
  fin_i.close();
  fin_e.close();
}

void del_record()
{
  char t;
  data d;
  string filename;
  cout << "\nDelete a record of Income(I) / Expense(E) : ";
  cin >> t;
  if(t == 'I')  //Delete an income
    filename = "income.txt";
  else if(t == 'E')
    filename = "expense.txt";

  view_in_categories(t, "NA", "NA");
  cout << "\nEnter the no. of the record to be deleted : ";
  int n, counter = 0;
  cin >> n; // the target record's no.

  fin.open(filename.c_str());
  fout_tmp.open("temp.txt");
  while(fin >> d.amount)
  {
    counter++;
    fin >> d.date >> d.type;
    if(counter == n)  // when it comes to the target record.
      continue;
    fout_tmp << d.amount << " " << d.date << " " << d.type << endl;
  }  // output all the records except the target record to a temporary file.
  fin.close();
  fout_tmp.close();

  fin_tmp.open("temp.txt"); //get data from temp.txt
  fout.open(filename.c_str());  //open income.txt/expense.txt with no previos records.
  while(fin_tmp >> d.amount)
  {
    fin_tmp >> d.date >> d.type;
    fout << d.amount << " " << d.date << " " << d.type << endl;
  } // output records in temp.txt to income.txt/expense.txt. The target will be removed.
  fin_tmp.close();
  fout.close();
}





int main() {
  int option;  //Option can be add, view etc.
  cout << "1. Add\n" << "2. View in categories\n" << "3. Print statement\n";
  cout << "4. Edit\n" << "5. Set budget\n" << "6. Suggestion\n" << "0. Exit"<< endl;
  cout << "Choose your option: ";
  cin >> option;

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
        cout << "Income(I) / Expense(E): ";
        cin >> transaction;
        cout << "Time period: ";
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
        cout << "******Print Statement******\nEnter month : ";
        string month;
        cin >> month;

        month = "2019-" + month;
        make_statement(month);
        break;
      }
        case 4: //Edit record
      {
        cout << "******Edit records******\n";
        cout << "You may choose to : \n1. Delete\n2. Replace\nEnter your option : ";
        int c;
        cin >> c;
        if(c == 1)
        {
          del_record();
        }
        else if(c == 2)
        {

        }
        else
          cout << "Invalid option. " << endl;
        break;
      }
    }
    cout << "\n\n1. Add\n" << "2. View in categories\n" << "3. Print statement\n";
    cout << "4. Edit\n" << "5. Set budget\n" << "6. Get suggestion\n" << "0. Exit"<< endl;
    cout << "Choose your option: ";
    cin >> option;
  }

  cout << "End of program. Bye." << endl;
  return 0;
}
