#include "transposition_table.hpp"


transposition_table::transposition_table()
{
    m_invalid_entry.valid = false;
}

void transposition_table::clear()
{
    if(m_table.size() > max_tt_size)
        m_table.clear();
}
void transposition_table::insert(uint64_t hash, tt_entry entry) 
{
    std::lock_guard<std::mutex> lock(m_insertion_mutex);
    m_table[hash] = entry;
}
tt_entry transposition_table::lookup(uint64_t hash, int depth) 
{
    if (m_table.find(hash) != m_table.end()) 
    {
        return m_table[hash];
    }
    return m_invalid_entry;
}
void transposition_table::set_top_move(Move m)
{
    m_top_move = m;
}
Move transposition_table::selected_move() 
{
    return m_top_move;
}