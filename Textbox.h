//
// Created by Joey Koumjian on 11/30/22.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {
    public:
    Textbox() {}
    Textbox(sf::Color color, int size, bool selected){
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        m_selected = selected;
        if (selected){
            textbox.setString("_");
        }
        else {
            textbox.setString("");
        }
    }

    void setFont(sf::Font &font){
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f position){
        textbox.setPosition(position);
    }

    void setLimit(bool TF){
        m_hasLimit = TF;
    }

    void setLimit(bool TF, int limit){
        m_limit = limit - 1;
        m_hasLimit = TF;
    }

    void setSelected(bool selected){
        m_selected = selected;
        if (!selected){
            std::string T = text.str();
            std::string newT = "";
            for(int i = 0 ; i < T.length() ; i++){
                newT += T[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText() {
        return text.str();
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(textbox);
    }

    void typed(sf::Event input){
        if (m_selected){
            int charInput = input.text.unicode;
            if (charInput < 128){
                if(m_hasLimit){
                    if(text.str().length() <= m_limit){
                        doInput(charInput);
                    }
                    else if (text.str().length() > m_limit && charInput == DELETE_KEY){
                        deleteEndChar();
                    }
                }
            }
        }
    }

    private:
    sf::Text textbox;
    std::ostringstream text;
    bool m_selected = false;
    bool m_hasLimit = false;
    int m_limit;

    void doInput(int charInput) {
        if (charInput != DELETE_KEY && charInput != ENTER_KEY && charInput != ESCAPE_KEY){
            text << static_cast<char>(charInput);
        }
        else if (charInput == DELETE_KEY){
            if(text.str().length() > 0){
                deleteEndChar();
            }
        }
        textbox.setString(text.str() + "_");
    }

    void deleteEndChar(){
        std::string T = text.str();
        std::string newT = "";
        for(int i = 0 ; i < T.length()-1 ; i++){
            newT += T[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }
};