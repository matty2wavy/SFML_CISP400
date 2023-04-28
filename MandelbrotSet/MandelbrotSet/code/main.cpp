#include <SFML/Graphics.hpp>
#include "ComplexPlane.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;
using namespace sf;

int main()
{
    unsigned int width = VideoMode::getDesktopMode().width;
    unsigned int height = VideoMode::getDesktopMode().height;
    float aspectRatio = (float)height / (float)width;

    RenderWindow window(VideoMode(width, height), "Mandelbrot Set", Style::Default);

    ComplexPlane cp(aspectRatio);
    Font font;
    Text hud;
    font.loadFromFile("fonts/UniversCondensed.ttf");
    hud.setFont(font);
    hud.setCharacterSize(20);
    hud.setPosition(20, 20);
    hud.setFillColor(Color::White);

    VertexArray vArray(Points, width * height);

    enum class State { CALCULATING, DISPLAYING };
    State state = State::CALCULATING;

    while (window.isOpen())
    {
        /*
        *********************
        Handle Input Segment
        *********************
        */

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2i pixelPos = Mouse::getPosition(window);
                Vector2f worldPos = window.mapPixelToCoords(pixelPos, cp.getView());
                if (event.mouseButton.button == Mouse::Left)
                {
                    cp.zoomIn();
                    cp.setCenter(worldPos);
                    state = State::CALCULATING;
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    cp.zoomOut();
                    cp.setCenter(worldPos);
                    state = State::CALCULATING;
                }
            }
            else if (event.type == Event::MouseMoved)
            {
                Vector2i pixelPos = Mouse::getPosition(window);
                Vector2f worldPos = window.mapPixelToCoords(pixelPos, cp.getView());
                cp.setMouseLocation(worldPos);
            }
        }

        /*
        ****************
        Update the Scene
        ****************
        */

        if (state == State::CALCULATING)
        {
            int pixelWidth = width;
            int pixelHeight = height;
            for (int i = 0; i < pixelHeight; i++)
            {
                for (int j = 0; j < pixelWidth; j++)
                {
                    vArray[j + i * pixelWidth].position = { (float)j,(float)i };
                    Vector2f coord = window.mapPixelToCoords({ j, i }, cp.getView());
                    size_t count = ComplexPlane::countIterations(coord);
                    Uint8 r = 0;
                    Uint8 g = 0;
                    Uint8 b = 0;
                    cp.iterationsToRGB(count, r, g, b);
                    vArray[j + i * pixelWidth].position = { (float)j, (float)i };
                    vArray[j + i * pixelWidth].color = Color(r, g, b);
                }
            }
            state = State::DISPLAYING;
            cp.loadText(hud);
        }
        window.clear();
        window.draw(vArray);
        window.draw(hud);
        window.display();
    }

    return 0;
}
