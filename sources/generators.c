#include "generators.h"

#include "constants.h"

void generator_initialize(
  struct generator* generator,
  enum form form,
  struct phase* phase
) {
  generator->phase = phase;

  generator_form_set(generator, form);
}

void generator_form_set(
  struct generator* generator,
  enum form form
) {
  switch (form) {
    case noise:
      generator->generate = generate_noise;
      break;
    case sawtooth_down:
      generator->generate = (
        generate_sawtooth_down
      );
      break;
    case sawtooth_up:
      generator->generate = (
        generate_sawtooth_up
      );
      break;
    case sine:
      generator->generate = generate_sine;
      break;
    case square:
      generator->generate = generate_square;
      break;
    case triangle:
      generator->generate = generate_triangle;
      break;
    default:
      generator->generate = generate_empty;
      break;
  }
}

float generator_generate(
  struct generator* generator
) {
  return (*generator->generate)(generator->phase);
}

float generate(
  enum form form,
  struct phase* phase
) {
  switch (form) {
    case sine:
      return generate_sine(phase);
    case square:
      return generate_square(phase);
    case sawtooth_down:
      return generate_sawtooth_down(phase);
    case sawtooth_up:
      return generate_sawtooth_up(phase);
    case noise:
      return generate_noise(phase);
    case triangle:
      return generate_triangle(phase);
    default:
      return generate_empty(phase);
  }
}

float generate_empty(struct phase* phase) {
  return 0.0f;
}

float generate_noise(struct phase* phase) {
  return 0.0f;
}

float generate_sawtooth_down(
  struct phase* phase
) {
  return (
    2.0f * (
      phase->value * (
        1.0f / pi_two
      )
    )
  ) - 1.0f;
}

float generate_sawtooth_up(struct phase* phase) {
  return 1.0f - (
    2.0f * (
      phase->value * (
        1.0f / pi_two
      )
    )
  );
}

float generate_sine(struct phase* phase) {
  return 0.0f;
}

float generate_square(struct phase* phase) {
  return phase->value <= pi ? 1.0f : -1.0f;
}

float generate_triangle(struct phase* phase) {
  float triangle_value = (
    (2.0f * (phase->value * (1.0f / pi_two)))
    - 1.0f
  );

  if (triangle_value < 0) {
    triangle_value = -triangle_value;
  }

  return 2.0f * (triangle_value - 0.5f);
}

