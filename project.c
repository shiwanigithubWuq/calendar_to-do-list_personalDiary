#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

#define MAX_EVENTS 31
#define MAX_DESCRIPTION_LENGTH 100
#define MAX_LENGTH 50


void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void green()
{
    printf("\033[32m");
}

void blue()
{
    printf("\033[0;34m");
}

void purple()
{
    printf("\033[0;35m");
}

void cyan()
{
    printf("\033[0;36m");
}

void reset()
{
    printf("\033[0m");
}

// Function that returns the index of the
// day for date DD/MM/YYYY
int day_Number(int day, int month, int year)
{

    static int arr[] = {0, 3, 2, 5, 0, 3,
                        5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + arr[month - 1] + day) % 7;
}

// Function that returns the name of the
// month for the given month Number
// January - 0, February - 1, March - 2, April - 3 and so on
char *get_Month_Name(int monthNumber)
{
    char *month;

    switch (monthNumber)
    {
    case 0:
        month = "January";
        break;
    case 1:
        month = "February";
        break;
    case 2:
        month = "March";
        break;
    case 3:
        month = "April";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "June";
        break;
    case 6:
        month = "July";
        break;
    case 7:
        month = "August";
        break;
    case 8:
        month = "September";
        break;
    case 9:
        month = "October";
        break;
    case 10:
        month = "November";
        break;
    case 11:
        month = "December";
        break;
    }
    return month;
}

// Function to return the number of days
// in a particular month
int number_Of_Days(int monthNumber, int year)
{
    // January
    if (monthNumber == 0)
        return (31);

    // February
    if (monthNumber == 1)
    {
        // If the year is leap then Feb
        // has 29 days
        if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            return (29);
        else
            return (28);
    }

    // March
    if (monthNumber == 2)
        return (31);

    // April
    if (monthNumber == 3)
        return (30);

    // May
    if (monthNumber == 4)
        return (31);

    // June
    if (monthNumber == 5)
        return (30);

    // July
    if (monthNumber == 6)
        return (31);

    // August
    if (monthNumber == 7)
        return (31);

    // September
    if (monthNumber == 8)
        return (30);

    // October
    if (monthNumber == 9)
        return (31);

    // November
    if (monthNumber == 10)
        return (30);

    // December
    if (monthNumber == 11)
        return (31);
}

// Function to print the calendar of
// the given year
void print_Calendar(int year)
{
    cyan();
    printf("        Calendar - %d\n\n", year);
    reset();
    int days;

    // Index of the day from 0 to 6
    int spaces = day_Number(1, 1, year);

    // i for Iterate through months
    // j for Iterate through days
    // i for Iterate through month
    for (int i = 0; i < 12; i++)
    {
        days = number_Of_Days(i, year);

        yellow();
        // Print the current month name
        printf("\n ------------%s-------------\n",
               get_Month_Name(i));
        reset();

        // Print the columns
        blue();
        printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
        reset();

        // Print appropriate spaces
        int index;
        for (index = 0; index < spaces; index++)
        {
            printf("     ");
        }

        for (int j = 1; j <= days; j++)
        {
            printf("%5d", j);

            if (++index > 6)
            {
                index = 0;
                printf("\n");
            }
        }

        if (index)
            printf("\n");

        spaces = index;
    }

    return;
}

// Structure to represent a date
struct Date
{
    int day;
    int month;
    int year;
};

typedef struct month {
    struct Date DATE;
    char events[MAX_DESCRIPTION_LENGTH];
    struct month *next;
} Month;

// Array to hold heads for each month
Month *heads[12];

// Function to initialize a month
Month *head() {
    return NULL;
}

// Function to insert an event into a month
void insert_in_month(struct Date date, Month **head) {
    Month *new_node = (Month *)malloc(sizeof(Month));
    if (new_node == NULL) 
    {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->DATE = date;
    printf("Enter the event you want to schedule on %d %d %d : ", date.day, date.month, date.year);
    scanf("%s", new_node->events);
    new_node->next = NULL;

    if (*head == NULL) 
    {
        *head = new_node;
    } 
    else 
    {
        Month *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function to display events scheduled for a particular day
void display_day_schedule(struct Date date, Month *head) 
{
    Month *current = head;
    int flag = 0;

    if (head == NULL) 
    {
        printf("No events scheduled for this month.\n");
    } 
    else 
    {
        printf("Events scheduled for %d %d %d:\n", date.day, date.month, date.year);
        while (current != NULL) {
            if (current->DATE.day == date.day && current->DATE.month == date.month && current->DATE.year == date.year) 
            {
                printf("%s\n", current->events);
                flag = 1;
            }
            current = current->next;
        }
        if (flag == 0) 
        {
            printf("No events scheduled for %d %d %d\n", date.day, date.month, date.year);
        }
    }
}

// Function to sort the scheduled events of a month as per date
void sort(Month *head)
{
    Month *p,*q,*last=NULL,*tmp;
    
    if (head == NULL || head->next == NULL)
        return;

    do {
        tmp = head;
        while(tmp->next!=last)
        {
            if(tmp->DATE.year > tmp->next->DATE.year || 
               (tmp->DATE.year == tmp->next->DATE.year && tmp->DATE.month > tmp->next->DATE.month) ||
               (tmp->DATE.year == tmp->next->DATE.year && tmp->DATE.month == tmp->next->DATE.month && tmp->DATE.day > tmp->next->DATE.day))
            {
                struct Date temp_date = tmp->DATE;
                tmp->DATE = tmp->next->DATE;
                tmp->next->DATE = temp_date;

                char temp_events[MAX_DESCRIPTION_LENGTH];
                strcpy(temp_events, tmp->events);
                strcpy(tmp->events, tmp->next->events);
                strcpy(tmp->next->events, temp_events);
            }
            tmp=tmp->next;
        }
        last=tmp;
    } while(last != head->next);
}

// Function to display month's schedule
void display_month_schedule(Month *head)
{
    Month *p = head;
    if (head == NULL) 
    {
        printf("No events scheduled for this month.\n");
    } 
    else
    {
        sort(head);
        while(p!=NULL)
        {
            
            printf("\n\n");
            printf("%d %d %d\n", p->DATE.day, p->DATE.month, p->DATE.year);
            printf("%s\n", p->events);
            
            p = p->next;
        }
    }
}

// Structure to represent an event node in the linked list
struct EventNode
{
    char description[MAX_DESCRIPTION_LENGTH];
    struct EventNode *next;
};

// Array to store events for each day
struct EventNode *events[MAX_EVENTS] = {NULL};

// Function to compare two dates
bool compareDates(struct Date date1, struct Date date2)
{
    return (date1.day == date2.day && date1.month == date2.month && date1.year == date2.year);
}

// Function to print events on a given date
void printEvents(struct EventNode *head, struct Date date)
{
    bool found = false;
    while (head != NULL)
    {
        green();
        printf("Event on ");
        reset();
        yellow();

        printf(" %02d/%02d/%d : ", date.day, date.month, date.year);
        reset();
        purple();
        printf("%s\n", head->description);
        reset();

        reset();
        head = head->next;
        found = true;
    }
    if (!found)
    {
        printf("No events found for %02d/%02d/%d\n", date.day, date.month, date.year);
    }
}

// Function to insert an event into the linked list
void insertEvent(int day, const char *description)
{
    struct EventNode *newNode = (struct EventNode *)malloc(sizeof(struct EventNode));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    snprintf(newNode->description, sizeof(newNode->description), "%s", description);
    newNode->next = events[day];
    events[day] = newNode;
}

// this is the task node
typedef struct Task
{
    int done;
    char taskName[50];
    struct Task *next;
} Task;

void addTask(Task **head, char *taskName)
{
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (newTask == NULL)
    {
        printf("memory allocation for the Task node is failed\n");
        return;
    }

    strcpy(newTask->taskName, taskName);
    newTask->next = *head;
    *head = newTask;
    printf("new tasks would be added above it");
}

void taskDone(Task *head, int taskNumber)
{
    int index = 1;
    while (head != NULL)
    {
        if (index == taskNumber)
        {
            head->done = 1;
            return;
        }
        head = head->next;
        index++;
    }

    printf("enter valid index which exists in your list");
}

// To delete a particular task
void deleteTask(Task **head, int taskNumber)
{
    Task *present = *head;
    Task *prev = NULL;
    int index = 1;

    while (present != NULL && index != taskNumber)
    {
        prev = present;
        present = present->next;
        index++;
    }

    if (index == taskNumber)
    {
        if (index == 1)
        {
            *head = present->next;
        }
        else
        {
            prev->next = present->next;
        }
        free(present);
        printf("task present at number %d has been successfully removed from your to do list \n ", index);
    }

    else
    {
        printf("the task number you entered is not in range");
    }
}

void taskEntry(Task *head, char *fileName)
{

    FILE *file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("this file  committed an error in opening ");
        return;
    }
    while (head != NULL)
    {
        fprintf(file, " (%d) %s \n ", head->done, head->taskName);
        head = head->next;
    }

    fclose(file);
}

void loadTask(Task **head, char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("an error committed due to nundetermined reason in opening the file foe reading");
        return;
    }
    char taskName[100];
    int done;

    while (fscanf(file, "%d %[^\n]", &done, taskName) != EOF)
    {
        addTask(head, taskName);
        (*head)->done = done;
    }
    fclose(file);
}

void displayTasks(Task *head)
{
    int index = 1;
    printf("To-Do List:\n");
    while (head != NULL)
    {
        printf("%d. [%s] %s\n", index, head->done ? "X" : " ", head->taskName);
        head = head->next;
        index++;
    }
}

void clearList(Task **head)
{
    Task *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}
struct Task1 {
    char description[MAX_LENGTH];
    int completed;
};

struct Task1 tasks[MAX_LENGTH];
int numTasks = 0;

void saveTasksToFile() {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < numTasks; i++) {
        fprintf(file, "%d,%s\n", tasks[i].completed, tasks[i].description);
    }

    fclose(file);
}

void loadTasksFromFile() {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No previous tasks found.\n");
        return;
    }

    char line[MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^\n]", &tasks[numTasks].completed, tasks[numTasks].description);
        numTasks++;
    }

    fclose(file);
}

void add_Task(char *description) {
    if (numTasks < MAX_LENGTH) {
        strcpy(tasks[numTasks].description, description);
        tasks[numTasks].completed = 0;
        numTasks++;
        printf("Task added successfully!\n");
        saveTasksToFile();
    } else {
        printf("Cannot add more tasks, maximum limit reached.\n");
    }
}

void display_Tasks() {
    printf("To-Do List:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("%d. [%s] %s\n", i + 1, tasks[i].completed ? "X" : " ", tasks[i].description);
    }
}

void mark_Completed(int index) {
    if (index >= 1 && index <= numTasks) {
        tasks[index - 1].completed = 1;
        printf("Task marked as completed!\n");
        saveTasksToFile();
    } else {
        printf("Invalid task index!\n");
    }
}
void delete_Task(int index) {
    if (index >= 1 && index <= numTasks) {
        for (int i = index - 1; i < numTasks - 1; i++) {
            strcpy(tasks[i].description, tasks[i + 1].description);
            tasks[i].completed = tasks[i + 1].completed;
        }
        numTasks--;
        printf("Task deleted successfully!\n");
        saveTasksToFile();
    } else {
        printf("Invalid task index!\n");
    }
}

int main()
{
    int year;

    system("cls");
    // Sample events for demonstration
    // Changing colour of Enter key
    yellow();
    printf("Enter 1 : ");
    reset();
    blue();
    printf("If you want to access Calendar\n\n");
    reset();
    yellow();
    printf("Enter 2 : ");
    reset();
    blue();
    printf("If you want to access To-Do List\n\n");
    reset();
    yellow();
    printf("Enter 3 : ");
    reset();
    blue();
    printf("If you want to see the calendar of your desidered year \n\n");
    reset();
    yellow();
    printf("Enter 4 : ");
    reset();
    blue();
    printf("If you want to schedule some important event, meeting, or birthdays\n\n");
    reset();
    yellow();
    printf("Enter 5 : ");
    reset();
    blue();
    printf("Exit \n\n");
    reset();

    // Initialize array of heads
    for (int i = 0; i < 12; i++) 
    {
        heads[i] = head();
    }


    int x;

    scanf("%d", &x);
    if (x != 1 && x != 2 && x != 3 && x != 4 && x!=5)
    {
        system("cls");
        printf("enter a valid number");
    }
    if (x == 3)
    {
        system("cls");
        printf("Enter a year: \n\n");
        scanf("%d", &year);
        // Function Call to print complete year
        print_Calendar(year);
    }
    if(x==4){
    int choice;
        struct Date date;
        char mon[20];
        Month *h;
        yellow();
        printf("Enter '8' : ");
        reset();
        blue();
        printf("if you want to add an event in your schedule.\n");
        reset();
        yellow();
        printf("Enter '9' : ");
        reset();
        blue();
        printf("If you want to see the events planned on a particular date.\n");
        reset();
        yellow();
        printf("Enter '6' : ");
        reset();
        blue();
        printf("if you want to see all the events of a particular month.\n");
        reset();
        yellow();
        printf("Enter '7' : ");
        reset();
        blue();
        printf("To exit.\n");
        reset();

        char year[12][20]={"january","february","march","april","may","june","july","august","september","october","november","december"};

        while (1) 
        {
            green();
            printf("Enter '7', '8', '9' or '6'\n");
            reset();
            scanf("%d", &choice);

            if (choice == 8) 
            {
                cyan();
                printf("Enter date on which you have to schedule some event (in DD MM YYYY format): ");
                reset();
                scanf("%d %d %d", &date.day, &date.month, &date.year);
                insert_in_month(date, &heads[date.month - 1]);
            } 
            else if (choice == 9) 
            {
                cyan();
                printf("Which day's schedule you want to see?\nEnter Date (in DD MM YYYY format):");
                reset();
                scanf("%d %d %d", &date.day, &date.month, &date.year);
                display_day_schedule(date, heads[date.month - 1]);
            }
            else if (choice==6)
            {
                cyan();
                printf("Which month's schedule do you want to see ? \n");
                reset();
                purple();
                printf("Enter the month: ");
                reset();
                scanf("%s", mon);
                for (int i = 0; i < 12; i++) {
                    if (strcmp(year[i], mon) == 0) {
                        h = heads[i];
                        break;
                    }
                }
                display_month_schedule(h);
                } else if (choice == 7) {
                    break;
                } 
            else 
            {
                printf("You have entered an invalid number\n");
            }
        }
    
}

    if (x == 5)
    {
        return 0;
    }
    if (x == 1)
    {

        struct Date date;
        system("cls");

        // Input date to check events
        blue();
        printf("Enter date to check events ");
        reset();
        printf(" (DD MM YYYY): ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);

        // January month
        if (date.month == 1)
        {
            insertEvent(1, "New year day");
            insertEvent(2, "National Science Fiction Day");
            insertEvent(3, "International Mind Body wellness Day");
            insertEvent(4, "world braille day");
            insertEvent(5, "National Birds day");
            insertEvent(6, "World War Orphans Day");
            insertEvent(8, "African National Congress Foundations Day");
            insertEvent(9, "NRI Day");
            insertEvent(10, "world hindi day");
            insertEvent(11, "Death anniversary of Lal Bahadur Shastri");
            insertEvent(12, "national youth day");
            // insertEvent(13, "Lohri");
            // insertEvent(14, "Makar Sankranti");
            insertEvent(15, "indian army day");
            insertEvent(16, "nationl Startup Day");
            insertEvent(17, "Benjamin franklin day");
            insertEvent(18, "National Thesarus Day");
            insertEvent(20, "Penguin Awareness Day");
            insertEvent(21, "World Religion Day");
            insertEvent(23, "Netaji Subhash Chandra Bose Birthday");
            insertEvent(24, "National Girl Child Day");
            insertEvent(25, "national voters day");

            if (date.year >= 1950)
            {
                insertEvent(26, "Republic Day of India");
            }

            if (date.year >= 1945)
            {
                insertEvent(27, "International Holocaust Day");
            }

            insertEvent(28, "Data protection Day");

            if (date.year >= 1948)
            {
                insertEvent(30, "martyrs day");
            }

            insertEvent(31, "International Zebra Day");

            if (date.year == 2024)
            {
                insertEvent(13, "Lohri");
                insertEvent(14, "Bhogi");
                insertEvent(15, "Makar Snakranthi/Pongal");
                insertEvent(16, "Kanuma");
            }
        }

        // February month
        if (date.month == 2)
        {
            insertEvent(1, "indian coast guard day");
            insertEvent(2, "world wetlands day");
            // insertEvent(3, "");
            insertEvent(4, "world cancer day &independence of sri lanka");
            // insertEvent(5, "");
            insertEvent(6, "international day of zero tolerence to female mutilation");
            // insertEvent(7, "");
            insertEvent(8, "international safer internet day");
            // insertEvent(9, "");
            // insertEvent(10, "");
            insertEvent(11, "world day of sick");
            insertEvent(12, "darwin's day");
            insertEvent(13, "sarojini naidu's birth anniversary");
            insertEvent(14, "saint valentine's day");
            insertEvent(15, "international childhood cancer day");
            // insertEvent(16, "");
            // insertEvent(17, "");
            insertEvent(18, "taj mohotsav");
            // insertEvent(19, "");
            insertEvent(20, "World Day of Social Justice");

            if (date.year >= 1987)
            {
                insertEvent(20, "Arunachal Pradesh Foundation Day");
            }

            insertEvent(21, "International Mother Language Day");
            insertEvent(22, "World Scout Day");
            // insertEvent(23, "");
            insertEvent(24, "Central Excise Duty");
            // insertEvent(25, "");
            // insertEvent(26, "");
            insertEvent(27, "World NGO Day");
            insertEvent(28, "1)National Science Day \n 2)Rare Disease Day");

            if (date.year % 4 == 0)
            {
                insertEvent(29, "Leap year day");
            }

            if (date.year == 2024)
            {
                insertEvent(14, "Vasant Panchami");
                insertEvent(5, "Kala Ghoda Festival");
            }
        }

        // March month
        if (date.month == 3)
        {
            insertEvent(1, "1)Zero Discrimination Day \n 2) World Civil Defence Day \n 3) Self Injury Awareness Day (SIAD) \n 4) World Civil Defence Day");
            insertEvent(2, "Employee Appreciation Day");
            insertEvent(3, "World Hearing Day");
            insertEvent(4, "National Safety Day");
            // insertEvent(5, "");
            // insertEvent(6, "");
            // insertEvent(7, "");
            insertEvent(8, "1)International Women's Day \n 2)Ramakrishna Jayanti");
            // insertEvent(9, "");
            insertEvent(10, "CISF Raising Day");
            // insertEvent(11, "");
            insertEvent(12, "Mauritius Day");
            // insertEvent(13, "");
            insertEvent(14, "Pi Day");
            insertEvent(15, "1)	World Sleep Day \n 2)	World Consumer Rights Day");
            insertEvent(16, "World Consumer Rights Day");
            // insertEvent(17, "");
            insertEvent(18, "Ordnance Factory Day");
            // insertEvent(19, "");
            insertEvent(20, "1)international Day of Happiness \n 2)World Sparrow Day");
            insertEvent(21, "1)World Forestry Day \n 2)World Down Syndrome \n 3)World Poetry Day");
            insertEvent(22, "World Water Day");
            insertEvent(23, "World Meteorological Day");
            insertEvent(24, "World Tuberculosis (TB) Day");
            // insertEvent(25, "");
            // insertEvent(26, "");
            insertEvent(27, "World Theater Day");
            // insertEvent(28, "");
            // insertEvent(29, "");
            // insertEvent(30, "");
            // insertEvent(31, "");

            if (date.year == 2024)
            {
                insertEvent(9, "No Smoking Day");
                insertEvent(20, "Hindi New Year");
                insertEvent(24, "Holika Dahan");
                insertEvent(25, "Holi");
                insertEvent(29, "Good Friday");
            }
        }

        // April month
        if (date.month == 4)
        {

            if (date.year >= 1936)
            {
                insertEvent(1, "Odisha Foundation Day");
            }

            insertEvent(1, "April Fools Day");
            insertEvent(2, "World Autism Awareness Day");
            insertEvent(3, "World Cloud Security Day");
            insertEvent(4, "International Day of mine Awareness");
            insertEvent(5, "National Maritime Day");
            insertEvent(7, "World Health day");
            // insertEvent(9,"Telugu New Year");
            insertEvent(10, "World homopaethy Day");
            insertEvent(11, "National Pet Day");
            insertEvent(12, "International Day of Human Space Flight");
            insertEvent(13, "Vaisakhi");
            // insertEvent(14,"Tamil New Year");
            // insertEvent(15,"Bihu");
            // insertEvent(17,"Ram Navami");
            insertEvent(18, "World Heritage Day");
            insertEvent(21, "National Civil Service Day");
            insertEvent(22, "World Earth Day");
            insertEvent(23, "World Book and Copyright Day");
            insertEvent(24, "National Panchayati Raj Day");
            insertEvent(25, "World Malaria day");
            insertEvent(26, "World Intellectual Property Day");
            insertEvent(28, "World Day for Safety and Health at work");
            insertEvent(30, "World Veterinary Day");

            if (date.year == 2024)
            {
                insertEvent(9, "Ugadi/Gudi Padwa(Telugu New Year)");
                insertEvent(14, "Tamil New Year");
                insertEvent(15, "Bihu(Bengali New Year)");
                insertEvent(17, "Ram Navami");
                insertEvent(23, "Hanuman Jayanthi");
            }
        }

        // May month
        if (date.month == 5)
        {
            insertEvent(1, "1)International Labour Day");

            if (date.year >= 1960)
            {
                insertEvent(1, "Maharashtra Day");
                insertEvent(1, "Gujarat Day");
            }

            insertEvent(3, "1)Press Freedom Day");
            insertEvent(4, "1)Coal Miners Day \n 2)International Firefighter's Day");
            insertEvent(7, "World Athletics day");
            insertEvent(8, "1)World Red Cross Day \n 2)World Thalassemia Day");
            insertEvent(9, "Rabindranath Tagore Day");
            insertEvent(11, "National Technological Day");
            insertEvent(12, "International Nurse Day");
            insertEvent(15, "International Day of Families");
            insertEvent(17, "1)World Telecommunication Day \n 2)World Hypertension Day");
            insertEvent(18, "1)World AIDS Day \n 2)International Museum Day");
            insertEvent(20, "National Endangered Species Day");
            insertEvent(21, "1)National Anti-Terrorism Day \n 2)Armed Forces Day");
            insertEvent(22, "International Day for Biological Diversity");
            insertEvent(31, "1)National Memorial Day \n 2)Anti-Tobacco Day");

            if (date.year == 2024)
            {
                insertEvent(1, "World Laughter Day");
                insertEvent(3, "World Asthma Day");
                insertEvent(8, "Mothers Day");
            }
        }

        if (date.month == 6)
        {
            insertEvent(1, "1)World Milk Day \n 2)Global Day of Parents");

            if (date.year >= 2014)
            {
                insertEvent(2, "Telangana Formation Day");
            }

            insertEvent(3, "World Bicycle Day");
            insertEvent(4, "International Day of Innocent Children Victims of Agression");
            insertEvent(5, "World Environment Day");
            insertEvent(7, "World Food Safety Day");
            insertEvent(8, "1)World Brain Tumor Day \n 2)World Oceans Day");
            insertEvent(12, "World Day against Child Labour");
            insertEvent(14, "World Blood Donor day");
            insertEvent(15, "World Elder Abuse Awareness Day");
            insertEvent(17, "World Day to Control Desertification and Drought");
            insertEvent(18, "Autistic Pride Day");
            insertEvent(20, "1)World Refugee Day \n 2)World Father's Day");
            insertEvent(21, "1)World Music Day \n 2)World Hydrography Day \n 3)International Yoga Day");
            insertEvent(23, "1)International Olympic Day 2)United Nations Public Service Day \n 3)International Widow's Day");
            insertEvent(26, "International Day Against Drug Abuse and Illicit Trafficking ");
            insertEvent(29, "1)National Statistics Day \n 2)International Day of Tropics");
            insertEvent(30, "World Asteroid Day");
        }

        // July month
        if (date.month == 7)
        {
            insertEvent(1, "1)National Doctors Day \n 2)National Postal Worker Day \n 3)Canada Day \n 4)Chartered Accountants Day (India) \n 5)National U.S. Postage Stamp Day \n 6)National Gingersnap Day");
            insertEvent(2, "world UFO day");
            insertEvent(3, "national fried clam day");
            insertEvent(4, "independance day USA");
            insertEvent(5, "Algeria independence Day");
            insertEvent(6, "world zoonoses Day");
            insertEvent(7, "world chocolate day");
            insertEvent(8, "National SCUD day");
            insertEvent(9, "National sugar cookie Day");
            insertEvent(10, "Nikola Tesla Day");
            insertEvent(11, "World population Day");
            insertEvent(12, "National simplicity Day");
            insertEvent(13, "Kashmnir Martyr's Day");
            insertEvent(14, "Bastille Day or French Day");
            insertEvent(15, "social Media Giving Day");
            // insertEvent(16, "");
            insertEvent(17, "World Emoji Day");
            insertEvent(18, "international Nelson Mandela Day");
            // insertEvent(19, "");
            insertEvent(20, "international chess Day");
            // insertEvent(21, "Guru purnima");
            insertEvent(22, "Pi Approximation Day");
            insertEvent(23, "National Mango Day");
            insertEvent(24, "National Thermal Engineer Day");
            // insertEvent(25, "National Refreshment Day");

            if (date.year >= 1999)
            {
                insertEvent(26, "Kargil Vijay Diwas");
            }

            // insertEvent(27, "");
            insertEvent(28, "World Nature conservation Day");
            insertEvent(29, "International Tiger Day");
            insertEvent(30, "International Friendship Day");
            // insertEvent(31, "");

            if (date.year == 2024)
            {
                insertEvent(7, "Jagannath Puri Rath Yatra");
                insertEvent(21, "Guru Purnima");
                insertEvent(25, "National Refreshment Day");
            }
        }

        // August month
        if (date.month == 8)
        {
            insertEvent(1, "Yorkshire Day");
            // insertEvent(2, "");
            insertEvent(3, "National Watermelon Day");
            insertEvent(4, "National sisters day");
            insertEvent(5, "National oyster Day");
            insertEvent(6, "Hiroshima Day");
            insertEvent(7, "National Handloom Day");
            insertEvent(8, "Quit india Movement Day");
            insertEvent(9, "Nagasaki Day");
            insertEvent(10, "National Lazy Day");
            insertEvent(11, "ingersoll Day");
            insertEvent(12, "National Middle child Day");
            insertEvent(13, "World Elephant Day");
            insertEvent(14, "Youm-e-Azadi(pakistan independence day)");

            if (date.year >= 1947)
            {
                insertEvent(15, "Independence Day in india");
            }

            insertEvent(16, "parsi new year");
            insertEvent(17, "Indonesian independence Day");
            // insertEvent(18, "");
            insertEvent(19, "World photography Day");
            insertEvent(20, "sadbhavna diwas");
            insertEvent(21, "National senior citizens Day");
            insertEvent(22, "World plant Milk Day");
            insertEvent(23, "internaut Day");
            insertEvent(24, "pluto demoted Day");
            insertEvent(25, "notting Hill carnival");
            insertEvent(26, "Women's Equality Day");
            insertEvent(27, "National Tug of War Day");
            insertEvent(28, "National red wine Day");
            insertEvent(29, "national sports Day");
            // insertEvent(30, "");
            insertEvent(31, "Hari Merdeka(Malaysia National Day)");

            if (date.year == 2024)
            {
                insertEvent(6, "Friendship Day");
                insertEvent(9, "Nag Panchami");
                insertEvent(19, "Raksha Bandhan");
                insertEvent(26, "Krishna Janmashtami");
            }
        }

        // September month
        if (date.month == 9)
        {
            insertEvent(1, "National Nutrition Week");
            insertEvent(2, "World Coconut Day");
            insertEvent(3, "Skyscraper Day");
            insertEvent(5, "1) International Day of charity \n 2) Teachers' Day");
            insertEvent(7, "Brazillian Independence Day");
            insertEvent(8, "1) International Literacy Day \n 2) World Physical Therapy Day");
            insertEvent(10, "World Suicide Prevention Day");
            insertEvent(11, "National Forest Martyrs Day");
            insertEvent(14, "1) World First Aid Day \n 2) Hindi Diwas");
            insertEvent(15, "Engineer's Day(India)");
            insertEvent(16, "1) Malaysia Day \n 2)Vishwakarma Puja \n 3) World Ozone Day");
            insertEvent(17, "1) World Patient Safety Day \n 2) Onam");
            insertEvent(18, "World Bamboo Day");
            insertEvent(19, "International Talk Like a Pirate Day");
            insertEvent(21, "1) International Day of Peace(UN) \n 2) World Alzheimer's Day");
            insertEvent(22, "1)Rose Day(Welfare of Cancer patients) \n 2) World Rhino Day");
            insertEvent(23, "International Day of Sign Language");
            insertEvent(24, "1) World Rivers Day \n 2) World Maritime Day");
            insertEvent(25, "Antyodaya Diwas");
            insertEvent(26, "1) World Contraception Day \n 2) World Enivornmental Health Day");
            insertEvent(27, "World Tourism Day");
            insertEvent(28, "World Rabies Day");
            insertEvent(29, "World Heart Day");

            if (date.year == 2024)
            {
                insertEvent(7, "Ganesh Chaturthi");
                insertEvent(16, "Vishwakarma puja");
                insertEvent(17, "Onam");
            }
        }

        // October month
        if (date.month == 10)
        {
            insertEvent(1, "1)International Day of the Older Persons \n 2)International Coffee Day \n 3)World Vegetarian Day");
            insertEvent(2, "1)Gandhi Jayanthi \n 2)International day of non violence");
            insertEvent(3, "German Unity Day");
            insertEvent(4, "World Animal Welfare Day");
            insertEvent(5, "World Teachers' Day");
            insertEvent(6, "German-American Day");
            insertEvent(8, "Indian Air Force Day");
            insertEvent(9, "World Postal Day");
            insertEvent(10, "World Mental Health Day");
            insertEvent(11, "International Day of the Girl Child");
            insertEvent(13, "International Day for Disaster Risk Reduction");
            insertEvent(14, "World Standards Day");
            insertEvent(15, "1)Pregnancy and Infant Loss Remembrance Day \n 2)Global Handwashing Day \n 3)World White Cane Day \n 4)World Students Day");
            insertEvent(16, "1)World Food Day \n 2)World Spine Day \n 3)Boss Day \n 4)World Anaesthesia Day");
            insertEvent(17, "International Day for the Eradication of Poverty");
            insertEvent(20, "World Statistics Day");
            insertEvent(23, "Mole Day");
            insertEvent(24, "1)United Nations Day \n 2)World Development Information Day");
            insertEvent(29, "Dhanteras");
            insertEvent(30, "World Thrift Day");
            insertEvent(31, "Rashtriya Ekta Diwas or National Unity Day \n 2)Halloween Day");

            if (date.year == 2024)
            {
                insertEvent(12, "Dussehra");
            }
        }

        // November month
        if (date.month == 11)
        {
            insertEvent(1, "1)World Vegan Day \n 2)Diwali \n 3)All Saint's Day \n 4)Karnataka Formation Day");
            insertEvent(2, "All Soul's Day");
            insertEvent(3, "Bhai Dooj");
            insertEvent(5, "World Tsunami Awarenes  Day");
            insertEvent(6, "International Day for Preventing the Exploitation of the Environment in War and Armed Conflict");
            insertEvent(7, "1)Infant Protection Day \n 2)National Cancer Awareness Day");
            insertEvent(9, "Legal Services Day");
            insertEvent(10, "World Science Day for Peace and Development");
            insertEvent(11, "1)Armistice Day \n 2)National Education Day \n 3)World Usability Day ");
            insertEvent(12, "World Pneumonia Day");
            insertEvent(13, "World Kindness Day");
            insertEvent(14, "1)World Diabetes Day \n 2)Children's Day");
            insertEvent(15, "Guru Nanak Jayanti");
            insertEvent(16, "International Day for Tolerance");
            insertEvent(17, "National Epilepsy Day");
            insertEvent(19, "International Men's Day");
            insertEvent(20, "Africa Industrialisation Day");
            insertEvent(21, "World Television Day");
            insertEvent(25, "Internation Day for the Elimination of Violence against Women");
            insertEvent(26, "Constitution day of India");
            insertEvent(29, "International Day of Solidarity with Palestinian People");
            insertEvent(30, "Saint Andrew's Day");
        }
        // December month
        if (date.month == 12)
        {
            insertEvent(1, "World AIDS Day");
            insertEvent(2, "1)National Pollution Control Day \n 2)International Day for the Abolition of Slavery ");
            insertEvent(3, "World Day of the Handicapped");
            insertEvent(4, "Indian Navy Day");
            insertEvent(5, "1) International Volunteer Day \n 2) World Soil Day");
            insertEvent(7, "1)Armed Force Flag day \n 2) International Civil Aviation Day");
            insertEvent(9, "International Anti Corruption Day");
            insertEvent(10, "Human Right Day");
            insertEvent(11, "International Mountain Day");
            insertEvent(14, "National Energy Conservation Day");
            insertEvent(16, "Vijay Diwas");
            insertEvent(18, "Minorities Right Day in India");
            insertEvent(19, "Goa Liberation Day");
            insertEvent(20, "International Human Solidarity Day");
            insertEvent(22, "National Mathematics Day");
            insertEvent(23, "Kisan Diwas");
            insertEvent(24, "National Mathematics Day");
            insertEvent(25, "1)Chritmas Day \n 2)Atal Bihari Vajpayee Birthday");
            insertEvent(31, "New Year's Eve");
        }

        // Print events on the given date
        if (date.day >= 1 && date.day <= MAX_EVENTS && events[date.day] != NULL)
        {
            printEvents(events[date.day], date);
        }
        else
        {
            printf("No events found for %02d/%02d/%d\n", date.day, date.month, date.year);
        }

        // Free allocated memory for linked lists
        for (int i = 0; i < MAX_EVENTS; ++i)
        {
            struct EventNode *temp = events[i];
            while (temp != NULL)
            {
                struct EventNode *prev = temp;
                temp = temp->next;
                free(prev);
            }
        }
    }

    if (x == 2) {
        loadTasksFromFile();

    int choice, index;
    char description[MAX_LENGTH];

    do {
        blue();
        printf("\nMenu:\n");
        reset();
        yellow();
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        reset();
        cyan();
        printf("Enter your choice: ");
        reset();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                green();
                printf("Enter task description: ");
                reset();
                getchar(); // clear input buffer
                fgets(description, sizeof(description), stdin);
                description[strlen(description) - 1] = '\0'; // remove newline character
                add_Task(description);
                break;
            case 2:
                display_Tasks();
                break;
            case 3:
                green();
                printf("Enter task index to mark as completed: ");
                reset();
                scanf("%d", &index);
                mark_Completed(index);
                break;
            case 4:
                printf("Enter task index to delete: ");
                scanf("%d", &index);
                delete_Task(index);
                break;
            case 5:
                green();
                printf("Exiting...\n");
                reset();
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;

    }
}