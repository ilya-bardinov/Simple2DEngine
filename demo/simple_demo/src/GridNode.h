#include "simple2dengine/nodes/canvas/canvas_node.h"
#include "simple2dengine/engine.h"

using namespace simple2dengine;

class GridNode : public simple2dengine::CanvasNode
{
    public:
        using CanvasNode::CanvasNode;
        virtual ~GridNode() { };

        void generate();

    private:
        const int gridRows = 7;
        const int gridColumns = 5;
        const float gridElementsMargin = 5.0f;
};
