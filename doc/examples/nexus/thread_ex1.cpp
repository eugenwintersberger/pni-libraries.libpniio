/*example for the library using a thread*/

#include "thread_ex1.hpp"
#include "thread_writer.hpp"
#include "thread_clireader.hpp"


int main(int ,char **)
{
    StringIOQueue q;
    Writer write("userlog.nx",q);
    CliReader cli("Nexus log $>",q);
    std::thread wthread(write);
    std::thread clithread(cli);

    //in the very end we need to join the thread
    wthread.join();
    clithread.join();

    return 0;
}    
