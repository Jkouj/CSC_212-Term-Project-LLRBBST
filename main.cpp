#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include "Button.h"
#include <vector>
#include <string>
using namespace std;
using Txr = sf::Texture;


class Timer {
public:
    void startTimer() {
        m_StartTime = std::chrono::system_clock::now();
        m_bRunning = true;
    }
    void stopTimer() {
        m_EndTime = std::chrono::system_clock::now();
        m_bRunning = false;
    }
    double elapsedMilliseconds() {
        std::chrono::time_point<std::chrono::system_clock> endTime;
        if (m_bRunning) endTime = std::chrono::system_clock::now();
        else endTime = m_EndTime;
        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
    }
private:
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;
    bool m_bRunning = false;
};

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

void setCurrentSlide(sf::Sprite &slideBG, sf::Sprite &slideGif, int slideIndex, TextureStore &textureStore, sf::Sprite &textfieldBG, Textbox &textfield, sf::Sprite &appendButton, sf::Sprite &popButton, sf::Sprite &insertButton, sf::Sprite &deleteButton, sf::Sprite &accessButton, sf::Sprite &removeButton, sf::Sprite &errorPopup, int &currentDiagram) {
    // invalidate animation timer
    slideBG.setTexture(textureStore.slideTxrs[slideIndex]);
    if (slideIndex == 6) {
        currentDiagram = 1;
    } else if (slideIndex == 9) {
        currentDiagram = 2;
    } else if (slideIndex == 12) {
        currentDiagram = 3;
    } else if (slideIndex == 15) {
        currentDiagram = 4;
    } else if (slideIndex == 31) {
        currentDiagram = 5;
    } else if (slideIndex == 43) {
        currentDiagram = 6;
    } else {
        currentDiagram = 0;
        if (slideIndex == 23) {
            slideGif.resize(60, 59);
            slideGif.setPosition(68, 0);
            animate(slideGif, textureStore.slide24, textureStore.slide24Times);
        } else if (slideIndex == 27) {
            slideGif.resize(20, 25);
            slideGif.setPosition(108, 0);
            animate(slideGif, textureStore.slide28, textureStore.slide28Times);
        } else if (slideIndex == 28) {
            slideGif.resize(20, 35);
            slideGif.setPosition(108, 0);
            animate(slideGif, textureStore.slide29, textureStore.slide29Times);
        } else if (slideIndex == 29) {
            slideGif.resize(20, 35);
            slideGif.setPosition(108, 0);
            animate(slideGif, textureStore.slide30, textureStore.slide30Times);
        } else if (slideIndex == 33) {
            slideGif.resize(25, 35);
            slideGif.setPosition(103, 0);
            animate(slideGif, textureStore.slide34, textureStore.slide34Times);
        } else {
            // disable slideGif
        }
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
    
    Textbox textbox1(sf::Color::Red, 50, false);
    textbox1.setFont(pixilFont);
    textbox1.setPosition({100, 100});
    textbox1.setLimit(true, 10);

    Button appendButton("append", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    Button popButton("pop", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    Button insertButton("insert", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    Button deleteButton("delete", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    Button accessButton("access", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    Button searchButton("search", {80, 80}, 20, sf::Color::Black, sf::Color::Black);
    appendButton.setPosition({0, 0});
    appendButton.setFont(pixilFont);
    
    int currentDiagram = 0;
    
    setCurrentSlide(slideBG, slideGif, slideIndex, textureStore, textfieldBG, textfield, appendButton, popButton, insertButton, deleteButton, ccessButton, removeButton, errorPopup, currentDiagram);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                case sf::Event::TextEntered:
                    textbox1.typed(event);
                    break;
                case sf::Event::MouseButtonPressed:
                    if (currentDiagram == 1) {
                        if (isHovering(appendButton, window)) {
                            // append
                        } else if (isHovering(popButton, window)) {
                            // pop
                        } else if (isHovering(insertButton, window)) {
                            // insert
                        } else if (isHovering(deleteButton, window)) {
                            // delete
                        } else if (isHovering(accessButton, window)) {
                            // access
                        }
                    } else if (currentDiagram == 2) {
                        if (isHovering(searchButton, window)) {
                            // linear search
                        }
                    } else if (currentDiagram == 3) {
                        if (isHovering(searchButton, window)) {
                            // binary search
                        }
                    } else if (currentDiagram == 4) {
                        if (isHovering(searchButton, window)) {
                            // binary insert
                        }
                    }
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                        sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                        if (current != 45) {
                            current++;
                            setCurrentSlide(currentSlide, slides, image);
                        }
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
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
