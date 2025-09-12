#include <stdio.h>

__attribute__((export_name("foo_hello")))
int foo_hello(void) {
	printf("hello from wasm\n");
	return 0;
}

int main(void) {
	printf("hello from the main function\n");
	return 0;
}
