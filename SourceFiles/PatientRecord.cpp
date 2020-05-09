#include "../HeaderFiles/PatientRecord.h"


PatientRecord::PatientRecord(int id, string firstName, string lastName, string disease, string region, int entry, int exit) {
    recordID = id;
    patientFirstName = firstName;
    patientLastName = lastName;
    diseaseID = disease;
    country = region;
    entryDate = entry;
    exitDate = exit;
}

int PatientRecord::id() {
    return recordID;
}

int PatientRecord::entry() {
    return entryDate;
}

string PatientRecord::firstName() {
    return patientFirstName;
}

string PatientRecord::lastName() {
    return patientLastName;
}

string PatientRecord::getCountry() {
    return country;
}

string PatientRecord::disease() {
    return diseaseID;
}

// Compare with x
// if x has entry = -1 or "" ignore entry
bool PatientRecord::compare(PatientRecord *x) {
    if(x == NULL)
        return true;

    if(x->id() != -1 && x->id() != recordID)
        return false;
    if(x->firstName() != "" && x->firstName() != patientFirstName)
        return false;
    if(x->lastName() != "" && x->lastName() != patientLastName)
        return false;
    if(x->disease() != "" && x->disease() != diseaseID)
        return false;
    if(x->getCountry() != "" && x->getCountry() != country)
        return false;
    if(x->entry() != -1 && x->entry() != entryDate)
        return false;
    if(x->exitDate != -1 && x->exitDate != exitDate)
        return false;
    
    return true;
}