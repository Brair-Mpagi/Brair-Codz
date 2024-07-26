#include <stdio.h>
#include <math.h>

void solveQuadratic() {
    printf("\n           Quadratic Equation Solver\n\n");
    double a, b, c;
    printf("Enter values for a, b, c:\n");
    printf("a: ");
    scanf("%lf", &a);
    printf("b: ");
    scanf("%lf", &b);
    printf("c: ");
    scanf("%lf", &c);

    double discriminant = b * b - 4 * a * c;

    if (a == 0) {
        printf("'a' can't be zero!\n");
        solveQuadratic();
    } else if (discriminant < 0) {
        printf("Discriminant should be greater than zero!\n");
        printf("Math Error\n");
        solveQuadratic();
//    } else if (discriminant > 0) {
//        double root1 = (-b + sqrt(discriminant)) / (2 * a);
//        double root2 = (-b - sqrt(discriminant)) / (2 * a);
//        printf("Roots %.2f & %.2f are real and distinct\n", root1, root2);
//        solveQuadratic();
    } else if (discriminant == 0) {
        double root = -b / (2 * a);
        printf("Roots are real and equal\n");
        printf("Roots are %.2f & %.2f\n", root, root);
        solveQuadratic();
    } else {
        printf("Roots are imaginary\n");
        double real = -b / (2 * a);
        double imaginary = sqrt(-discriminant) / (2 * a);
        printf("Real part = %.2f & imaginary part = %.2f\n", real, imaginary);
        solveQuadratic();
    }
}

int main() {
    solveQuadratic();
    return 0;
}

