#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib> 
#include <sstream>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits
#include <sstream>
using namespace std;

bool duplicate_id(int &id) {
    fstream patient_file;
    patient_file.open("patient-Detail.txt", ios::in);
    if (patient_file.is_open()) {
        string line {""};
        while (getline(patient_file, line)) {
            if (line.length() == 5) {
                int duplicate_id = atoi(line.c_str());
                if (duplicate_id == id) {
                    return true;
                }
            }
        }
    } else {
        cout << "The file was not successfully opened" << endl;
        exit(1);
    }
    patient_file.close();
    return false;
} 

/*
    pass data type as a parameter so that we don’t need to write the same code 
    for different data types
*/
//Template function - validate user input datatype 
template<typename T>
T &validateInput(T &val) {
    cout << "\nPlease enter a valid input" << endl;
    cin.clear(); // get rid of failure state
    //skip through the leftover characters in the input buffer and go to the next iteration 
    //to ask the user.
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
} 

bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
   if (isdigit(str[i]) == false) {
       return false;
   }
   return true;
}

//This function parameters reference to the memory of these variables
void valid_id_input(int &patient_ID, bool &checker) {
    while (checker) { //loop until checker is set to false
        cout << "\nEnter your patient ID (e.g. 10154 - 5 digits): ";
        cin.sync(); //discards all unread characters from the input buffer.
        cin >> noskipws >> patient_ID; 
        //Convert patient id to string type
        string patient_ID_string = to_string(patient_ID);
        if (patient_ID_string.length() == 0) { //must not be empty
            cout << "\nYour ID must not be blank" << endl;
            checker = true;
        } else if (cin.fail()) { //if wrong input type exit the function
             &validateInput(patient_ID);
             checker = true;
        //Make sure id length is exactly 5
        } else if (patient_ID_string.length() < 5 || patient_ID_string.length() > 5) {
            cout << "\nID accept only 5 digits" << endl;
            checker = true;
        //Return true if id is duplicated and output a message
        } else if (duplicate_id(patient_ID)) {
            cout << "\nThis ID: " << patient_ID << " already exist" << endl;
            checker = true;

        } else {
            checker = false;
        }
    }
}

void valid_name_input(string &patient_name, bool &checker) {
    while (checker) {
        cout << "\nEnter your name full name: " ;
        getline(cin, patient_name);
        if (patient_name.length() == 0) {
            cout << "\nYour full name must not be blank" << endl;
            checker = true;
        } else if (patient_name.length() > 30) {
            cout << "\nYour name must not be greater than 30 characters" << endl;
            checker = true;
        } else if (patient_name.length() <= 3) {
            cout << "\nYour name must not be less than 3 characters" << endl;
        } 
        else if (check_number(patient_name)) {
            cout << "\nName must be a string type"<< endl;
        }
         else {
            checker = false;
        }
    }
}

void valid_date_of_birth(int &patient_DOB, bool &checker) {
    while (checker == true) {
        cout << "\nEnter your DOB(ddmmyyyy 8 digits - must not include space between numbers): ";
        //cin >> skipws >> patient_DOB;
        string patient_DOB_string = to_string(patient_DOB);
        getline(cin, patient_DOB_string);
        if (patient_DOB_string.length() < 8 || patient_DOB_string.length() > 8) {
            cout << "\nMust be 8 digits" << endl;
            checker = true;
        } else {
            patient_DOB = atoi(patient_DOB_string.c_str());
            checker = false;
        } 
    }
}



  