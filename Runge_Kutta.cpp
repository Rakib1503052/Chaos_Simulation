#include "Particles.hpp"
#include <cmath>

inline float Chaos::Particle::Dx(float t, const Curt C)
{
	return sin(C[y]) - b * C[x];
}

inline float Chaos::Particle::Dy(float t, const Curt C)
{
	return sin(C[z]) - b * C[y];
}

inline float Chaos::Particle::Dz(float t, const Curt C)
{
	return sin(C[x]) - b * C[z];
}

Chaos::Curt Chaos::Particle::Runge_Kutta(float t, const Curt C, float h)
{
	//K_1
	float Kx1 = Dx(t, C);
	float Ky1 = Dy(t, C);
	float Kz1 = Dz(t, C);

	//K_2
	float Kx2 = Dx(t + h / 2, Curt{ C[x] + Kx1 * h / 2,
									C[y] + Ky1 * h / 2,
									C[z] + Kz1 * h / 2 });

	float Ky2 = Dy(t + h / 2, Curt{ C[x] + Kx1 * h / 2,
									C[y] + Ky1 * h / 2,
									C[z] + Kz1 * h / 2 });

	float Kz2 = Dz(t + h / 2, Curt{ C[x] + Kx1 * h / 2,
									C[y] + Ky1 * h / 2,
									C[z] + Kz1 * h / 2 });
	/*=====================================================*/
	//K_3
	float Kx3 = Dx(t + h / 2, Curt{ C[x] + Kx2 * h / 2,
									C[y] + Ky2 * h / 2,
									C[z] + Kz2 * h / 2 });

	float Ky3 = Dy(t + h / 2, Curt{ C[x] + Kx2 * h / 2,
									C[y] + Ky2 * h / 2,
									C[z] + Kz2 * h / 2 });

	float Kz3 = Dz(t + h / 2, Curt{ C[x] + Kx2 * h / 2,
									C[y] + Ky2 * h / 2,
									C[z] + Kz2 * h / 2 });
	/*=====================================================*/
	//K_4
	float Kx4 = Dx(t + h, Curt{ C[x] + Kx3 * h,
								C[y] + Ky3 * h,
								C[z] + Kz3 * h });

	float Ky4 = Dy(t + h, Curt{ C[x] + Kx3 * h,
								C[y] + Ky3 * h,
								C[z] + Kz3 * h });

	float Kz4 = Dz(t + h, Curt{ C[x] + Kx3 * h,
								C[y] + Ky3 * h,
								C[z] + Kz3 * h });

	return Curt{ C[x] + (Kx1 + 2 * Kx2 + 2 * Kx3 + Kx4) * h / 6,
				 C[y] + (Ky1 + 2 * Ky2 + 2 * Ky3 + Ky4) * h / 6,
				 C[z] + (Kz1 + 2 * Kz2 + 2 * Kz3 + Kz4) * h / 6 };
}

Chaos::Curt Chaos::Particle::RK(const Curt C, float h)
{
	float Kx = Dx(0, C) * h;
	float Ky = Dy(0, C) * h;
	float Kz = Dz(0, C) * h;

	return Curt{ C[x] + Kx, C[y] + Ky, C[z] + Kz };
}