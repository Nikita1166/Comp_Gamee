#include "stdafx.h"
#include "map.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;


int main() {
	setlocale(LC_ALL, "");
	IpAddress ip = IpAddress::getLocalAddress();
	TcpSocket socket;
	Packet packet;
	char type;
	char mode = ' ';
	register int x = 0;
	register int y = 0;
	register int i = 0, j = 0;
	int p = 0, flag = 0;
	int Three_deck = 0, Double_deck = 0, Single_deck = 0;
	char buffer[2000];
	size_t received;
	string text = "connect to: ";

	cout << ip << endl;
	cout << "c -, s -" << endl;
	cin >> type;
	if (type == 's'){
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Serwer";
		mode = 's';

	}
	else if (type == 'c'){
		cout << "new ip:";
		cin >> ip;

		socket.connect(ip, 2000);
		text += "client";
		mode = 'r';

	}
	socket.send(text.c_str(), text.length() + 1);
	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;



	RenderWindow window(sf::VideoMode(928, 448), "Network");


	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);


	while (window.isOpen()){

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();

			}

			if ((event.type == sf::Event::MouseButtonPressed) &&
				(event.key.code == sf::Mouse::Left))	{
				i = 0; j = 0;
				Three_deck = 0;
				Double_deck = 0;
				Single_deck = 0;
				j = floor(pos.x / 32);
				i = floor(pos.y / 32);
				if (Map[i][j] == 't')	{
					for (i = 1; i <= 10; i++)
						for (j = 1; j <= 10; j++)	{
							if (Map[i][j] == '+')
								Map[i][j] = '-';
						}

				label:
					srand(time(0));
					p = rand() % 2;
					if (p == 0)	{
						if (Three_deck < 1)	{
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;

							bool qwer = false;
							for (x = i - 1; x <= i + 1; x++){
								for (y = j - 2; y <= j + 2; y++)	{
									if ((Map[x][y] == '+') || (Map[x][y] == '*'))	{

										goto label;
									}

								}

							}

							x = i;
							for (y = j - 1; y <= j + 1; y++)	{
								Map[x][y] = '+';
							}
							Three_deck++;
							goto label;
						}

						if (Double_deck < 2)	{
							i = 0; j = 0;
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;
							for (x = i - 1; x <= i + 1; x++)
								for (y = j - 1; y <= j + 2; y++)	{
									if ((Map[x][y] == '+') || (Map[x][y] == '*'))
										goto label;
								}
							x = i;
							for (y = j; y <= j + 1; y++)	{
								Map[x][y] = '+';
							}
							Double_deck++;
							goto label;
						}
						if (Single_deck < 3)	{
							i = 0; j = 0;
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;
							if (Map[i][j] == '-')	{
								for (x = i - 1; x <= i + 1; x++)
									for (y = j - 1; y <= j + 1; y++)	{
										if (Map[x][y] == '+')
											goto label;
									}
								Map[i][j] = '+';
								Single_deck++;
							}
							goto label;
						}
					}
					else
					{
						if (Three_deck < 1)	{
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;

							for (x = i - 2; x <= i + 2; x++)
								for (y = j - 1; y <= j + 1; y++)	{
									if ((Map[x][y] == '+') || (Map[x][y] == '*'))
										goto label;
								}

							y = j;
							for (x = i - 1; x <= i + 1; x++)	{
								Map[x][y] = '+';

							}
							Three_deck++;
							goto label;
						}
						if (Double_deck < 2)	{
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;

							for (x = i - 1; x <= i + 2; x++)
								for (y = j - 1; y <= j + 1; y++)	{
									if ((Map[x][y] == '+') || (Map[x][y] == '*'))
										goto label;
								}
							y = j;
							for (x = i; x <= i + 1; x++)	{
								Map[x][y] = '+';
							}
							Double_deck++;
							goto label;
						}
						if (Single_deck < 3)	{
							srand(time(0));
							i = 1 + rand() % 9;
							j = 1 + rand() % 9;
							if (Map[i][j] == '-')	{
								for (x = i - 1; x <= i + 1; x++)
									for (y = j - 1; y <= j + 1; y++)	{
										if (Map[x][y] == '+')
											goto label;
									}
								Map[i][j] = '+';
								Single_deck++;
							}
							goto label;
						}
					}
				}
			}
			window.clear();
			for (int i = 0; i < HEIGHT_MAP; i++)
				for (int j = 0; j < WIDTH_MAP; j++)	{
					if (Map[i][j] == '*')	s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
					if (Map[i][j] == '=')	s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
					if (Map[i][j] == '1')	s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
					if (Map[i][j] == '2')	s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
					if (Map[i][j] == '3')	s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
					if (Map[i][j] == '4')	s_map.setTextureRect(sf::IntRect(128, 0, 32, 32));
					if (Map[i][j] == '5')	s_map.setTextureRect(sf::IntRect(160, 0, 32, 32));
					if (Map[i][j] == '6')	s_map.setTextureRect(sf::IntRect(192, 0, 32, 32));
					if (Map[i][j] == '7')	s_map.setTextureRect(sf::IntRect(224, 0, 32, 32));
					if (Map[i][j] == '8')	s_map.setTextureRect(sf::IntRect(256, 0, 32, 32));
					if (Map[i][j] == '9')	s_map.setTextureRect(sf::IntRect(288, 0, 32, 32));
					if (Map[i][j] == '0')	s_map.setTextureRect(sf::IntRect(320, 0, 32, 32));
					if (Map[i][j] == 'A')	s_map.setTextureRect(sf::IntRect(32, 32, 32, 32));
					if (Map[i][j] == 'B')	s_map.setTextureRect(sf::IntRect(64, 32, 32, 32));
					if (Map[i][j] == 'C')	s_map.setTextureRect(sf::IntRect(96, 32, 32, 32));
					if (Map[i][j] == 'D')	s_map.setTextureRect(sf::IntRect(128, 32, 32, 32));
					if (Map[i][j] == 'E')	s_map.setTextureRect(sf::IntRect(160, 32, 32, 32));
					if (Map[i][j] == 'F')	s_map.setTextureRect(sf::IntRect(192, 32, 32, 32));
					if (Map[i][j] == 'G')	s_map.setTextureRect(sf::IntRect(224, 32, 32, 32));
					if (Map[i][j] == 'H')	s_map.setTextureRect(sf::IntRect(256, 32, 32, 32));
					if (Map[i][j] == 'I')	s_map.setTextureRect(sf::IntRect(288, 32, 32, 32));
					if (Map[i][j] == 'J')	s_map.setTextureRect(sf::IntRect(320, 32, 32, 32));
					if (Map[i][j] == '-')	s_map.setTextureRect(sf::IntRect(0, 32, 32, 32));
					if (Map[i][j] == 't')	s_map.setTextureRect(sf::IntRect(96, 64, 32, 32));
					if (Map[i][j] == '+')	s_map.setTextureRect(sf::IntRect(0, 64, 32, 32));
					s_map.setPosition(j * 32, i * 32);
					window.draw(s_map);
				}
			if (mode == 's')	{
				socket.receive(packet);
				if (packet >> x >> y){
					cout << x << ":" << y << endl;
				}
			}

			if (mode == 'r')	{
				if ((event.type == sf::Event::MouseButtonPressed) &&
					(event.key.code == sf::Mouse::Left))	{
					x = floor(pos.x / 32);
					y = floor(pos.y / 32);

				}
				packet << x << y;
				socket.send(packet);
				packet.clear();

			}


			window.display();
		}
	}
	return 0;
}
