#include "airport.h"

void userMenu() {
    int choice;
    while(1) {
        printf("\nUser Menu\n");
        printf("1. Book Ticket\n2. View Flights\n3. Generate Ticket\n4. Back\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                displayFlights();
                break;
            case 3:
                // Generate ticket implementation
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

void bookTicket() {
    Passenger new_passenger;
    Flight flights[MAX_FLIGHTS];
    int flight_count = 0;
    
    loadFlights(flights, &flight_count);
    
    printf("\nAvailable Flights:\n");
    for(int i = 0; i < flight_count; i++) {
        if(flights[i].booked_seats < flights[i].total_seats) {
            printf("%d. %s (%s to %s) - Available Seats: %d\n", 
                   i+1, flights[i].flight_no, flights[i].origin, 
                   flights[i].destination, 
                   flights[i].total_seats - flights[i].booked_seats);
        }
    }
    
    int choice;
    printf("Select flight: ");
    scanf("%d", &choice);
    choice--;
    
    if(choice < 0 || choice >= flight_count) {
        printf("Invalid selection!\n");
        return;
    }
    
    strcpy(new_passenger.flight_no, flights[choice].flight_no);
    
    printf("\nEnter Passenger Details:\n");
    printf("Name: ");
    scanf("%s", new_passenger.name);
    printf("Passport Number: ");
    scanf("%s", new_passenger.passport);
    printf("Nationality: ");
    scanf("%s", new_passenger.nationality);
    printf("Age: ");
    scanf("%d", &new_passenger.age);
    printf("Class (1-Economy, 2-Business, 3-First): ");
    scanf("%d", &new_passenger.ticket_class);
    printf("Preferred Seat: ");
    scanf("%s", new_passenger.seat);
    
    if(checkSeatAvailability(new_passenger.flight_no, new_passenger.seat)) {
        printf("Seat already booked!\n");
        return;
    }
    
    savePassenger(new_passenger);
    flights[choice].booked_seats++;
    
    FILE *fp = fopen(FLIGHT_FILE, "wb");
    if(fp == NULL) {
        printf("Error updating flight data!\n");
        return;
    }
    fwrite(flights, sizeof(Flight), flight_count, fp);
    fclose(fp);
    
    printf("Booking successful!\n");
    generateTicket(new_passenger);
}

int checkSeatAvailability(char flight_no[], char seat[]) {
    Passenger passengers[MAX_PASSENGERS];
    int count = 0;
    loadPassengers(passengers, &count);
    
    for(int i = 0; i < count; i++) {
        if(strcmp(passengers[i].flight_no, flight_no) == 0 && 
           strcmp(passengers[i].seat, seat) == 0) {
            return 1;
        }
    }
    return 0;
}

void generateTicket(Passenger p) {
    char filename[50];
    sprintf(filename, "ticket_%s.txt", p.passport);
    
    FILE *fp = fopen(filename, "w");
    if(fp) {
        fprintf(fp, "==================================\n");
        fprintf(fp, "          E-TICKET\n");
        fprintf(fp, "==================================\n");
        fprintf(fp, "Name: %s\n", p.name);
        fprintf(fp, "Passport: %s\n", p.passport);
        fprintf(fp, "Flight: %s\n", p.flight_no);
        fprintf(fp, "Seat: %s\n", p.seat);
        fprintf(fp, "Class: %s\n", 
               p.ticket_class == 1 ? "Economy" :
               p.ticket_class == 2 ? "Business" : "First");
        fprintf(fp, "==================================\n");
        fclose(fp);
        printf("Ticket saved as %s\n", filename);
    } else {
        printf("Error generating ticket!\n");
    }
}
// Add other user functions here