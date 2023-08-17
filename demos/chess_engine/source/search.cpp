#include "search.hpp"

void pvs_search::signal_stop()
{
    m_stopping = true;
}

pvs_search::pvs_search(int max_sel_depth)
    : m_max_sel_depth(max_sel_depth)
{
    
}