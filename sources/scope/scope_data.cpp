/// Implementation of internal class methods of trace call data

#include "scope_data"

namespace trace
{
    namespace
    {
        const std::string GLOBAL_NAME = "";
        const std::string GLOBAL_PATH = "scope:";
        const std::string PATH_SEPARATOR = "/";
        const std::string GLOBAL_FULL_NAME = GLOBAL_PATH;
    }

    scope::data::data(scope& self)
        : m_self(self),
          m_owner(self),
          m_name(GLOBAL_NAME),
          m_path(GLOBAL_PATH),
          m_full_name(GLOBAL_FULL_NAME)
    {
    }

    scope::data::data(scope& self, scope& owner, const std::string& name)
        : m_self(self),
          m_owner(owner),
          m_name(name),
          m_path(owner.get_full_name() + PATH_SEPARATOR),
          m_full_name(m_path + m_name)
    {
    }

    const std::string& scope::data::get_name() const
    {
        return m_name;
    }

    const std::string& scope::data::get_path() const
    {
        return m_path;
    }

    const std::string& scope::data::get_full_name() const
    {
        return m_full_name;
    }
}

// Unicode signature: Владимир Керимов
