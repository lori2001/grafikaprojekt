#include "SavannaFloor.h"

#include <math.h>
#include <vector>

SavannaFloor::SavannaFloor(void)
{
	
}

SavannaFloor::~SavannaFloor(void) {

}

bool SavannaFloor::Init()
{
	// text�ra
	m_floorTexture.FromFile("assets/savanna.jpg");


	// A talaj 4 cs�cspontja
	float a = 20;

	std::vector<Vertex>vertices;
	vertices.push_back({ glm::vec3(-a, 0, a), glm::vec3(0, 1, 0), glm::vec2(0, 0) });
	vertices.push_back({ glm::vec3(a, 0,  a), glm::vec3(0, 1, 0), glm::vec2(a / 2, 0) });
	vertices.push_back({ glm::vec3(a, 0, -a), glm::vec3(0, 1, 0), glm::vec2(0, a / 2) });
	vertices.push_back({ glm::vec3(-a, 0, -a), glm::vec3(0, 1, 0), glm::vec2(a / 2, a / 2) });

	std::vector<int> indices = { 0, 1, 2, 2, 3, 0 };

	m_FloorVertexBuffer.BufferData(vertices);
	m_FloorIndices.BufferData(indices);

	// VAO-ban le�rjuk hogyan lesz a VBO-ban elt�rolva a talaj adat
	m_FloorVao.Init(
		{
			// 0-�s attrib�tum | vec3-b�l tudja, hogy 3 float | offest = 0 | h�ny byte-ra van a k�vi cs�cspont | VBO
			{ CreateAttribute<0, glm::vec3,	0, sizeof(Vertex)>, m_FloorVertexBuffer },
			// 1-es attrib�tum | vec3-b�l tudja, hogy 3 float | offest = sizeof(vec3) | h�ny byte-ra van a k�vi cs�cspont | VBO
			{ CreateAttribute<1, glm::vec3, (sizeof(glm::vec3)), sizeof(Vertex)>, m_FloorVertexBuffer },
			// 2-es attrib�tum | vec2-b�l tudja, hogy 2 float | offest = 2*sizeof(vec3) | h�ny byte-ra van a k�vi cs�cspont | VBO
			{ CreateAttribute<2, glm::vec2, (2 * sizeof(glm::vec3)), sizeof(Vertex)>, m_FloorVertexBuffer},
		},
		m_FloorIndices
		);

	return true;
}

void SavannaFloor::Render(ProgramObject* m_program, glm::mat4 viewProj, glm::vec3 lightPos, glm::vec3 lightDir, glm::vec3 ambientCol)
{
	// m_program->Use();

	m_FloorVao.Bind();
	m_program->SetTexture("texImage", 0, m_floorTexture);
	glm::mat4 floor = glm::mat4(1.0f);

	m_program->SetUniform("MVP", viewProj * floor);
	m_program->SetUniform("world", floor);
	m_program->SetUniform("lightPos", lightPos);
	m_program->SetUniform("lightDir", lightDir);
	m_program->SetUniform("ambientCol", ambientCol);
	m_program->SetUniform("worldIT", glm::inverse(glm::transpose(floor)));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

	m_program->Unuse();
}