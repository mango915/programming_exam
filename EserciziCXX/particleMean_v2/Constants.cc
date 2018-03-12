#include "Constants.h"

Constants::Constants()
    : massPion(0.1395706), massProton(0.938272), massK0(0.497611),
      massLambda0(1.115683) {}

Constants::~Constants() {}

Constants *Constants::instance() {
  static Constants *constants = new Constants;
  return constants;
}

const double Constants::get_massPion() { return massPion; }
const double Constants::get_massProton() { return massProton; }
const double Constants::get_massK0() { return massK0; }
const double Constants::get_massLambda0() { return massLambda0; }
