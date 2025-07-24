#include "Snake.hpp"

Snake::Snake (int x_head, int y_head, direction dir)
    : m_head{ x_head, y_head }, m_dir{ dir }
{
}

void
Snake::consume_fruit(const Fruit &fruit) {
}
