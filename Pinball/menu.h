#pragma once
#include "constants.h"
#include "Library.h"
#include "Level_1.h"
#include "Level_2.h"
#include "Level_3.h"
#include "Impossible.h"
using namespace sf;

void menu(RenderWindow& window) {

	Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;
	Texture t; t.loadFromFile("Images/H_background.jpg");
	Texture back; back.loadFromFile("Images/back.png");
	Sprite sBack(back); sBack.setPosition((width - 80) / 2, 900);
	t1.loadFromFile("Images/background1.jpg");
	t2.loadFromFile("Images/pinball.png");
	t3.loadFromFile("Images/exit.png");
	t4.loadFromFile("Images/levels.png");
	t5.loadFromFile("Images/1.png");
	t6.loadFromFile("Images/2.png");
	t7.loadFromFile("Images/3.png");
	t8.loadFromFile("Images/Impossible.png");
	t9.loadFromFile("Images/help.png");

	Sprite sBackground(t1), sPinBall(t2), sExit(t3), sLevels(t4), s1(t5), s2(t6), s3(t7), sImpossible(t8), sHelp(t9);

	sPinBall.setPosition((width - 288) / 2, 5);
	sLevels.setPosition((width - 268) / 2, 300);
	sExit.setPosition((width - 266) / 2, 640);
	sHelp.setPosition((width - 224) / 2, 470);
	s1.setPosition((width - 400) / 3 - 50, (height - 254) / 2);
	s2.setPosition((width - 400) / 3 * 2 - 150, (height - 276) / 2);
	s3.setPosition(width - 650, (height - 248) / 2);
	sImpossible.setPosition(width / 2 - 40, 800);

	bool Menu = true;
	int choose(0);

	while (window.isOpen()) {
		window.setMouseCursorVisible(true);

		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}
		if (Menu) {
			if (IntRect((width - 268) / 2, 300, 269, 89).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 11; }
			if (IntRect((width - 266) / 2, 640, 267, 87).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 22; }
			if (IntRect((width - 224) / 2, 470, 267, 87).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 33; }
		}
		switch (choose)
		{
		case 11:

			Menu = false;

			if (!Menu) {
				if (IntRect((width - 400) / 3 - 50, (height - 254) / 2, 170, 254).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 1; }
				if (IntRect((width - 400) / 3 * 2 - 150, (height - 276) / 2, 217, 276).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 2; }
				if (IntRect(width - 650, (height - 248) / 2, 216, 248).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 3; }
				if (IntRect(width / 2 - 40, 800, 80, 80).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { choose = 4; }
				if (IntRect((width - 80) / 2, 900, 280, 280).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { Menu = true; menu(window); }

				switch (choose)
				{
				case 1:
					window.setMouseCursorVisible(false);
					Level_1(window);
					menu(window);
					return void();
					break;
				case 2:
					window.setMouseCursorVisible(false);
					Level_2(window);
					menu(window);
					return void();
					break;
				case 3:
					window.setMouseCursorVisible(false);
					Level_3(window);
					menu(window);
					return void();
					break;
				case 4:
					window.setMouseCursorVisible(false);
					Impossible(window);
					menu(window);
					return void();
					break;
				}
			}
			window.clear();

			window.draw(sBackground);
			window.draw(sPinBall);
			window.draw(sBack);
			window.draw(s1);
			window.draw(s2);
			window.draw(s3);
			window.draw(sImpossible);

			window.display();

			break;
		case 22:
			window.close();
			return void();
			break;
		case 33:
			Menu = false;
			if (!Menu) {
				if (IntRect((width - 80) / 2, 900, 280, 280).contains(Mouse::getPosition(window)) && Mouse::isButtonPressed(Mouse::Left)) { Menu = true; menu(window); }
			}
			sBackground.setTexture(t);

			window.clear();

			window.draw(sBackground);
			window.draw(sBack);

			window.display();

			sBackground.setTexture(t1);
			break;
		}

		if (Menu) {
			window.clear();

			window.draw(sBackground);
			window.draw(sPinBall);
			window.draw(sLevels);
			window.draw(sExit);
			window.draw(sHelp);

			window.display();
		}

	}
}