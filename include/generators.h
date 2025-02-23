#ifndef __GENERATORS_H
#define __GENERATORS_H

#include "form.h"
#include "phase.h"

typedef float (*generate_function)(struct phase*);

struct generator {
  enum form form;
  struct phase* phase;
  generate_function generate;
};

void generator_initialize(
  struct generator*,
  enum form,
  struct phase*
);

void generator_form_set(
  struct generator*,
  enum form
);

float generator_generate(struct generator*);

float generate(enum form, struct phase*);
float generate_empty(struct phase*);
float generate_noise(struct phase*);
float generate_sawtooth_down(struct phase*);
float generate_sawtooth_up(struct phase*);
float generate_sine(struct phase*);
float generate_square(struct phase*);
float generate_triangle(struct phase*);

#endif

