#include "call_data"
#include <deque>

namespace qua
{
    namespace trace
    {
        namespace
        {
            thread_local std::deque<call> tl_calls;
        }

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

        const call& call::stack::get_call(size_t offset)
        {
            size_t num_of_calls = tl_calls.size();
            if (!num_of_calls)
                throw std::length_error("No call stack initialized for current thread to trace.");
            if (offset >= num_of_calls)
                throw std::out_of_range("Unable to get call with offset specified from call stack.");
            return tl_calls[offset];
        }

        call::warden call::stack::push(const call& new_call)
        {
            tl_calls.push_front(new_call);
            return call::warden();
        }

        call::warden::warden()
            : m_pop(true)
        {
        }

        call::warden::warden(call::warden&& temporary)
            : m_pop(temporary.m_pop)
        {
            temporary.m_pop = false; // to avoid pop
        }

        call::warden::~warden()
        {
            if (m_pop)
            {
                tl_calls.pop_front();
            }
        }
    }
}
