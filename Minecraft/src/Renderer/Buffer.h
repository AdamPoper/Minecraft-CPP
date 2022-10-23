#pragma once
#include <GL/glew.h>
#include "../Logger/Logger.h"
#include <vector>
#include "../Util/Vertex.h"

class Buffer
{
public:
	
	Buffer() = default;

	uint32_t GetRenderID() const;

	virtual void Bind() = 0;

	virtual void UnBind() = 0;

	virtual constexpr std::size_t GetSize() const = 0;

protected:

	uint32_t m_renderID;
};

class VertexBuffer : public Buffer
{
public:

	VertexBuffer() = default;

	VertexBuffer(Vertex* data, std::size_t size);

	void Bind();

	void UnBind();

	constexpr std::size_t GetSize() const;

	const Vertex* GetRawData() const;

private:

	std::vector<Vertex> m_buffer;
};

class IndexBuffer : public Buffer
{
public:

	IndexBuffer() = default;

	IndexBuffer(uint32_t* data, std::size_t size);

	void Bind();

	void UnBind();

	constexpr std::size_t GetSize() const;

	const uint32_t* GetRawData() const;

private:
	
	std::vector<uint32_t> m_buffer;
};