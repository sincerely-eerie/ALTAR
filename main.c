#include <stdio.h>
#include <stdlib.h>

// specs
#define STACK_SIZE 256
#define HEAP_SIZE 65536
#define PROG_MAX 32768

typedef unsigned char Uint8;
typedef unsigned short int Uint16;

// microcode
enum opcodes {
	NOOP,
	PUSH,
	BRK = 255
};

typedef struct {
	Uint8 data[256];
	Uint8 sp;
} stack;

typedef struct {
	Uint8 prog[65536];
	Uint16 ip;
	stack dst, rst;
} VM;

void push(stack *st, Uint8 val) {
	st->sp++;
	st->data[st->sp] = val;
}

Uint8 pop(stack *st) {
	return st->data[st->sp--];
}

void dispatch(VM *vm) {
	switch(vm->prog[vm->ip]) {
		case 0x00:
			// Do nothing
			break;
		case 0x01:
			vm->ip++;
			push(&vm->dst, vm->prog[vm->ip]);
			break;
		case 0x02:
			// temp for pop test
			printf("Popped: %x", pop(&vm->dst));
			break;
		case 0xff:
			// Crash and burn
			fprintf(stderr, "HOT TAMALE!\n");
			exit(255);
			break;
	}
}

void run_vm (VM *vm) {
	while (vm->ip < PROG_MAX) {
		dispatch(vm);
		vm->ip++;
	}
}

int main(void) {
	VM vm = {.prog={0x01, 0x69, 0x02}};
	run_vm(&vm);
}

