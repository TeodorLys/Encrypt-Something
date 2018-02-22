#pragma once
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Window\Mouse.hpp>
#include <string>

class Image_Display {
private:
 sf::RenderWindow window;
 sf::Texture te;
 sf::RectangleShape sp;
 sf::View v;
public:
 Image_Display();

 void Check_Mouse_Movement(sf::Mouse &m);

 void Open_Image_Viewer(std::string&);

};

