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

void add(int n)
{
  fout_i.open("income.txt", ios::app);
  fout_e.open("expense.txt", ios::app);

  data * data_ptr = new data[n] ();
  for(int i = 0; i < n; i++)
  {
    cin >> data_ptr[i].transaction >> data_ptr[i].amount >> data_ptr[i].date >> data_ptr[i].type;

    if(data_ptr[i].transaction == 'E')
      fout_e << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
    else if(data_ptr[i].transaction == 'I')
      fout_i << data_ptr[i].amount << " " << data_ptr[i].date << " " << data_ptr[i].type << endl;
  }

  fout_i.close();
  fout_e.close();
  delete [] data_ptr;
}


int main() {
  string option;
  cout << "Input your option: ";
  cin >> option;
  cout << endl;

  while(option != "Exit")
  {
    if(option == "add")
      {
        int n;
        cout << "How many records you would like to add: ";
        cin >> n;

        add(n);
      }
   

    cout << "Input your option: ";
    cin >> option;
    cout << endl;
  }

  cout << "End of program. Bye." << endl;
  return 0;
}
