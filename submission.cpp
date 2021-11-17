#include<bits/stdc++.h>
#include "submission.h"
using namespace std;


int main()                                             // main function deals with the creation of system and for reading & writing in files
{

    ifstream fin;                         // required ifstream object to read from txt file
    ofstream fout;                        // required ofstream object to write in the txt file
    string Input_file = "oo_input.txt";      // kindly change this line and put input file name, file should be present in the same folder where the cpp file is
    string Output_file = "output01.txt";  // you will get and .txt file withe this name, containing out puts of the query
    string command;                       // we will read the full line and call it command e.g. "Slot_numbers_for_driver_of_age 21" is single command
    string operation;                     // will tell what we want to do in the following command
    string message;
    int capacity;                         // this will be the capacity of the Parking lot, as in maximum number of slots


    fin.open(Input_file, ios::in);                                // opening the file in "in" mode, to read inputs
    fout.open(Output_file,ios::trunc | ios:: out);                // trunc remover all old content from file

    getline(fin,command);                                          // the first command will be a create command for sure

    capacity = get_second_integer_term(command);                   // abstract the integer value of parking lot capacity

    ParkingLot MapleMonkParkingLot = ParkingLot(capacity);            //  MapleMonkParkingLot is the primary objective as it encapsulate majority of functions
    fout<<"Created parking of "<<capacity<<" slots"<<endl;        // Output for "Create_parking_lot" query

    cout<<"Welcome to the MapleMonkParkingLot System, refer the output file for query-responses"<<endl;
    // once we have created ParkingLot object, now we can answer other queries
    // based on the current object states
    // we are performing all the queries in O(1) time complexity
    // also space used is not more than O(n) as for each park query, we make sure the capacity constraint is satisfied

    do
    {
        if(!getline(fin,command) || command.empty())            // we need to check if queries are ended.
        {
            break;
        }

        operation = get_command_operation(command);            // operation will decide, how to proceed further

        // As we have ParkingLot object "MapleMonkParkingLot" established,
        // we can now use the specific functions to handle their specific queries

        if(operation=="park")
        {
            message = MapleMonkParkingLot.handle_park_query(command);   // handle_park_query returns a string, with final output to be printed
            fout<<message<<endl;
        }
        else if(operation == "Leave")
        {
            message = MapleMonkParkingLot.handle_Leave_query(command);  // handle_Leave_query returns a string, with final output to be printed
            fout<<message<<endl;
        }
        else if(operation == "slot_numbers_for_cars_with_colour")     // handle_Slot_numbers_for_driver_of_age_query returns a set of slot indexes for a value of driver age;
        {
            set<int> all_slots = MapleMonkParkingLot.handle_Slot_numbers_for_colour_query(command);

            if(all_slots.size()==0)                                 // check if there is no slot for given value of driver age
            {
                fout<<endl;
            }
            else                                                    // 1 based indexing is followed here
            {
                fout<<(*all_slots.begin())+1;
                auto it = all_slots.begin();
                it++;
                for(it;it!=all_slots.end();it++)
                {
                    fout<<", "<<(*it)+1;                               // indexes are printed as comma separated values
                }
                fout<<endl;
            }
        }
        else if(operation == "slot_number_for_registration_number")     // handle_Slot_number_for_car_with_number_query will simply return an integer
        {
            int slotNo = MapleMonkParkingLot.handle_Slot_number_for_car_with_number_query(command);
            if(slotNo==-2)
            {
                string regNo = MapleMonkParkingLot.get_regNo_term(command);
                fout<<"Not found "<<endl;
            }
            else
            {
                fout<<slotNo+1<<endl;                                             // one based indexing is followed
            }

        }
        else if(operation == "registration_numbers_for_cars_with_colour")  // handle_Vehicle_registration_number_for_driver_of_age_query returns vector of all the regNo
                                                                               // for a given value of the driver age
        {
            vector<string> all_regNo = MapleMonkParkingLot.handle_Vehicle_registration_number_for_colour_query(command);

            if(all_regNo.size()==0)
                fout<<endl;                                            // as givenn in the sample input output nothing will be printed in case of empty vector
            else
            {
                fout<<all_regNo[0];
                for(int i=1;i<all_regNo.size();i++)
                    fout<<", "<<all_regNo[i];                           //  we will print comma separated values
                fout<<endl;
            }
        }

        else if(operation == "status"){
            map<int, Car> vehicle_info = MapleMonkParkingLot.tell_the_status();
            MapleMonkParkingLot.show_parking_history();

            fout<<"Slot No. "<<" Registration No. " << " Colour" <<endl;
            for(auto it: vehicle_info)
            {
                fout<<it.first+1<<"         "<<it.second.get_regNo()<<"     " << it.second.get_colour() << endl;;
            }
            //cout<<endl<<endl;
        }

        else                                                         // if the operation is not matching with any of the possibility than it can be said as wrong query
        {
            fout<< "This is a wrong Query kindly check it again"<<endl;
        }

    }
    while(true);

    fin.close();
    fout.close();

    return 0;
}
