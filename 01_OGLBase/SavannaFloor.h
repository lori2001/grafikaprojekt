#pragma once

// GLM
#include <glm/glm.hpp>

#include "includes/ProgramObject.h"
#include "includes/BufferObject.h"
#include "includes/VertexArrayObject.h"
#include "includes/TextureObject.h"

class SavannaFloor {
public:
	SavannaFloor();
	~SavannaFloor();

	bool Init();
	void Render(ProgramObject*, glm::mat4);

private:
	VertexArrayObject	m_FloorVao;			// VAO
	IndexBuffer			m_FloorIndices;		// index buffer
	ArrayBuffer			m_FloorVertexBuffer;// VBO

	Texture2D			m_floorTexture;

	struct Vertex
	{
		glm::vec3 p;
		glm::vec3 n;
		glm::vec2 t;
	};

};
