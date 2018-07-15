#include <stdio.h>

// This demo shows how pointer arithmetic behaves for different pointer types.
// Note that incrementing an array pointer moves the pointer to the next array
// element, independent of the size of the array content. Incrementing a void*
// pointer on the other hand is not permitted by the standard. Some compilers,
// such as GCC, ignore this and perform pointer arithmetics as if void* would
// have size 1.
int main() {
	char chars[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	printf("     sizeof(char) = %ld\n", sizeof(char));
	printf("            chars = %p\n", chars);
	printf("        &chars[0] = %p\n", &chars[0]);
	printf("        &chars[1] = %p\n", &chars[1]);
	printf("          chars+1 = %p\n", chars+1);
	printf("((void*)chars)+1  = %p\n", ((void*)chars)+1);

	printf("\n");

	int ints[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	printf("      sizeof(int) = %ld\n", sizeof(int));
	printf("             ints = %p\n", ints);
	printf("         &ints[0] = %p\n", &ints[0]);
	printf("         &ints[1] = %p\n", &ints[1]);
	printf("           ints+1 = %p\n", ints+1);
	printf("     *int(ints)+1 = %p\n", ((int*)ints)+1);
	printf("    *void(ints)+1 = %p\n", ((void*)ints)+1);
}
