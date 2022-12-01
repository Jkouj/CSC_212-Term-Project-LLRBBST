#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"

int main() {
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445,
                              (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(900, 900), "SFML Project");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    sf::Texture gif;
    gif.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/diagram1.jpg");
    if (!gif.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/diagram1.jpg")) {
        std::cout << "cant load texture";
    }

    sf::Sprite image;
    image.setTexture(gif);

    sf::Font arial;
    arial.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/arial.ttf");
    Textbox textbox1(sf::Color::Red, 15, false);
    textbox1.setFont(arial);
    textbox1.setPosition({100, 100});
    textbox1.setLimit(true, 10);

    Button button1("Click Me!", {200, 50}, 20, sf::Color::Green, sf::Color::Black);
    button1.setPosition({100, 300});
    button1.setFont(arial);

    while (window.isOpen()) {
        sf::Event event;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            textbox1.setSelected(true);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            textbox1.setSelected(false);
        }

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    textbox1.typed(event);
                    break;
                case sf::Event::MouseMoved:
                    if (button1.isHovering(window)) {
                        button1.setBackground(sf::Color::White);
                    } else {
                        button1.setBackground(sf::Color::Green);
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    if (button1.isHovering(window)){
                        std::cout << "You clicked the button" << std::endl;
                    }
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(image);
        textbox1.drawTo(window);
        button1.drawTo(window);
        window.display();
    }
}
