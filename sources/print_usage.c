#include "print_usage.h"

#include <stdio.h>

#include "form.h"

void print_usage(unsigned char is_error) {
  FILE* output_stream = (
    is_error == 0
    ? stdout
    : stderr
  );

  fprintf(
    output_stream,
    "USAGE: vave [form] [Hz] [?Amplitude]\n"
    "  forms:\n"
  );
  
  for (
    unsigned short int i = 0;
    i < FORM_COUNT;
    ++i
  ) {
    fprintf(
      output_stream,
      "    - %s\n",
      form_names[i]
    );
  }
}

