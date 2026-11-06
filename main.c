#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_PATH "anniversaries_data.txt"

//structure for database
typedef struct Anniversary {
    int year;
    int month;
    int day;
    char eventType[50];
    char eventCategory[50];
    char eventName[100];
}Anniversary;


// Node for linked list
typedef struct Node {
    Anniversary data;
    struct Node *next;
} Node;



// Function prototypes
void printAllAnniversaries(Node *head);
void loadDatabase(Node **head);
void displayFromDatabase(Node* head);
void saveDatabase(Node *head);
void addToDatabase(Node **head, Anniversary data);
int ValidDate(int day, int month, int year);
void entry(Node **head);
void writeToDatabase(Node *head, Anniversary data);
void displayByCategory(Node *head);
void displayByDay(Node *head, int displayDay, int displayMonth);
void displayByPreviousMonth(Node *head, int currentMonth);
void displayByNextMonth(Node *head, int presentMonth);



Node* createNode(Anniversary a) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = a;
        newNode->next = NULL;
    } else {
        printf("Memory allocation error in createNode\n");
    }
    return newNode;
}

// Main function
int main() {

        int option;
        Node *head = NULL;
        loadDatabase(&head);
        int displayDay, displayMonth;
        int currentMonth;
        int presentMonth;
    // Creating the menu using do while loop
    do{
        printf ("\nMenu:\n");
        printf("Option 1: Add new entry\n");
        printf("Option 2: Display from database\n");
        printf("Option 3: Display birthdays/anniversaries by category\n");
        printf("Option 4: Display birthdays/anniversaries by day\n");
        printf("Option 5: Display birthdays/anniversaries for the previous month\n");
        printf("Option 6: Display birthdays/anniversaries for the next month\n");

        printf("Option 7: Exit\n");

        printf("Enter an option from 1 to 7: ");
        scanf("%d",&option);
        switch(option){
            case 1 :
                entry(&head);
                break;

            case 2:
                displayFromDatabase(head);
                printAllAnniversaries(head); // Print all anniversaries when option 2 is chosen
                break;

            case 3 :
                displayByCategory(head);
                break;

            case 4:
                printf("\nEnter the day for display: ");
                scanf("%d", &displayDay);
                printf("Enter the month for display: ");
                scanf("%d", &displayMonth);
                displayByDay(head, displayDay, displayMonth);
                break;

            case 5:
                printf("\nEnter the current month for display: ");
                scanf("%d", &currentMonth);
                displayByPreviousMonth(head, currentMonth);
                break;

            case 6:
                printf("\nEnter the current month for display: ");
                scanf("%d", &presentMonth);
                displayByNextMonth(head, presentMonth);
                break;

            case 7:
                saveDatabase(head);
                // Save the database to the file before exiting
                break;
            default:
                printf("\nYou entered an option that is not in the menu, please enter a correct option. ");
        }

    }
    while(option!=7);

    // Free memory
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}

void loadDatabase(Node **head) {
    FILE *file = fopen(FILE_PATH, "r");

    if (file != NULL) {
        Anniversary data;
        Node *newNode;

        while (fscanf(file, "Year: %d\nMonth: %d\nDay: %d\nCategory: %[^\n]\nType: %[^\n]\nName/Description of the Event: %[^\n]\n---------------------------------------------------------\n",
               &data.year, &data.month, &data.day, data.eventCategory, data.eventType, data.eventName) == 6) {
            newNode = createNode(data);
            newNode->next = *head;
            *head = newNode;
        }
         printf("\nData loaded successfully.\n\n");

    } else {
        printf("There is nothing in the file\n");
        return;
    }
    fclose(file);
}

void displayFromDatabase(Node* head){
    FILE *file = fopen(FILE_PATH, "r");
    if (file != NULL) {
        Anniversary data;
        Node *newNode;

        while (!EOF) {
            fscanf(file, "Year: %d\nMonth: %d\nDay: %d\nCategory: %[^\n]\nType: %[^\n]\nName/Description of the Event: %[^\n]\n---------------------------------------------------------\n",
               &data.year, &data.month, &data.day, data.eventCategory, data.eventType, data.eventName);
            newNode = createNode(data);
            newNode->next = head;
            head = newNode;

                printf("\nYear: %d\n", data.year);
                printf("Month: %d\n", data.month);
                printf("Day: %d\n", data.day);
                printf("Category: %s\n", data.eventCategory);
                printf("Type: %s\n", data.eventType);
                printf("Name/Description of the Event: %s\n", data.eventName);
                printf("---------------------------------------------------------\n");
        }
    }else{
        printf("There is no data in the file\n");
    }
        fclose(file);
}


void saveDatabase(Node *head) {
    FILE *file = fopen(FILE_PATH, "w");

    if (file != NULL) {
        Node *current = head;

        while (current != NULL) {
            fprintf(file, "Year: %d\n", current->data.year);
            fprintf(file, "Month: %d\n", current->data.month);
            fprintf(file, "Day: %d\n", current->data.day);
            fprintf(file, "Category: %s\n", current->data.eventCategory);
            fprintf(file, "Type: %s\n", current->data.eventType);
            fprintf(file, "Name/Description of the Event: %s\n", current->data.eventName);
            fprintf(file, "---------------------------------------------------------\n");

            current = current->next;
        }

        fclose(file);
        printf("\nData saved successfully.\n");
    } else {
        printf("Error opening the file for writing.\n");
    }
}

void addToDatabase(Node **head, Anniversary data) {
    // Add the new entry to the linked list
    Node *newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;

    // Save the database to the file
    saveDatabase(*head);
}

// Function to check if the entered date is valid
int ValidDate(int day, int month, int year) {
    if (year < 0 || year >2024 || month < 1 || month > 12 || day < 1) {
        printf ("\nInvalid date input, Please enter valid date.\n");
        return 0; // Invalid date
    }

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust for leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }

    return 1;
}

void entry(Node **head) {
    Anniversary Add_anniversary;

    do {
        printf("\nEnter the year: ");
        scanf(" %d", &Add_anniversary.year);
        printf("\nEnter the month: ");
        scanf(" %d", &Add_anniversary.month);
        printf("\nEnter the day: ");
        scanf(" %d", &Add_anniversary.day);
        printf("\nEvent Date: %d/%d/%d", Add_anniversary.year, Add_anniversary.month, Add_anniversary.day);
        printf("\nEnter the type of event (birthday, nameday, etc): ");
        scanf(" %[^\n]", Add_anniversary.eventType);
        printf("\nEnter the category of event (Family, Friend, Relative, Colleague, Others): ");
        scanf(" %[^\n]", Add_anniversary.eventCategory);
        printf("\nName or description of the event: ");
        scanf(" %[^\n]", Add_anniversary.eventName);

        if (ValidDate(Add_anniversary.year, Add_anniversary.month, Add_anniversary.day)) {
            // Add the new entry to the linked list
            addToDatabase(head, Add_anniversary);


        }
    } while (!ValidDate(Add_anniversary.year, Add_anniversary.month, Add_anniversary.day));
}



void displayByCategory(Node *head) {
    // Display available categories
    printf("\nAvailable Categories:\n");
    printf("1) Family\n");
    printf("2) Friend\n");
    printf("3) Relative\n");
    printf("4) Colleague\n");
    printf("5) Others\n");

    int choice;
    printf("Choose the category you want to search (1-5): ");
    scanf("%d", &choice);

    char searchCategory[50];
    int found = 0;

    // Maps the user's choice to the corresponding category
    switch (choice) {
        case 1:
            strcpy(searchCategory, "Family");
            break;
        case 2:
            strcpy(searchCategory, "Friend");
            break;
        case 3:
            strcpy(searchCategory, "Relative");
            break;
        case 4:
            strcpy(searchCategory, "Colleague");
            break;
        case 5:
            strcpy(searchCategory, "Others");
            break;
        default:
            printf("Invalid choice. Please choose a category from 1 to 5.\n");
            return;
    }

    Node *current = head;

    printf("\nAnniversaries/Birthdays in the category '%s':\n", searchCategory);

    while (current != NULL) {
    // Used strcasecmp for case-insensitive comparison
    if (strcasecmp(current->data.eventCategory, searchCategory) == 0) {
        // Display the anniversary/birthday data
        printf("\nYear: %d\n", current->data.year);
        printf("Month: %d\n", current->data.month);
        printf("Day: %d\n", current->data.day);
        printf("Category: %s\n", current->data.eventCategory);
        printf("Type: %s\n", current->data.eventType);
        printf("Name/Description of the Event: %s\n", current->data.eventName);
        printf("---------------------------------------------------------\n");

        found = 1;
    }
    current = current->next;
}

    if (!found) {
        printf("No anniversaries/birthdays found in the category '%s'.\n", searchCategory);
    }
}


void displayByDay(Node *head, int displayDay, int displayMonth) {
    if (head == NULL) {
        printf("No anniversaries/birthdays found.\n");
        return;
    }

    Node *current = head;
    int found = 0;

    printf("\nAnniversaries/Birthdays on %d/%d:\n", displayDay, displayMonth);

    while (current != NULL) {
        if (current->data.month == displayMonth && current->data.day == displayDay) {
            // Display the anniversary/birthday data
            printf("\nYear: %d\n", current->data.year);
            printf("Month: %d\n", current->data.month);
            printf("Day: %d\n", current->data.day);
            printf("Category: %s\n", current->data.eventCategory);
            printf("Type: %s\n", current->data.eventType);
            printf("Name/Description of the Event: %s\n", current->data.eventName);
            printf("---------------------------------------------------------\n");

            found = 1;
        }
        current = current->next;
    }

    if (!found) {
        printf("No anniversaries/birthdays found on %d/%d.\n", displayDay, displayMonth);
    }
}


void displayByPreviousMonth(Node *head, int currentMonth) {
    printf("\nAnniversaries/Birthdays in the previous month (chronological order for the day):\n");

    Node *current = head;
    int found = 0;

    // Created a dynamic array of pointers to nodes
    Node **eventsArray = NULL;
    int eventCount = 0;

    // Traverse the linked list and store events in the previous month
    while (current != NULL) {
        int previousMonth;
        if (current->data.month == 1) {
            previousMonth = 12;
        } else {
            previousMonth = current->data.month + 1;
        }

        if (previousMonth == currentMonth) {
            // Resized the array to accommodate the new node
            eventsArray = realloc(eventsArray, (eventCount + 1) * sizeof(Node *));
            if (eventsArray == NULL) {
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }

            // Store the node in the array
            eventsArray[eventCount++] = current;
        }
        current = current->next;
    }

    // Sort events in the array based on the day
    for (int i = 0; i < eventCount - 1; i++) {
        for (int j = 0; j < eventCount - i - 1; j++) {
            if (eventsArray[j]->data.day > eventsArray[j + 1]->data.day) {
                Node *temp = eventsArray[j];
                eventsArray[j] = eventsArray[j + 1];
                eventsArray[j + 1] = temp;
            }
        }
    }

    // Print events in chronological order for the day
    for (int i = 0; i < eventCount; i++) {
        // Display the anniversary/birthday data
        printf("%02d/%02d - %s (%s, %s)\n", eventsArray[i]->data.month, eventsArray[i]->data.day,
               eventsArray[i]->data.eventName, eventsArray[i]->data.eventType, eventsArray[i]->data.eventCategory);

        found = 1;
    }

    // Free the dynamically allocated array
    free(eventsArray);

    if (!found) {
        printf("No events found in the previous month.\n");
    }
}
void displayByNextMonth(Node *head, int presentMonth){
        printf("\nAnniversaries/Birthdays in the next month (chronological order for the day):\n");

    Node *current = head;
    int found = 0;

    // Create a dynamic array of pointers to nodes
    Node **eventsArray = NULL;
    int eventCount = 0;

    // Traverse the linked list and store events in the previous month
    while (current != NULL) {
        int nextMonth;
        if (current->data.month == 12) {
            nextMonth = 1;
        } else {
            nextMonth = current->data.month - 1;
        }

        if (nextMonth == presentMonth) {
            // Resize the array to accommodate the new node
            eventsArray = realloc(eventsArray, (eventCount + 1) * sizeof(Node *));
            if (eventsArray == NULL) {
                printf("Memory allocation error.\n");
                exit(EXIT_FAILURE);
            }

            // Store the node in the array
            eventsArray[eventCount++] = current;
        }
        current = current->next;
    }

    // Sort events in the array based on the day
    for (int i = 0; i < eventCount - 1; i++) {
        for (int j = 0; j < eventCount - i - 1; j++) {
            if (eventsArray[j]->data.day > eventsArray[j + 1]->data.day) {
                // Swap nodes in the array
                Node *temp = eventsArray[j];
                eventsArray[j] = eventsArray[j + 1];
                eventsArray[j + 1] = temp;
            }
        }
    }

    // Print events in chronological order for the day
    for (int i = 0; i < eventCount; i++) {
        // Display the anniversary/birthday data
        printf("%02d/%02d - %s (%s, %s)\n", eventsArray[i]->data.month, eventsArray[i]->data.day,
               eventsArray[i]->data.eventName, eventsArray[i]->data.eventType, eventsArray[i]->data.eventCategory);

        found = 1;
    }

    // Free the dynamically allocated array
    free(eventsArray);

    if (!found) {
        printf("No events found in the previous month.\n");
    }
}







void printAllAnniversaries(Node *head) {
    if (head == NULL) {
        printf("No anniversaries/birthdays found.\n");
        return;
    }

    Node *current = head;

    printf("\nAll Anniversaries/Birthdays:\n");

    while (current != NULL) {
        // Display the anniversary/birthday data
        printf("\nYear: %d\n", current->data.year);
        printf("Month: %d\n", current->data.month);
        printf("Day: %d\n", current->data.day);
        printf("Category: %s\n", current->data.eventCategory);
        printf("Type: %s\n", current->data.eventType);
        printf("Name/Description of the Event: %s\n", current->data.eventName);
        printf("---------------------------------------------------------\n");

        current = current->next;
    }
}
