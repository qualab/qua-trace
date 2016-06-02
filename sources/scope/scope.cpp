﻿/// Implementation of trace scope

#include "scope_data"
#include <deque>

namespace trace
{
    namespace
    {
        thread_local std::deque<scope> scope_stack;
    }

    scope::scope(const std::string& name)
        : m_data(std::make_shared<scope::data>(*this, global(), name))
    {
    }

    scope::scope(scope& owner, const std::string& name)
        : m_data(std::make_shared<scope::data>(*this, owner, name))
    {
    }

    scope::scope()
        : m_data(std::make_shared<scope::data>(*this)) // global scope
    {
    }

    scope& scope::global()
    {
        static scope s_global;
        return s_global;
    }

    scope& scope::local()
    {
        if (scope_stack.empty())
            scope_stack.push_back(global());
        return scope_stack.back();
    }
}

// Unicode signature: Владимир Керимов
