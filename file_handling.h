#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

//Global variables 
vector<string> locations_arr;
vector<string> symptoms_arr;


void read_high_risk_locations() {
    fstream high_risk_location_file;
    high_risk_location_file.open("high-risk-location.txt", ios::in);
    if (high_risk_location_file.is_open()) {
        string line {""};
        cout << "\nID  Location" << endl;
        while (getline(high_risk_location_file, line)) {
            cout << line << endl;
            locations_arr.push_back(line);
        }
    } else {
        cout << "The file was not successfully opened" << endl;
        exit(1);
    }
    high_risk_location_file.close();
}

void read_symptom_file() {
    fstream symptom_file;
    symptom_file.open("symptom.txt", ios::in);
    if (symptom_file.is_open()) {
        string line {""};
        cout << "\nRisk Level  Symptom" << endl;
        while (getline(symptom_file, line)) {
            cout << line << endl;
            symptoms_arr.push_back(line);
        }
    } else {
        cout << "The file was not successfully opened" << endl;
        exit(1);
    }
    symptom_file.close();
}

bool patient_has_visited(string &patient_location) {
    ifstream high_risk_location_file {"high-risk-location.txt"};
    string record {""};
    bool patient_visited_covid_location {false};
    while(getline(high_risk_location_file, record)) {
        //compare patient location visited input with the file which 
        //has the list high risk locations. If found return true
        if (patient_location.compare(record) == 0) {
            patient_visited_covid_location = true;
            return patient_visited_covid_location;
        }
    }
    return patient_visited_covid_location;
}

bool patient_has_symptom(string &patient_symptom) {
    ifstream symptom_file {"symptom.txt"};
    string record {""};
    bool patient_have_symptom {false};
    while (getline(symptom_file, record)) { //read each line
        //compare patient symptom input with the file which 
        //has the list of symptoms. If found return true
        if (patient_symptom.compare(record) == 0) {
            patient_have_symptom = true;
            return patient_have_symptom;
        }
    }
    return patient_have_symptom;
}

void query_high_risk_location_file(string &target_location, string &field) {
    ifstream high_risk_location_file("high-risk-location.txt");
    string location {""}, record {""};
    // while there are records in the file
    while(getline(high_risk_location_file, record)) {
        istringstream ss(record);
        //store it to the location variable
        ss >> location;
        if (target_location.compare(location) == 0) {
            cout << "You entered: " << location;
            // It does, so let's print the rest of the fields
            while(getline(ss, field, ',')) {
                cout << field << "";
            }
            cout << endl;
        }       
    }
    high_risk_location_file.close();
}

void query_symptom_file(string &target_symptom, string &field) {
    ifstream symptom_file("symptom.txt");
    string symptom {""}, record {""};
    // while there are records in the file
    while(getline(symptom_file, record)) {
        istringstream ss(record);
        //store it to the location variable
        ss >> symptom;
        if (target_symptom.compare(symptom) == 0) {
            cout << "You entered: " << symptom;
            // It does, so let's print the rest of the fields
            while(getline(ss, field, ',')) {
                cout << field << "";
            }
            cout << endl;
        }       
    }
    symptom_file.close();
}



