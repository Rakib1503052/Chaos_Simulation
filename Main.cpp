#include "Common.h"
#include <iostream>
#include <conio.h>

//std::vector<Chaos::Particle> Particles;
Chaos::Particle* Particles;
size_t N = 3;
float MaxSize = 4.0;
size_t Iter = 10000;

void UI();

int main(int argc, char* argv[])
{
	UI();
	Particles = new Chaos::Particle[N];

	//Initial positions of the particles
	Particles[0].ParticleInit(Iter, 0.1, 0.2, 0.2);
	Particles[1].ParticleInit(Iter, 0.1, 0.2, 0.3);
	Particles[2].ParticleInit(Iter, 0.1, 0.3, 0.2);

	SetSpectrum();
	GlMain(argc, argv);

	delete[] Particles;
	return 0;
}

void UI()
{
	using namespace std;
	
	cout << "This is a simulation of Thomas attractor, a Chaotic system.\n";
	cout << "It shows that for a non-linear system, even if deterministic,\n";
	cout << "a small difference in one state may result in a large difference\n";
	cout << "at a later state.\n\n\n";
	cout << "This simulator shows the trajectory of particles following\n";
	cout << "the Thomas attractor system. The system is described by the\n";
	cout << "following equations.\n";
	cout << "\tdx/dt = sin y - bx\n";
	cout << "\tdy/dt = sin z - by\n";
	cout << "\tdz/dt = sin x - bz\n";
	cout << "Where b is an arbitrary system constant. In this simulation\n";
	cout << "b = 0.208186.\n\n\n";
	cout << "In this simulation, 3 particles are simulated for 10000\n";
	cout << "iterations with an interval of 0.02s.\n\n";
	cout << "During the animation, use the arrow keys to move the view.\n";
	cout << "Use Page UP and Page Down keys to zoom in and zoom out.\n\n";
	cout << "Press any key to start the animation.\n";
#pragma warning(suppress : 4996)
	getch();
}