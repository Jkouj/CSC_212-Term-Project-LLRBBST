#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <vector>
#include <string>
using Txr = sf::Texture;

void loadTexture(string &path, Txr &texture) {
    texture.loadFromFile(path + std::to_string(i) + ".jpg");
    // if loading failed, print error message and exit(0)
}

void loadTextureGroup(string &path, Txr *textures, int numTextures) {
    Txr temp;
    for (int i = 0; i < numTextures; i++) {
        loadTexture(path, temp);
        textures[i] = temp;
    }
}

bool isHovering(sf::Sprite &sprite, sf::RenderWindow &window) {
    float x = (float)sf::Mouse::getPosition(window).x;
    float y = (float)sf::Mouse::getPosition(window).y;
    float up = sprite.getPosition().y;
    float left = sprite.getPosition().x;
    float down = spriteX + sprite.getLocalBounds().height;
    float right = spriteY + sprite.getLocalBounds().width;
    return (x < right && x > left && y < down && y > up);
}

void setCurrentSlide(sf::Sprite &slideBG, sf::Sprite &slideGif, int slideIndex, TextureStore &textureStore) {
    int gifSlides[6] = { 6, 9, 12, 15, 31, 43 };
    for (int i = 0; i < 6; i++) {
        if (slideIndex == diagramSlides[i]) {
            buildDiagram();
            return;
        }
    }
    slideBG.setTexture(textureStore.slideTxrs[slideIndex]);
    // set slideGif texture
}

class TextureStore {
public:
    Txr boxTxr;
    Txr slideTxrs[45];
    Txr errorTxrs[4];
    Txr buttonTxrs[18];
    Txr textfieldBGTxrs[5];
    Txr slide24Gif[3];
    Txr slide28Gif[29];
    Txr slide29Gif[27];
    Txr slide30Gif[82];
    Txr slide34Gif[17];
    Txr textfieldOpenGifs[25];
    Txr textfieldCloseGifs[20];
    Txr textfieldPromptGifs[56];
    void load() {
        loadTexture("", boxTxr);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/slides/slide", slideTxrs, 45);
        loadTextureGroup("", errorTxrs, 4);
        loadTextureGroup("", buttonTxrs, 18);
        loadTextureGroup("", textfieldBGTxrs, 5);
        loadTextureGroup("", slide24Gif, 3);
        loadTextureGroup("", slide28Gif, 29);
        loadTextureGroup("", slide29Gif, 27);
        loadTextureGroup("", slide30Gif, 82);
        loadTextureGroup("", slide34Gif, 17);
        loadTextureGroup("", textfieldOpenGifs, 25);
        loadTextureGroup("", textfieldCloseGifs, 20);
        loadTextureGroup("", textfieldPromptGifs, 56);
    }
}

int main() {
    // Load textures
    TextureStore textureStore = TextureStore();
    textureStore.load();
    // Load pixil font
    sf::Font pixilFont;
    pixilFont.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/pixilfont.ttf");
    // Create window
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 1280, (sf::VideoMode::getDesktopMode().height / 2) - 900);
    window.create(sf::VideoMode(1280, 720), "SFML Project");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
    
    sf::Sprite slideBG, slideGif;
    int slideIndex = 0;
    setCurrentSlide(slideIndex);
    
    Textbox textbox1(sf::Color::Red, 50, false);
    textbox1.setFont(pixilFont);
    textbox1.setPosition({100, 100});
    textbox1.setLimit(true, 10);

//     Button button1(" 4 ", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
//     button1.setPosition({0, 0});
//     button1.setFont(pixilFont);

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
//                        //image.setTexture(gif1);
//                    }
//                    break;

//                case sf::Event::MouseButtonPressed:
//                    if (button1.isHovering(window)){
//                        //image.setTexture(gif2);
//                        std::cout << "You clicked the button" << std::endl;
//                    }

//                case sf::Event::MouseButtonReleased:
//                        if (button1.isHovering(window)){
//                            image.setTexture(gif1);
//                        }
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (current != 45) {
                            current++;
                            setCurrentSlide(currentSlide, slides, image);
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                            sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                        if (current != 0) {
                            current--;
                            setCurrentSlide(currentSlide);
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
