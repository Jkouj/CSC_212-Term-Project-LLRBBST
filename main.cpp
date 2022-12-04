#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <vector>
#include <string>

#define KEY_LEFT 75
#define KEY_RIGHT 77

bool isOver(sf::Sprite &sprite, sf::RenderWindow &window){
    float mouseX = (float)sf::Mouse::getPosition(window).x;
    float mouseY = (float)sf::Mouse::getPosition(window).y;
    float spriteX = sprite.getPosition().x;
    float spriteY = sprite.getPosition().y;
    float spriteXWidth = sprite.getPosition().x + sprite.getLocalBounds().width;
    float spriteYHeight = sprite.getPosition().x + sprite.getLocalBounds().height;

    //if mouse is within button
    if (mouseX < spriteXWidth && mouseX > spriteX && mouseY < spriteYHeight && mouseY > spriteY){
        return true;
    }
    return false;
}

void getSlides(std::vector<sf::Texture> &slides){
    sf::Texture tempTexture;
    for (int i = 1 ; i < slides.size()+1; i++) {
        tempTexture.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/slides/slide"+std::to_string(i)+".jpg");
        slides[i] = tempTexture;
    }
}

int main() {
    std::vector<sf::Texture> slides(45);
    getSlides(slides);

    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 1280,
                              (sf::VideoMode::getDesktopMode().height / 2) - 900);
    window.create(sf::VideoMode(2560, 1600), "SFML Project");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    sf::Texture gif;
    gif.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/diagram1.jpg");
    sf::Texture gif2;
    gif2.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/diagram12.jpg");
    if (!gif.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/diagram1.jpg")) {
        std::cout << "cant load texture";
    }

    sf::Sprite image;
    int current = 1;
    image.setTexture(slides[current]);


    sf::Font arial;
    arial.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/pixilfont.ttf");
    Textbox textbox1(sf::Color::Red, 50, false);
    textbox1.setFont(arial);
    textbox1.setPosition({100, 100});
    textbox1.setLimit(true, 10);

    Button button1(" 4 ", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    button1.setPosition({0, 0});
    button1.setFont(arial);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
//                case sf::Event::TextEntered:
//                    textbox1.typed(event);
                    break;
//                case sf::Event::MouseMoved:
//                    if (button1.isHovering(window)) {
//                        //image.setTexture(gif2);
//                    } else {
//                        //image.setTexture(gif);
//                    }
//                    break;

//                case sf::Event::MouseButtonPressed:
//                    if (button1.isHovering(window)){
//                        //image.setTexture(gif2);
//                        std::cout << "You clicked the button" << std::endl;
//                    }

//                case sf::Event::MouseButtonReleased:
//                        if (button1.isHovering(window)){
//                            image.setTexture(gif);
//                        }
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                        if (image.getTexture() == &slides[45]) {
                            //nothing
                        } else {
                            current += 1;
                            image.setTexture(slides[current]);
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        if (image.getTexture() == &slides[1]){
                            //nothing
                        }
                        else {
                            current -= 1;
                            image.setTexture(slides[current]);
                        }
                    }
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(image);
        //textbox1.drawTo(window);
        //button1.drawTo(window);
        window.display();
    }
}
