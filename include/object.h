#pragma once


#if _WIN64
	#include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#elif __linux__
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h>
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#endif

#include "core.h"
#include <particle.h>

class Mover
{

public:

	float size;
	cyclone::Vector3 m_position;
	cyclone::Particle* m_particle;	

	Mover() { 
		size = 1.0f;
		m_position = cyclone::Vector3(3, 1, 0);

		m_particle = new cyclone::Particle();
		m_particle->setPosition(0, 20, 0); //initial posx
		m_particle->setVelocity(0, 0, 0); //initial vel
		m_particle->setMass(1.0f); //mass
		m_particle->setDamping(0.8f); //damping
		m_particle->setAcceleration(cyclone::Vector3::GRAVITY); //initial acc
	};

	void update(float duration) {
		// cyclone::Vector3 wind(1.0f, 0, 0);
		// m_particle->addForce(wind);
		m_particle->integrate(duration);
		checkEdges();
	}

	void resetParameters() {
		m_particle->setPosition(0, 20, 0); //initial posx
		m_particle->setVelocity(0.0f, 0.0f, 0.0f);
		m_particle->setMass(1.0f); // 1.0kg-mostly blast damage
		m_particle->setDamping(0.8f);
		m_particle->setAcceleration(cyclone::Vector3::GRAVITY); //initial acc
	}

	void checkEdges() {
		cyclone::Vector3 pos = m_particle->getPosition();
		cyclone::Vector3 vel = m_particle->getVelocity();

		if (pos.x >= 100 - size / 2) {
			pos.x = 100 - size / 2;
			vel.x *= -1;
		} else if (pos.x <= -100 + size / 2) {
			pos.x = -100 + size / 2;
			vel.x *= -1;
		}
		if (pos.y <= size / 2) {
			pos.y = size / 2;
			vel.y *= -1;
		}
		if (pos.z >= 100 - size / 2) {
			pos.z = 100 - size / 2;
			vel.z *= -1;
		} else if (pos.z <= -100 + size / 2) {
			pos.z = -100 + size / 2;
			vel.z *= -1;
		}
		m_particle->setPosition(pos);
		m_particle->setVelocity(vel);
	}

	void stop() {
	}

	void draw(int shadow)
	{
		cyclone::Vector3 position;
		m_particle->getPosition(&position); //get the current pos of particle

		if (shadow)
			glColor3f(0.1f, 0.1f, 0.1f);
		else
			glColor3f(1.0,0,0);

		glPushMatrix();
			glTranslatef(position.x, position.y, position.z);
			// glTranslated(m_position.x, m_position.y, m_position.z);
			glutSolidSphere(size, 30, 30);
		glPopMatrix();
	}
};

