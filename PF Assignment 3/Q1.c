#include <stdio.h>

void calculateRepayment(float loan, float interestRate, int years, int currentYear) {
    if (loan <= 0) {
        printf("Year %d: Remaining Loan = 0\n", currentYear);
        return;
    }

    float repayment = 10000;
    loan = loan - repayment;

    float interest = loan * (interestRate / 100);

    loan = loan + interest;

    printf("Year %d: Remaining Loan = %.2f\n", currentYear, loan);

    calculateRepayment(loan, interestRate, years - 1, currentYear + 1);
}

int main() {
    float loan = 100000.0;
    float interestRate = 5.0;
    int years = 3;
    printf("Loan Repayment Schedule:\n");
    calculateRepayment(loan, interestRate, years, 1);
    return 0;
}