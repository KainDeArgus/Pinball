#include "Library.h"
#include "menu.h"

int main() {
	RenderWindow window(VideoMode(width, height), "Pinball", Style::Fullscreen);
	window.setFramerateLimit(60);

	menu(window);
}