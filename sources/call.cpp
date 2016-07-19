/// Implementation of class call methods

#include <trace/call>

namespace
{
    std::string only_file_name(const std::string& file_path)
    {
        size_t pos = file_path.find_last_of("/\\");
        if (pos == std::string::npos)
            return file_path;
        else
            return file_path.substr(pos + 1);
    }
}

QUA_TRACE_BEGIN

call::call(const std::string&  name,
           const std::string&  file,
                 std::uint64_t line)
    : scope(name),
      m_file(only_file_name(file)),
      m_line(line)
{
}

const std::string& call::get_file() const
{
    return m_file;
}

std::uint64_t call::get_line() const
{
    return m_line;
}

QUA_TRACE_END

// Unicode signature: Владимир Керимов
