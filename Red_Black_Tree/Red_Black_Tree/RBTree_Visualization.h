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

const int StartDrawPositionX = 900;
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
	Red_Black_Tree<int> tree_;

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
	//sizes of the window
	width_ = width;
	height_ = height;

	circleRadius = 26;

	selectedNode_ = nullptr;

	//textSettings
	font_.loadFromFile("fonts/tahoma.ttf");
	valueText_.setFont(font_);
	valueText_.setCharacterSize(18);
	valueText_.setFillColor(Color::Black);

	//button boxes
	insertButton_.setProperties(280, 950, 70, 30, "insert");
	searchButton_.setProperties(360, 950, 70, 30, "find");
	deleteButton_.setProperties(440, 950, 70, 30, "delete");
	nodeKeyInput_.setProperties(200, 950, 60, 30, "", Color::Blue);

	//node circles
	nodeCircle_.setRadius(circleRadius);
	nodeCircle_.setOutlineColor(Color::Black);
	nodeCircle_.setOutlineThickness(3);
}

template<typename T>
void TreeVisualization<T>::launch()
{
	Node<T>* temp;
	//the size of the win
	window_.create(VideoMode(width_, height_), "Red_Black_Tree");
	window_.setFramerateLimit(60);

	while (window_.isOpen())
	{
		Event e;
		while (window_.pollEvent(e))
		{
			//closing
			if (e.type == Event::Closed)
			{
				window_.close();
			}
			//if mouseButton pressed
			if (e.type == sf::Event::MouseButtonPressed)
			{
				onMouseEvent(e);
			}
			//if text entered
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
		//update the window
		window_.clear(sf::Color(195, 235, 199));
		draw();
		window_.display();

	}
}

//mouse pressed -case
template<typename T>
void TreeVisualization<T>::onMouseEvent(Event &e)
{
	nodeKeyInput_.looseFocus();
	//left button
	if (e.mouseButton.button == sf::Mouse::Left)
	{
		try {
			//get the coordinates of the place where user clicked
			Vector2i mouse = Mouse::getPosition(window_);

			//define the position and choose a case
			if (deleteButton_.isSelected(mouse))
			{
				tree_.deleteNode(stoi(nodeKeyInput_.getString()));
			}

			if (insertButton_.isSelected(mouse))
			{
				tree_.publicAddNode(stoi(nodeKeyInput_.getString()));
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
			cout << "wrong input, check data\n";
		}
	}
}

template<typename T>
void TreeVisualization<T>::drawTree(Node<T>* node, int pX, int height, int descensionSide)
{
	//node - root
	//px - medium width
	//descensionSide - level
	if (node == nullptr)
		return;

	//change coordinates
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
	if (node->color == BLACK)
	{
		nodeCircle_.setOutlineColor(Color::Black);
	}
	else
	{
		nodeCircle_.setOutlineColor(Color::Red);
	}
	if (node == selectedNode_)
	{
		nodeCircle_.setFillColor(Color::Cyan);
	}
	else
	{
		nodeCircle_.setFillColor(sf::Color(230, 225, 218));
	}
	window_.draw(nodeCircle_);

	auto bounds = valueText_.getGlobalBounds();
	valueText_.setPosition(x - bounds.width / 2, y - bounds.height);
	valueText_.setString(to_string(node->key));
	window_.draw(valueText_);

	drawTree(node->left, x, height + 1, -1);
	drawTree(node->right, x, height + 1, 1);
}

template<typename T>
void TreeVisualization<T>::draw()
{
	//update the window
	window_.draw(deleteButton_.getBox());
	window_.draw(deleteButton_.getText());
	window_.draw(insertButton_.getBox());
	window_.draw(insertButton_.getText());
	window_.draw(searchButton_.getBox());
	window_.draw(searchButton_.getText());


	window_.draw(nodeKeyInput_.getBox());
	window_.draw(nodeKeyInput_.getText());

	//---tree building
	//check the height from the root
	treeHeight = tree_.getHeight(tree_.getRoot()), width_ / 2;
	//draw tree
	drawTree(tree_.getRoot());
}
#endif  // TreeVisualization_RBTree_H_
