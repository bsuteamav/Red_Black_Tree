#ifndef TreeVisualization_RBTree_H_
#define TreeVisualization_RBTree_H_

#include <SFML/Graphics.hpp>
#include <time.h>
#include <string>
#include <stack>
#include <cmath>
#include <algorithm>

#include "InputBox.h"
#include "Red_Black_Tree.h"

const int StartDrawPositionX = 400;
const int StartDrawPositionY = 40;

using namespace sf;

template<typename T>
class TreeVisualization
{
private:
	int treeHeight;
	int width_;
	int height_;
	int circleRadius;
	Node<T>* selectedNode_;

	RenderWindow window_;
	Font font_;
	CircleShape nodeCircle_;
	Text valueText_;
	Button deleteButton_;
	Button insertButton_;
	Button searchButton_;
	InputBox nodeKeyInput_;
	Red_Black_Tree<T> tree_;

	void draw();
	// void drawTree(Node* node, int x, int h);
	void drawTree(Node<T>* node, int pX = StartDrawPositionX, int height = 0, int descensionSide = 0);
	void onMouseEvent(Event &e);
public:
	TreeVisualization(int width, int height);
	void launch();
};

template<typename T>
TreeVisualization<T>::TreeVisualization(int width, int height)
{
	width_ = width;
	height_ = height;

	circleRadius = 22;

	selectedNode_ = nullptr;

	font_.loadFromFile("fonts/arial.ttf");

	valueText_.setFont(font_);
	valueText_.setCharacterSize(14);
	valueText_.setFillColor(Color::Black);


	insertButton_.setProberties(20, 20, 70, 30, "Insert");
	searchButton_.setProberties(20, 55, 70, 30, "Find");
	deleteButton_.setProberties(20, 90, 70, 30, "Delete");
	nodeKeyInput_.setProberties(20, 125, 50, 30, "", Color::Black);

	nodeCircle_.setRadius(circleRadius);
	nodeCircle_.setOutlineColor(Color::Black);
	nodeCircle_.setOutlineThickness(2);
}

template<typename T>
void TreeVisualization<T>::launch()
{
	Node<T>* temp;
	window_.create(VideoMode(width_, height_), "Red Black Tree!");
	window_.setFramerateLimit(60);

	while (window_.isOpen())
	{
		Event e;
		while (window_.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window_.close();
			}
			if (e.type == sf::Event::MouseButtonPressed)
			{
				onMouseEvent(e);
			}
			if (e.type == sf::Event::TextEntered)
			{
				if (nodeKeyInput_.isChoosed())
				{
					if (e.text.unicode >= 32 && e.text.unicode <= 126)
					{
						nodeKeyInput_.enter(e.text.unicode);
					}
					else if (e.text.unicode == 8)
					{
						nodeKeyInput_.deleteLast();
					}
				}
			}
		}
		window_.clear(sf::Color(255, 255, 255));
		draw();
		window_.display();

	}
}

template<typename T>
void TreeVisualization<T>::onMouseEvent(Event &e)
{
	nodeKeyInput_.looseFocus();
	if (e.mouseButton.button == sf::Mouse::Left)
	{
		try {
			Vector2i mouse = Mouse::getPosition(window_);

			if (nodeKeyInput_.select(mouse))
			{
				// cout << "here\n";
			}
			if (deleteButton_.isSelected(mouse))
			{
				tree_.deleteNode(stoi(nodeKeyInput_.getString()));

			}

			if (insertButton_.isSelected(mouse))
			{
				tree_.addNode(stoi(nodeKeyInput_.getString()));
			}

			if (searchButton_.isSelected(mouse))
			{
				selectedNode_ = tree_.search(stoi(nodeKeyInput_.getString()));
			}
			nodeKeyInput_.setFocus();
			nodeKeyInput_.clear();
		}
		catch (...)
		{
			cout << "bad input\n";
		}
	}
}

template<typename T>
void TreeVisualization<T>::drawTree(Node<T>* node, int pX, int height, int descensionSide)
{
	if (node == nullptr)
		return;

	int x = pX + (circleRadius + 4) * descensionSide * (1 << (treeHeight - height - 1));
	int y = StartDrawPositionY + 64 * height;
	double k = circleRadius / (sqrt((x - pX)*(x - pX) + 64 * 64));
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(pX - k * (pX - x), StartDrawPositionY + 64 * (height - 1) + k * 64),sf::Color::Black),
		sf::Vertex(sf::Vector2f(x, y),sf::Color::Black)
	};
	if (height)
		window_.draw(line, 2, sf::Lines);

	nodeCircle_.setPosition(x - circleRadius, y - circleRadius);
	if (node->color == 1)
	{
		nodeCircle_.setOutlineColor(Color::Black);
	}
	else
	{
		nodeCircle_.setOutlineColor(Color::Red);
	}
	if (node == selectedNode_)
	{
		nodeCircle_.setFillColor(Color::Green);
	}
	else
	{
		nodeCircle_.setFillColor(Color::White);
	}
	window_.draw(nodeCircle_);

	auto bounds = valueText_.getGlobalBounds();
	valueText_.setPosition(x - bounds.width / 2, y - bounds.height);
	valueText_.setString(to_string(node->key));
	window_.draw(valueText_);


	// t.setPosition(sf::Vector2f(x, y));

/*    sf::VertexArray line(sf::Lines, 2); //or sf::LineStrip
	line[0].position = sf::Vector2f(pX, y - 64);
	line[0].color = line_color;
	line[1].position = sf::Vector2f(x, y);
	line[1].color = line_color;*/

	// if (height > 0) { window.draw(line); }
	// window.draw(t);
	drawTree(node->left, x, height + 1, -1);
	drawTree(node->right, x, height + 1, 1);
}

template<typename T>
void TreeVisualization<T>::draw()
{
	window_.draw(deleteButton_.getBox());
	window_.draw(deleteButton_.getText());
	window_.draw(insertButton_.getBox());
	window_.draw(insertButton_.getText());
	window_.draw(searchButton_.getBox());
	window_.draw(searchButton_.getText());


	window_.draw(nodeKeyInput_.getBox());
	window_.draw(nodeKeyInput_.getText());

	treeHeight = tree_.getHeight(tree_.getRoot());
	drawTree(tree_.getRoot());
}
#endif  // TreeVisualization_RBTree_H_