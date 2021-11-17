#include<bits/stdc++.h>
#include "../submission.h"
using namespace std;

int main(){

    ifstream fin;                         // required ifstream object to read from txt file
    ifstream fout;                        // required ofstream object to write in the txt file
    string Input_file = "get_second_integer_input.txt";      // kindly change this line and put input file name, file should be present in the same folder where the cpp file is
    string Output_file = "get_second_integer_output.txt"; 
    string command;
    string second_integer_fun;
    string second_integer_original;

    fin.open(Input_file, ios::in);                                // opening the file in "in" mode, to read inputs
    fout.open(Output_file, ios::in);  

    while(getline(fout, second_integer_original)){
        getline(fin, command);
        second_integer_fun = to_string(get_second_integer_term(command));
        cout << second_integer_fun << " " << second_integer_original << endl;
        if(second_integer_fun != second_integer_original) cout << "error" << endl;
    }



    return 0;
}