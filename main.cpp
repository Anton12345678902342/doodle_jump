#include <SFML/Graphics.hpp>
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace sf;
int HeroDirect = 4;
int speed = 0.1;
int ground = 160;

float offsetX = 0, offsetY = 0;

class PLAYER
{

public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;


	PLAYER(Texture& image)
	{
		sprite.setTexture(image);

		dx = dy = 0.1;
	}

	void update(float tim)
	{
		rect.left += dx * tim;

		if (!onGround) dy = dy + 0.0005 * tim;
		rect.top += dy * tim;
		onGround = false;

		if (rect.top > ground)
		{
			rect.top = ground;
			onGround = true;
		}

		if (dx < 0) sprite.setTextureRect(IntRect(0, 0, 100, 100));
		if (dx > 0) sprite.setTextureRect(IntRect(100, 0, 100, 100));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}
};


int main()
{
	RenderWindow window(sf::VideoMode(500, 250), "Doodle Jump!");
	window.setFramerateLimit(120);

	Texture hero;
	hero.loadFromFile("hero/mem.png");
	PLAYER p(hero);

	Texture platform2;
	platform2.loadFromFile("hero/plat.png");

	Texture Youlose;
	Youlose.loadFromFile("hero/you.png");

	Sprite youlose;
	youlose.setTexture(Youlose);
	youlose.setPosition(1000, 1000);

	Sprite plat, plat2;
	plat.setTexture(platform2);
	plat.setPosition(100, -25);
	plat2.setTexture(platform2);
	plat2.setPosition(200, -125);

	Clock clock;

	int HeroY = 0;
	//HeroY = sus.getPosition().y;

	while (window.isOpen() | HeroY < 150)
	{

		float tim = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		tim = tim / 800;

		srand(time(0));

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}



		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			HeroDirect = 1;
			p.dx = -0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			HeroDirect = 2;
			p.dx = 0.1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround)
			{
				HeroDirect = 3;
				p.dy = -0.406;
				p.onGround = false;
			}
		}


		sf::FloatRect spriteBounds = p.sprite.getGlobalBounds();
		sf::FloatRect platBounds = plat.getGlobalBounds();
		sf::FloatRect platBounds2 = plat2.getGlobalBounds();

		plat2.move(0, 0.05 * tim);
		double y2 = plat2.getPosition().y;
		if (y2 >= 250)
		{
			switch (rand() % 5)
			{
			case 0:
				plat2.setPosition(0, -25);
				break;
			case 1:
				plat2.setPosition(50, -25);
				break;
			case 2:
				plat2.setPosition(150, -25);
				break;
			case 3:
				plat2.setPosition(250, -25);
				break;
			case 4:
				plat2.setPosition(325, -25);
				break;
			default:
				break;
			}
		}
		plat.move(0, 0.05 * tim);
		double y = plat.getPosition().y;
		if (y >= 250)
		{
			switch (1 + rand() % 5)
			{
			case 0:
				plat.setPosition(0, -150);
			case 1:
				plat.setPosition(50, -150);
			case 2:
				plat.setPosition(150, -150);
			case 3:
				plat.setPosition(250, -150);
			case 4:
				plat.setPosition(325, -150);
			default:
				break;
			}
		}
		int flag = 0;
		if (spriteBounds.intersects(platBounds))
		{
			p.onGround = true;
			p.sprite.setPosition(p.rect.left - offsetX, p.rect.top - offsetY);
			p.dy = 0;
			if (Keyboard::isKeyPressed(Keyboard::Up) && p.onGround)
			{
				HeroDirect = 3;
				p.dy = -0.406;
				p.onGround = false;
			}
		}
		if (spriteBounds.intersects(platBounds2))
		{
			p.onGround = true;
			p.dy = 0;
			p.sprite.setPosition(p.rect.left - offsetX, p.rect.top - offsetY);
			if (Keyboard::isKeyPressed(Keyboard::Up) && p.onGround)
			{
				HeroDirect = 3;
				p.dy = -0.406;
				p.onGround = false;
			}
		}


		int bama2 = p.sprite.getPosition().y;
		if (bama2 > 150)
		{
			youlose.setPosition(0, -20);
			plat.setPosition(1000, 0);
			plat2.setPosition(1000, 600);
		}

		p.update(tim);

		window.clear(Color::Blue);
		window.draw(p.sprite);
		window.draw(plat);
		window.draw(plat2);
		window.draw(youlose);
		window.display();

	}
}