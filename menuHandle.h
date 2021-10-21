#include <iostream>
#include <string>
#include <vector>
using namespace std;

void display_menu() {
    cout << "\n1- Enter your detail for COVID-Test Recommendation: " << endl;
    cout << "\n2- Submit Your Covid test status & Update the location database: " << endl;
    cout << "\n3- Display the Updated Location (High Risk for COVID): " << endl;
    cout << "\n4- Update COVID Patient Details: " << endl;
    cout << "\n5- Display the COVID Positive Patient Detail" << endl;
    cout << "\n6- Quit" << endl;
}

void display_patient_details() {
    fstream  patient_details_file;
    patient_details_file.open("patient-Detail.txt", ios::in);
    if (patient_details_file.is_open()) {
        string line {""};
        cout << "Display Patient Details" << endl;
        while (getline(patient_details_file, line)) {
            cout << line << endl;
            //if (line.empty() != 0) {
              //cout << "blank line found!" << endl;
                //exit(1);
           //}
        }
    } else {
        cout << "Patient details file was not opened successfully" << endl;
    } 
    patient_details_file.close();
}
