#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//add pre-defined first lookup table
const char specialtyName[4][30] = {"General Practice (OPD)", "Paediatrics", "Cardiology", "Neurology"};
const float baseFee[4] = {1500.00, 2500.00, 4500.00, 5000.00};
const int consultationTime[4] = {15, 20, 30, 30};
const int daliyCap[4] = {30, 20, 12, 10};

//add pre-defined second lookup table
const char wardName[4][30] = {"Genaral Ward", "Paediatric Ward", "Surgical Ward", "ICU(Intensive Care Unit)"};
const float daliyBedRate[4] = {3000.00, 6000.00, 12000.00, 25000.00};
const int bedCapacity[4] = {20, 10, 10, 5};

int choice;
int patientCount = 0;
char patientName[100][50];
int patientAge[100];
int emergencyLevel[100];
int specialtyId[100];
int isAdmitted[100];
int wardId[100];
int bedNumber[100];
int daysAdmitted[100];
float waitTime[100];
float surcharge[100];
float wardCost[100];
float grossTotal[100];
float discount[100];
float finalAmount[100];

int bedOccupancy[4][20] = {0};

int queueCount[4] = {0};

void registerPatient();
int findFreeBed(int ward);
void viewBedStatus(void);
void displayPriorityQueue(void);
void performanceReport(void);
void saveBedStatus(void);

int main()
{

    do {
    printf("\n=============================================================\n");
    printf("     SMART HOSPITAL PATIENT & RESOURCE ALLOCATION SYSTEM\n");
    printf("=============================================================\n");
    printf("1. Register New Patient\n");
    printf("2. View Bed Status\n");
    printf("3. Display Patients by Priority Oder\n");
    printf("4. Generate Performance Report\n");
    printf("5. Exit\n");
    printf("-------------------------------------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:registerPatient();
    break;
    case 2:viewBedStatus();
    break;
    case 3:displayPriorityQueue();
    break;
    case 4:performanceReport();
    break;
    case 5:printf("Good Bye See you Again\n");
    break;
    default:
        printf("Invalid choice. Please enter 1-5.\n");
        }




    } while (choice != 5);
    return 0;
}


void registerPatient()
{
    int i= patientCount;

     if (patientCount >=100)
     {
          printf("Patient records are full. Cannot register more patients.\n");
     }

        printf("--- Patient Registration ---\n");

        printf("Patient Name: \n");
        while (getchar() != '\n');
        fgets(patientName[i], 50, stdin);
        patientName[i][strcspn(patientName[i], "\n")] = 0;

        do
        {
            printf("Patient Age: ");
            scanf("%d", &patientAge[i]);
        }while (patientAge[i]<0 || patientAge[i]>120);

        do
        {
            printf("Emegency Level (1=Normal, 2=Urgent, 3=Critical); ");
            scanf("%d", &emergencyLevel[i]);
        }while (emergencyLevel[i]<1 || emergencyLevel[i]>3);

        do
        {
            printf("Specialty ID (1=OPD, 2=Paediatrics, 3=Cardiology, 4=Neurology): ");
            scanf("%d", &specialtyId[i]);
        }while (specialtyId[i]<1 || specialtyId[i]>4);

        do
        {
            printf("Is Admitted to Ward? (1=Yes, 0=No): ");
            scanf("%d", &isAdmitted[i]);
        }while (isAdmitted[i] !=0 && isAdmitted[i] !=1);

        if(isAdmitted[i] == 1)
        {
            do
            {
                printf("Ward ID (1=General, 2=Paediatric, 3=Surgical, 4=ICU); ");
                scanf("%d", &wardId[i]);
            }while (wardId[i]<1 || wardId[i]>4);

            int bed = findFreeBed(wardId[i]-1);
            if (bed == -1)
            {
                printf("Sorry, %s is at full capacity.\n", wardName[wardId[i]-1]);
                isAdmitted[i]=0;
                wardId[i]=0;
                bedNumber[i]=-1;
                daysAdmitted[i]=0;

            }else
            {
                bedOccupancy[wardId[i]-1][bed]=1;
                bedNumber[i]=bed;
                do
                {
                    printf("Days Admitted: ");
                    scanf("%d", &daysAdmitted[i]);

                }while (daysAdmitted[i]<1);
            }

        }else
        {
            wardId[i]=0;
            bedNumber[i]= -1;
            daysAdmitted[i]=0;
        }

        int a = specialtyId[i] - 1;

        waitTime[i] = queueCount[a] * consultationTime[a];
        queueCount[a]++;

        if (emergencyLevel[i] == 1)
        {
            surcharge[i] = 0.00;
        }else if (emergencyLevel[i] == 2)
        {
            surcharge[i] = baseFee[a] * 0.20;
        }else
        {
            surcharge[i] = baseFee[a] * 0.50;
        }
        if (isAdmitted[i] == 1)
        {
            int c = wardId[i] - 1;
            wardCost[i] = daysAdmitted[i] * daliyBedRate[c];
        }else
        {
            wardCost[i] = 0.00;
        }


        grossTotal[i] = baseFee[a] + surcharge[i] + wardCost[i];

        if (patientAge[i]<5 || patientAge[i]>65)
        {
            discount[i] = grossTotal[i] * 0.15;
        }else
        {
            discount[i] = 0;
        }

        finalAmount[i] = grossTotal[i] - discount[i];

        saveBedStatus();

        patientCount++;

        char emergencyText[3][10] = {"Normal", "Urgent", "Critical"};
        int emergencyPct = (emergencyLevel[i] == 1) ? 0 : (emergencyLevel[i] == 2 ? 20 : 50);

        printf("Patient Registration successfull\n\n\n");

        printf("==============================================================\n");
        printf("             SMART HOSPITAL ADMISSION & BILL\n");
        printf("--------------------------------------------------------------\n");
        printf("Patient ID                  :PAT-%d\n", 1001+i);
        printf("Patient Name                :%s\n", patientName[i]);
        printf("Age                         :%d Years %s\n", patientAge[i], (patientAge[i] < 5 || patientAge[i] > 65) ? "(15% Subsidy Eligible)" : "");
        printf("Specialty                   :%s\n", specialtyName[a]);
        if (isAdmitted[i])
        {
            printf("Assigned Ward               :%s (Bed #%02d)\n", wardName[wardId[i]-1], bedNumber[i]+1);
        }else
        {
            printf("Assigned ward               :Not Admitted\n");
        }
        printf("Urgency Level               :Level %d (%s)\n", emergencyLevel[i], emergencyText[emergencyLevel[i]-1]);
        printf("--------------------------------------------------------------\n");
        printf("Base Consultation Fee       :LKR %.2f\n", baseFee[a]);
        printf("Emergency Surcharge         :LKR %.2f (%d%%)\n", surcharge[i], emergencyPct);
        if (isAdmitted[i])
        {
            printf("Ward Stay Cost (%d days)     :LKR %.2f\n", daysAdmitted[i], wardCost[i]);
        }else
        {
            printf("Ward Stay Cost               :LKR 0.00\n");
        }
        printf("--------------------------------------------------------------\n");
        printf("Gross Total Bill            :LKR %.2f\n", grossTotal[i]);
        printf("Age Subsidy Discount        :LKR -%.2f (%s)\n",discount[i], discount[i] > 0 ? "15%" : "0%");
        printf("--------------------------------------------------------------\n");
        printf("Final Payable Amount        :LKR %.2f\n", finalAmount[i]);
        if (waitTime[i] == 0)
        {
            printf("Estimated Waiting Time      :0.00 mins (Immediate Attention)\n");
        }else
        {
            printf("Estimated Waiting Time      :%.2f mins\n", waitTime[i]);
        }
        printf("==============================================================\n");



     }


int findFreeBed(int ward)
{
    for (int b=0; b < bedCapacity[ward]; b++)
    {
        if (bedOccupancy[ward][b]==0)
        {
            return b;
        }

    }
    return -1;

}

void viewBedStatus(void)
{
    printf("---Bed Occupancy Status---\n");
    for (int w=0; w<4; w++)
    {
        printf("\n%s (Capacity: %d)\n", wardName[w], bedCapacity[w]);
        for (int b=0; b<bedCapacity[w]; b++)
        {
            printf("%d ", bedOccupancy[w][b]);
        }
    }
    printf("\n1 = Bed is already occupied, 0 = Bed is free\n");
}


void displayPriorityQueue(void)
{
    if (patientCount==0)
    {
        printf("\nNo Patient Registerd In The System Yet.\n");
        return;
    }
    int sortedOrder[100];
    for (int i = 0; i<patientCount;i++)
    {
        sortedOrder[i] = i;
    }

    for (int i = 0; i<patientCount - 1; i++)
    {
        for (int j = 0; j<patientCount - i - 1; j++)
        {
            int currentId = sortedOrder[j];
            int nextId = sortedOrder[j + 1];

            if (emergencyLevel[currentId]<emergencyLevel[nextId])
            {
                int temp = sortedOrder[j];
                sortedOrder[j] = sortedOrder[j + 1];
                sortedOrder[j + 1] = temp;
            }
        }
    }
    printf("\n=========================================================================================\n");
    printf("                          SMART HOSPITAL - PATIENT PRIORITY QUEUE                       \n");
    printf("=========================================================================================\n");
    printf("%-12s %-22s %-6s %-18s %-12s\n", "Patient ID", "Patient Name", "Age", "Emergency Level", "Assigned Bed");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < patientCount; i++)
    {
        int id = sortedOrder[i];
        char emergencyText[20];
        char specialtyText[20];
        char bedText[15];

        if (emergencyLevel[id] == 3)
        {
            strcpy(emergencyText,"Level 3 (Critical)");
        }else if (emergencyLevel[id] == 2)
        {
            strcpy(emergencyText,"Level 2 (Urgent)");
        }else
        {
            strcpy(emergencyText, "Level 1 (Normal)");
        }
        if (isAdmitted[id] == 1 && bedNumber[id] != -1)
        {
            sprintf(bedText, "Ward %d (Bed #%02d)", wardId[id], bedNumber[id]+1);
        }else
        {
            strcpy(bedText, "Not Admitted");
        }

            printf("PAT-%d     %-22s %-6d %-18s %-12s\n", 1001 + id, patientName[id], patientAge[id], emergencyText, bedText);
    }
    printf("=========================================================================================\n");

}

void performanceReport(void)
{
    if (patientCount == 0)
    {
        printf("\nNo Patient Registered Yet.\n");
        return;
    }
    int emergencyCount[4] = {0};
    float totalRevenue = 0;
    float totalDiscount = 0;
    int topPatient =0;

    for (int i = 0; i < patientCount; i++)
    {
        emergencyCount[emergencyLevel[i]]++;
        totalRevenue += finalAmount[i];
        totalDiscount += discount[i];
        if (finalAmount[i]>finalAmount[topPatient]) topPatient = i;
    }
    printf("\n----performance Report----\n");
    printf("Total Patient Registered : %d\n", patientCount);
    printf("Level 1 (Normal)  : %d\n", emergencyCount[1]);
    printf("Level 2 (urgent)  : %d\n", emergencyCount[2]);
    printf("Level 3 (Critical)  : %d\n", emergencyCount[3]);
    printf("Total Revenue Earned      :LKR %.2f\n", totalRevenue);
    printf("Total Discount            :LKR %.2f\n", totalDiscount);

    printf("\nBed Occupancy Percentage Per Ward\n");
    for (int w = 0; w<4; w++)
    {
        int occipied = 0;
        for (int b = 0; b<bedCapacity[w]; b++)
        {
            if(bedOccupancy[w][b]==1)
            {
                occipied++;
            }
        }
        printf(" %-28s: %.1f%%\n", wardName[w], (occipied * 100.00)/ bedCapacity[w]);
    }
    printf("\nHighest-Paying Patient : %s (PAT-%04d) - LKR %.2f\n", patientName[topPatient], 1001+topPatient, finalAmount[topPatient]);
}


void saveBedStatus(void)
{
    FILE *fptr = fopen("beds_status.txt", "w");
    if (fptr == NULL)
    {
        printf("Error cannot open beds_status.txt for writing.\n");
        return;
    }
    for (int w = 0; w < 4; w++)
    {
        for (int b = 0; b < bedCapacity[w]; b++)
        {
            fprintf(fptr, "%d", bedOccupancy[w][b]);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
    printf("Bed status saved successfully\n");
}


