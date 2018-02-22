#include "Image_Display.h"
#include <SFML\Window\Event.hpp>


Image_Display::Image_Display(){}

int a, b;
float c, d;
bool heldDown = false;
void Image_Display::Check_Mouse_Movement(sf::Mouse &m) {
  if (m.isButtonPressed(sf::Mouse::Left) && !heldDown) {
   a = m.getPosition(window).x;
   b = m.getPosition(window).y;
   c = sp.getPosition().x;
   d = sp.getPosition().y;
   heldDown = true;
  }
  if (heldDown)
   sp.setPosition(sf::Vector2f(m.getPosition(window).x + (c - a), m.getPosition(window).y + (d - b)));
}

void Image_Display::Open_Image_Viewer(std::string &path) {
 if(!te.loadFromMemory(path.data(), path.size())) return;

 sp.setTexture(&te);

 float x = 1600;
 float y = 900;

 window.create(sf::VideoMode(static_cast<unsigned int>(x), static_cast<unsigned int>(y)), "Hello");

 y = 500.f;

 sp.setSize(sf::Vector2f((y * te.getSize().x / te.getSize().y), y));

 sp.setOrigin(sp.getSize().x / 2, sp.getSize().y / 2);

 sp.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)));

 v = window.getDefaultView();
 
 sf::Event ev;
 sf::Mouse mouse;

 window.mapPixelToCoords(mouse.getPosition(window), v);

 float b = 1.f;

 while (window.isOpen()) {
  while (window.pollEvent(ev)) {
   switch (ev.type) {
   case sf::Event::Closed:
	window.close();
	break;

   case sf::Event::MouseMoved:

	Check_Mouse_Movement(mouse);

	break;

   case sf::Event::MouseButtonReleased:
	heldDown = false;
	break;

   case sf::Event::MouseWheelMoved:
	v.setCenter(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2));

	if (ev.mouseWheel.delta < 1)
	 v.zoom(b * 2);
	else
	 v.zoom(b / 2);
	break;

   case sf::Event::KeyPressed:
	if (ev.key.code == sf::Keyboard::F) {
	 sp.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)));

	}
	break;

   }
  }
  
  
  window.clear();
  window.setView(v);
  window.draw(sp);
  window.display();
 }

}
