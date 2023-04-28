#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <complex>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

ComplexPlane::ComplexPlane(float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	m_view.setSize(BASE_WIDTH, -BASE_HEIGHT * m_aspectRatio);
	m_view.setCenter(0.0, 0.0);
	m_zoomCount = 0;
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
	float x_size = BASE_WIDTH * pow(BASE_ZOOM, m_zoomCount);
	float y_size = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_zoomCount);
	m_view.setSize(x_size, y_size);
}

void ComplexPlane::setCenter(Vector2f coord)
{
	m_view.setCenter(coord);
}

View ComplexPlane::getView()
{
	return m_view;
}

void ComplexPlane::setMouseLocation(Vector2f coord)
{
	m_mouseLocation = coord;
}

void ComplexPlane::loadText(Text& text)
{
    ostringstream oss;
    oss << "Mandelbrot Set" << endl;
    oss << "Center: (" << m_view.getCenter().x << ", " << m_view.getCenter().y << ")" << endl;
    oss << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl;
    oss << "Left click to Zoom in" << endl;
    oss << "Right click to Zoom out" << endl;
    text.setString(oss.str());
}

size_t ComplexPlane::countIterations(Vector2f coord)
{
	size_t iter = 0;
	complex<double> z(0, 0);
	complex<double> c(coord.x, coord.y);
	while (iter < MAX_ITER && abs(z) < 2.0)
	{
		z = z * z + c;
		iter++;
	}
	return iter;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    if (count == MAX_ITER) {
        // Black color for max iterations
        r = 0;
        g = 0;
        b = 0;
    }
    else {
        // Divide color scheme into 5 regions
        const size_t region_size = MAX_ITER / 5;
        const size_t region = count / region_size;
        const size_t remainder = count % region_size;
        const Uint8 base_color = (Uint8)((255.0 / region_size) * remainder);
        if (region == 0) { // Purple/blue
            r = 200;
            g = 0;
            b = base_color + 128;
        }
        else if (region == 1) { // Turquoise
            r = 0;
            g = base_color + 128;
            b = 128;
        }
        else if (region == 2) { // Green
            r = 0;
            g = 128;
            b = base_color + 128;
        }
        else if (region == 3) { // Yellow
            r = base_color + 128;
            g = 128;
            b = 0;
        }
        else { // Red
            r = 200;
            g = base_color + 128;
            b = 0;
        }
    }
}

