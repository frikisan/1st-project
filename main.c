#include "airport.h"

const char PASSENGER_FILE[] = "passengers.dat";
const char FLIGHT_FILE[] = "flights.dat";

int main() {
    initializeSystem();
    
    printf("\nAirport Management System\n");
    printf("=========================\n");
    
    if(login()) {
        int choice;
        while(1) {
            printf("\n1. Admin Mode\n2. User Mode\n3. Exit\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            
            switch(choice) {
                case 1:
                    adminMenu();
                    break;
                case 2:
                    userMenu();
                    break;
                case 3:
                    exit(0);
                default:
                    printf("Invalid choice!\n");
            }
        }
    }
    return 0;
}

void initializeSystem() {
    FILE *fp = fopen(FLIGHT_FILE, "ab");
    if(fp) fclose(fp);
    fp = fopen(PASSENGER_FILE, "ab");
    if(fp) fclose(fp);
}

int login() {
    char username[20], password[20];
    printf("\nLogin\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    if(strcmp(password, PASSWORD) == 0 && strcmp(username, "admin") == 0) {
        return 1;
    }
    printf("Invalid credentials!\n");
    return 0;
}