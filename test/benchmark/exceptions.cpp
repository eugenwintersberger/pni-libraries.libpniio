//implementation of tool errors

#include "exceptions.hpp"

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const cli_argument_error &e)
{
    return e.print(o);
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const cli_option_error &e)
{
    return e.print(o);
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const cli_error &e)
{
    return e.print(o);
}

//-----------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &o,const cli_help_request &e)
{
    return e.print(o);
}
