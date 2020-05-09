#include <iostream>
#include <fstream>
#include <sstream>
#include "../HeaderFiles/Hash_Table.h"

using namespace std;

// Turn date string to int
int dateToInt(string date) {
    if(date == "-" || date == "")   // empty date = 0
        return 0;

    string temp;
    stringstream dateStream(date);

    getline(dateStream, temp, '-');
    int d = stoi(temp);
    getline(dateStream, temp, '-');
    int m = stoi(temp);
    getline(dateStream, temp, '-');
    int y = stoi(temp);

    return y*10000 + m*100 + d;     // date = YYYYMMDD
}


int main(int argc, char* argv[]) {
    string fName, lName, country, disease, entryStr, exitStr,
        line, patientRecordsFile;
    int id, entryDate, 
        exitDate, diseaseHashtableNumOfEntries, countryHashtableNumOfEntries, bucketSize;

    if(argc < 9) {
        cout << "- Not Enough Parameters" << endl;
        return 1;
    }

    for(int i = 1; i < argc; i+=2) {
        string temp = argv[i];

        if(!temp.compare("-p"))
            patientRecordsFile = argv[i+1];                     // Input file
        else if(!temp.compare("-h1"))
            diseaseHashtableNumOfEntries = atoi(argv[i+1]);     // Num of buckets in disease HT
        else if(!temp.compare("-h2"))
            countryHashtableNumOfEntries = atoi(argv[i+1]);     // Num of buckets in country HT
        else if(!temp.compare("-b"))
            bucketSize = atoi(argv[i+1]);                       // Bucket Size in Bytes
        else {
            cout << "- Invalid Parameter: " << temp << endl;
            return 1;
        }
    }

    Hash_Table *table_country = new Hash_Table(countryHashtableNumOfEntries, bucketSize, "Country"),
               *table_disease = new Hash_Table(diseaseHashtableNumOfEntries, bucketSize, "Disease");

    ifstream s(patientRecordsFile);

    while(getline(s, line)) {
        istringstream s(line);

        if(!(s >> id >> fName >> lName >> disease >> country >> entryStr >> exitStr)) {
            cout << "- ERROR: Unable to read Record" << endl;
            return 1;
        }

        entryDate = dateToInt(entryStr);
        exitDate = dateToInt(exitStr);
        // Entry date < Exit date else skip record
        if(exitDate !=0 && entryDate > exitDate) {
            cout << "- Invalid Date. Patient ID: " << id << endl;
            continue;
        }
        // Insert Patient record into hash tables
        PatientRecord *p = new PatientRecord(id, fName, lName, disease, country, entryDate, exitDate);
        table_country->insert(p);
        table_disease->insert(p);
    }

    s.close();  // Close patientRecordsFile

    while(cout << "> " && getline(cin, line)) {
        string query = "", param1 = "", param2 = "", param3 = "";
        int date1, date2, temp;

        //cout << "> ";
        istringstream s(line);
        s >> query;
        
        if(query == "/globalDiseaseStats") {
            s >> param1 >> param2;

            date1 = dateToInt(param1);
            date2 = dateToInt(param2);

            if(date1 > date2) {     // swap date1 and date 2 if date2 < date1
                temp = date1;
                date1 = date2;
                date2 = temp;
            }

            if(param1 != "" && param2 == "") 
                cout << "- Missing Parameter <date2>" << endl;
            else
                table_disease->globalStats(date1, date2);
        }
        else if(query == "/diseaseFrequency") {
            s >> disease >> param1 >> param2 >> param3;
            // if param3 != "" create dummy PatientRecord with this attribute
            PatientRecord *p = param3 == "" ? NULL : new PatientRecord(-1, "", "", "", param3, -1, -1);

            date1 = dateToInt(param1);
            date2 = dateToInt(param2);
            
            if(date1 > date2) {     // swap date1 and date 2 if date2 < date1
                temp = date1;
                date1 = date2;
                date2 = temp;
            }

            table_disease->frequency(disease, date1, date2, p);
            if(p != NULL) delete p;
        }
        else if(query == "/topk-Diseases") {
            int k;
            s >> k >> country >> param2 >> param3;
            // Create dummy PatientRecord with country attribute
            PatientRecord *p = new PatientRecord(-1, "", "", "", country, -1, -1);
            
            date1 = 0;
            date2 = 0;
            if(param2 != "") {
                date1 = dateToInt(param2);
                date2 = dateToInt(param3);
            }

            if(date1 > date2) {
                temp = date1;
                date1 = date2;
                date2 = temp;
            }

            table_disease->topK(k, date1, date2, p);
            if(p != NULL) delete p;
        }
        else if(query == "/topk-Countries") {
            int k;
            s >> k >> disease >> param2 >> param3;
            // Create dummy PatientRecord with disease attribute
            PatientRecord *p = new PatientRecord(-1, "", "", disease, "", -1, -1);
            
            date1 = 0;
            date2 = 0;
            if(param2 != "") {
                date1 = dateToInt(param2);
                date2 = dateToInt(param3);
            }

            if(date1 > date2) {
                temp = date1;
                date1 = date2;
                date2 = temp;
            }

            table_country->topK(k, date1, date2, p);
            if(p != NULL) delete p;
        }
        else if(query == "/insertPatientRecord") {
            s >> id >> fName >> lName >> disease >> country >> entryStr >> param1;

            PatientRecord *p = new PatientRecord(id, fName, lName, disease, country, dateToInt(entryStr), dateToInt(param1));
            table_country->insert(p);
            table_disease->insert(p);

            cout << "Record added" << endl;
        }
        else if(query == "/recordPatientExit") {
            s >> id >> exitStr;
            table_country->changeExitDate(id, dateToInt(exitStr));
        }
        else if(query == "/numCurrentPatients") {
            s >> param1;
            table_disease->numCurrentPatients(param1);
        }
        else if(query == "/exit") {
            cout << "exiting" << endl;
            table_country->deleteRecords();     // Delete all PatientRecords
            delete table_country;               // Completely delete table_country data structure
            delete table_disease;               // Completely delete table_disease data structure

            return 0;
        } else if(query != "") {                // Unrecognised user input
            cout << "- Invalid Query";
            if(query.at(0) != '/')              // Check if forgotten '/'
                cout << ": Maybe you mean '/" << line << "'.";
            cout << endl;
        }
    }

    return 1;
}