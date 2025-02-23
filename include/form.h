#ifndef __FORM_H
#define __FORM_H

#define FORM_COUNT 6

enum form {
  noise,
  sawtooth_down,
  sawtooth_up,
  sine,
  square,
  triangle
};

extern const char* form_names[FORM_COUNT];

#endif

