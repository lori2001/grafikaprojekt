#pragma once

// C++ includes
#include <memory>
#include <vector>
#include <random>

// SDL
#include <SDL.h>
#include <SDL_opengl.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>

// mesh
#include "includes/ObjParser_OGL3.h"

class Rocks {
public:
	Rocks() {
		m_rock_mesh = nullptr;
	}

	void Init() {
		// mesh betöltése
		m_rock_mesh = std::unique_ptr<Mesh>(ObjParser::parse("assets/rock/rock.obj"));
		m_rock_mesh->initBuffers();

		// texturák betöltése
		m_rockSpecularTexture.FromFile("assets/rock/rockSpecular.png");
		// m_rockNormalTexture.FromFile("assets/rock/rockNormal.png");
		// m_rockDiffuseTexture.FromFile("assets/rock/rockDiffuse.png");

		// tulajdonságok véletlenszerûsítése
		for (int i = 0; i < m_num_of_rocks; i++) {
			m_rock_mesh_worlds.push_back({
				glm::translate(glm::f32vec3(m_x_dist(gen), m_y_dist(gen), m_z_dist(gen))) *
				glm::scale(glm::vec3(m_scale(gen), m_scale(gen), m_scale(gen))) *
				glm::rotate(m_rotation(gen), glm::vec3(0, 1, 0))
				});
		}
	}

	void Render(ProgramObject* m_program, const glm::mat4& viewProj) {
		m_program->SetTexture("texImage", 0, m_rockSpecularTexture);
		for (auto& rock_worlds : m_rock_mesh_worlds) {
			m_program->SetUniform("MVP", viewProj * rock_worlds);
			m_program->SetUniform("world", rock_worlds);
			m_program->SetUniform("worldIT", glm::inverse(glm::transpose(rock_worlds)));
			m_rock_mesh->draw();
		}
	}

private:
	int m_num_of_rocks = 25;

	std::unique_ptr<Mesh> m_rock_mesh;
	Texture2D			m_rockSpecularTexture;
	Texture2D			m_rockDiffuseTexture;
	Texture2D			m_rockNormalTexture;
	
	std::vector<glm::mat4> m_rock_mesh_worlds;

	std::default_random_engine gen{4};

	std::uniform_real_distribution<float> m_z_dist{ -15.0F, 15.0F };
	std::uniform_real_distribution<float> m_x_dist{-15.0F, 15.0F};
	std::uniform_real_distribution<float> m_y_dist{0.0F, 0.3F};
	std::uniform_real_distribution<float> m_scale{ 1.0F, 2.0F };
	std::uniform_real_distribution<float> m_rotation{ 0.0F, 180.0F * (M_PI / 180.0F) };
};