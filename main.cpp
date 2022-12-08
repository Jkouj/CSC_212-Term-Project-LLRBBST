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
    Txr boxTxr;
    Txr slideTxrs[46];
    Txr errorTxrs[4];
    Txr buttonTxrs[18];
    Txr textfieldBGTxrs[5];
    Txr diagram1[55];
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
                                100,100,100,100,100}
    Txr diagram3[22];
    Txr diagramInsert[27];
    Txr diagramDeletion[82];
    Txr diagramRotation[17];
    Txr diagramSearch[29];
    Txr textfieldOpenGifs[20];
    Txr textfieldCloseGifs[15];
    
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
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/errors/f", errorTxrs, 4);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/buttons/f", buttonTxrs, 18);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldBG/f", textfieldBGTxrs, 5);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/f", diagram1, 55);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram2/f", diagram2, 55);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram3/f", diagram3, 22);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramInsert/f", diagramInsert, 27);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramDeletion/f", diagramDeletion, 82);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramRotation/f", diagramRotation, 17);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramSearch/f", diagramSearch, 29);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldOpen/f", textfieldOpenGifs, 20);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldClose/f", textfieldCloseGifs, 15);
    }
};



void setCurrentSlide(sf::Sprite &slideBG, Textbox &textbox, int slideIndex, TextureStore &store) {
    slideBG.setTexture(store.slideTxrs[slideIndex]);
    if (slideIndex == 1) textbox.setSelected(true);
    else textbox.setSelected(false);
}

void positionGif(sf::Sprite &gif, int slideIndex) {
    if (slideIndex==6 || slideIndex==9 || slideIndex==12 || slideIndex==26 || slideIndex==27 || slideIndex==28 || slideIndex==31) {
        gif.setPosition({500,500});
    } else {
        gif.setPosition({-1000,-1000});
    }
}

void updateGifFrame(sf::Sprite &gif, int slideIndex, TextureStore &store, int &frameIndex) {
    frameIndex++;
    int endIndex;
    if (slideIndex == 6) {
        if (frameIndex == 55) frameIndex = 0;
        gif.setTexture(store.diagram1[frameIndex]);
    } else if (slideIndex == 9) {
        if (frameIndex == 55) frameIndex = 0;
        gif.setTexture(store.diagram2[frameIndex]);
    } else if (slideIndex == 11) {
        if (frameIndex == 22) frameIndex = 0;
        gif.setTexture(store.diagram3[frameIndex]);
    } else if (slideIndex == 28) {
        if (frameIndex == 27) frameIndex = 0;
        gif.setTexture(store.diagramInsert[frameIndex]);
    } else if (slideIndex == 29) {
        if (frameIndex == 82) frameIndex = 0;
        gif.setTexture(store.diagramDeletion[frameIndex]);
    } else if (slideIndex == 34) {
        if (frameIndex == 17) frameIndex = 0;
        gif.setTexture(store.diagramRotation[frameIndex]);
    } else if (slideIndex == 31) {
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
    // Textbox
    Textbox textbox(sf::Color::Black, 50, true);
    textbox.setFont(pixilFont);
    textbox.setPosition({0, 0});
    // Display first slide
    setCurrentSlide(slideBG, textbox, slideIndex, store);
    positionGif(slideGif, slideIndex);
    // Update
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
                            setCurrentSlide(slideBG, textbox, slideIndex, store);
                            positionGif(slideGif, slideIndex);
                            gifFrameIndex = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) {
                        // Prev slide
                        if (slideIndex != 0) {
                            slideIndex--;
                            setCurrentSlide(slideBG, textbox, slideIndex, store);
                            positionGif(slideGif, slideIndex);
                            gifFrameIndex = 0;
                        }
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                        // Next gif frame
                        updateGifFrame(slideGif, slideIndex, store, gifFrameIndex);
                    }
                default:
                    break;
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(slideBG);
        window.draw(slideGif);
        textbox.drawTo(window);
        window.display();
    }
}
