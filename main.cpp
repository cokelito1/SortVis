#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>
#include <cstdlib>
#include <iostream>

#include "SelectionSort.h"
#include "BubbleSort.h"
#include "MergeSort.h"
#include "RadixSort.h"

int main(int argc, char **argv) {
	unsigned int width = 1366;
	unsigned int heigth = 768;

	if (argc < 3) {
		std::cout << argv[0] << " <width> <heigth>" << std::endl;
		return -1;
	}
	else {
		width = std::stoi(argv[1]);
		heigth = std::stoi(argv[2]);
	}

	time_t seed = time(NULL);
	std::cout << "Seed: " << seed << std::endl;
	srand(seed);
	std::vector<sf::RectangleShape> Lines(width);

	int j = 0;
	for (auto& i : Lines) {
		i.setSize(sf::Vector2f(1.0f, (float)(rand() % heigth) + 1));
		i.setPosition(sf::Vector2f((float)j, 0.0f));
		j++;
	}

	unsigned long long Comparisons = 0;
	auto Comp = [&Comparisons](sf::RectangleShape& s1, sf::RectangleShape& s2) {
		Comparisons++;
		if (s1.getSize().y > s2.getSize().y) {
			return false;
		}
		return true;
	};

	auto Swap = [](size_t IndexOne, size_t IndexTwo, std::vector<sf::RectangleShape>& lines) {
		float tmp = lines[IndexOne].getSize().y;
		lines[IndexOne].setSize(sf::Vector2f(lines[IndexOne].getSize().x, lines[IndexTwo].getSize().y));
		lines[IndexTwo].setSize(sf::Vector2f(lines[IndexTwo].getSize().x, tmp));
	};

	int sel;
	std::cout << "(1): Radix Sort\n(2): Bubble Sort\n(3) Merge Sort\n(4) Selection Sort\n";
	std::cin >> sel;

	Sorter<sf::RectangleShape>* sort;
	switch (sel)
	{
	case 1:
		sort = new RadixSort<sf::RectangleShape>;
		break;
	case 2:
		sort = new BubbleSort<sf::RectangleShape>;
		break;
	case 3:
		sort = new MergeSort<sf::RectangleShape>;
		break;
	case 4:
		sort = new SelectionSort<sf::RectangleShape>;
		break;
	default:
		sort = new RadixSort <sf::RectangleShape>;
		break;
	}

	//rSort.Sort(Comp, Lines, Swap);

	bool Sorting = true;
	bool Sorted = false;

	sf::RenderWindow w(sf::VideoMode(width, heigth), "wea", sf::Style::Fullscreen);
	sf::Font f;
	f.loadFromFile("Lato-Black.ttf");

	sf::Text text;
	text.setPosition(50, w.getSize().y - 40);
	text.setFont(f);
	text.setCharacterSize(12);

	sf::Clock clock;
	sf::Clock total;
	float SortTime;
	while (w.isOpen()) {
		std::string data = sort->GetName() + " Comparisons ";
		sf::Event evt;
		while (w.pollEvent(evt)) {
			switch (evt.type)
			{
			case sf::Event::Closed:
				w.close();
				break;
			case sf::Event::KeyPressed:
				if (evt.key.code == sf::Keyboard::Escape) {
					w.close();
				}
				break;
			default:
				break;
			}
		}

		w.clear();
		for (auto& i : Lines) {
			w.draw(i);
		}
		w.draw(text);
		w.display();

		if (sort->Step(Comp, Lines, Swap) && !Sorted) {
			for (auto& i : Lines) {
				i.setFillColor(sf::Color::Green);
			}
			Sorting = false;
			Sorted = true;
			SortTime = total.getElapsedTime().asSeconds();
			std::cout << "finished you motherfucker in: " << SortTime << std::endl;
		}

		data.append(std::to_string(Comparisons));
		data.append(", Frame time: ");
		data.append(std::to_string(clock.restart().asMilliseconds()));
		data.append("ms");
		data.append(", Elapsed time: ");
		if (Sorting) {
			data.append(std::to_string(total.getElapsedTime().asSeconds()));
		}
		else {
			data.append(std::to_string(SortTime));
		}
		text.setString(data);
	}

	delete sort;
	return 0;
}