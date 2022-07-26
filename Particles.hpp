#pragma once
#include <array>
#include <vector>

namespace Chaos
{
	typedef std::array<float, 3> Curt;

	class Particle
	{
	private:
		//Enumeration
		static const size_t x = 0, y = 1, z = 2;
		//Constants
		float b = 0.208186;

		float T = 0;
		float MaxT = 10.0;
		float dT = 0.02;

		//Differencial equations
		inline float Dx(float t, const Curt C);
		inline float Dy(float t, const Curt C);
		inline float Dz(float t, const Curt C);

		//Particle properties
		Curt Coords;
		std::vector<Curt> Trace;
		float GlMaterialAmbient[4];
		float GlMaterialDiffuse[4];
		float GlMaterialSpecular[4];
		float GlMaterialShine;

		Curt Runge_Kutta(float t, const Curt C, float h);
		Curt RK(const Curt C, float h);

	public:

		Particle() {}

		inline void ParticleInit(size_t IterLength, float X, float Y, float Z)
		{
			Coords = { X,Y,Z };
			Trace.reserve(IterLength);
			//dT = MaxT / IterLength;
			MaxT = IterLength * dT;
		}

		inline float GetCurrentTime() { return T; }

		void Update()
		{
			if (T < MaxT)
			{
				Trace.push_back(this->Coords);
				//this->Coords = this->Runge_Kutta(this->T, this->Coords, this->dT);
				this->Coords = this->RK(this->Coords, this->dT);
				this->T += this->dT;
				//UpdateSize(this->Coords);
			}

			//return this->Coords;
		}


		inline void SetMaterialAmb(std::array<float, 4> val)
		{
			GlMaterialAmbient[0] = val[0];
			GlMaterialAmbient[1] = val[1];
			GlMaterialAmbient[2] = val[2];
			GlMaterialAmbient[3] = val[3];
		}
		inline void SetMaterialDif(std::array<float, 4> val)
		{
			GlMaterialDiffuse[0] = val[0];
			GlMaterialDiffuse[1] = val[1];
			GlMaterialDiffuse[2] = val[2];
			GlMaterialDiffuse[3] = val[3];
		}
		inline void SetMaterialSpc(std::array<float, 4> val)
		{
			GlMaterialSpecular[0] = val[0];
			GlMaterialSpecular[1] = val[1];
			GlMaterialSpecular[2] = val[2];
			GlMaterialSpecular[3] = val[3];
		}
		inline void SetMaterialShn(float Shine)
		{
			GlMaterialShine = Shine;
		}

		void GlDrawFunc(void);
	};
}