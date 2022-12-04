//
// Created by Joey Koumjian on 11/30/22.
//
#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
    Button(){};
    Button(std::string text, sf::Vector2f size, int charSize, sf::Color backColor, sf::Color textColor){
        m_text.setString(text);
        m_text.setFillColor(textColor);
        m_text.setCharacterSize(charSize);
        m_button.setSize(size);
        m_inButton.setSize({size.x-10,size.y-10});
        m_button.setFillColor(backColor);
    }

    void setFont(sf::Font &font){
        m_text.setFont(font);
    }

    void setBackground(sf::Color color){
        m_button.setFillColor(color);
    }

    void setTextColor(sf::Color color){
        m_text.setFillColor(color);
    }

    void setPosition(sf::Vector2f position){
        m_button.setPosition(position);
        float X = (position.x + m_button.getLocalBounds().width / 2) - (m_text.getLocalBounds().width / 2);
        float Y = (position.y + m_button.getLocalBounds().height / 2) - (m_text.getLocalBounds().height / 2);
        m_text.setPosition({X+50,Y+50});
        m_inButton.setPosition({position.x+5,position.y+5});
        m_text.setPosition({X,Y});
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(m_button);
        window.draw(m_inButton);
        window.draw(m_text);
    }

    bool isHovering(sf::RenderWindow &window){
        float mouseX = (float)sf::Mouse::getPosition(window).x;
        float mouseY = (float)sf::Mouse::getPosition(window).y;
        float buttonX = m_button.getPosition().x;
        float buttonY = m_button.getPosition().y;
        float buttonXWidth = m_button.getPosition().x + m_button.getLocalBounds().width;
        float buttonYHeight = m_button.getPosition().x + m_button.getLocalBounds().height;

        //if mouse is within button
        if (mouseX < buttonXWidth && mouseX > buttonX && mouseY < buttonYHeight && mouseY > buttonY){
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape m_button;
    sf::RectangleShape m_inButton;
    sf::Text m_text;
};
