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



    } while (choice != 5);
    return 0;
}
