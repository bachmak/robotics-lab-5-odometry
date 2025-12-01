#include "app/lab_5.h"
#include "app/lab_6.h"

extern "C" void setup();
extern "C" void loop();

enum class Target
{
  LAB_5,
  LAB_6,
};

Target get_target()
{
#if defined(TARGET_LAB_5)
  return Target::LAB_5;
#elif defined(TARGET_LAB_6)
  return Target::LAB_6;
#else
#error "No target defined. Please define TARGET_LAB_5 or TARGET_LAB_6."
#endif
}

void setup() {}

void loop()
{
  switch (get_target())
  {
  case Target::LAB_5:
    lab_5::run();
    break;
  case Target::LAB_6:
    lab_6::run();
    break;
  }
}