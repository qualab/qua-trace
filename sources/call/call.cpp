#include "call_data"
#include <deque>

namespace qua
{
    namespace trace
    {
        namespace
        {
            thread_local std::deque<call> tl_call_stack;
        }

        call::call(const wchar_t* name, const wchar_t* file, long long line)
            : m_data(std::make_shared<call::data>(name, file, line))
        {
            tl_call_stack.push_front(*this);
        }

        call::~call()
        {
            tl_call_stack.pop_front();
        }

        const wchar_t* call::get_name() const
        {
            return m_data->get_name();
        }

        const wchar_t* call::get_file() const
        {
            return m_data->get_file();
        }

        long long call::get_line() const
        {
            return m_data->get_line();
        }

        const call& call::stack::get_call(size_t offset)
        {
            if (tl_call_stack.empty())
                throw std::length_error("No call stack initialized for current thread to trace.");
            if (offset >= tl_call_stack.size())
                throw std::out_of_range("Unable to get call with offset specified from call stack.");
            return tl_call_stack[offset];
        }
    }
}
