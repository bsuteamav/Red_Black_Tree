#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

#define maxTextLenght 3

Font font;

class Button {
protected:
	double x;
	double y;

	Text TXT;
	double width;
	double height;

	RectangleShape BOX;
public:
	string text;

	virtual Button& setProberties(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "button")
	{
		font.loadFromFile("fonts/arial.ttf");

		x = _x;
		y = _y;
		width = _width;
		height = _height;
		text = _text;
		TXT.setFont(font);
		TXT.setCharacterSize(20);
		TXT.setFillColor(Color::White);
		TXT.setPosition(x, y);

		BOX.setSize(Vector2f(width, height));
		BOX.setPosition(x, y);
		BOX.setFillColor(sf::Color(133, 133, 133));
		BOX.setOutlineThickness(1);
		BOX.setOutlineColor(Color(66, 66, 66));
		return *this;
	}

	Button(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "button")
	{
		setProberties(_x, _y, _width, _height, _text);
	}


	bool isSelected(Vector2i _mouse)
	{
		if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height))
		{
			return  true;
		}
		else
		{
			return false;
		}
	}

	Text& getText()
	{
		TXT.setString(text);
		return TXT;
	}

	RectangleShape& getBox()
	{
		return BOX;
	}

};

class InputBox : public Button {
protected:
	bool focus;
public:
	InputBox& setProberties(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "", Color color = Color::White)
	{
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		text = _text;
		focus = false;

		TXT.setFont(font);
		TXT.setCharacterSize(20);
		TXT.setFillColor(Color::Black);
		TXT.setPosition(x, y);

		BOX.setSize(Vector2f(width, height));
		BOX.setPosition(x, y);
		BOX.setFillColor(Color::White);
		BOX.setOutlineColor(color);
		BOX.setOutlineThickness(2);
		return *this;
	}
	InputBox(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "", Color color = Color::White)
	{
		setProberties(_x, _y, _width, _height, _text, color);
	}
	void setFocus()
	{
		focus = true;
	}
	bool isChoosed()
	{
		return focus;
	}
	void clear()
	{
		text.clear();
		text.push_back('|');
	}
	void looseFocus()
	{
		focus = false;
		if (text.back() == '|')
			text.pop_back();
	}
	bool select(Vector2i _mouse)
	{
		if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
			if (!focus) {
				focus = true;
				text += "|";
			}
		}
		return focus;
	}
	void enter(char ch)
	{
		if (text.size() < maxTextLenght + 1)
		{
			text.pop_back();
			text.push_back(ch);
			text.push_back('|');
		}
	}
	string getString() const
	{
		return text;
	}
	void deleteLast()
	{
		if (text.size() > 1)
		{
			text.pop_back();
			text.pop_back();
			text.push_back('|');
		}
	}
};