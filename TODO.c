// global buffer
// RUN: clang -O -g -fsanitize=address %t && ./a.out
int global_array[100] = {-1};
int main(int argc, char **argv) {
  return global_array[argc + 100];  // BOOM
}

// stack buffer
// RUN: clang -O -g -fsanitize=address %t && ./a.out
int main(int argc, char **argv) {
  int stack_array[100];
  stack_array[1] = 0;
  return stack_array[argc + 100];  // BOOM
}

// ... https://en.wikipedia.org/wiki/AddressSanitizer
// XXX radi na odabranim platformama i ne podrzava staticko linkanje
