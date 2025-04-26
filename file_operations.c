#include "airport.h"

void saveFlight(Flight f) {
    FILE *fp = fopen(FLIGHT_FILE, "ab");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&f, sizeof(Flight), 1, fp);
    fclose(fp);
}

void savePassenger(Passenger p) {
    FILE *fp = fopen(PASSENGER_FILE, "ab");
    if(fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&p, sizeof(Passenger), 1, fp);
    fclose(fp);
}

void loadFlights(Flight flights[], int *count) {
    FILE *fp = fopen(FLIGHT_FILE, "rb");
    *count = 0;
    if(fp != NULL) {
        while(fread(&flights[*count], sizeof(Flight), 1, fp)) {
            (*count)++;
        }
        fclose(fp);
    }
}

void loadPassengers(Passenger passengers[], int *count) {
    FILE *fp = fopen(PASSENGER_FILE, "rb");
    *count = 0;
    if(fp != NULL) {
        while(fread(&passengers[*count], sizeof(Passenger), 1, fp)) {
            (*count)++;
        }
        fclose(fp);
    }
}


// Add other file operations here