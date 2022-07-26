#pragma once

#include <array>
#include <vector>
#include <cmath>
#include "Particles.hpp"

//extern std::vector<Chaos::Particle> Particles;
extern Chaos::Particle* Particles;
extern size_t N;
extern float MaxSize;

void SetSpectrum();
void GlMain(int argc, char* argv[]);