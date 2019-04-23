// ENGG 1340 course project - Financial system.
// The program includes the following functions:
// add, view, statment, edit, suggest, budget.
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

ofstream fout_i, fout_e, fout_tmp;  //For income and expense files, tmp stores the deleted record.
ifstream fin_i, fin_e, fin_tmp;  //For income and expense files, tmp is for recover the deleted record. (Undo)

struct data
{
  char transaction; // Income or Expense.
  double amount; // Amount of money.
  string date, type; // Date and type.
};
// So the input format should be: transaction amount date to_int_type
// e.g. E 200 2019-Apr-23 entertainment

void add(int n)
{
  fout_i.open("income.txt", ios::app);
  fout_e.open("expense.txt", ios::app);

  data * data_ptr = new data[n] ();
  for(int i = 0; i < n; i++)
  {
    cout << "Income(I) or Expense(E) : ";
    cin >> data_ptr[i].transaction;

    cout << "Amount of money : ";
    cin >> data_ptr[i].amount;

    cout << "Date (Format of date input, e.g. 2019-Apr-23) : ";
    cin >> data_ptr[i].date;

    cout << "Type : ";
    cin >> data_ptr[i].type;

    if(data_ptr[i].transaction == 'E')
      fout_e << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;

    else if(data_ptr[i].transaction == 'I')
      fout_i << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
  }

  fout_i.close();
  fout_e.close();
  delete [] data_ptr;
}

void search_record(char transaction, string date, string type)
{
  if(date == "NA")  // Do not limites by date. Any date will do.
    date  = "-";
  else if(date.length() != 11)
    date = date + "-"; // Prevent the situation that if user input year 2019, and there is a record of $2019.

  if(type == "NA")  // Do not limited by type. Any type will do.
    type = " ";

  string data;
  cout << "\nResult : " << endl;
  if(transaction == 'I')
  {
    int n = 0;
    while( getline(fin_i, data) )
    {
      if(data.find(date) != -1 && data.find(type) != -1)
      {
        cout << data << endl;
        n++;
      }
    }
    if(n == 0)
      cout << "No record found." << endl;
  }
  else if(transaction == 'E')
  {
    int n = 0;
    while( getline(fin_e, data) )
    {
      if(data.find(date) != -1 && data.find(type) != -1)
      {
        cout << data << endl;
        n++;
      }
    }
    if(n == 0)
      cout << "No record found." << endl;
  }
}

void view()
{
  char transaction;
  string date, type;
  cout << "Income(I) / Expense(E): ";
  cin >> transaction;

  cout << "Time period: ";
  cin >> date;

  cout << "Type: ";
  cin >> type;

  if(transaction != 'I' && transaction != 'E')
    cout << "Invalid input." << endl;
  else if(transaction == 'I')
  {
    fin_i.open("income.txt");
    if(fin_i.fail())
      cout << "Fail to open file." << endl;
    else
      search_record('I', date, type);
  }
  else if(transaction == 'E')
  {
    fin_e.open("expense.txt");
    if(fin_e.fail())
      cout << "Fail to open file." << endl;
    else
      search_record('E', date, type);
  }
}


int main() {
  int option;  //Option can be add, view etc.
  cout << "Choose your option: ";
  cout << " 1. Add " << "2. View " << "3. Edit " << "0. Exit"<< endl;
  cin >> option;

  while(option != 0)
  {
    switch (option)
    {
      case 1:
      {
        int n;
        cout << "How many records you would like to add: ";
        cin >> n;
        cout << "*******Input format: transaction amount date type******" << endl;
        add(n);
        break;
      }
      case 2:
      {
        cout << "How would you like to view: ";
        // input format: transaction date type
        // e.g. E 2019-Apr food, E 2019-Mar shopping.

        view();
        break;
      }






    }
    cout << "\nChoose your option: ";
    cout << " 1. Add " << "2. View " << "3. Edit " << "0. Exit"<< endl;
    cin >> option;
  }

  cout << "End of program. Bye." << endl;
  return 0;
}
