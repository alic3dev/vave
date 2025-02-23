#ifndef __PHASE_H
#define __PHASE_H

struct phase {
  float value;
  float increment;
};

void phase_initialize(
  struct phase*,
  float,
  float
);

void phase_advance(struct phase*);

#endif

