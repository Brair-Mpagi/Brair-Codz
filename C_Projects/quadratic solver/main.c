#include <stdio.h>
#include <math.h>

void solve1() {
    printf("\n\n\t>>>'a' cannot be zero\n");
    printf("\tMath Error!\n\n");
}

void solve2(double a, double b, double d) {
    printf("\nRoots are imaginary\n");
    double realPart = -b / (2 * a);
    double imaginaryPart = sqrt(-d) / (2 * a);
    printf("\nRoots: %f  and %f ", realPart, imaginaryPart);
}

void solve3(double b, double a) {
    double root = -b / (2 * a);
    printf("Roots are real and equal\n");
    printf("\nRoots are %f & %f\n", root, root);
}

void solve4(double a, double b, double d) {
    double root1 = (-b + sqrt(d)) / (2 * a);
    double root2 = (-b - sqrt(d)) / (2 * a);
    printf("\nRoots %f & %f are real and distinct\n", root1, root2);
}

int main() {
    printf("Quadratic solver\n");

    printf("\nInput coefficient a, b, c\n");

    // input prompt for a b c
    double a, b, c;

    printf("a:  ");
    scanf("%lf", &a);

    // a condition
    if (a == 0) {
        solve1();
    } else {
        printf("b:  ");
        scanf("%lf", &b);
        printf("c:  ");
        scanf("%lf", &c);
    }

    // discriminant function
    double d = b * b - 4 * a * c;  // Corrected the discriminant calculation
    printf(" Your discriminant is: %lf\n", d);

    // discriminant conditions
    if (d < 0) {
        solve2(a, b, d);
    } else if (d == 0) {
        solve3(b, a);
    } else if (d > 0) {
        solve4(a, b, d);
    } else {
        printf("Null input!!!\n");
    }

    return 0;
}

