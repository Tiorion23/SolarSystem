#include "Camera.h"

Camera::Camera(sf::Vector2f startCoords, sf::Vector2f resolution): startingView(sf::View(startCoords, resolution))
{
	default_scale = 1000000000.f;  //default scale 1pix = 1000000000 meters
	scale = 1.f;               //scale coefficient 
	xRes = resolution.x;    //camera resolution on Х-axis
	yRes = resolution.y;    //camera resolution on У-axis
	view = startingView;
	view.zoom(default_scale);
}

Camera::Camera() { }

sf::View Camera::getStartingView() const
{
	return startingView;
}

float Camera::get_scale() { return scale; }

sf::View Camera::getView() const { return view; }

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

void Camera::move(sf::Vector2f oldPosition, sf::Vector2f newPosition)
{
    //определяем перемещение относительно старой позиции
    const sf::Vector2f deltaPos = oldPosition - newPosition;
    //перемещаем вид
                // не даем переместиться за границы карты
                // что-то не так с правым нижним и верхним углами
                //левый верхний угол
    /*if ((view.getCenter() + deltaPos).x < (xRes / 2 * default_scale) && (view.getCenter() + deltaPos).y < (xRes / 2 * default_scale))
        view.setCenter(sf::Vector2f((xRes / 2 * default_scale), (yRes / 2 * default_scale)));
    // левый нижний угол
    else if ((view.getCenter() + deltaPos).x < (xRes / 2 * default_scale) && yRes >(worldSize.y - (yRes / 2 * default_scale)))
        view.setCenter(sf::Vector2f((xRes / 2 * default_scale), (worldSize.y - (yRes / 2 * default_scale))));
    //правый верхний угол
    else if ((view.getCenter() + deltaPos).x > (worldSize.x - (xRes / 2 * default_scale))
        && (view.getCenter() + deltaPos).y < (yRes / 2 * default_scale))
        view.setCenter(sf::Vector2f((worldSize.x - (xRes / 2 * default_scale)), (yRes / 2 * default_scale)));
    //правый нижний угол
    else if ((view.getCenter() + deltaPos).x > (worldSize.x - (xRes / 2 * default_scale))
        && (view.getCenter() + deltaPos).y > (worldSize.y - (yRes / 2 * default_scale)))
        view.setCenter(sf::Vector2f((worldSize.x - (xRes / 2 * default_scale)),
            (worldSize.y - (yRes / 2 * default_scale))));

    else if ((view.getCenter() + deltaPos).x < (xRes / 2 * default_scale)) //граница слева
        view.setCenter(sf::Vector2f((xRes / 2 * default_scale), (view.getCenter() + deltaPos).y));
    else if ((view.getCenter() + deltaPos).y < (yRes / 2 * default_scale)) //граница сверху
        view.setCenter(sf::Vector2f((view.getCenter() + deltaPos).x, (yRes / 2 * default_scale)));
    else if ((view.getCenter() + deltaPos).x > (worldSize.x - xRes / 2 * default_scale)) // граница справа
        view.setCenter(sf::Vector2f((worldSize.x - xRes / 2 * default_scale), (view.getCenter() + deltaPos).y));
    else if ((view.getCenter() + deltaPos).y > (worldSize.y - yRes / 2 * default_scale)) // граница снизу
        view.setCenter(sf::Vector2f((view.getCenter() + deltaPos).x, (worldSize.y - yRes / 2 * default_scale)));
    else*/
        view.setCenter(view.getCenter() + deltaPos*default_scale*scale);
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
