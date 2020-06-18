#include "Equations.h"

// Castea el resultado a int para que no moleste
int equation::pointsRecovery(float raceRecoveryFac, float seconds) {
  return raceRecoveryFac*seconds;
}

int equation::meditationRecovery(float meditationFactor, float intelligence,
                                 float seconds) {
  return meditationFactor * intelligence * seconds;
}
