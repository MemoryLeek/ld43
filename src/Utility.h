#ifndef UTILITY_H
#define UTILITY_H

template<typename T>
void UNUSED(T &)
{
}

namespace Utility
{
	template<typename T>
	T lerp(T start, T end, float value)
	{
		return start + (end - start) * value;
	}
}

constexpr int RES_X = 1280;
constexpr int RES_Y = 720;

constexpr float RENDERSCALE = 4;
constexpr float GRAVITY = 10;
constexpr int TILE_SIZE = 32;

#endif // UTILITY_H
