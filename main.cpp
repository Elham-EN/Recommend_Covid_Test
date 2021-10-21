#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <ios> //used to get stream size
#include <limits> //used to get numeric limits
#include <sstream>
#include "inputValidation.h"
#include "menuHandle.h"
#include "file_handling.h"
using namespace std;

//function prototypes
void menu_display();
void display_patient_details();
void valid_id_input(int &, bool &);
void valid_name_input(string &, bool &);
void valid_date_of_birth(int &, bool &);
void valid_mobile_number_input(string &, bool &);
template <typename T> T &validateInput(T &val);
void read_high_risk_locations();
void query_high_risk_location_file(string &, string &);
void read_symptom_file();
void query_symptom_file(string &, string &);
bool patient_has_visited(string &);
bool patient_has_symptom(string &);


void add_patient_details() {
    int patient_ID {0}, patient_DOB;
    bool checker = {true};
    string location_visted_time {""}, location_visted {""}, symptom {""};
    string patient_name {""}, patient_address {""}, patient_mobile_no {""};
    string overseas_visited {""}, covid_test {""}, status {""};
    string high_risk_location_field {""}, symptom_field {""};

    fstream patient_file, symptop_file, high_risk_covid_location_file;
    patient_file.open("patient-Detail.txt", ios::out |ios::app);
    
    if (patient_file.is_open()) { //check if the file is open

        valid_id_input(patient_ID, checker);
        cin.sync(); //clear out what's left in the input buffer stream
        checker = true;


        valid_name_input(patient_name, checker);
        cin.sync();//clear out what's left in the input buffer stream
        checker = true;
        
        valid_date_of_birth(patient_DOB, checker);
        cin.sync();//clear out what's left in the input buffer stream
        checker = true;

        while (checker) {
            cout << "\nEnter your home address (street NO, street name, suburb, postcode, state): ";
            getline(cin, patient_address);
             if (patient_address.length() == 0) {
                cout << "\nYour home address is required" << endl;
                checker = true;
             } else {
                 checker = false;
             } 
        }
        cin.sync();//clear out what's left in the input buffer stream
        checker = true;

        while (checker == true) {
            cout << "\nDid you arrive from overseas in the past two weeks (type 'yes', otherwise type no) " << endl;
            getline(cin, overseas_visited);
            if (overseas_visited.length() == 0) {
                cout << "\nCannot be blank, please type 'yes' or 'no' only" << endl;
            } else {
                checker = false;
            }
        }
        cin.sync();//clear out what's left in the input buffer stream
        checker = true;

        cout << "\nSelect a location id from High Risk COVID area from the list (otherwise type 'no'): ";
        read_high_risk_locations();
        while (checker == true) {
            cout << "\nEnter only id otherwise type 'no': ";
            getline(cin, location_visted);
            if (location_visted.length() == 0) {
                cout << "\nInput cannot be blank" << endl;
                checker = true;
            } else {
                checker = false;
                query_high_risk_location_file(location_visted, high_risk_location_field);
            }
        }
        cin.sync();//clear out what's left in the input buffer stream
        checker = true;

        cout << "\nSelect a symptom from the list (otherwise type 'no'): ";
        read_symptom_file();
        while (checker == true) {
            cout << "\nEnter only symptom from the list (otherwise type 'no'): ";
            getline(cin, symptom);
            if (symptom.length() == 0) {
                cout << "\nInput cannot be blank" << endl;
                checker = true;
            } else {
                checker = false;
                query_symptom_file(symptom, symptom_field);
            }
        }
        cin.sync();//clear out what's left in the input buffer stream 

        patient_file << "\n";
        patient_file << patient_ID << endl;
        patient_file << patient_name << endl;
        patient_file << patient_DOB << endl;
        patient_file << patient_address << endl;
        patient_file << overseas_visited << endl;
        patient_file << high_risk_location_field << endl;
        patient_file << symptom;
        patient_file << symptom_field << endl;
        patient_file.close();

        ifstream symptom_file {"symptom.txt"};
        //Check if symptom file is empty
        if (symptom_file.peek() == ifstream::traits_type::eof()) {
            cout << "\nUnable to recommend COVID Test. Required data missing" << endl;
        } else {
            string patient_symptom = symptom + symptom_field;
            string patient_high_risk_location = location_visted + high_risk_location_field;
            
            //if patient has visited high risk location and has the symptom
            if (patient_has_visited(patient_high_risk_location) == true && 
                    patient_has_symptom(patient_symptom) == true) {
                cout << "\nYou should take a COVID test" << endl;
            }
            //if patient has not visited high risk location but has the symptom 
            else if (patient_has_visited(patient_high_risk_location) == false
                && patient_has_symptom(patient_symptom) == true) {
                cout << "\nisolate yourself at home ";
                if (overseas_visited == "yes") {
                    cout << "if you have been to overseas" << endl;
                }
                cout << endl;
            }
        }   

    } else {
        cout << "Patient file was not created" << endl;
    }
}

int main () {
    int flag {0}, choice {0};
    cout << "Covid Recommendation System" << endl;
    while (flag == 0) { //loop as long as flag is equal to 0
        display_menu(); //display the menu
        cout << "\nPlease enter a number to select option from the menu: ";
        cin >> choice;
        if (choice == 1) {
            add_patient_details(); 
        } 
        else if (choice == 5) {
            display_patient_details();
        } 
        // to verify if the given stream has an erroneous state
        else if (cin.fail()) { //if not an integer input
        //prompt error message & clear out the buffer stream
            &validateInput(choice); 
        } else if (choice == 6) {
            flag = 1; //stop the loop
        } else {
            cout << "\nUnknown selection, please try again" << endl;
        }
    }
    cout << "\nThank you for using our COVID TEST application" << endl;
    return 0;
}
