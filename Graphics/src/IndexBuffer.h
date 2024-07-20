#pragma once

class IndexBuffer {
private:
	size_t m_RendererID;
	size_t m_Count;
public:
	IndexBuffer(const size_t* data, size_t count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	inline size_t GetCount() const { return m_Count; };
};