#include <stdio.h>
#include "menu.h"

int main() {
    int choice;


    do {
        systemMenu();
        scanf("%d", &choice);

    } while (choice != 5);

    return 0;
}
