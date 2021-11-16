#include "bqpch.h"
#include "bq/core/astar.h"

using namespace std::placeholders;
 

bq::astar::node::node(bq::v2i coordinates_, std::shared_ptr<node> parent_)
{
    m_parent = parent_;
    m_coordinates = coordinates_;
    m_G = m_H = 0;
}


unsigned bq::astar::node::F() const
{
    return m_G + m_H;
}

bq::astar::pathfinder::pathfinder()
{
    set_diagonal(false);
    m_direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}

void bq::astar::pathfinder::set_size(bq::v2i worldSize_)
{
    m_size = worldSize_;
}

void bq::astar::pathfinder::set_diagonal(bool enable_)
{
    m_directions = (enable_ ? 8 : 4);
}


void bq::astar::pathfinder::add_collision(bq::v2i coordinates_)
{
    m_walls.push_back(coordinates_);
}


std::unique_ptr<std::vector<bq::v2i>> bq::astar::pathfinder::pathfind(bq::v2i source_, bq::v2i target_)
{
    using node_ptr = std::shared_ptr<node>;

    if (detect_collision(target_)) {
        return std::make_unique<std::vector<bq::v2i>>();
    }

    node_ptr current = nullptr;
    std::set<node_ptr> openSet, closedSet;
    openSet.insert(std::make_shared<node>(source_));

    while (!openSet.empty()) {
        current = *openSet.begin();
        for (auto node : openSet) {
            if (node->F() <= current->F()) {
                current = node;
            }
        }

        if (current->m_coordinates == target_) {
            break;
        }

        closedSet.insert(current);
        openSet.erase(std::find(openSet.begin(), openSet.end(), current));

        for (unsigned i = 0; i < m_directions; ++i) {
            bq::v2i newCoordinates(current->m_coordinates + m_direction[i]);
            if (detect_collision(newCoordinates) ||
                find_node(closedSet, newCoordinates)) {
                continue;
            }

            unsigned totalCost = current->m_G + ((i < 4) ? 10 : 14);

            std::shared_ptr<node> successor = find_node(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = std::make_shared<node>(newCoordinates, current);
                successor->m_G = totalCost;
                successor->m_H = get_heuristic(successor->m_coordinates, target_);
                openSet.insert(successor);
            }
            else if (totalCost < successor->m_G) {
                successor->m_parent = current;
                successor->m_G = totalCost;
            }
        }
    }
    auto path = std::make_unique < std::vector < bq::v2i > >();
    while (current != nullptr) {
        path->push_back(current->m_coordinates);
        current = current->m_parent;
    }
    return std::move(path);
}

std::shared_ptr<bq::astar::node> bq::astar::pathfinder::find_node(std::set < std::shared_ptr<node> > & nodes_, bq::v2i coordinates_)
{
    for (auto node : nodes_) {
        if (node->m_coordinates == coordinates_) {
            return node;
        }
    }
    return nullptr;
}


unsigned bq::astar::pathfinder::get_heuristic(bq::v2i source_, bq::v2i target_)
{
    auto delta = std::move(get_delta(source_, target_));
    return static_cast<unsigned>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

bq::v2i bq::astar::pathfinder::get_delta(bq::v2i source_, bq::v2i target_)
{
    return{ std::abs(static_cast<int>(source_.x) - static_cast<int>(target_.x)),  abs(static_cast<int>(source_.y) - static_cast<int>(target_.y)) };
}

bool bq::astar::pathfinder::detect_collision(bq::v2i coordinates_)
{
    if (coordinates_.x < 0 || coordinates_.x >= m_size.x ||
        coordinates_.y < 0 || coordinates_.y >= m_size.y ||
        std::find(m_walls.begin(), m_walls.end(), coordinates_) != m_walls.end()) {
        return true;
    }
    return false;
}