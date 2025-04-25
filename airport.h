/**
 * @file airport.h
 * @brief Header guard to prevent multiple inclusions of the same header file.
 *
 * The `#define AIRPORT_H` directive is part of an include guard mechanism.
 * It ensures that the contents of this header file are included only once
 * during the compilation process, even if the file is included multiple times
 * in different parts of the code. This prevents redefinition errors and
 * improves compilation efficiency.
 *
 * @brief Header file for airport-related functionalities and definitions.
 * 
 * This file contains declarations and macros related to the airport module.
 * It ensures that the header is included only once in the compilation process
 * by using an include guard.
 */
#ifndef AIRPORT_H //if AIRPORT_H is not defined 
#define AIRPORT_H // Define AIRPORT_H to "mark" this header as included

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PASSENGERS 100
#define MAX_FLIGHTS 50
#define MAX_SEATS 300
#define PASSWORD "admin123"

typedef struct {
    char name[50];
    char passport[10];
    char nationality[20];
    int age;
    char flight_no[10];
    char seat[5];
    int ticket_class;
} Passenger;

typedef struct {
    char flight_no[10];
    char origin[50];
    char destination[50];
    char departure[6];
    char arrival[6];
    int total_seats;
    int booked_seats;
    float ticket_price[3];
} Flight;

// File names -> extern variebles they are declared in other files
extern const char PASSENGER_FILE[];
extern const char FLIGHT_FILE[];

// Function declarations
void adminMenu();
void userMenu();
void addFlight();
void displayFlights();
void bookTicket();
void viewPassengers();
void savePassenger(Passenger p);
void saveFlight(Flight f);
int checkSeatAvailability(char flight_no[], char seat[]);
void initializeSystem();
int login();
void editPassenger();
void cancelBooking();
void generateTicket(Passenger p);
void loadFlights(Flight flights[], int *count);
void loadPassengers(Passenger passengers[], int *count);
void updatePassengerDetails(const char *passportNumber, const char *newSeatNumber, const char *newPassportNumber); 
void editFlight();
#endif // Terminates a block of code that was started with a preprocessor: #if, #ifdef #ifndef header guard prevent multiple inclusions