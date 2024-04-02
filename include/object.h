#pragma once



//#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>


#include "core.h"
#include "particle.h"


class Mover
{

public:

	float size;
	cyclone::Vector3 m_position;
  cyclone::Particle *m_particle;


	Mover() { 
		size = 1.0f;
		m_position = cyclone::Vector3(3, 1, 0);
    m_particle = new cyclone::Particle();

    /*
    m_particle->setPosition(5,20,0); //initial position 
    m_particle->setVelocity(0,0,0); //initial velocity
    m_particle->setMass(1.0f); //initial mass 
    m_particle->setDamping(0.99f); //initial damping 
    m_particle->setAcceleration(cyclone::Vector3::GRAVITY); //initial setAcceleration
    */
    //Fireball
    m_particle->setPosition(0,0,0);
    m_particle->setMass(1.0f); // 1.0kg - mostly blast damage
    m_particle->setVelocity(0.0f, 0.0f, 10.0f); // 5m/s
    m_particle->setAcceleration(0.0f, 0.6f, 0.0f); // Floats up
    m_particle->setDamping(0.9f);
    
	};

	void update(float duration) {
    cyclone::Vector3 wind(1.0f,0,0); //wind blow in x direction
    m_particle->addForce(wind);
    m_particle->integrate(duration);
    checkEdges();

    cyclone::Vector3 position;
    m_particle->getPosition(&position);

    if (position.x >= 100) {
    m_particle->setPosition(0,0,10.0f);
    m_particle->setVelocity(0,0,0);
    }
  }

  void checkEdges() {
    cyclone::Vector3 position;
    m_particle->getPosition(&position);
    cyclone::Vector3 velocity;
    m_particle->getVelocity(&velocity);

/*    if ((position.y - size) <= 0) {
      m_particle->setPosition(cyclone::Vector3(position.x, position.y + 0.1, position.z));
      m_particle->setVelocity(cyclone::Vector3(velocity.x, -0.9 * velocity.y, velocity.z));
    }*/
  }

	void stop() {


	}

	void draw(int shadow)
	{
    cyclone::Vector3 position;
    m_particle->getPosition(&position);
		if (shadow)
			glColor3f(0.1f, 0.1f, 0.1f);
		else
			glColor3f(1.0,0,0);

		glPushMatrix();
			glTranslated(position.x, position.y, position.z);
			glutSolidSphere(size, 30, 30);
		glPopMatrix();

	}
};

