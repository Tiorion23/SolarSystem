#include "Camera.h"

Camera::Camera() { }
Camera::Camera(sf::Vector2f resolution)
{
	input_offset = sf::Vector2i(0, 0);
	world_offset = Vectorld2d();
	default_world_display_scale = 100000000.f;  //default scale 1pix = 100000000 meters
	world_display_scale = 1.f;               //scale coefficient
	world_view = sf::View();
	ui_view = sf::View();
	world_view.setSize(resolution);
	ui_view.setSize(resolution);
	ui_view.setCenter(resolution * 0.5f);
}

void Camera::set_input_offset(sf::Vector2i offset) {
	this->input_offset += offset;
}

void Camera::set_world_offset(Vectorld2d offset) {
	this->world_offset = this->world_offset + offset;
}

void Camera::reset_offsets() {
	input_offset = sf::Vector2i(0, 0);
	world_offset = Vectorld2d();
}

void Camera::resize(float newWidth, float newHeight)
{
	world_view.setSize(newWidth, newHeight);		// changing world view size to fit new window size
	world_view.zoom(world_display_scale);		// rescaling world view back to previous scale
	ui_view.setSize(newWidth, newHeight);		// changing UI view size to fit new window size
}

void Camera::move() {
	move_by_world_offset();
	move_by_input_offset();
	reset_offsets();
}

void Camera::move_to(sf::Vector2f coords) {
	world_view.setCenter(coords);
}

void Camera::move(sf::Vector2i oldPosition, sf::Vector2i newPosition)
{    
    const sf::Vector2i deltaPos = oldPosition - newPosition;						//calculating pointer position change from old position
	world_view.move(sf::Vector2f(deltaPos) * world_display_scale);			// moving camera by calculated position change
}

void Camera::move_by_world_offset() {
	if (world_offset != Vectorld2d(0., 0.))
		world_view.move(sf::Vector2f(world_offset.x, world_offset.y));
}

void Camera::move_by_input_offset() {
	if (input_offset != sf::Vector2i(0, 0))
		world_view.move(sf::Vector2f(input_offset.x * world_display_scale, input_offset.y * world_display_scale));
}

void Camera::zoom() {
	world_view.zoom(0.8);
	world_display_scale *= 0.8;
}

void Camera::zoom_out() {
	world_view.zoom(1.2);
	world_display_scale *= 1.2;
}