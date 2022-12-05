#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <vector>
#include <string>
using namespace std;
using Txr = sf::Texture;

void loadTexture(string &path, Txr &texture) {
    texture.loadFromFile(path + std::to_string(i) + ".jpg");
}

void loadTextureGroup(string &path, Txr *textures, int numTextures) {
    Txr temp;
    for (int i = 0; i < numTextures; i++) {
        loadTexture(path, temp);
        textures[i] = temp;
    }
}

class TextureStore {
public:
    Txr box;
    Txr slides[45];
    Txr errors[4];
    Txr buttons[18];
    Txr textfieldBGs[5];
    Txr slide24[3];
    Txr slide28[29];
    Txr slide29[27];
    Txr slide30[82];
    Txr slide34[17];
    Txr textfieldOpen[25];
    Txr textfieldClose[20];
    Txr textfieldPrompt[56];
    int slide24Times[3];
    int slide28Times[29];
    int slide29Times[27];
    int slide30Times[82];
    int slide34Times[17];
    int textfieldOpenTimes[25];
    int textfieldCloseTimes[20];
    int textfieldPromptTimes[56];
    TextureStore() {
        slide24Times = { 1000, 1000, 1000 };
        slide28Times = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
        slide29Times = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
        slide30Times = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
        slide34Times = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
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
};

void animate(sf::Sprite sprite, Txr *textures, int *durations) {
    
}

void setCurrentSlide(sf::Sprite &slideBG, sf::Sprite &slideGif, int slideIndex, TextureStore &textureStore) {
    // invalidate animation timer
    slideBG.setTexture(textureStore.slideTxrs[slideIndex]);
    } else if (slideIndex == 23) {
        slideGif.resize();
        slideGif.setPosition();
        animate(slideGif, textureStore.slide24, textureStore.slide24Times);
    } else if (slideIndex == 27) {
        slideGif.resize();
        slideGif.setPosition();
        animate(slideGif, textureStore.slide28, textureStore.slide28Times);
    } else if (slideIndex == 28) {
        slideGif.resize();
        slideGif.setPosition();
        animate(slideGif, textureStore.slide29, textureStore.slide29Times);
    } else if (slideIndex == 29) {
        slideGif.resize();
        slideGif.setPosition();
        animate(slideGif, textureStore.slide30, textureStore.slide30Times);
    } else if (slideIndex == 33) {
        slideGif.resize();
        slideGif.setPosition();
        animate(slideGif, textureStore.slide34, textureStore.slide34Times);
    } else {
        // make slideGif invisible
    }
}

bool isHovering(sf::Sprite &sprite, sf::RenderWindow &window) {
    float x = (float)sf::Mouse::getPosition(window).x;
    float y = (float)sf::Mouse::getPosition(window).y;
    float up = sprite.getPosition().y;
    float left = sprite.getPosition().x;
    float down = up + sprite.getLocalBounds().height;
    float right = left + sprite.getLocalBounds().width;
    return (x < right && x > left && y < down && y > up);
}

int main() {
    // Load textures
    TextureStore textureStore = TextureStore();
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
    cout << "Window was closed" << endl;
    exit(0);
}
