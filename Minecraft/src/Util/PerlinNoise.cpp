#include "PerlinNoise.h"

const uint32_t PerlinNoise::s_seedInitilizerValue = 1000;

PerlinNoise::PerlinNoise(glm::ivec2 size) :
	m_size(size),
	m_seed(size.x * size.y),
	m_output(size.x * size.y)
{
	std::srand((unsigned)std::time(nullptr));
	for (float& value : m_seed)
	{
		value = static_cast<float>((std::rand() % s_seedInitilizerValue))
			/ static_cast<float>(s_seedInitilizerValue);
	}
    GenNoise();
}

float PerlinNoise::GetNoise(glm::ivec2 coords)
{
    return m_output[coords.y * m_size.x + coords.x];
}

glm::ivec2 PerlinNoise::GetSize() const
{
    return m_size;
}

void PerlinNoise::GenNoise()
{
    int width = m_size.x;
    int height = m_size.y;
    int octaves = 5;
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float noise = 0.0f;
            float scale = 1.0f;
            float scaleAcc = 0.0f;
            for (int o = 0; o < octaves; o++) {
                int pitch = width >> o;
                int sampleX1 = (x / pitch) * pitch;
                int sampleY1 = (y / pitch) * pitch;
                int sampleX2 = (sampleX1 + pitch) % width;
                int sampleY2 = (sampleY1 + pitch) % width;
                float blendX = (float)(x - sampleX1) / (float)pitch;
                float blendY = (float)(y - sampleY1) / (float)pitch;
                float linIntSampleT = (1.0f - blendX) * m_seed[sampleY1 * width + sampleX1] + blendX * m_seed[sampleY1 * width + sampleX2];
                float linIntSampleB = (1.0f - blendX) * m_seed[sampleY2 * width + sampleX1] + blendX * m_seed[sampleY2 * width + sampleX2];
                noise += (blendY * (linIntSampleB - linIntSampleT) + linIntSampleT) * scale;
                scaleAcc += scale;
                scale /= m_scaleDivisor;
            }
            m_output[y * width + x] = noise / scaleAcc;
        }
    }
}