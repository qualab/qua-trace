#include "call_data"

namespace qua
{
    namespace trace
    {
        call::call(const char* name, const char* file, long long line)
            : m_data(std::make_shared<call::data>(name, file, line))
        {
        }

        call::~call()
        {
        }

        const char* call::get_name() const
        {
            return m_data->get_name();
        }

        const char* call::get_file() const
        {
            return m_data->get_file();
        }

        long long call::get_line() const
        {
            return m_data->get_line();
        }
    }
}
