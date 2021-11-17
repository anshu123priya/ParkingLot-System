#include<bits/stdc++.h>
#include "../submission.h"
using namespace std;

int main(){

    ifstream fin;                         // required ifstream object to read from txt file
    ifstream fout;                        // required ofstream object to write in the txt file
    string Input_file = "get_colour_input.txt";      // kindly change this line and put input file name, file should be present in the same folder where the cpp file is
    string Output_file = "get_colour_output.txt"; 
    string command;
    string colour_fun;
    string colour_original;

    fin.open(Input_file, ios::in);                                // opening the file in "in" mode, to read inputs
    fout.open(Output_file, ios::in);  

    while(getline(fout, colour_original)){
        getline(fin, command);
        colour_fun = get_colour_term(command);
        cout << colour_fun << " " << colour_original << endl;
        if(colour_fun != colour_original) cout << "error" << endl;
    }



    return 0;
}