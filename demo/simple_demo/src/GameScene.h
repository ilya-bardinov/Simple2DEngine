#include "simple2dengine/nodes/node.h"
#include "simple2dengine/nodes/canvas/text_node.h"
#include "GridNode.h"
#include "simple2dengine/engine.h"

using namespace simple2dengine;

class GameScene : public simple2dengine::Node
{
    public:
        using Node::Node;
        virtual ~GameScene() { };

        virtual void onCreate() override;
        virtual void onEnter() override;
        virtual void onInput(sf::Event event) override;
        virtual void onUpdate(int deltaInMs) override;
        virtual void onExit() override;
        virtual void onDestroy() override;

    private:
        std::shared_ptr<GridNode> gridNode;
        std::shared_ptr<simple2dengine::TextNode> fpsText;
};
