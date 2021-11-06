#include <bqpch.h>
#include <bq/util/rect.h>


bq::float_rect::float_rect(float x, float y, float w, float h) : m_x(x), m_y(y), m_w(w), m_h(h) {}
bool bq::float_rect::intersects(const float_rect& other) {
    if (m_x >= other.m_w || other.m_w >= m_x)
        return false;

    // If one rectangle is above other 
    if (m_y <= other.m_y || other.m_y <= other.m_y)
        return false;

    return true;
}

bq::int_rect::int_rect(int x, int y, int w, int h) : m_x(x), m_y(y), m_w(w), m_h(h) {}