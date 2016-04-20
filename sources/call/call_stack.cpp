/// Implementation of call stack internal mechanisms

#include "call_stack"
#include <stdexcept>
#include <algorithm>

namespace trace
{
    namespace
    {
        // thread local storage of traced calls
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

    void call::stack::each(const call::stack::handler_type& handler)
    {
        std::for_each(tl_calls.begin(), tl_calls.end(), handler);
    }

    call::stack::iterator call::stack::begin()
    {
        return call::stack::iterator(call::stack::iterator::data(tl_calls.begin()));
    }

    call::stack::iterator call::stack::end()
    {
        return call::stack::iterator(call::stack::iterator::data(tl_calls.end()));
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

    call::stack::iterator::iterator(call::stack::iterator::data&& new_data)
        : m_data(new(m_storage) call::stack::iterator::data(std::move(new_data)))
    {
    }

    call::stack::iterator::iterator(const call::stack::iterator& another)
        : m_data(new(m_storage) call::stack::iterator::data(*another.m_data))
    {
    }

    call::stack::iterator::iterator(call::stack::iterator&& temporary)
        : m_data(new(m_storage) call::stack::iterator::data(std::move(*temporary.m_data)))
    {
    }

    call::stack::iterator::~iterator()
    {
        m_data->~data();
    }

    call::stack::iterator& call::stack::iterator::operator = (const call::stack::iterator& another)
    {
        m_data->get_reference() = another.m_data->get_value();
        return *this;
    }

    call::stack::iterator& call::stack::iterator::operator = (call::stack::iterator&& temporary)
    {
        m_data->get_reference() = std::move(temporary.m_data->get_reference());
        return *this;
    }

    call::stack::iterator& call::stack::iterator::operator ++ ()
    {
        ++m_data->get_reference();
        return *this;
    }

    call::stack::iterator& call::stack::iterator::operator -- ()
    {
        --m_data->get_reference();
        return *this;
    }

    call::stack::iterator call::stack::iterator::operator ++ (int)
    {
        iterator result = *this;
        ++m_data->get_reference();
        return result;
    }

    call::stack::iterator call::stack::iterator::operator -- (int)
    {
        iterator result = *this;
        --m_data->get_reference();
        return result;
    }

    call::stack::iterator call::stack::iterator::operator + (size_t delta) const
    {
        iterator result = *this;
        return result += delta;
    }

    call::stack::iterator call::stack::iterator::operator - (size_t delta) const
    {
        iterator result = *this;
        return result -= delta;
    }

    size_t call::stack::iterator::operator - (const call::stack::iterator& another) const
    {
        return m_data->get_value() - another.m_data->get_value();
    }

    call::stack::iterator& call::stack::iterator::operator += (size_t delta)
    {
        m_data->get_reference() += delta;
        return *this;
    }

    call::stack::iterator& call::stack::iterator::operator -= (size_t delta)
    {
        m_data->get_reference() -= delta;
        return *this;
    }

    bool call::stack::iterator::operator == (const call::stack::iterator& another) const
    {
        return m_data->get_value() == another.m_data->get_value();
    }

    bool call::stack::iterator::operator != (const call::stack::iterator& another) const
    {
        return m_data->get_value() != another.m_data->get_value();
    }

    bool call::stack::iterator::operator <= (const call::stack::iterator& another) const
    {
        return m_data->get_value() <= another.m_data->get_value();
    }

    bool call::stack::iterator::operator >= (const call::stack::iterator& another) const
    {
        return m_data->get_value() >= another.m_data->get_value();
    }

    bool call::stack::iterator::operator < (const call::stack::iterator& another) const
    {
        return m_data->get_value() < another.m_data->get_value();
    }

    bool call::stack::iterator::operator > (const call::stack::iterator& another) const
    {
        return m_data->get_value() > another.m_data->get_value();
    }

    const call& call::stack::iterator::operator * () const
    {
        return *m_data->get_value();
    }

    const call& call::stack::iterator::operator [] (int offset) const
    {
        return m_data->get_value()[offset];
    }

    const call* call::stack::iterator::operator -> () const
    {
        return &*m_data->get_value();
    }

    call::stack::iterator::data::data(call::stack::iterator::data::value_type value)
        : m_value(value)
    {
    }

    call::stack::iterator::data::value_type call::stack::iterator::data::get_value() const
    {
        return m_value;
    }

    call::stack::iterator::data::value_type& call::stack::iterator::data::get_reference()
    {
        return m_value;
    }
}

/// @author Владимир Керимов
