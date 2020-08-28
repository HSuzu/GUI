#include "Square.h"
#include "utils/gui_utils.h"

namespace GUI {

Square::Square(
    const glm::vec2 &pos,
    const glm::vec2 &dim,
    const glm::vec4 &color
) : _position(pos),
    _dimension(dim),
    _color(color)
{}

void Square::position(float x, float y)
{
    _position.x = x;
    _position.y = y;
}

void Square::dimension(float w, float h)
{
    _dimension.x = w;
    _dimension.y = h;
}

void Square::backgroundColor(const char *color)
{
    _color = Utils::GUI::color(color);
}

}
