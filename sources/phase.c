#include "phase.h"

#include "constants.h"

void phase_initialize(
  struct phase* phase,
  float sample_rate,
  float frequency
) {
  phase->value = 0;
  phase->increment = (
    (pi_two / sample_rate) * frequency
  );
}

void phase_advance(struct phase* phase) {
  phase->value = phase->value + phase->increment;

  if (phase->value >= pi_two) {
    phase->value = phase->value - pi_two;
  }

  if (phase->value < 0.0f) {
    phase->value = phase->value + pi_two;
  }
}

