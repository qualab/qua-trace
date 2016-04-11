#include "call_data"

namespace qua
{
    namespace trace
    {
        call::data::data(const char* name, const char* file, long long line)
            : m_name(name), m_file(file), m_line(line)
        {
        }

        const char* call::data::get_name() const
        {
            return m_name.c_str();
        }

        const char* call::data::get_file() const
        {
            return m_file.c_str();
        }

        long long call::data::get_line() const
        {
            return m_line;
        }

        std::deque<call>& call::data::get_calls()
        {
            static thread_local std::deque<call> tl_calls;
            return tl_calls;
        }
    }
}
