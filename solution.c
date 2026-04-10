#include <stdio.h>
#include <string.h>

#define SEATS 48
#define FILE_NAME "seats.dat"

// Structure for each seat
typedef struct {
    int seat_id;
    int assigned; // 0 = empty, 1 = taken
    char first[20];
    char last[20];
} Seat;

// Function prototypes
void initSeats(Seat plane[]);
void loadSeats(Seat plane[]);
void saveSeats(Seat plane[]);

void showEmptyCount(Seat plane[]);
void showEmptySeats(Seat plane[]);
void showAlphabetical(Seat plane[]);
void assignSeat(Seat plane[]);
void deleteSeat(Seat plane[]);
void flightMenu(Seat plane[]);

int main() {
    Seat outbound[SEATS];
    Seat inbound[SEATS];

    // Load saved data (if exists)
    loadSeats(outbound);
    loadSeats(inbound);

    char choice;

    while (1) {
        printf("\n=== MAIN MENU ===\n");
        printf("a) Outbound Flight\n");
        printf("b) Inbound Flight\n");
        printf("c) Quit\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        if (choice == 'a') {
            flightMenu(outbound);
        } else if (choice == 'b') {
            flightMenu(inbound);
        } else if (choice == 'c') {
            printf("Exiting program...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

// Initialize seats
void initSeats(Seat plane[]) {
    for (int i = 0; i < SEATS; i++) {
        plane[i].seat_id = i + 1;
        plane[i].assigned = 0;
        strcpy(plane[i].first, "");
        strcpy(plane[i].last, "");
    }
}

// Load data from file
void loadSeats(Seat plane[]) {
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        initSeats(plane);
        return;
    }

    fread(plane, sizeof(Seat), SEATS, fp);
    fclose(fp);
}

// Save data to file
void saveSeats(Seat plane[]) {
    FILE *fp = fopen(FILE_NAME, "wb");

    if (fp == NULL) {
        printf("Error saving data!\n");
        return;
    }

    fwrite(plane, sizeof(Seat), SEATS, fp);
    fclose(fp);
}

// Count empty seats
void showEmptyCount(Seat plane[]) {
    int count = 0;
    for (int i = 0; i < SEATS; i++) {
        if (!plane[i].assigned)
            count++;
    }
    printf("Empty seats: %d\n", count);
}

// List empty seats
void showEmptySeats(Seat plane[]) {
    printf("Empty seats:\n");
    for (int i = 0; i < SEATS; i++) {
        if (!plane[i].assigned)
            printf("Seat %d\n", plane[i].seat_id);
    }
}

// Show alphabetical list
void showAlphabetical(Seat plane[]) {
    Seat temp[SEATS];
    int count = 0;

    for (int i = 0; i < SEATS; i++) {
        if (plane[i].assigned) {
            temp[count++] = plane[i];
        }
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(temp[i].last, temp[j].last) > 0) {
                Seat t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    printf("Assigned seats (alphabetical):\n");
    for (int i = 0; i < count; i++) {
        printf("%s %s - Seat %d\n",
               temp[i].first, temp[i].last, temp[i].seat_id);
    }
}

// Assign seat
void assignSeat(Seat plane[]) {
    int seat;

    printf("Enter seat number (1-48) or 0 to cancel: ");
    scanf("%d", &seat);

    if (seat == 0) return;

    if (seat < 1 || seat > SEATS) {
        printf("Invalid seat.\n");
        return;
    }

    if (plane[seat - 1].assigned) {
        printf("Seat already taken.\n");
        return;
    }

    printf("Enter first name: ");
    scanf("%s", plane[seat - 1].first);

    printf("Enter last name: ");
    scanf("%s", plane[seat - 1].last);

    plane[seat - 1].assigned = 1;

    saveSeats(plane); // SAVE AFTER CHANGE

    printf("Seat assigned successfully.\n");
}

// Delete seat
void deleteSeat(Seat plane[]) {
    int seat;

    printf("Enter seat number to delete (or 0 to cancel): ");
    scanf("%d", &seat);

    if (seat == 0) return;

    if (seat < 1 || seat > SEATS || !plane[seat - 1].assigned) {
        printf("Invalid seat.\n");
        return;
    }

    plane[seat - 1].assigned = 0;
    strcpy(plane[seat - 1].first, "");
    strcpy(plane[seat - 1].last, "");

    saveSeats(plane); // SAVE AFTER CHANGE

    printf("Seat assignment removed.\n");
}

// Flight menu
void flightMenu(Seat plane[]) {
    char choice;

    while (1) {
        printf("\n--- FLIGHT MENU ---\n");
        printf("a) Show number of empty seats\n");
        printf("b) Show list of empty seats\n");
        printf("c) Show alphabetical list\n");
        printf("d) Assign a seat\n");
        printf("e) Delete a seat assignment\n");
        printf("f) Return to main menu\n");
        printf("Enter choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a': showEmptyCount(plane); break;
            case 'b': showEmptySeats(plane); break;
            case 'c': showAlphabetical(plane); break;
            case 'd': assignSeat(plane); break;
            case 'e': deleteSeat(plane); break;
            case 'f': return;
            default: printf("Invalid choice.\n");
        }
    }
}