#include "Camera.h"

Camera::Camera() { }
Camera::Camera(sf::Vector2f startCoords, sf::Vector2f resolution): startingView(sf::View(startCoords, resolution))
{
	default_scale = 100000000.f;  //default scale 1pix = 100000000 meters
	scale = 1.f;               //scale coefficient 
	xRes = resolution.x;    //camera resolution on Õ-axis
	yRes = resolution.y;    //camera resolution on Ó-axis
	view = startingView;
	ui_view = startingView;
	ui_view.setCenter(ui_view.getSize() * 0.5f);
	view.zoom(default_scale);
}

sf::View Camera::getStartingView() const
{
	return startingView;
}

float Camera::get_scale() { return scale; }

sf::View Camera::getView() const { return view; }
sf::View Camera::getUIView() const { return ui_view; }

void Camera::setView(sf::View newView)
{
	view = newView;
}

void Camera::setView(sf::Vector2f center, sf::Vector2f size)
{
	view = sf::View(center, size);
}

void Camera::resize(int newWidth, int newHeight)
{
	xRes = newWidth;
	yRes = newHeight;
	setView(view.getCenter(), sf::Vector2f(newWidth, newHeight));
	view.zoom(default_scale*scale);
}

void Camera::move(sf::Vector2i oldPosition, sf::Vector2i newPosition)
{    
    const sf::Vector2i deltaPos = oldPosition - newPosition;						//calculating pointer position change from old position
    view.setCenter(view.getCenter() + sf::Vector2f(deltaPos)*default_scale*scale);	//setting view center based on delta and current scale
}


void Camera::reset()
{
    view = startingView;
    view.zoom(default_scale);
    scale = 1.f;
}

void Camera::rescale(float s) {
    view.zoom(s);
    scale = s * scale;
}
