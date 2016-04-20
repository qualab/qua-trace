#include "call_stack"
#include <stdexcept>

namespace qua
{
    namespace trace
    {
        namespace
        {
            thread_local call_storage tl_calls;
        }

        const call& call::stack::get_call(size_t offset)
        {
            if (tl_calls.empty())
                throw std::length_error("No call stack initialized for current thread to trace.");
            if (offset >= tl_calls.size())
                throw std::out_of_range("Unable to get call with offset specified from call stack.");
            return tl_calls[offset];
        }

        call::warden call::stack::push(const call& new_call)
        {
            tl_calls.push_front(new_call);
            return call::warden();
        }

        size_t call::stack::size()
        {
            return tl_calls.size();
        }

        call::stack::const_iterator call::stack::begin()
        {
            return call::stack::const_iterator(call::stack::const_iterator::data(tl_calls.begin()));
        }

        call::stack::const_iterator call::stack::end()
        {
            return call::stack::const_iterator(call::stack::const_iterator::data(tl_calls.end()));
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

        call::stack::const_iterator::const_iterator(call::stack::const_iterator::data&& new_data)
            : m_data(new(m_storage) call::stack::const_iterator::data(std::move(new_data)))
        {
        }

        call::stack::const_iterator::const_iterator(const call::stack::const_iterator& another)
            : m_data(new(m_storage) call::stack::const_iterator::data(*another.m_data))
        {
        }

        call::stack::const_iterator::const_iterator(call::stack::const_iterator&& temporary)
            : m_data(new(m_storage) call::stack::const_iterator::data(std::move(*temporary.m_data)))
        {
        }

        call::stack::const_iterator::~const_iterator()
        {
            m_data->~data();
        }

        call::stack::const_iterator& call::stack::const_iterator::operator ++ ()
        {
            ++m_data->get_reference();
            return *this;
        }

        call::stack::const_iterator& call::stack::const_iterator::operator -- ()
        {
            --m_data->get_reference();
            return *this;
        }

        call::stack::const_iterator call::stack::const_iterator::operator ++ (int)
        {
            const_iterator result = *this;
            ++m_data->get_reference();
            return result;
        }

        call::stack::const_iterator call::stack::const_iterator::operator -- (int)
        {
            const_iterator result = *this;
            --m_data->get_reference();
            return result;
        }

        call::stack::const_iterator call::stack::const_iterator::operator + (size_t delta) const
        {
            const_iterator result = *this;
            return result += delta;
        }

        call::stack::const_iterator call::stack::const_iterator::operator - (size_t delta) const
        {
            const_iterator result = *this;
            return result -= delta;
        }

        size_t call::stack::const_iterator::operator - (const call::stack::const_iterator& another) const
        {
            return m_data->get_value() - another.m_data->get_value();
        }

        call::stack::const_iterator& call::stack::const_iterator::operator += (size_t delta)
        {
            m_data->get_reference() += delta;
            return *this;
        }

        call::stack::const_iterator& call::stack::const_iterator::operator -= (size_t delta)
        {
            m_data->get_reference() -= delta;
            return *this;
        }

        call::stack::const_iterator::data::data(call::stack::const_iterator::data::value_type value)
            : m_value(value)
        {
        }

        call::stack::const_iterator::data::value_type call::stack::const_iterator::data::get_value() const
        {
            return m_value;
        }

        call::stack::const_iterator::data::value_type& call::stack::const_iterator::data::get_reference()
        {
            return m_value;
        }
    }
}
