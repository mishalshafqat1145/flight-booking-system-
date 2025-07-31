#include <iostream>
#include <string>
using namespace std;
// Admin credentials
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "1234";

// Function for admin login
bool adminLogin() {
    string username, password;
    cout << "           Admin Login      \n";
    cout << "================================\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
        return true;
    } else {
        return false;
    }
}

struct Flight {
    string flight_Number;
    string departure;
    string destination;
    int ava_Seats;
};

struct Booking {
    string ticket_ID;
    string pass_Name;
    string contNo;
    int age;
    int Booked_tick;
    string flight_No;
};


const int flightCount = 3;
Flight flights[flightCount] = {
    {"PK101", "lahore", "uk", 50},
    {"PK202", "islamabad", "dubai", 30},
    {"PK303", "karachi", "spain", 40}
};

const int maxBookings = 100;
Booking bookings[maxBookings];
int bookingCount = 0;


void searchFlights() {
    string dep, dest;
    int matchCount = 0;

    cout << "\n Search Flights\n";
    cout << "Enter Departure City:(e.g, lahore,islamabad, karachi)\n ";
    cin >> dep;
    cout << "Enter Destination City:(e.g,uk, dubai,spain) \n";
    cin >> dest;

    cout << "\nMatching Flights:\n";
    for (int i = 0; i < flightCount; i++) {
        if (flights[i].departure == dep && flights[i].destination == dest)
		 {
            cout<<"Flight:            " << flights[i].flight_Number<<endl;
            cout<<"Seats Available:   " << flights[i].ava_Seats << endl;
            matchCount++;
        }
    }
    if (matchCount == 0) {
        cout << "No flights found for your search.\n";
    }
}

void bookTicket()
{
    string selectedFlight, name, contact;
    int age, tickets, foundIndex = -1;

    cout << "\n Book Ticket\n";
    cout << "Enter Flight Number(PK101,PK202,PK303): \n ";
    cin >> selectedFlight;

    for (int i = 0; i < flightCount; i++)
	 {
        if (flights[i].flight_Number == selectedFlight)
		 {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        cout << "Flight not found.\n";
        return;
    }

    cout << "\nEnter Passenger Name:            \t";
    cin >> name;
    cout << "\nEnter Age:                       \t";
    cin >> age;
    cout << "\nEnter Contact Number (11 digits):\t";
    cin >> contact;
    cout << "\nEnter Number of Tickets:         \t";
    cin >> tickets;

    if (name == "" || contact == "" || age <= 0 || tickets <= 0) {
        cout << "All fields must be filled correctly.\n";
        return;
    }
    if (contact.length() != 11) {
        cout << "Contact number must be exactly 11 digits.\n";
        return;
    }

    if (flights[foundIndex].ava_Seats >= tickets) {
    int paymentMethod;
     cout << "\n Payment Method:\n\n1. Credit/Debit Card\n\n2. Bank Transfer\n\n3. Mobile Wallet\nSelect option: ";
     cin >> paymentMethod;
     if (paymentMethod < 1 || paymentMethod > 3) {
     cout << "Invalid payment method selected. Booking cancelled.\n";
     return;
     }


        flights[foundIndex].ava_Seats -= tickets;

        Booking newBooking;
        newBooking.ticket_ID = "TICKET-";
        newBooking.ticket_ID += (char)('0' + bookingCount + 1);
        newBooking.pass_Name = name;
        newBooking.contNo = contact;
        newBooking.age = age;
        newBooking.Booked_tick = tickets;
        newBooking.flight_No = selectedFlight;

        bookings[bookingCount] = newBooking;
        bookingCount++;

        cout << "\nBooking Confirmed!\n";
        cout << "Ticket ID:\t" << newBooking.ticket_ID << endl;
        cout << "Passenger:\t" << name <<endl;
		cout << "Contact:  \t" << contact << endl;
        cout << "Flight:   \t" << selectedFlight <<endl; 
		cout << "Tickets:  \t" << tickets << endl;
    } else {
        cout << "Seats Not Available. Only " << flights[foundIndex].ava_Seats << " left.\n";
    }
}

void cancelBooking() {
    string ticketID;
    cout << "\n Cancel Booking\n";
    cout << "Enter Ticket ID:(e.g:- TICKET-0,TICKET-1) ";
    cin >> ticketID;

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].ticket_ID == ticketID ) {
            for (int j = 0; j < flightCount; j++) {
                if (flights[j].flight_Number == bookings[i].flight_No)
				 {
                    flights[j].ava_Seats += bookings[i].Booked_tick;
                    break;
                }
            }

            cout << "Booking for " << bookings[i].pass_Name << " has been cancelled.\n";
            for (int k = i; k < bookingCount - 1; k++) {
                bookings[k] = bookings[k + 1];
            }
            bookingCount--;
            return;
        }
    }
    cout << "Ticket not found.\n";
}

void viewBookings() {
    cout << "\n View All Bookings\n";
    if (bookingCount == 0) {
        cout << "No bookings found.\n";
        return;
    }
    for (int i = 0; i < bookingCount; i++) {
        cout << "Ticket ID: " << bookings[i].ticket_ID << endl;
        cout << "Passenger: " << bookings[i].pass_Name <<endl;
		cout << "Contact:   " << bookings[i].contNo << endl;
        cout << "Flight:    " << bookings[i].flight_No<<endl;
		cout << "Tickets:   " << bookings[i].Booked_tick << endl;
        cout << "-----------------------------\n";
    }
}


int main() 
{
	int choice;
	cout << "\n================================\n";
    cout << "\nWelcome to Flight Booking System\n";
    cout << "\n================================\n";
    // Admin login required first
    if (!adminLogin()) {
        cout << "Access denied. Exiting...\n";
        return 0;  // Exit the program
    }
    cout << "Admin access granted.\n";
   // Show menu only after successful login
    while (true) {
        cout << "\n===========================\n";
        cout << "\n   Flight Booking System \n";
        cout << "\n===========================\n";
        cout << "1. Search Flights\n";
        cout << "2. Book Ticket\n";
        cout << "3. Cancel Booking\n";
        cout << "4. View Bookings\n";
        cout << "5. Exit\n";
        cout << "===========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "===========================\n";

        if (choice == 1) {
            searchFlights();
        }
        else if (choice == 2) {
            bookTicket();
        }
        else if (choice == 3) {
            cancelBooking();
        }
        else if (choice == 4) {
            viewBookings();
        }
        else if (choice == 5) {
            cout << "Exiting...\n";
            cout << "Thank you for using the Flight Booking System!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

