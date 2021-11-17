#include<bits/stdc++.h>
#include "../submission.h"
using namespace std;

int main(){

    ifstream fin;                         // required ifstream object to read from txt file
    ifstream fout;                        // required ofstream object to write in the txt file
    string Input_file = "input_ut.txt";      // kindly change this line and put input file name, file should be present in the same folder where the cpp file is
    string Output_file = "output_ut.txt"; 
    string command;
    string operation_fun;
    string operation_original;

    fin.open(Input_file, ios::in);                                // opening the file in "in" mode, to read inputs
    fout.open(Output_file, ios::in);  

    while(getline(fout, operation_original)){
        getline(fin, command);
        operation_fun = get_command_operation(command);
        if(operation_fun != operation_original) cout << "error" << endl;
    }

    
    return 0;
}