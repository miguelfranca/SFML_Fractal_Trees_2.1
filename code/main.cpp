#include <ctime>
#include <cstdio>
#include "node.h"

void transform(node &, const float, const float, const float);
void drawNode(node &current, sf::RenderWindow &window, bool toDraw);
void drawTree(node &n, sf::RenderWindow &window);
node *createTree();
void saveWindow(sf::RenderWindow &window);

sf::Texture texture;

int main() {

	srand(time(NULL));

	node* n = createTree();

	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Fractal Tree (Custom)");

	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - screenWidth) / 2.f, 0));

	drawTree(*n, window);


	int frames = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			else {
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
					delete n;

					n = createTree();

					drawTree(*n, window);
				}
				//
				//if (event.type == sf::Event::MouseWheelMoved) {
				//	float zoom = (event.mouseWheel.delta == 1) ? DEFAULT_ZOOM : 1.f / DEFAULT_ZOOM;
				//	transform(*n, zoom, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				//	minLength_G /= zoom;
				//	drawTree(*n, window);
				//	//printf("\n%d", n->full());
				//}


			}

			
		}
		frames++;
		if (frames % 50 == 0) {
			transform(*n, DEFAULT_ZOOM, sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
			minLength_G /= DEFAULT_ZOOM;
			drawTree(*n, window);
			//saveWindow(window);
		}
	}

	delete n;

	return 0;
}

void transform(node &n, const float zoom, const float mx, const float my) {
	n.X() = (n.X() - mx) / zoom + mx;
	n.Y() = (n.Y() - my) / zoom + my;
	n.length() /= zoom;
	for (unsigned i = 0; i < n.getN(); i++)
		transform(*n[i], zoom, mx, my);
}

float rainbow(float x) {
	return sin(1.f / tan(x));
}
sf::Color color(float x) {
	return sf::Color((sf::Uint8)(rainbow(x - 0.75f) * 255), (sf::Uint8)(rainbow(x - 0.5f) * 255), (sf::Uint8)(rainbow(x - 0.25f) * 255));
}

node *createTree() {
	node* n = new node(1, screenWidth / 2.f, (float)screenHeight, DEFAULT_SIZE / 0.6f);
	n->create_branch(0, DEFAULT_SIZE, -90);
	(*n)[0]->tree(-90);
	/*node* n = new node(0, screenWidth / 2.f, screenHeight/2.f, DEFAULT_SIZE/0.6);
	n->tree(-90);*/
	printf("\n%d", n->full());

	return n;
}

bool isIN(node &n) {
	return n.X() <= screenWidth - border && n.Y() <= screenHeight - border && n.X() >= border && n.Y() >= border;
}

void drawTree(node &n, sf::RenderWindow &window) {
	window.clear();
	drawNode(n, window, isIN(n));
	window.display();
}

void drawNode(node &current, sf::RenderWindow &window, bool toDraw_father) {
	for (unsigned i = 0; i < current.getN(); i++) {
		if (minLength > current[i]->length()) continue;

		//sf::Color col = color(current[i]->length() / minLength_G * DEFAULT_SIZE);
		//sf::Color col = current[i]->length() < minLength_G ? sf::Color(0, 255, 0, 100) : sf::Color(153, 77, 0); //165,42,42
		sf::Color col = sf::Color::White;

		bool toDraw_son = isIN(*current[i]);

		if (toDraw_father || toDraw_son) {
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(current.X(), current.Y()), col),
				sf::Vertex(sf::Vector2f(current[i]->X(), current[i]->Y()), col)
			};
			window.draw(line, 2, sf::Lines);
		}

		if (toDraw_son) {
			if (current[i]->getN() == 0) {
				float angle = 180.f / PI * atan2(current[i]->Y() - current.Y(), current[i]->X() - current.X());
				current[i]->tree(angle);
			}
			drawNode(*current[i], window, toDraw_son);
		}
		else {
			float y = current[i]->Y();
			float x = current[i]->X();
			float Oy;
			float Ox;

			if (y < border)
			{
				Oy = border;
			}
			else {
				if (y < screenHeight - border) {
					Oy = y;
				}
				else {
					Oy = screenHeight - border;
				}
			}

			if (x < border)
			{
				Ox = border;
			}
			else {
				if (x < screenWidth - border) {
					Ox = x;
				}
				else {
					Ox = screenWidth - border;
				}
			}

			if (sqrt((x - Ox)*(x - Ox) + (y - Oy)*(y - Oy)) < dist_factor * current[i]->length()) {
				if (current[i]->getN() == 0) {
					float angle = 180.f / PI * atan2(current[i]->Y() - current.Y(), current[i]->X() - current.X());
					current[i]->tree(angle);
				}
				drawNode(*current[i], window, toDraw_son);
			}
		}
	}
}


void saveWindow(sf::RenderWindow &window) {

	window.display();

	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);
	texture.copyToImage().saveToFile("img_" + std::to_string(time(NULL)) + "_" + std::to_string((int)clock()) + ".jpg");

	window.display();
}
