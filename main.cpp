 #include <iostream>
#include <fstream>	//file handling
#include<iomanip>	//for setw function
#include <string>	//for string
#include <algorithm> // Include the <algorithm> header for transform function
#include <cctype> // Include the <cctype> header for tolower function


using namespace std;

fstream data;
int choice, option, pchoice;
char yesapp;
string searchName;
int Patients;

struct Doctor {
    string dname;
    string dgender;
    string dcontact;
    string availability;
    string dspecialization;
};

struct Patient {
    string pname;
    int page;
    string pgender;
    string pcontact;
    string phealthrecord;
    string pappointment;
    string medicaltest;
};

struct Staff {
	string sname;
    string sdesignation;
    int ssalary;
};


void addDoctor();
void updateDoctor();
void deleteDoctor();
void viewDoctors();

void addPatient();
void viewPatients();
void updatePatient();
void medicalTests();

void addStaff();
void viewStaff();

void mainMenu();
void doctorMenu();
void patientMenu();
void staffMenu();


void replaceSpacesWithUnderscores(string &str);
bool caseInsensitiveCompare(const string& str1, const string& str2);

int main(){
	cout << "" << endl;
	cout << "\t\t\t\t\t $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "\t\t\t\t --------------------------------------------------" << endl;
    cout << "\b\t\t\t\t\tWELCOME TO HOSPITAL MANAGEMENT SYSTEM\b" << endl;
    cout << "\t\t\t\t --------------------------------------------------" << endl;
    cout<<"\t\t\t\t\tDate: "<<__DATE__<<"\t"<<"Time: "<<__TIME__<<endl;
	cout << "\t\t\t\t---------------------------------------------------" << endl <<endl;
	
	
    while (true){
        mainMenu();
    }
    system("pause");
    return 0;
}

void mainMenu() {
   
   cout << "\t\t\t\t\t $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "1. Doctor's Information" << endl;
    cout << "2. View all Doctors" << endl;
    cout << "3. Patient's Information" << endl;
    cout << "4. Staff Information" << endl;
    cout << "5. Exit" << endl;
    cout << "Choose an option (1-5): ";
	int choice;

    cout << "Enter a choice: ";
	cin >> choice;
	
	if(choice==isalpha(choice)){
    	cout<<"You Enter Alphaphet"<<endl;
        cout<<"Code is Terminated .......";
    	cin.clear();
        cin.ignore();
        exit(0);
	}


    cout << endl << endl;
    switch (choice) {
    case 1:
        doctorMenu();
        break;
    case 2:
        viewDoctors();
        break;
    case 3:
        patientMenu();
        break;
    case 4:
        staffMenu();
        break;
    case 5: 
    {
    	cout << "\t\t\t\t\t------------------------------" << endl;
		cout << "\t\t\t\t\tThank you For using our services." << endl;
        cout << "" << endl;
        cout << "\t\t\t\t\t------------------------------" << endl;
        cout << " \t\t\t\t\t Stay healthy, Stay safe" << endl;
        cout << "" << endl;
        cout << "\t\t\t\t\t------------------------------" << endl;
        exit(0);
        break;
	}
        
    default:
        cout << "Wrong choice entered\n";
        break;
    }
}

void doctorMenu() {
	do{
		cout << "\t\t\t\t\tDOCTOR'S INFORMATION'" << endl;

    cout<<"1. Add a new doctor" << endl;
    cout<<"2. Update doctor information" << endl;
    cout<<"3. Delete a doctor" << endl;
    cout<<"4. To Exit From this menu"<<endl;
    cout << "Choose an option (1-4): ";
    cin >> option;
    if(option==isalpha(option)){
    	cout<<"You Enter Alphaphet"<<endl;
        cout<<"Code is Terminated .......";
    	cin.clear();
        cin.ignore();
        exit(0);
	}
    
    switch (option) {
    case 1:
        addDoctor();
        break;
    case 2:
        updateDoctor();
        break;
    case 3:
        deleteDoctor();
        break;
    default:
        cout << "Wrong choice entered\n";
    }
    	}while(option!=4);
}

void addDoctor() {
    data.open("doctors.txt", ios::app);

    char choice;
    do {
        Doctor doctor;
        cin.ignore();
        cout << "Enter doctor name: ";
        getline(cin, doctor.dname);
      
        cout << "Enter doctor gender (F/M/O): ";
        getline(cin, doctor.dgender);

        cout << "Enter doctor contact(03xxxxxxxxx): ";
        getline(cin, doctor.dcontact);

        cout << "Enter Doctor specialization(Consultant, Heart Surgeon, Cardiologist): ";
        getline(cin, doctor.dspecialization);

        cout << "Enter Doctor Availability(hham-hhpm): ";
        getline(cin, doctor.availability);
        
        cout << "---------------------------------------------------" << endl;
        cout << "Doctor registered successfully! \n";
        cout << "---------------------------------------------------" << endl;
        
         
        replaceSpacesWithUnderscores(doctor.dname);
        replaceSpacesWithUnderscores(doctor.dgender);
        replaceSpacesWithUnderscores(doctor.dcontact);
        replaceSpacesWithUnderscores(doctor.dspecialization);
        replaceSpacesWithUnderscores(doctor.availability);

        cout << "To register another doctor press 'y' or Press any other key to go to doctor's menu: ";
        cin >> choice;
        
	
        data << doctor.dname << " " << doctor.dgender << " " << doctor.dspecialization << " " << doctor.availability << endl;

    } while (choice == 'y' || choice == 'Y');
    data.close();
}

void updateDoctor() {
    // Open the file for reading and writing
    fstream data("doctors.txt", ios::in | ios::out);

    if (!data.is_open()) {
        cout << "Error opening doctors.txt file.\n";
        return;
    }
    
    string searchName;
    cout << "Enter the name of the doctor to update: ";
    cin.ignore();
    getline(cin, searchName);
    replaceSpacesWithUnderscores(searchName);

    Doctor doctor;
    bool found = false;

    // Create a temporary file
    ofstream tempFile("temp_doctors.txt", ios::out);

    if (!tempFile.is_open()) {
        cout << "Error creating temporary file.\n";
        data.close();
        return;
    }

    // Search for the doctor by name and copy to the temporary file
    while (data >> doctor.dname >> doctor.dgender >> doctor.dspecialization >> doctor.availability) {
        if (caseInsensitiveCompare(doctor.dname, searchName)){
            found = true;
            cout << "Current Information:\n";
            cout << "Name: " << doctor.dname << ", Gender: " << doctor.dgender << ", Specialization: " << doctor.dspecialization << ", Availability: " << doctor.availability << endl;

            // Update information
            cout << "------------------------------------------" << endl;
            cout << "Enter to information updated:\n";
            cout << "------------------------------------------" << endl<<endl;
            cout << "Enter doctor name: ";
        getline(cin, doctor.dname);

        cout << "Enter doctor gender (F/M/O): ";
        getline(cin, doctor.dgender);

        cout << "Enter doctor contact(03xxxxxxxxx): ";
        getline(cin, doctor.dcontact);

        cout << "Enter Doctor specialization(Consultant, Heart Surgeon, Cardiologist): ";
        getline(cin, doctor.dspecialization);

        cout << "Enter Doctor Availability(hham-hhpm): ";
        getline(cin, doctor.availability);

            
        replaceSpacesWithUnderscores(doctor.dname);
        replaceSpacesWithUnderscores(doctor.dgender);
        replaceSpacesWithUnderscores(doctor.dcontact);
        replaceSpacesWithUnderscores(doctor.dspecialization);
        replaceSpacesWithUnderscores(doctor.availability);
        
        }

        // Write to temporary file
        tempFile << doctor.dname << " " << doctor.dgender << " " << doctor.dspecialization << " " << doctor.availability << endl;
    }

    data.close();
    tempFile.close();

    // Remove the original file
    remove("doctors.txt");

    // Rename the temporary file to the original file
    rename("temp_doctors.txt", "doctors.txt");

    if (!found) {
    	cout << "--------------------------------" << endl;
        cout << "Doctor not found.\n";
        cout << "--------------------------------" << endl;
    } else {
    	cout << "---------------------------------------------------" << endl;
        cout << "Doctor information updated successfully!\n";
        cout << "---------------------------------------------------" << endl;
    }
}


void deleteDoctor() {
    // Open the file for reading and writing
    fstream data("doctors.txt", ios::in | ios::out);

    if (!data.is_open()) {
        cout << "Error opening doctors.txt file.\n";
        return;
    }

    string searchName;
    cout << "Enter the name of the doctor to delete: ";
    cin.ignore();
    getline(cin, searchName);
    replaceSpacesWithUnderscores(searchName);

    Doctor doctor;
    ofstream tempFile("temp.txt", ios::out);

    if (!tempFile.is_open()) {
        cout << "Error creating temporary file.\n";
        data.close();
        return;
    }

    bool found = false;

    // Search for the doctor by name
    while (data >> doctor.dname >> doctor.dgender >> doctor.dspecialization >> doctor.availability) {
        if (caseInsensitiveCompare(doctor.dname ,searchName)){
            found = true;
            cout << "---------------------------------------------------" << endl;
            cout << "Doctor found and deleted successfully!\n";
            cout << "---------------------------------------------------" << endl;
        } else {
            // Write doctors other than the one to be deleted to the temporary file
            tempFile << doctor.dname << " " << doctor.dgender << " " << doctor.dspecialization << " " << doctor.availability << endl;
        }
    }

    if (!found) {
        cout << "Doctor not found.\n";
    }

    // Close both files
    data.close();
    tempFile.close();

    // Remove the original file
    remove("doctors.txt");

    // Rename the temporary file to the original file
    rename("temp.txt", "doctors.txt");
}

void viewDoctors() {
    Doctor doctor;
    data.open("doctors.txt", ios::in);

    if (!data.is_open()) {
        cout << "Error opening doctors.txt file.\n";
        return;
    }
	
	cout << "\t\t\t\t\tVIEW ALL DOCTORS" << endl;
    cout << left << setw(20) << "Name" << setw(10) << "Gender" << setw(20) << "Specialization" << setw(15) << "Availability" << endl;
    cout << "-----------------------------------------------------------" << endl;

    // Read data in the correct order
    while (data >> doctor.dname >> doctor.dgender >> doctor.dspecialization >> doctor.availability) {
    	
    	// Replace underscores with spaces in each variable
        replace(doctor.dname.begin(), doctor.dname.end(), '_', ' ');
        replace(doctor.dgender.begin(), doctor.dgender.end(), '_', ' ');
        replace(doctor.dspecialization.begin(), doctor.dspecialization.end(), '_', ' ');
        replace(doctor.availability.begin(), doctor.availability.end(), '_', ' ');
    	
        cout << left << setw(20) << doctor.dname << setw(10) << doctor.dgender << setw(20) << doctor.dspecialization << setw(15) << doctor.availability << endl;
    }

    data.close();
}

void patientMenu() {
	
	do{
		
	cout << "\t\t\t\t\tPATIENT'S INFORMATION'" << endl;
		
    cout << "1. Add a new patient" << endl;
    cout << "2. View all patients" << endl;
    cout << "3. Update patient information" << endl;
    cout << "4. Patient medical tests" << endl;
    cout<< "5. To Exit From this menu"<<endl;
    cout << "Choose an option (1-5): ";
    cin >> pchoice;
    if(pchoice==isalpha(pchoice)){
    	cout<<"You Enter Alphaphet"<<endl;
        cout<<"Code is Terminated .......";
    	cin.clear();
        cin.ignore();
        exit(0);
	}
    switch (pchoice) {
    case 1:
        addPatient();
        break;
    case 2:
        viewPatients();
        break;
    case 3:
        updatePatient();
        break;
        
    case 4:
		medicalTests();
	    break;
    default:
        cout << "Wrong choice entered\n";
    }
    	}while(pchoice!=5);
}

void addPatient() {
    data.open("patients.txt", ios::app);
    char pChoice;
    do {
        Patient patient;
        
        cin.ignore();
        cout<<"Enter patients name: ";
        getline(cin, patient.pname);

        cout << "Enter patient age: ";
        cin >> patient.page;
	
        cout << "Enter patient gender(F/M/O): ";
        cin.ignore();
        getline(cin, patient.pgender);

        cout << "Enter patient contact(03xxxxxxxxx): ";
        getline(cin, patient.pcontact);

        cout << "Enter patient Health record(Heart pain, Heart Attack, By-pass, Surgery, Angioplasty): ";
        getline(cin, patient.phealthrecord);

        cout << "Press 'y' to book an Appointment: ";
        cin >> patient.pappointment;
        if (patient.pappointment == "y" || patient.pappointment == "Y") {
            string date;
            string time;
            cout << "Enter date of the appointment: ";
            cin >> date;
            cout << "Enter time for the appointment: ";
            cin >> time;
            cout << "Confirmation message sent to " << patient.pcontact << ". Your appointment on " << date << " (" << time << ") is confirmed. Thank you!\n";
        }

        

        replaceSpacesWithUnderscores(patient.pname);
        replaceSpacesWithUnderscores(patient.pgender);
        replaceSpacesWithUnderscores(patient.pcontact);
        replaceSpacesWithUnderscores(patient.phealthrecord);

        data << patient.pname << " " << patient.page << " " << patient.pgender << " " << patient.pcontact << " " << patient.phealthrecord << " " << patient.pappointment << endl;

        cout << "To register another patient press 'y'. or press any other key to stop adding more patients. \n";
        cin >> pChoice;

    } while (pChoice == 'y' || pChoice == 'Y');
    data.close();
}

void viewPatients() {
    Patient patient;
    data.open("patients.txt", ios::in);

    cout << left << setw(20) << "Name" << setw(5) << "Age" << setw(10) << "Gender" << setw(20) << "Health Record" << setw(15) << "Contact" << setw(15) << "Appointment" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    while (data >> patient.pname >> patient.page >> patient.pgender >> patient.pcontact >> patient.phealthrecord >> patient.pappointment) {

        // Replace underscores with spaces in each variable
        replace(patient.pname.begin(), patient.pname.end(), '_', ' ');
        replace(patient.pgender.begin(), patient.pgender.end(), '_', ' ');
        replace(patient.phealthrecord.begin(), patient.phealthrecord.end(), '_', ' ');
        replace(patient.pappointment.begin(), patient.pappointment.end(), '_', ' ');

        cout << left << setw(20) << patient.pname << setw(5) << patient.page << setw(10) << patient.pgender << setw(20) << patient.phealthrecord << setw(15) << patient.pcontact << setw(15) << patient.pappointment << endl;
    }

    data.close();
}

void updatePatient() {
    // Open the file for reading and writing
    fstream data("patients.txt", ios::in | ios::out);

    if ( !data.is_open()) {
        cout << "Error opening patients.txt file.\n";
        return;
    }

    string searchName;
    cout << "Enter the name of the patient to update: ";
    cin.ignore();
    getline(cin, searchName);
    replaceSpacesWithUnderscores(searchName);
    
    Patient patient;
    bool found = false;

    // Create a temporary file
    ofstream tempFile("temp_patients.txt", ios::out);

    if (!tempFile.is_open()) {
        cout << "Error creating temporary file.\n";
        data.close();
        return;
    }

    // Search for the patient by name and copy to the temporary file
    while (data >> patient.pname >> patient.page >> patient.pgender >> patient.phealthrecord >> patient.pcontact >> patient.pappointment) {
        if (caseInsensitiveCompare(patient.pname, searchName)){
            found = true;
            cout << "Current Information:\n";
            cout << "Name: " << patient.pname << ", Age: " << patient.page << ", Gender: " << patient.pgender << ", Health Record: " << patient.phealthrecord << ", Contact: " << patient.pcontact << ", Appointment: " << patient.pappointment << endl;

            // Update information
            cout << "Enter updated information:\n";
            cout << "Enter patient name: ";
            getline(cin, patient.pname);

            cout << "Enter patient age: ";
            cin >> patient.page;
            cin.ignore();

            cout << "Enter patient gender(F/M/O): ";
            getline(cin, patient.pgender);

            cout << "Enter patient health record(Heart pain, Heart Attack, By-pass, Surgery, Angioplasty): ";
            getline(cin, patient.phealthrecord);

            cout << "Enter patient contact(03xxxxxxxxx): ";
            getline(cin, patient.pcontact);

            cout << "Enter patient appointment(DD-MM-YYYY, hh:mm): ";
            getline(cin, patient.pappointment);
            
        replaceSpacesWithUnderscores(patient.pname);
        replaceSpacesWithUnderscores(patient.pgender);
        replaceSpacesWithUnderscores(patient.pcontact);
        replaceSpacesWithUnderscores(patient.phealthrecord);
        }

        // Write to temporary file
        tempFile << patient.pname << " " << patient.page << " " << patient.pgender << " " << patient.phealthrecord << " " << patient.pcontact << " " << patient.pappointment << endl;
    }

    data.close();
    tempFile.close();

    // Remove the original file
    remove("patients.txt");

    // Rename the temporary file to the original file
    rename("temp_patients.txt", "patients.txt");

    if (!found) {
        cout << "\nPatient not found.\n";
    } else {
    	cout << "---------------------------------------------------" << endl;
        cout << "Patient information updated successfully!\n";
        cout << "---------------------------------------------------" << endl;
    }
}

bool caseInsensitiveCompare(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) {
        return false;
    }

    for (size_t i = 0; i < str1.length(); ++i) {
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false;
        }
    }

    return true;
}


void medicalTests() {
	string Name;
    cout << "Enter the name of the patient for medical tests: ";
    cin.ignore();
    getline(cin, Name) ;
    replaceSpacesWithUnderscores(Name);
   Patient patient;
    // Perform medical tests
    cout << "Performing Diagnostic medical tests for " << Name << "\n";
    cout << "Press 1 for ECG \n";
    cout << "Press 2 for EKG \n";
    cout << "Press 3 for Cardiac enzymes test(ck MB ,troponin I levels) \n";
    cout << "Press 4 for Angiography \n";
    cout << "Enter your choice (1-4): ";

    int testchoice;
    cin >> testchoice;

    // Update the medical test based on the user's choice
    switch (testchoice) {
        case 1:
            patient.medicaltest = "ECG";
            cout << "---------------------------------------------------" << endl;
            cout<<"patient is registered successfully for ECG"<<endl;
			cout << "---------------------------------------------------" << endl;
            break;
        case 2:
            patient.medicaltest = "EKG";
            cout << "---------------------------------------------------" << endl;
             cout<<"patient is registered successfully for EKG"<<endl;
             cout << "---------------------------------------------------" << endl;
            break;
        case 3:
            patient.medicaltest = "Cardiac enzymes test(ck MB ,troponin I levels)";
            cout << "---------------------------------------------------" << endl;
             cout<<"patient is registered successfully for Cardiac enzymes test(ck MB ,troponin I levels)"<<endl;
             cout << "---------------------------------------------------" << endl;
            break;
        case 4:
            patient.medicaltest = "Angiography";
            cout << "---------------------------------------------------" << endl;
            cout<<"patient is registered successfully for Angiography"<<endl;
            cout << "---------------------------------------------------" << endl;
            break;
        default:
            patient.medicaltest = "NO";
            cout << "NO medical test \n";
    }

}	
  
void staffMenu() {
    int staffOption;
    do {
        cout << "\t\t\t\t\tSTAFF'S INFORMATION'" << endl;

        cout << "1. Add a new staff" << endl;
        cout << "2. View staff information" << endl;
        cout << "3. To Exit From this menu" << endl;
        cout << "Choose an option (1-3): ";
        cin >> staffOption;
        if(staffOption==isalpha(staffOption)){
    	cout<<"You Enter Alphaphet"<<endl;
        cout<<"Code is Terminated .......";
    	cin.clear();
        cin.ignore();
        exit(0);
	}
        switch (staffOption) {
            case 1:
                addStaff();
                break;
            case 2:
                viewStaff();
                break;
            case 3:
                cout << "Exiting staff menu.\n";
                break;
            default:
                cout << "Wrong choice entered\n";
        }
    } while (staffOption != 3);

    // Reset the main menu option after staff menu is completed
    option = 0;
}


void addStaff() {
	Staff staff;
	char pChoice;
    data.open("staff.txt", ios::app);
    do{
    cin.ignore();
    cout << "Enter Staff's Name: ";
    getline(cin, staff.sname);
    cout << "Enter Designation(Nurse, Helper, Receptionist, ): ";
    getline(cin, staff.sdesignation);
    cout << "Enter Salary per Month: ";
    cin>>staff.ssalary;
	
	replaceSpacesWithUnderscores(staff.sname);
    replaceSpacesWithUnderscores(staff.sdesignation);
    cout << "-------------------------------------" << endl;
	cout << "Staff added successfully.\n";
	cout << "-------------------------------------" << endl;
    
    cout << "To register another patient press 'y'. or press any other key to stop adding more patients. \n";
    cin >> pChoice;
	
    data << staff.sname << " " << staff.sdesignation << " " << staff.ssalary << endl;
	} while ( pChoice == 'y' || pChoice == 'Y');
    data.close();
    
}
void viewStaff() {
	Staff staff;
    data.open("staff.txt", ios::in);
    
    cout << "List of Staff:\n";
    cout << left << setw(20) << "Name" << setw(20) << "Designation:" << setw(10) << "Salary per Month:"<< endl;
    cout << "---------------------------------------------------------" << endl;
    
    while (data >> staff.sname >> staff.sdesignation >> staff.ssalary) {
    	
		 // Replace underscores with spaces in each variable
        replace(staff.sname.begin(), staff.sname.end(), '_', ' ');
        replace(staff.sdesignation.begin(), staff.sdesignation.end(), '_', ' ');		
		
		cout << left << setw(20) << staff.sname << setw(20) << staff.sdesignation<< setw(10) << staff.ssalary<< endl;
    }
    data.close();
}

void replaceSpacesWithUnderscores(string &str) {
    for (char &ch : str) {
        if (ch == ' ') {
            ch = '_';
        }
    }
}
