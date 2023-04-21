// Include important C++ libraries here
//Matthew Nguyen & Eric Stevens
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <random>
using namespace sf;
using namespace std;


//Function to calculate the midpoint
Vector2f midpoint(const Vector2f& p1, const Vector2f& p2)
{
	return Vector2f((p1.x + p2.x) / 2.0f, (p1.y + p2.y) / 2.0f);
}

int main()
{
	//Create a video mode object
	VideoMode vm(1920, 1080);
	//Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);
	//Create a texture to hold a praphic on the GPU
	Texture textureBackground;
	//Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.jpg");
	//Create a sprite
	Sprite spriteBackground;
	//Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	//Set the sprite to cover the entire screen
	spriteBackground.setPosition(0, 0);

	//Prompt the user to enter the three vertices.
	Text messageText1;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText1.setFont(font);
	messageText1.setString("Click on any three points on the screen to create vertices for the triangle.");
	messageText1.setCharacterSize(25);
	messageText1.setFillColor(Color::White);

	//Prompt the user to enter the fourth point. 
	Text messageText2;
	messageText2.setFont(font);
	messageText2.setString("Then choose a fourth point to start the algorithm.");
	messageText2.setCharacterSize(25);
	messageText2.setFillColor(Color::White);

	//Position the text.
	messageText1.setPosition(20, 20);
	messageText2.setPosition(20, 50);

	//Create two vectors for vertices and points
	vector<CircleShape> vertices;
	vector<CircleShape> points;
	Vector2f point;

	//Generate a random number between 0 and 2
	random_device rd;
	mt19937 gen(rd()); // I found this online, it is called the Mersenne Twister and is a RNG with state size of 19937 bits.
	uniform_int_distribution<> dis(0, 2);

	//Get the three vertices
	while (vertices.size() < 3)
	{
		window.draw(messageText1);
		window.draw(messageText2);
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);
				CircleShape vertexDot(4.0f);
				vertexDot.setFillColor(Color::Blue);
				vertexDot.setPosition(clickPosition.x - 4.0f, clickPosition.y - 4.0f);
				vertices.push_back(vertexDot);
				window.draw(vertexDot);
			}
		}
		window.display();
	}

	//Get the fourth click and initiate the algorithm
	bool algorithmStarted = false;
	while (window.isOpen())
	{
		//Close the window
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
			{
				if (!algorithmStarted)
				{
					point = Vector2f(event.mouseButton.x, event.mouseButton.y);
					CircleShape dot(2.0f);
					dot.setFillColor(Color::Red);
					dot.setPosition(point);
					points.push_back(dot);
					algorithmStarted = true;
				}
				else
				{
					while (algorithmStarted)
					{
						//Get the random vertex and the midpoint
						int vertexIndex = dis(gen);
						Vector2f vertex = vertices[vertexIndex].getPosition();
						point = midpoint(point, vertex);

						//Draw a dot at said point
						CircleShape dot(2.0f);
						dot.setFillColor(Color::Red);
						dot.setPosition(point);
						points.push_back(dot);
						window.draw(dot);
						window.display();
					}
				}
			}
		}
		for (const auto& vertex : vertices)
		{
			window.draw(vertex);
		}
		for (const auto& dot : points)
		{
			window.draw(dot);
		}

		window.display();
	}
	return 0;
}

