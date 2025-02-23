#include "vave.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#include "cexil.h"

#include "form.h"
#include "generators.h"
#include "phase.h"
#include "print_usage.h"

int main(int argc, char** argv) {
  if (argc < 3 || argc > 4) {
    print_usage(1);
    return 1;
  }

  enum form form;
  float frequency;
  float sample_rate = 44100.0f;
  unsigned int amplitude = 100;

  if (strcmp(argv[1], "noise") == 0) {
    form = noise;
  } else if (
    strcmp(argv[1], "sawtooth") == 0 ||
    strcmp(argv[1], "sawtooth_down") == 0
  ) {
    form = sawtooth_down;
  } else if (
    strcmp(argv[1], "sawtooth_up") == 0
  ) {
    form = sawtooth_up;
  } else if (strcmp(argv[1], "sine") == 0) {
    form = sine;
  } else if (strcmp(argv[1], "square") == 0) {
    form = square;
  } else if (strcmp(argv[1], "triangle") == 0) {
    form = triangle;
  } else {
    fprintf(
      stderr,
      "Unknown form: %s\n",
      argv[1]
    );
    print_usage(1);
    return 1;
  }

  unsigned int current_character = 0;
  unsigned int has_decimal = 0;

  while (argv[2][current_character] != '\0') {
    char number = argv[2][current_character];
    
    if (
      ((number < '0' || number > '9') && 
       number != '.'
      ) || 
      (number == '.' && has_decimal > 0)
    ) {
      fprintf(
        stderr,
        "Not a valid frequency: %s\n",
        argv[2]
      );
      print_usage(1);
      return 1;
    }

    if (number == '.') {
      has_decimal = 10;
    } else {
      number = number - '0';

      if (has_decimal > 0) {
        frequency = frequency + (
          (float)number / has_decimal
        );

        has_decimal = has_decimal * 10;
      } else {
        frequency = (
          (frequency * 10) +
          number
        );
      }
    }

    current_character = current_character + 1;
  }
  
  current_character = 0;

  if (argc == 4) {
    amplitude = 0;

    while (argv[3][current_character] != '\0') {
      char number = argv[3][current_character];
    
      if (number < '0' || number > '9') {
        fprintf(
          stderr,
          "Not a valid amplitude: %s\n",
          argv[3]
        );
        print_usage(1);
        return 1;
      }

      number = number - '0';

      amplitude = (
        (amplitude * 10) +
        number
      );

      current_character = current_character + 1;
    }
  }

  if (amplitude > 100) {
    fprintf(
      stderr,
      "Not a valid amplitude: %s\n",
      argv[3]
    );
    print_usage(1);
    return 1;
  }

  struct phase phase;
  phase_initialize(
    &phase,
    sample_rate,
    frequency
  );

  struct generator generator;
  generator_initialize(
    &generator,
    form,
    &phase
  );

  struct cexil_renderer renderer;
  struct cexil_size size_screen;
  unsigned char status_size_set = (
    cexil_size_set_to_terminal(&size_screen)
  );

  if (status_size_set != 0) {
    fprintf(
      stderr,
      "Unable to determine terminal size\n"
    );
    return status_size_set;
  }

  size_screen.height = size_screen.height - 4;

  cexil_renderer_initialize(
    &renderer,
    &size_screen
  );

  float value = 0.0f;
  float amplitude_height = (float)(
    ((renderer.size.height - 1.0f) / 2.0f) *
    ((float)amplitude / 100.0f)
  );

  struct timespec frame_time = { 0, 25000000 };
  unsigned char running = 1;

  do {
    cexil_renderer_render_clear(&renderer);

    for (
      unsigned int x = 0;
      x < renderer.size.width;
      ++x
    ) {
      value = generator_generate(&generator);
      phase_advance(&phase);
      int y = (int)(
        ((float)(renderer.size.height - 1) / 2.0f)
        + (value * amplitude_height)
      );
      renderer.pixels[y][x] = 1;
    }

    cexil_renderer_render(&renderer); 

    printf(
      "frequency_%g;phase_%g;value_%g\n",
      frequency,
      phase.value,
      value
    );

    nanosleep(&frame_time, (void*)0);
  } while (running == 1);

  cexil_renderer_destroy(&renderer);

  return 0;
}

