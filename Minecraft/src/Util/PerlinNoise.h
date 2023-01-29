#pragma once

#include <vector>
#include <random>
#include <time.h>

#include "../Logger/Logger.h"
#include "../glm/glm.hpp"

class PerlinNoise
{
public:

	PerlinNoise() = default;

	PerlinNoise(glm::ivec2 size);

	PerlinNoise(const PerlinNoise&) = delete;
	
	float GetNoise(glm::ivec2 coords);

	glm::ivec2 GetSize() const;

private:

	void GenNoise();

private:

	static const uint32_t s_seedInitilizerValue;

	std::vector<float> m_seed;

	std::vector<float> m_output;

	glm::ivec2 m_size;

	const float m_scaleDivisor = 0.6f;
};