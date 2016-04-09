#include "call_data"

namespace qua
{
    namespace trace
    {
        call::data::data(const wchar_t* name, const wchar_t* file, long long line)
            : m_name(name), m_file(file), m_line(line)
        {
        }

        const wchar_t* call::data::get_name() const
        {
            return m_name.c_str();
        }

        const wchar_t* call::data::get_file() const
        {
            return m_file.c_str();
        }

        long long call::data::get_line() const
        {
            return m_line;
        }
    }
}
