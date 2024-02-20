#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct doctor{
    int id, age;
    char name[30], spec[30];
};


void writeDoctor(){
    fstream f("Doctor.txt", ios::app);
    doctor d1;
    char c;
    do{
        cout << "Enter ID: ", cin >> d1.id;
        cin.ignore();
        cout << "Enter name: "; cin.getline(d1.name, 30);
        cout << "Enter age: ", cin >> d1.age;
        cin.ignore();
        cout << "Enter Specialization: ", cin.getline(d1.spec, 30);
        f.write((char*) &d1, sizeof(d1));
        cout << "Do you want to add another doctor Y/N? ";
        cin >> c;
    }while(tolower(c) == 'y');
    f.close();
}

void readDoctors(){
    doctor d1;
    ifstream f;
    f.open("Doctor.txt", ios::in);
    if(f.is_open()){
        cout << "------------------------------------------\n";
        cout << "ID\tName\t\tAge\tSpeciality\n";
        cout << "------------------------------------------\n";
        f.read((char*) &d1, sizeof(d1));
        while(!f.eof()){
            cout << d1.id << "\t" << setw(15) << left << d1.name << "\t" << d1.age << "\t" <<  d1.spec <<  "\n";
            f.read((char*) &d1, sizeof(d1));
        }
        f.close();
    }
    else cout << "Cannot open the file!\n";
}

void searchDoctors() {
    ifstream f;
    f.open("Doctor.txt", ios::in);
    cout << "Enter Doctor ID: ";
    int key;
    cin >> key;

    if (f.is_open()) {
        doctor d1;
        bool found = false;

        cout << "--------------------------------------------\n";
        cout << "ID\tName\t\tAge\tSpeciality\n";
        cout << "--------------------------------------------\n";

        while (f.read((char*)&d1, sizeof(d1))) {
            if (d1.id == key) {
                found = true;
                cout << d1.id << "\t" << setw(15) << left << d1.name << "\t" << d1.age << "\t" << d1.spec << "\n";
            }
        }

        f.close();

        if (!found) {
            cout << "Not found!\n";
        }
    } else {
        cout << "Cannot open the file!\n";
    }
}



struct patient{
    int id, age;
    char name[30], disease[20];
};

void writePatient(){
    fstream f("Patient.txt", ios::app);
    patient p1;
    char c;
    do{
        cout << "Enter ID: ", cin >> p1.id;
        cin.ignore();
        cout << "Enter name: "; cin.getline(p1.name, 30);
        cout << "Enter age: ", cin >> p1.age;
        cin.ignore();
        cout << "Enter disease: "; cin.getline(p1.disease, 30);
        f.write((char*) &p1, sizeof(p1));
        cout << "Do you want to add another patient Y/N? ";
        cin >> c;
    }while(tolower(c) == 'y');
    f.close();
    
}

void readPatients(){
    patient p1;
    ifstream f;
    f.open("Patient.txt", ios::in);
    if(f.is_open()){
        cout << "----------------------------------------\n";
        cout << "ID\tName\t\tAge\tDisease\n";
        cout << "----------------------------------------\n";
        f.read((char*) &p1, sizeof(p1));
        while(!f.eof()){
            cout << p1.id << "\t" << setw(15) << left << p1.name << "\t" << p1.age << "\t" <<  p1.disease <<  "\n";
            f.read((char*) &p1, sizeof(p1));
        }
        f.close();
    }
    else cout << "Cannot open the file!\n";
}

void searchPatients() {
    ifstream f;
    f.open("Patient.txt", ios::in);
    cout << "Enter patient ID: ";
    int key;
    cin >> key;
    
    if (f.is_open()) {
        patient p1;
        bool found = false;

        cout << "----------------------------------------\n";
        cout << "ID\tName\t\tAge\tDisease\n";
        cout << "----------------------------------------\n";

        while (f.read((char*)&p1, sizeof(p1))) {
            if (p1.id == key) {
                found = true;
                cout << p1.id << "\t" << setw(15) << left << p1.name << "\t" << p1.age << "\t" << p1.disease << "\n";
            }
        }

        f.close();

        if (!found) {
            cout << "Not found!\n";
        }
    } else {
        cout << "Cannot open the file!\n";
    }
}


bool isDoctorExist(const char doctorName[]) {
    ifstream doctorFile("Doctor.txt", ios::in);
    doctor d1;
    bool found = false;
    while (doctorFile.read((char*)&d1, sizeof(d1))) {
        if (strcmp(d1.name, doctorName) == 0) {
            found = true;
            break;
        }
    }
    doctorFile.close();
    return found;  
}

bool isPatientExist(int patientID) {
    ifstream patientFile("Patient.txt", ios::in);
    patient p1;
    bool found = false;
    while (patientFile.read((char*)&p1, sizeof(p1))) {
        if (p1.id == patientID) {
            found = true;
            break;
        }
    }
    patientFile.close();
    return found; 
}


void bookAppointment() {
    
    cout << "Available Doctors:\n";
    readDoctors();

    
    patient p1;
    cout << "Enter patient ID: ";
    cin >> p1.id;
    cin.ignore();

    
    if (!isPatientExist(p1.id)) {
        cout << "Invalid patient ID. Appointment booking failed.\n";
        return;
    }

    cout << "Enter patient name: ";
    cin.getline(p1.name, 30);
    cout << "Enter patient age: ";
    cin >> p1.age;
    cin.ignore();
    cout << "Enter patient disease: ";
    cin.getline(p1.disease, 30);

    
    doctor d1;
    cout << "Enter the name of the doctor you want to book an appointment with: ";
    cin.getline(d1.name, 30);


    if (!isDoctorExist(d1.name)) {
        cout << "Invalid doctor name. Appointment booking failed.\n";
        return;
    }

    
    char appointmentTime[20];
    cout << "Enter the preferred time for the appointment: ";
    cin.getline(appointmentTime, 20);

    
    fstream appointmentFile("Appointments.txt", ios::app | ios::binary);
    if (appointmentFile.is_open()) {
        appointmentFile.write((char*)&p1, sizeof(p1));
        appointmentFile.write((char*)&d1, sizeof(d1));
        appointmentFile.write(appointmentTime, sizeof(appointmentTime));
        appointmentFile.close();
        cout << "Appointment booked successfully!\n";
    } else {
        cout << "Cannot open the appointment file!\n";
    }
}


void viewAppointments() {
    ifstream appointmentFile("Appointments.txt", ios::in | ios::binary);
    if (appointmentFile.is_open()) {
        cout << "--------------------------------------------------------------------------------------------------------\n";
        cout << "Patient ID\tPatient Name\t\tPatient Disease\t\tDoctor Name\t\tAppointment Time\n";
        cout << "--------------------------------------------------------------------------------------------------------\n";

        patient p1;
        doctor d1;
        char appointmentTime[20];

        while (appointmentFile.read((char*)&p1, sizeof(p1)) && appointmentFile.read((char*)&d1, sizeof(d1)) && appointmentFile.read(appointmentTime, sizeof(appointmentTime))) {
            cout << setw(10) << left << p1.id << "\t" << setw(20) << left << p1.name << "\t" << setw(20) << left << p1.disease
                 << "\t" << setw(20) << left << d1.name << "\t" << appointmentTime << "\n";
        }

        cout << "---------------------------------------------------------------------------------------------------------\n";

        appointmentFile.close();
    } else {
        cout << "Cannot open the appointment file!\n";
    }
}




struct adminstrator{
    int id, age;
    char name[30], password[30];
};

void writeAdminstrator(){
    fstream f("Adminstrators.txt", ios::app);
    adminstrator a1;
    char c;
    do{
        cout << "----------------------------\n";
        cout << "|HOSPITAL MANAGEMENT SYSTEM|\n";
        cout << "----------------------------\n";
        cout << "-----------\n";
        cout << "|Add admin|\n";
        cout << "-----------\n";
        cout << "Enter ID: ", cin >> a1.id;
        cin.ignore();
        cout << "Enter name: "; cin.getline(a1.name, 30);
        cout << "Enter age: "; cin >> a1.age;
        cin.ignore();
        cout << "Enter password: "; cin.getline(a1.password, 30);
        f.write((char*) &a1, sizeof(a1));
        cout << "Do you want to add another adminstrator Y/N? ";
        cin >> c;
    }while(tolower(c) == 'y');
    f.close();
    
}

void readAdminstrator(){
    adminstrator a1;
    ifstream f;
    f.open("Adminstrators.txt", ios::in);
    if(f.is_open()){
        cout << "-----------------------------------------\n";
        cout << "ID\tName\t\tAge\tPassword\n";
        cout << "-----------------------------------------\n";
        f.read((char*) &a1, sizeof(a1));
        while(!f.eof()){
            cout << a1.id << "\t" << setw(15) << left << a1.name << "\t" << a1.age << "\t" <<  a1.password <<  "\n";
            f.read((char*) &a1, sizeof(a1));
        }
        f.close();
    }
    else cout << "Cannot open the file!\n";
}

void searchAdminstrators() {
    ifstream f;
    f.open("Adminstrators.txt", ios::in);
    cout << "Enter adminstrator ID: ";
    int key;
    cin >> key;

    if (f.is_open()) {
        adminstrator a1;
        bool found = false;

        cout << "-----------------------------------------\n";
        cout << "ID\tName\t\tAge\tPassword\n";
        cout << "-----------------------------------------\n";

        while (f.read((char*)&a1, sizeof(a1))) {
            if (a1.id == key) {
                found = true;
                cout << a1.id << "\t" << setw(15) << left << a1.name << "\t" << a1.age << "\t" << a1.password << "\n";
            }
        }

        f.close();

        if (!found) {
            cout << "Not found!\n";
        }
    } else {
        cout << "Cannot open the file!\n";
    }
}




bool isAdminstrator(int ID, char password[]){
    adminstrator a1;
    ifstream f;
    f.open("Adminstrators.txt", ios::in);
    if(f.is_open()){
        f.read((char*) &a1, sizeof(a1));
        while(!f.eof()){
            if(a1.id == ID && strcmp(a1.password, password) == 0){
                f.close();
                return true;
            }
            f.read((char*) &a1, sizeof(a1));
        }
        f.close();
    }
    else cout << "Cannot open the file!\n";
    return false;
}

int main()
{
    
    //writeAdminstrator();

    int id;
    char password[30];
    cout << "----------------------------\n";
    cout << "|HOSPITAL MANAGEMENT SYSTEM|\n";
    cout << "----------------------------\n";
    cout << "Enter adminstrator ID: ";
    cin >> id;
    cout << "Enter adminstrator password: ";
    cin.ignore();
    cin.getline(password, 30);
    if(isAdminstrator(id, password)){
        cout << "---------\n";
        cout << "|Welcome|\n";
        cout << "---------\n";
        int choice = 0;
        while(choice != 4){
            cout << "------------------\n";
            cout << "Choose department\n1. Doctors\n2. Patients\n3. Adminstrators\n4. Exit\n"; 
            cin >> choice;
            switch(choice){
                case 1:{      
                    int ch1 = 0;
                    while(ch1 != 4){
                        cout << "---------\n";
                        cout << "|Doctors|\n";
                        cout << "---------\n";
                        cout << "1. View Doctors\n2. Add Doctors\n3. Search Doctors\n4. Back\n";
                        cin >> ch1;
                        switch(ch1){
                            case 1: 
                                readDoctors();
                                break;
                            case 2: 
                                writeDoctor();
                                break;
                            case 3: 
                                searchDoctors();
                                break;
                            
                            case 4: break;
                            default: cout << "Invalid choice!";
                        }
                    }
                }
                break;
                case 2:{
                    int ch2 = 0;
                    while(ch2 != 6){
                        cout << "----------\n";
                        cout << "|Patients|\n";
                        cout << "----------\n";
                        cout << "1. View Patients\n2. Add Patients\n3. Search Patients\n4. Book Appointment\n5. View Appointments\n6. Back\n";  
                        cin >> ch2;
                        switch(ch2){
                            case 1: 
                                readPatients();
                                break;
                            case 2: 
                                writePatient();
                                break;
                            case 3: 
                                searchPatients();
                                break;
                            
                            case 4: 
                                bookAppointment();
                                break;
                            case 5: 
                                viewAppointments();
                                break;
                            
                            case 6: break;
                            default: cout << "Invalid choice!";
                        }
                    }
                }
                break;
                case 3:{
                    int ch3 = 0;
                    while(ch3 != 4){
                        cout << "---------------\n";
                        cout << "|Adminstrators|\n";
                        cout << "---------------\n";
                        cout << "1. View Adminstrators\n2. Add Adminstrators\n3. Search Adminstrators\n4. Back\n";
                        cin >> ch3;
                        switch(ch3){
                            case 1: 
                                readAdminstrator();
                                break;
                            case 2: 
                                writeAdminstrator();
                                break;
                            case 3: 
                                searchAdminstrators();
                                break;
                            
                            case 4: break;
                            default: cout << "Invalid choice!";
                        }
                    }
                }
                break;
                case 4: break;
                default: cout << "Invalid choice!\n";
            }
        }
    }
    else cout << "Wrong ID or password\n";

    return 0;
}
