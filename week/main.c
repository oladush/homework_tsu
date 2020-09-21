#include <stdio.h>

void print_day_of_week(int num_day){
    printf("Day of week: ");
    switch (num_day){
        case 1 : printf("monday\n"); break;
        case 2 : printf("tuesday\n"); break;
        case 3 : printf("wednesday\n"); break;
        case 4 : printf("thursday\n"); break;
        case 5 : printf("friday\n"); break;
        case 6 : printf("saturday\n"); break;
        case 7 : printf("sunday\n"); break;
    }
}

int main() {
    int num_day;

    printf("Enter a number from 1 to 7\n");

    scanf("%d", &num_day);

    num_day > 0 && num_day < 8 ? print_day_of_week(num_day) : printf("Invalid input format, enter a number from 1 to 7\n");

    return 0;
}
