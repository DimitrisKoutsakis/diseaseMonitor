#pragma once
#include <string>

using namespace std;


class PatientRecord {
private:
    int recordID, entryDate;
    string patientFirstName, patientLastName, country, diseaseID;

public:
    int exitDate;

    PatientRecord(int id, string firstName, string lastName, string disease, string region, int entry, int exit);
    int id();       // return ID
    int entry();    // return Entry Date
    bool compare(PatientRecord *x);     // compare patient record with x (x can be dummy record)
    string firstName();
    string lastName();
    string getCountry();
    string disease();
};

