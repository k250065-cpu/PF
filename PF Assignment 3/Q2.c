#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus,
                   int planet, int totalPlanets)
{
    if (fuel <= 0) {
        printf("Planet %d: Fuel Exhausted\n", planet);
        return;
    }
    if (planet > totalPlanets) {
        printf("All Planets Visited\n");
        return;
    }

    fuel -= consumption;

    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf("Fuel Exhausted\n");
        return;
    }

    fuel += recharge;

    if (planet % 4 == 0) {
        fuel += solarBonus;
    }

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    calculateFuel(fuel, consumption, recharge, solarBonus,
                  planet + 1, totalPlanets);
}

int main() {
    int fuel = 1000;
    int consumption = 150;
    int recharge = 50;
    int solarBonus = 100;
    int totalPlanets = 8;

    printf("---- Fuel Records ----\n");
    calculateFuel(fuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}