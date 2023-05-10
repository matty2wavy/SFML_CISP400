#include "Engine.h"
#include <ctime>
#include <random>

using namespace std;

Engine::Engine()
{
	VideoMode vm(1920, 1080);
	m_Window.create(vm, "Particle Engine", Style::Default);
}

void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl; // look at this

	while (m_Window.isOpen())
	{
		Time time1 = clock.restart();
		float time1asSeconds = time1.asSeconds();
		input();
		update(time1asSeconds);
		draw();
	}
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				//Create a loop to construct 5 particles
					//numPoints is a random number between 25 and 50
					//Pass the position of the mouse into constructor
				for (int i = 0; i < 5; i++)
				{
					int r = rand() % (50 - 25 + 1) + 25;
					int numPoints = r;
					//Particle(RenderTarget & target, int numPoints, Vector2i mouseClickPosition);
					Particle p(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y });
					m_particles.push_back(p);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			it++;
		}
		else
		{
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (long unsigned int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}
