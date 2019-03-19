#include "GridElementNode.h"

void GridElementNode::onInput(sf::Event event)
{
    if(event.type == sf::Event::EventType::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Button::Left)
        {
            if(getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
            {
                if(selected)
                {
                    this->setScale(1.0f, 1.0f);
                    this->setColor(sf::Color(255, 255, 255, 255));
                    selected = false;
                }
                else
                {
                    this->setScale(0.9f, 0.9f);
                    this->setColor(sf::Color(255, 255, 255, 128));
                    selected = true;
                }
            }
        }
    }
}
