// <trace/scope> implementation

#include <trace/scope>
#include <deque>

QUA_TRACE_BEGIN

namespace
{
    const std::string SCOPE_GLOBAL_NAME = "";
    const std::string SCOPE_GLOBAL_PATH = "";
}

scope::scope(const std::string& name)
    : m_name(name), m_owner(global())
{
    m_owner.add_child(*this);
}

scope::scope(scope& owner, const std::string& name)
    : m_name(name), m_owner(owner)
{
    m_owner.add_child(*this);
}

scope::scope()
    : m_name(SCOPE_GLOBAL_NAME), m_owner(*this)
{
    m_owner.add_child(*this); // global scope contain itself
}

void scope::add_child(scope& child)
{
    const std::string& name = child.get_name();
    auto found = m_map.find(name);
    if (found != m_map.end())
        throw name_conflict(*this, name);
    m_map.insert(name, child);
}

scope& scope::global()
{
    static scope s_global;
    return s_global;
}

const std::string& scope::get_name() const
{
    return m_name;
}

const std::string& scope::get_path() const
{
    return m_path;
}

QUA_TRACE_END

// Unicode signature: Владимир Керимов
