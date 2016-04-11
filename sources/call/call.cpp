#include "call_data"
#include <deque>

namespace qua
{
    namespace trace
    {
        call::call(const char* name, const char* file, long long line)
            : m_data(std::make_shared<call::data>(name, file, line))
        {
            data::get_calls().push_front(*this);
        }

        call::~call()
        {
            data::get_calls().pop_front();
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

        const call& call::stack::get_call(size_t offset)
        {
            size_t num_of_calls = data::get_calls().size();
            if (!num_of_calls)
                throw std::length_error("No call stack initialized for current thread to trace.");
            if (offset >= num_of_calls)
                throw std::out_of_range("Unable to get call with offset specified from call stack.");
            return data::get_calls()[offset];
        }
    }
}
