#include <stdio.h>

int main(){
	int b = 8;
	int *a = &b;
//	
////	printing memory addresses 
//	printf("Address b: \t       %p \n",&b);
//	
////	value stored in pointer a
//	printf("Address in pointer a:  %p \n",a);
//	printf("value in a: \t \t %d \n",a);
//
////	modifying b using pointers
//	*a =10;
//	printf("%d",b);
	
// printing pointer values

int a1 = 5;
int*pa1 = &a1;
printf("a1 : %d\n",a1);
printf("&a1: %d \n", &a1);
printf("pa1: %d\n",pa1);
printf("&pa1: %d\n",&pa1);
printf("*pa1 %d\n",*pa1);
















// swap two numbers without pointer
//	printf("\n\n\n swap numbers without pointers \n"); 
//	int z=2,x=3,temp;
//	temp = 0;
//	temp = z;
//	z = x;
//	x = temp;
//	printf("z: %d \n",z);
//	printf("x: %d",x);
//	
	
// swap two numbers with pointer 
//	printf("\n\n\n swap numbers with pointers \n");
//	int w=2,y=3;
//	
//	int *q = &w;
//	*q = y;
//	y = w;
//	printf("w: %d \n",w);
//	printf("y: %d",y);
	
	
	
	
	
	
	return 0;
}
