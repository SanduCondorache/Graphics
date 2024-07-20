#pragma once

class VertexBuffer {
private:
	size_t m_RendererID;
public:
	VertexBuffer(const void* data, size_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};
