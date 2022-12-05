#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <vector>
#include <string>
using namespace std;
using Txr = sf::Texture;


class TextureStore {
public:
    Txr slideBGs[45] = {};
    Txr slide24[3] = {};
    Txr slide28[29] = {};
    Txr slide29[27] = {};
    Txr slide30[82] = {};
    Txr slide34[17] = {};
    int slide24Times[3] = {1000, 1000, 1000};
    int slide28Times[29] = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
    int slide29Times[27] = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
    int slide30Times[82] = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
    int slide34Times[17] = { 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 25, 25, 25, 25, 500, 100 };
    TextureStore() {
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/slides/slide", slideBGs, 45);
        loadTextureGroup("", slide24, 3);
        loadTextureGroup("", slide28, 29);
        loadTextureGroup("", slide29, 27);
        loadTextureGroup("", slide30, 82);
        loadTextureGroup("", slide34, 17);
    }
private:
    static void loadTexture(string &path, Txr &texture) {
        texture.loadFromFile(path + ".jpg");
    }
    static void loadTextureGroup(string &path, Txr *textures, int numTextures) {
        Txr temp;
        for (int i = 0; i < numTextures; i++) {
            loadTexture(path, temp);
            textures[i] = temp;
        }
    }
};


void setCurrentSlide(sf::Sprite &slideBG, sf::Sprite &slideGif, int slideIndex, TextureStore &textureStore, Textbox &textfield, Txr *animationTxrs, int *animationTimes) {
    slideBG.setTexture(textureStore.slideBGs[slideIndex]);
    if (slideIndex == 23) {
        slideGif.resize(60, 59);
        slideGif.setPosition(68, 0);
        animate(slideGif, textureStore.slide24, textureStore.slide24Times);
        animationTxrs = textureStore.slide24;
        animationTimes = textureStore.slide24Times;
    } else if (slideIndex == 27) {
        slideGif.resize(20, 25);
        slideGif.setPosition(108, 0);
        animationTxrs = textureStore.slide28;
        animationTimes = textureStore.slide28Times;
    } else if (slideIndex == 28) {
        slideGif.resize(20, 35);
        slideGif.setPosition(108, 0);
        animationTxrs = textureStore.slide29;
        animationTimes = textureStore.slide29Times;
    } else if (slideIndex == 29) {
        slideGif.resize(20, 35);
        slideGif.setPosition(108, 0);
        animationTxrs = textureStore.slide30;
        animationTimes = textureStore.slide30Times;
    } else if (slideIndex == 33) {
        slideGif.resize(25, 35);
        slideGif.setPosition(103, 0);
        animationTxrs = textureStore.slide34;
        animationTimes = textureStore.slide34Times;
    } else {
        animationTxrs.clear();
        animationTimes.clear();
    }
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

    sf::Sprite slideBG;
    sf::Sprite slideGif;
    int slideIndex = 0;

    Textbox textfield(sf::Color::Red, 50, false);
    textfield.setFont(pixilFont);
    textfield.setPosition({100, 100});

    Txr *animationTxrs;
    int *animationTimes;

    setCurrentSlide(slideBG, slideGif, slideIndex, textureStore, textfield, animationTxrs, animationTimes);
    if (!animationTxrs.empty()) {
        slideGif.setTexture(animationTxrs[0]);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    textfield.typed(event);
                case sf::Event::MouseButtonPressed:

                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (slideIndex != 45) {
                            slideIndex++;
                            setCurrentSlide(slideBG, slideGif, slideIndex, textureStore, textfield, animationTxrs, animationTimes);
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                        if (slideIndex != 0) {
                            slideIndex--;
                            setCurrentSlide(slideBG, slideGif, slideIndex, textureStore, textfield, animationTxrs, animationTimes);
                        }
                    }
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(slideBG);
        window.draw(slideGif);
//         textfield.drawTo(window);
        window.display();
    }
    cout << "Window was closed" << endl;
    exit(0);
}
