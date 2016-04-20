#include <trace/call>
#include <iostream>
#include <cstdlib>
#include <conio.h>

void show_last_traced(const char* expected_name, const char* expected_file,
                      long long expected_line, size_t call_offset = 0)
{
    auto& call = qua::trace::call::stack::get_call();
    std::cout << "Current call:\n"
        " > File: '" << call.get_file() << "' (expected: '" << expected_file << "');\n"
        " > Function: '" << call.get_name() << "' (expected: '" << expected_name << "');\n"
        " > Line: " << call.get_line() << " (expected: " << expected_line << ")\n"
        << std::endl;

}

void inner()
{
    QUA_TRACE_CALL; long long same_line = __LINE__;
    show_last_traced(__func__, __FILE__, same_line);
}

void outer()
{
    QUA_TRACE_CALL; long long same_line = __LINE__;
    show_last_traced(__func__, __FILE__, same_line);
    inner();
}

void press_any_key()
{
    std::cout << "\n > Press any key... ";
    _getch();
}

int main(int argc, char* argv[])
{
    std::atexit(press_any_key);

    std::cout << "\n * Call stack trace simple test *\n" << std::endl;

    inner();
    outer();

    return 0;
}
