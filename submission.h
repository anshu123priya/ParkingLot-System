


#include<bits/stdc++.h>
using namespace std;

// get_command_operation, gives the first word of the line, i.e. operation of the query
// e.g. "park KA-01-HH-1234 White" gives -> "park"
// e.g. "Leave 2" gives ->  "Leave"
string get_command_operation(string command)
{
    string operation="";
    int i=0;                                             // i is index for iteration
    int len = command.length();                          // len is length of the command

    while(i<len && command[i]!=' ')                      // command[i]!=' '  => iterate until the first space
    {
        operation+=command[i];                          // collecting characters of first word of command
        i++;
    }
    return operation;
}


// get_colour_term, gives the second word of the line, i.e. colour of the query
// e.g. "park KA-01-HH-1234 White" gives -> "White"
string get_colour_term(string command)
{
    int len = command.length();
    int i = 0;
    while(i<len && command[i]!=' ')
    {
        i++;                                               // we are not interested in the first word
    }
    i++;
    string colour = "";
    while(i<len && command[i]!=' ')
    {
        colour = colour + command[i];         // storing second word of command in colour as only 2nd word could be a colour term
        i++;
    }
    return colour;                            // returning a colour or second word of command
}



// get_second_integer_term, gives the integer value of second word of the line
// e.g. "Leave 2" gives ->  2
// this function is utilized only where second work is a number
int get_second_integer_term(string command)
{
    int len = command.length();
    int i = 0;
    while(i<len && command[i]!=' ')
    {
        i++;                                               // we are not interested in the first word
    }
    i++;
    int integer_value = 0;
    while(i<len && command[i]!=' ')
    {
        integer_value = integer_value*10 + (command[i]-'0');   // command[i]-'0' gives the number coresponding to the same character like 6 for '6'
        i++;
    }
    return integer_value;                            // returning a integer value
}

// Class Definition of Vehicle class
class Vehicle
{
    protected:
    double mileage;                                // kept protected as it is not directly visible in real file vehicle

    public:
    string regNo;                                 // but these are nothing to hide, it is public
    //string VehicleType;
    string colour;

    Vehicle(string regNo, string colour, double mileage=17.5)
    {
                                                // default values are taken to avoid the hustle of reinitialization and to avoid separate non-parameterized constructor
        this->regNo = regNo;
        //this->VehicleType = VehicleType;
        this->colour = colour;
        this->mileage = mileage;
    }

    virtual double get_mileage()=0;
};
// Class Car inherit the Vehicle class with protected access level
// in order to keep mileage protected in Car class too
class Car: public Vehicle
{

    public:
    string company_name;


    Car(string colour = "none", string regNo="none",string company_name="Skoda_Octavia"):Vehicle(regNo, colour)
    {
        this->company_name = company_name;
    }
    void operator = (const Car &car2 )
    {
         company_name = car2.company_name;
         mileage = car2.mileage;
         regNo = car2.regNo;
         colour  = car2.colour;
    }
    void set_regNo(string regNo)
    {
        this->regNo = regNo;
    }
    string get_regNo()                          // protected member can not be access by other all class, this method is needed
    {
        return regNo;
    }

    string get_colour()                          // protected member can not be access by other all class, this method is needed
    {
        return colour;
    }


    double get_mileage()
    {
        return mileage;
    }
};

// Every Car will be assigned a Entry ticket at the time of entry to the ParkingLot
// class for the same is Defined below
class EntryTicket
{
    private:
    string regNo;                            // member variable for the EntryTicket Class
    int slotNo;
    time_t entryTime;
    time_t exitTime;

    public:
    EntryTicket(string regNo="none",int slotNo=-1):regNo(regNo),slotNo(slotNo)
    { }
    void set_entryTime(time_t entryTime)     // sets the value for etryTime
    {
        this->entryTime = entryTime;
    }
    void set_exitTime(time_t exitTime)       // sets the value for exitTime
    {
        this->exitTime = exitTime;
    }
    void show_ticket()
    {
        cout<<"Assigned to car no. "<<regNo<<" for the slot "<<slotNo+1<<", Entry Time :"<<ctime(&entryTime)<<", Exit Time :"<<ctime(&exitTime)<<endl;
    }
};

// ParkingLot is riches class of the Parking Lot system
// class definition =>
class ParkingLot
{
    private:
    string name;
    string location;
    int capacity;
    priority_queue< int,vector<int>,greater<int> > empty_slots;  // empty_slots help in determining the empty slot which is nearest to entry gate
    unordered_map<string, set< int >> slots_for_colour;                // slots_for_age maintains set of all the slot indexes for a age value
    map<int, Car> vehicle_at_slot;                     // vehicle_at_slot stores the pair of slot index and object of Car parked at that index
    unordered_map<string, int> slot_for_regNo;                   // slot_for_regNo stores the pair of Car's registration Number and the index of slot at which car is parked
    unordered_map<int,EntryTicket> ticket_of_slot;               // ticket_of_slot stores the pair of slot index and object of EntryTicket assigned to the Car, currently at the slot
    vector<EntryTicket> all_tickets;                             // all_tickets is maintained to keep track of parkin system history


    public:
                                                                // Constructor sets capacity and add all the slots to empty slots priority_queue (this works as min heap here)
    ParkingLot(int capacity,string name="MapleMonk_Parking_Lot",string location="Hyderbad_IN")
    {
        this->capacity = capacity;
        for(int i=0;i<capacity;i++)
        {
            empty_slots.push(i);                               // add all the slots to empty list, as all are empty
        }
        vehicle_at_slot.clear();
        slot_for_regNo.clear();
        all_tickets.clear();                                  // mark rest all empty too
        ticket_of_slot.clear();
    }
    int get_capacity()
    {
        return capacity;
    }

    void update_capacity(int new_capacity)              // we can update capacity in case some slots are not working or new added
    {
        capacity = new_capacity;
    }

    int get_slot()                                       // get_slot() provides base available-slot (nearest to entry gate)
    {
        int best_slot = empty_slots.top();
        empty_slots.pop();
        return best_slot;
    }

    pair<string,string> get_regNo_and_colour(string command) // get_regNo_and_age used to find values of age and regNo from Park query line
    {
        int len = command.length();
        int i=0;
        while(i<len && command[i]!=' ')
        {
            i++;                                     // first word is operation
        }
        i++;
        string regNo="";
        while(i<len && command[i]!=' ')
        {
            regNo += command[i];                     //  second word is registration number
            i++;
        }
        i++;
        string colour="";
        while(i<len && command[i]!=' ')
        {
            colour += command[i];
            i++;                                     // third is "driver_age "
        }
        
        pair<string,string> regNo_colour = make_pair(regNo,colour);

        return regNo_colour;
    }
    string handle_park_query(string command)                             // Park query is handled here
    {
        pair<string,string> regNo_colour = get_regNo_and_colour(command);
                                                                      // get_regNo_and_age returns the values separated from command
        string regNo = regNo_colour.first;
        string colour = regNo_colour.second;
        //cout << colour << endl;

        //Person driver = Person(driver_age);                           // needed to create Car object

        Car car = Car(colour,regNo);                                    // needed to put in vehicle_at_slot map for this slot_index

        if(slot_for_regNo.find(regNo)!=slot_for_regNo.end())
        {
            string message = "Car "+regNo+" is already present inside MapleMonkParkingLot";
            return message;
        }
        else if(vehicle_at_slot.size()<capacity)                       // if the parking lot have some vacant slots
        {
            //if(1>driver_age || driver_age>100)                       // check for query check driver's age
            //    return "Invalid driver age";

            int slot_index = get_slot();                              // find best slot to assign

            EntryTicket ticket = EntryTicket(regNo,slot_index);
            ticket.set_entryTime(time(NULL));                        // create EntryTicket, with current time

            ticket_of_slot[slot_index] = ticket;                    // pair ticket with slot index

            slots_for_colour[colour].insert(slot_index);           // same slot index for driver age (we be used later in querying)
            vehicle_at_slot[slot_index] = car;

            slot_for_regNo[regNo] = slot_index;                      // pair the registration number with slot (we be used later in querying)

            string message = "Allocated to slot number: ";
            message += to_string(slot_index+1);

            return message;                                            // once changes are done this message need to be printed in a new line
        }
        else                                                           // if the parking lot if fully filled
        {
            string message = "Sorry, parking lot is full";
            return message;
        }
    }
    string handle_Leave_query(string command)                          // Leave query is handled here
    {
        int leave_slot = get_second_integer_term(command);             // get the leaving slot index

        if(leave_slot>capacity || leave_slot<=0)                                         // check whether this slot index exist
        {
            return "slot "+to_string(leave_slot)+" do not exist";
        }
        else if(vehicle_at_slot.find(leave_slot-1)==vehicle_at_slot.end())  // check whether this slot index already empty
        {
            return "slot "+to_string(leave_slot)+" is already empty";
        }
        else                                                             // if there is a car then steps ->
        {
            Car car = vehicle_at_slot[leave_slot-1];                    // Car object which is parked at the leaving slot
            //int driver_age = car.driver.get_age();                     // age of the driver which is with the car parked at leaving slot
            string regNo = car.get_regNo();                            // regNo of Car which is parked at the leaving slot
            string colour = car.get_colour();

            EntryTicket ticket = ticket_of_slot[leave_slot-1];
            ticket_of_slot.erase(leave_slot-1);                       // EntryTicket is expired
            ticket.set_exitTime(time(NULL));                          // exitTime is added to the EntryTicket
            all_tickets.push_back(ticket);                            // parking history is maintained by keeping all the tickets

            empty_slots.push(leave_slot-1);                          // the slot is empty now,

            slots_for_colour[colour].erase(leave_slot-1);       // slot indes need to be deleted from set of driver_age
            vehicle_at_slot.erase(leave_slot-1);                 // there is no vehicle at the slot
            slot_for_regNo.erase(regNo);                       // we do not have slot for this regNo now

            string message = "Slot number ";
            message += to_string(leave_slot);
            message += " is Free ";

            return message;                                 // this message need to be printed as output
        }
    }

    set<int> handle_Slot_numbers_for_colour_query(string command)   // we want all the slot with given driver age
    {
        string colour = get_colour_term(command);     // function get_second_integer_term returns integer driver age reading from command
        set<int> set_of_slots = slots_for_colour[colour];     // we maintained the set of slots for all the ages ( is used here )

        return set_of_slots;                                  // the set is returned will be added in output file with appropriate formate
    }

    vector<string> handle_Vehicle_registration_number_for_colour_query(string command)   // we want all the vehicle regNo for a given driver age ( handle here )
    {
        string colour = get_colour_term(command);        // second integer term is the driver age in the command is abstracted out

        set<int> set_of_slots = slots_for_colour[colour];        // we have set of slot indexes for driver_age from slots_for_age

        vector<string> all_regNo_for_colour;                         // let's meke vector of all the regNo here

        for(auto it: set_of_slots)
        {
           if(vehicle_at_slot.find(it)!=vehicle_at_slot.end())
           {
                   all_regNo_for_colour.push_back(vehicle_at_slot[it].get_regNo());   // all regNo's are added
           }
       }
       return all_regNo_for_colour;                                 // this will be added in the file in the appropriated formate ( code in main() function )
    }
    string get_regNo_term(string command)                         // only used for Slot_number_for_car_with_number query
    {
        int len = command.length();
        int i = 0;
        while(i<len && command[i]!=' ')
        {
            i++;                                                  // first word is "Slot_number_for_car_with_number"
        }
        i++;
        string regNo = "";
        while(i<len && command[i]!=' ')
        {
            regNo += command[i];                                   // this is regNo ( second term here )
            i++;
        }
        return regNo;
    }
    int handle_Slot_number_for_car_with_number_query(string command)   // we want slot_No. for a regNo ( is handle here )
    {
        string regNo = get_regNo_term(command);              // regNo is abstracted from command
        if(slot_for_regNo.find(regNo)==slot_for_regNo.end())
            return -2;
        int slotNo = slot_for_regNo[regNo];                  // slot_for_regNo maps regNo to slotNo in O(1) time complexity
        return slotNo;
    }
    void show_parking_history()                             // For any system keeping track of all the history is very important
    {
        if(all_tickets.size()==0)
            cout<<"No parking history Yet"<<endl;
        else
        {
            for(int i=0;i<all_tickets.size();i++)
            {
                all_tickets[i].show_ticket();              // all the ticket that are expired i.e. car exit completed are described
            }
        }
    }
    map<int, Car> tell_the_status()
    {
        return vehicle_at_slot;
    }

};