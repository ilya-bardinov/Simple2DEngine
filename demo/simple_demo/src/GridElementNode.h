#include "simple2dengine/nodes/canvas/sprite_node.h"
#include "simple2dengine/engine.h"

using namespace simple2dengine;

class GridElementNode : public simple2dengine::SpriteNode
{
    public:
        using SpriteNode::SpriteNode;
        virtual ~GridElementNode() { };

        virtual void onInput(sf::Event event) override;

    private:
        bool selected = false;
};
