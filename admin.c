#include "airport.h"


void adminMenu() {
    int choice;
    while(1) {
        printf("\nAdmin Menu\n");
        printf("1. View All Flights\n2. Add Flight\n3. View Passengers\n");
        printf("4. Edit Passenger\n5. Edit Flights\n6. Cancel Booking\n7. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                displayFlights();
                break;
            case 2:
                addFlight();
                break;
            case 3:
                viewPassengers();
                break;
            case 4:
                editPassenger();
                break;
            case 5:
                editFlight();
                break;
            case 6:
                cancelBooking();
                break;
            case 7: 
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void addFlight() {
    Flight new_flight;
    printf("\nEnter Flight Number: ");
    scanf("%s", new_flight.flight_no);
    printf("Origin: ");
    scanf("%s", new_flight.origin);
    printf("Destination: ");
    scanf("%s", new_flight.destination);
    printf("Departure Time (HH:MM): ");
    scanf("%s", new_flight.departure);
    printf("Arrival Time (HH:MM): ");
    scanf("%s", new_flight.arrival);
    printf("Total Seats: ");
    scanf("%d", &new_flight.total_seats);
    printf("Economy Class Price: ");
    scanf("%f", &new_flight.ticket_price[0]);
    printf("Business Class Price: ");
    scanf("%f", &new_flight.ticket_price[1]);
    printf("First Class Price: ");
    scanf("%f", &new_flight.ticket_price[2]);
    
    new_flight.booked_seats = 0;
    saveFlight(new_flight);
    printf("Flight added successfully!\n");
}
void displayFlights() {
    Flight flights[MAX_FLIGHTS];
    int count = 0;
    loadFlights(flights, &count);
    
    printf("\nFlight Schedule:\n");
    printf("---------------------------------------------------------------------\n");
    printf("Flight No. | Origin      | Destination | Departure | Arrival | Seats\n");
    printf("---------------------------------------------------------------------\n");
    
    for(int i = 0; i < count; i++) {
        printf("%-10s | %-11s | %-11s | %-9s | %-7s | %d/%d\n",
               flights[i].flight_no,
               flights[i].origin,
               flights[i].destination,
               flights[i].departure,
               flights[i].arrival,
               flights[i].booked_seats,
               flights[i].total_seats);
    }
}

void viewPassengers() {
    Passenger passengers[MAX_PASSENGERS];
    int count = 0;
    loadPassengers(passengers, &count);
    
    printf("\nPassenger List:\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Name                | Passport  | Nationality   | Age | Flight  | Seat | Class\n");
    printf("--------------------------------------------------------------------------------\n");
    
    for(int i = 0; i < count; i++) {
        printf("%-19s | %-9s | %-13s | %-3d | %-7s | %-4s | %s\n",
               passengers[i].name,
               passengers[i].passport,
               passengers[i].nationality,
               passengers[i].age,
               passengers[i].flight_no,
               passengers[i].seat,
               passengers[i].ticket_class == 1 ? "Economy" :
               passengers[i].ticket_class == 2 ? "Business" : "First");
    }
}

void editPassenger() {
    char passport[10];
    printf("Enter passport number to edit: ");
    scanf("%s", passport);
    
    Passenger passengers[MAX_PASSENGERS];
    int count = 0;
    loadPassengers(passengers, &count);
    
    for(int i = 0; i < count; i++) {
        if(strcmp(passengers[i].passport, passport) == 0) {
            printf("Editing passenger: %s\n", passengers[i].name);
            printf("New name: ");
            scanf("%s", passengers[i].name);
            printf("New seat: ");
            scanf("%s", passengers[i].seat);
            
            // Save updated passengers
            FILE *fp = fopen(PASSENGER_FILE, "wb");
            if(fp) {
                fwrite(passengers, sizeof(Passenger), count, fp);
                fclose(fp);
                printf("Passenger updated!\n");
            }
            return;
        }
    }
    printf("Passenger not found!\n");
}

void cancelBooking() {
    char passport[10];
    printf("Enter passport number to cancel: ");
    scanf("%s", passport);
    
    Passenger passengers[MAX_PASSENGERS];
    int count = 0;
    loadPassengers(passengers, &count);
    
    FILE *fp = fopen(PASSENGER_FILE, "wb");
    if(!fp) {
        printf("Error opening file!\n");
        return;
    }
    
    int found = 0;
    for(int i = 0; i < count; i++) {
        if(strcmp(passengers[i].passport, passport) == 0) {
            found = 1;
            // Update flight seats
            Flight flights[MAX_FLIGHTS];
            int flight_count = 0;
            loadFlights(flights, &flight_count);
            for(int j = 0; j < flight_count; j++) {
                if(strcmp(flights[j].flight_no, passengers[i].flight_no) == 0) {
                    flights[j].booked_seats--;
                    break;
                }
            }
            // Save updated flights
            FILE *flight_file = fopen(FLIGHT_FILE, "wb");
            if(flight_file) {
                fwrite(flights, sizeof(Flight), flight_count, flight_file);
                fclose(flight_file);
            }
        } else {
            fwrite(&passengers[i], sizeof(Passenger), 1, fp);
        }
    }
    fclose(fp);
    printf(found ? "Booking cancelled!\n" : "Passenger not found!\n");
}

void updatePassengerDetails(const char *passportNumber, const char *newSeatNumber, const char *newPassportNumber) {
    FILE *fp = fopen(PASSENGER_FILE, "rb+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Passenger p;
    int found = 0;

    while (fread(&p, sizeof(Passenger), 1, fp)) {
        if (strcmp(p.passport, passportNumber) == 0) {
            found = 1;
            // Update the passenger details
            strncpy(p.seat, newSeatNumber, sizeof(p.seat) - 1);
            strncpy(p.passport, newPassportNumber, sizeof(p.passport) - 1);

            // Move the file pointer back to overwrite the record
            fseek(fp, -sizeof(Passenger), SEEK_CUR);
            fwrite(&p, sizeof(Passenger), 1, fp);
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("Passenger details updated successfully.\n");
    } else {
        printf("Passenger with passport number %s not found.\n", passportNumber);
    }
}

void editFlight() {
    char flight_no[10];
    printf("Enter flight number to edit: ");
    scanf("%s", flight_no);

    Flight flights[MAX_FLIGHTS];
    int count = 0;
    loadFlights(flights, &count);

    for (int i = 0; i < count; i++) {
        if (strcmp(flights[i].flight_no, flight_no) == 0) {
            printf("Editing flight: %s\n", flights[i].flight_no);
            printf("New Origin: ");
            scanf("%s", flights[i].origin);
            printf("New Destination: ");
            scanf("%s", flights[i].destination);
            printf("New Departure Time (HH:MM): ");
            scanf("%s", flights[i].departure);
            printf("New Arrival Time (HH:MM): ");
            scanf("%s", flights[i].arrival);
            printf("New Total Seats: ");
            scanf("%d", &flights[i].total_seats);
            printf("New Economy Class Price: ");
            scanf("%f", &flights[i].ticket_price[0]);
            printf("New Business Class Price: ");
            scanf("%f", &flights[i].ticket_price[1]);
            printf("New First Class Price: ");
            scanf("%f", &flights[i].ticket_price[2]);

            // Save updated flights
            FILE *fp = fopen(FLIGHT_FILE, "wb");
            if (fp) {
                fwrite(flights, sizeof(Flight), count, fp);
                fclose(fp);
                printf("Flight updated successfully!\n");
            } else {
                printf("Error saving updated flight details!\n");
            }
            return;
        }
    }
    printf("Flight not found!\n");
    return;
}



// Add other admin functions here (viewPassengers, editPassenger, cancelBooking)