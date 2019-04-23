// ENGG 1340 course project - Financial system.
// The program includes the following functions:
// add, view, statment, edit, suggest, budget.
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

ofstream fout_i, fout_e, fout_tmp;  //For income and expense files, tmp stores the deleted record.
ifstream fin_i, fin_e, fin_tmp;  //For income and expense files, tmp is for recover the deleted record. (Undo)





int main() {
  string option;
  cout << "Input your option: ";
  cin >> option;
  cout << endl;

  while(option != "Exit")
  {


    cout << "Input your option: ";
    cin >> option;
    cout << endl;
  }

  cout << "End of program. Bye." << endl;
  return 0;
}
