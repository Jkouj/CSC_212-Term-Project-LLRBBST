#include <iostream>
#include <SFML/Graphics.hpp>
//#include "Textbox.h"
//#include "Button.h"
#include <vector>
#include <string>
using Txr = sf::Texture;

class TextureStore {
public:
    Txr boxTxr;
    Txr slideTxrs[46];
    Txr errorTxrs[4];
    Txr buttonTxrs[18];
    Txr textfieldBGTxrs[5];
    Txr diagram1[57];
    Txr diagram2[55];
    Txr diagram3[22];
    Txr diagramInsert[27];
    Txr diagramDeletion[82];
    Txr diagramRotation[17];
    Txr diagramSearch[29];
    Txr textfieldOpenGifs[20];
    Txr textfieldCloseGifs[15];
    Txr textfieldPromptGifs[56];

    void loadTexture(std::string path, Txr &texture,int i) {
        texture.loadFromFile(path + std::to_string(i) + ".jpg");
        // if loading failed, print error message and exit(0)
    }


    void loadTextureGroup(std::string path, Txr *textures, int numTextures) {
        Txr temp;
        for (int i = 0; i < numTextures; i++) {
            loadTexture(path, temp, i);
            textures[i] = temp;
        }
    }
    void load() {
        //loadTexture("/Users/Joey/CLionProjects/HelloSFML/gifs/images/elementBox.png", boxTxr);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/slides/f", slideTxrs, 46);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/errors/f", errorTxrs, 4);//
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/buttons/f", buttonTxrs, 18);//
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldBG/f", textfieldBGTxrs, 5);//
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram1/f", diagram1, 57);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram2/f", diagram2, 55);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagram3/f", diagram3, 22);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramInsert/f", diagramInsert, 27);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramDeletion/f", diagramDeletion, 82);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramRotation/f", diagramRotation, 17);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/diagramSearch/f", diagramSearch, 29);
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldOpen/f", textfieldOpenGifs, 20);//20
        loadTextureGroup("/Users/Joey/CLionProjects/HelloSFML/gifs/images/textFieldClose/f", textfieldCloseGifs, 15);//15
        //loadTextureGroup("", textfieldPromptGifs, 56);
    }
};

void setCurrentSlide(sf::Sprite &slideBG, sf::Sprite &slideGif, int slideIndex, TextureStore &textureStore) {
    slideBG.setTexture(textureStore.slideTxrs[slideIndex]);
    // if slideIndex matches a slide displaying a gif, set slideGif's position, size, textures
    // need a repeating timer that takes a vector of durations
    // need to invalidate timer when slide changes
    // probably only need 1 timer, since I don't want 2 animations playing at once
}

bool isHovering(sf::Sprite &sprite, sf::RenderWindow &window) {
    float x = (float)sf::Mouse::getPosition(window).x;
    float y = (float)sf::Mouse::getPosition(window).y;
    float up = sprite.getPosition().y;
    float left = sprite.getPosition().x;
    float spriteX = sprite.getPosition().x;
    float spriteY = sprite.getPosition().y;
    float down = spriteX + sprite.getLocalBounds().height;
    float right = spriteY + sprite.getLocalBounds().width;
    return (x < right && x > left && y < down && y > up);
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
    window.create(sf::VideoMode(2560, 1440), "SFML Project");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);

    //create sprites
    sf::Sprite slideBG, slideGif;
    int slideIndex = 0;
    setCurrentSlide(slideBG, slideGif, slideIndex, textureStore);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (slideIndex != 45) {
                            slideIndex++;
                            setCurrentSlide(slideBG, slideGif, slideIndex, textureStore);
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                             sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
                        if (slideIndex != 0) {
                            slideIndex--;
                            setCurrentSlide(slideBG, slideGif, slideIndex, textureStore);
                        }
                    }
            }
        }
        window.clear(sf::Color(0, 0, 0, 255));
        window.draw(slideBG);
        window.display();
    }
}
