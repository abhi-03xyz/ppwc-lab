#include <stdio.h>

int main() {
    int prev_reading, curr_reading, total_units;
    float slab1_cost = 0, slab2_cost = 0, slab3_cost = 0;
    float maintenance_charge = 50.0, surcharge = 0, total_cost;

   
    printf("Enter the previous meter reading: ");
    scanf("%d", &prev_reading);
    printf("Enter the current meter reading: ");
    scanf("%d", &curr_reading);

   
    total_units = curr_reading - prev_reading;

   
    if (total_units <= 100) {
        slab1_cost = total_units * 3.0;
    } else if (total_units <= 300) {
        slab1_cost = 100 * 3.0;
        slab2_cost = (total_units - 100) * 5.0;
    } else {
        slab1_cost = 100 * 3.0;
        slab2_cost = 200 * 5.0;
        slab3_cost = (total_units - 300) * 7.0;
    }

   
    total_cost = slab1_cost + slab2_cost + slab3_cost + maintenance_charge;
    if (total_cost > 1000) {
        surcharge = total_cost * 0.10;
    }
    total_cost += surcharge;

   
    printf("\n-----------------------------------------\n");
    printf("Slab\t\tRate\tConsumed\tCost\n");
    printf("-----------------------------------------\n");
    if (slab1_cost > 0) printf("1 (<100)\t@3.00\t%d\t\t%.2f\n", (total_units < 100 ? total_units : 100), slab1_cost);
    if (slab2_cost > 0) printf("2 (101-300)\t@5.00\t%d\t\t%.2f\n", (total_units > 100 && total_units <= 300 ? total_units - 100 : 200), slab2_cost);
    if (slab3_cost > 0) printf("3 (>300)\t@7.00\t%d\t\t%.2f\n", (total_units > 300 ? total_units - 300 : 0), slab3_cost);
    printf("Maintenance\t\t\t\t%.2f\n", maintenance_charge);
    if (surcharge > 0) printf("Surcharge @10%% (>1000)\t\t\t%.2f\n", surcharge);
    printf("-----------------------------------------\n");
    printf("Total Bill\t\t\t\t%.2f\n", total_cost);

    return 0;
}

