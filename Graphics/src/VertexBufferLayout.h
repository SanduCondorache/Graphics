#pragma once

#include <vector>
#include <GL/glew.h>

#include "Renderer.h"

struct VertexBufferElement {
	size_t type;
	size_t count;
	unsigned char normalized;

	static size_t GetSizeOfType(size_t type) {
		if (type == GL_FLOAT) {
			return 4;
		}
		if (type == GL_UNSIGNED_INT) {
			return 4;
		}
		if (type == GL_UNSIGNED_BYTE) {
			return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {

private:
	std::vector<VertexBufferElement> m_Elements;
	size_t m_Stride;
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(size_t count) {
		static_assert(false);
	}

	template<>
	void Push<float>(size_t count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<size_t>(size_t count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(size_t count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const {
		return m_Elements;
	}

	inline size_t GetStride() const {
		return m_Stride;
	}
};