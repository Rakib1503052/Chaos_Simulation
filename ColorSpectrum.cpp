#include "Common.h"

using namespace std;

vector<array<float, 4>> Spectrum()
{
	vector<array<float, 4>> Spec(N);

	if (N == 1)
	{
		Spec[0] = { 1.0,0.0,0.0,1.0 };
	}
	else if (N == 2)
	{
		Spec[0] = { 1.0,0.0,0.0,1.0 };
		Spec[1] = { 0.0,0.0,1.0,1.0 };
	}
	else if (N == 3)
	{
		Spec[0] = { 1.0,0.0,0.0,1.0 };
		Spec[1] = { 0.0,1.0,0.0,1.0 };
		Spec[2] = { 0.0,0.0,1.0,1.0 };
	}
	else
	{
		size_t mid = (int)(N / 2);
		size_t N1 = mid - 2;
		size_t N2 = N - mid - 2;

		float diff1 = 1.0 / (N1 + 1);
		float diff2 = 1.0 / (N2 + 1);

		Spec[0] = { 1.0,0.0,0.0,1.0 };
		Spec[mid] = { 0.0,1.0,0.0,1.0 };
		Spec[N - 1] = { 0.0,0.0,1.0,1.0 };

		for (size_t i = 1; i < N1; i++)
		{
			Spec[i] = { (float)1.0 - (diff1 * i), (float)0.0 + (diff1 * i), 0.0,1.0 };
		}

		for (size_t i = 1; i < N2; i++)
		{
			Spec[mid + i] = { 0.0,(float)1.0 - (diff1 * i), (float)0.0 + (diff1 * i),1.0 };
		}
	}
	return Spec;
}

void SetSpectrum()
{
	auto ColorSpectrum = Spectrum();

	for (size_t i = 0; i < N; i++)
	{
		Particles[i].SetMaterialAmb(ColorSpectrum[i]);
		Particles[i].SetMaterialDif(array<float, 4>{ 0.5, 0.5, 0.5, 1.0 });
		Particles[i].SetMaterialSpc(array<float, 4>{ 0.2, 0.2, 0.2, 1.0 });
		Particles[i].SetMaterialShn(21.0);
	}
}