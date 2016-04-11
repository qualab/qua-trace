#include <iostream>
#include <qua/trace/call>

void show_last_traced(const char* expected_name, const char* expected_file,
                      long long expected_line, size_t call_offset = 0)
{
    auto& call = qua::trace::call::stack::get_call();
    std::cout << "Current call:\n"
        " > File: " << call.get_file() << " (expected: '" << expected_file << "');\n"
        " > Function: " << call.get_name() << " (expected: '" << expected_name << "');\n"
        " > Line: " << call.get_line() << "(expected: " << expected_line << ")\n"
        << std::endl;

}

void inner()
{
    QUA_TRACE_CALL; long long same_line = __LINE__;
    show_last_traced(__func__, __FILE__, __LINE__);
}

int main(int argc, char* argv[])
{
    inner();
    return 0;
}
