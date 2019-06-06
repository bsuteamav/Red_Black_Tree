#include <iostream>
#include <SFML/Graphics.hpp>
#include "Red_Black_Tree.h"
#include "RBTree_Visualization.h"
#include "Node.h"

using namespace std;
using namespace sf;

int main() {
	TreeVisualization<int> treeVisualization(1800, 1000);

	treeVisualization.launch();

	system("pause");
	return 0;
}
