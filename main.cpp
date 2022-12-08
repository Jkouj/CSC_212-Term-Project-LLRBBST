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
    Txr slideTxrs[46];
    Txr textfieldBGTxrs[5];
    Txr diagram1[55];
    int diagram1Durations[55] = {100,50,100,50,50,50,200,50,50,50,
                                50,50,50,50,100,500,500,130,500,250,
                                500,50,50,50,500,50,50,50,500,50,
                                100,50,50,50,200,50,50,50,50,50,
                                50,50,100,500,150,100,400,50,50,
                                50,50,2500,500,100,100};
    Txr diagram2[55];
    int diagram2Durations[55] = {50,50,50,50,50,
                                50,50,500,500,500,
                                450,500,500,500,500,
                                500,250,100,100,100,
                                100,100,100,100,100,
                                100,100,150,500,130,
                                500,400,450,500,500,
                                500,500,500,500,500,
                                500,300,100,100,100,
                                100,100,500,400,100,
                                100,100,100,100,100};
    Txr diagram3[22];
    int diagram3Durations[22] = {50,50,50,50,50,50,50,500,500,450,500
                                ,500,500,500,100,500,350,500,500,500,500,500,100};
    Txr diagramInsert[27];
    int diagramInsertDurations[27] = {500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,100};
    Txr diagramDeletion[82];
    int diagramDeletionDurations[82] = {500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,100,500,30,30,30,30,500,30,30,30,
                                        30,500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,100,500,30,30,30,30,500,30,30,30,30,500,500,30,
                                        30,30,30,500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,100,100};
    Txr diagramRotation[17];
    int diagramRotationDurations[17] = {500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,30};
    Txr diagramSearch[29];
    int diagramSearchDurations[29] = {500,30,30,30,30,500,30,30,30,30,500,30,30,30,30,500,100,500,30,30,30,30,500,30,30,30,30,500,100};
    
    static void loadTexture(string path, Txr &texture, int i) {
        texture.loadFromFile(path + to_string(i) + ".jpg");
    }
    static void loadTextureGroup(string path, Txr *textures, int numTextures) {
        Txr temp;
        for (int i = 0; i < numTextures; i++) {
            loadTexture(path, temp, i);
            textures[i] = temp;
        }
    }
    TextureStore() {
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/slides/f", slideTxrs, 46);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldBG/f", textfieldBGTxrs, 5);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/f", diagram1, 55);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram2/f", diagram2, 55);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram3/f", diagram3, 22);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramInsert/f", diagramInsert, 27);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramDeletion/f", diagramDeletion, 82);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramRotation/f", diagramRotation, 17);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramSearch/f", diagramSearch, 29);
    }
};



void setCurrentSlide(sf::Sprite &slideBG, Textbox &textbox, int slideIndex, TextureStore &store, int &currentGif) {
    slideBG.setTexture(store.slideTxrs[slideIndex]);

    if (slideIndex == 1) textbox.setSelected(true);
    else textbox.setSelected(false);

    if (slideIndex == 6) currentGif = 0;
    else if (slideIndex == 9) currentGif = 1;
    else if (slideIndex == 12) currentGif = 2;
    else if (slideIndex == 26) currentGif = 3;
    else if (slideIndex == 27) currentGif = 4;
    else if (slideIndex == 28) currentGif = 5;
    else if (slideIndex == 31) currentGif = 6;
    else currentGif = -1;
}

void positionGif(sf::Sprite &gif, int currentGif) {
    if (currentGif == -1) {
        gif.setPosition({-1000,-1000});
    } else {
        gif.setPosition({500,500});
    }
}

void updateGifFrame(sf::Sprite &gif, int currentGif, TextureStore &store, int &frameIndex) {
    frameIndex++;
    if (currentGif == 0) {
        if (frameIndex == 55) frameIndex = 0;
        gif.setTexture(store.diagram1[frameIndex]);
    } else if (currentGif == 1) {
        if (frameIndex == 55) frameIndex = 0;
        gif.setTexture(store.diagram2[frameIndex]);
    } else if (currentGif == 2) {
        if (frameIndex == 22) frameIndex = 0;
        gif.setTexture(store.diagram3[frameIndex]);
    } else if (currentGif == 3) {
        if (frameIndex == 27) frameIndex = 0;
        gif.setTexture(store.diagramInsert[frameIndex]);
    } else if (currentGif == 4) {
        if (frameIndex == 82) frameIndex = 0;
        gif.setTexture(store.diagramDeletion[frameIndex]);
    } else if (currentGif == 5) {
        if (frameIndex == 17) frameIndex = 0;
        gif.setTexture(store.diagramRotation[frameIndex]);
    } else if (currentGif == 6) {
        if (frameIndex == 29) frameIndex = 0;
        gif.setTexture(store.diagramSearch[frameIndex]);
    } else {
        frameIndex--;
    }
}



int main() {
    // Textures
    TextureStore store = TextureStore();
    // Pixil font
    sf::Font pixilFont;
    pixilFont.loadFromFile("/Users/Joey/CLionProjects/HelloSFML/pixilfont.ttf");
    // Window
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 1280, (sf::VideoMode::getDesktopMode().height / 2) - 900);
    window.create(sf::VideoMode(2560, 1440), "SFML Project");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
    // Sprites
    sf::Sprite slideBG, slideGif;
    int slideIndex = 0;
    int gifFrameIndex = 0;
    int currentGif = -1;
    // Textbox
    Textbox textbox(sf::Color::Black, 50, true);
    textbox.setFont(pixilFont);
    textbox.setPosition({0, 0});
    // Display first slide
    setCurrentSlide(slideBG, textbox, slideIndex, store);
    positionGif(slideGif, slideIndex);
    // Update
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    // Closed window
                    cout << "Window was closed. :/" << endl;
                    window.close();
                case sf::Event::KeyPressed:
                    // Pressed a key
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        // Next slide
                        if (slideIndex != 45) {
                            slideIndex++;
                            setCurrentSlide(slideBG, textbox, slideIndex, store, currentGif);
                            positionGif(slideGif, currentGif);
                            gifFrameIndex = 0;
                            clock.restart();
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                        // Prev slide
                        if (slideIndex != 0) {
                            slideIndex--;
                            setCurrentSlide(slideBG, textbox, slideIndex, store, currentGif);
                            positionGif(slideGif, currentGif);
                            gifFrameIndex = 0;
                            clock.restart();
                        }
                    }
                default:
                    break;
            }
            if (clock.getElapsedTime.asMilliseconds >= 100) {
                updateGifFrame(slideGif, currentGif, store, gifFrameIndex);
                clock.restart();
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(slideBG);
        window.draw(slideGif);
        textbox.drawTo(window);
        window.display();
    }
}
