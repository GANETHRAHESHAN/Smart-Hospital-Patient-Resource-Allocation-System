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

int bedOccupancy[4][20] = {0};

void registerPatient();
int findFreeBed(int ward);

int main()
{

    do {
    printf("=============================================================\n");
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
        getchar() != '\n';
        fgets(patientName[i], 50, stdin);

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
        printf("Patient Registration successfull\n\n\n");


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
