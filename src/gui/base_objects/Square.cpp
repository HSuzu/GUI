#include "Square.h"

namespace GUI {

Square::Square(
    const glm::vec2 &pos,
    const glm::vec2 &dim,
    const glm::vec4 &color
) : _position(pos),
    _dimension(dim),
    _color(color)
{

}

}
