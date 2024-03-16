#include <memory>

#include <file_mapper.hpp>
#include <interpreter.hpp>

#include <iostream>

namespace b7k
{

    extern "C" int main(int argc, const char *argv[])
    {
        if (argc <= 1)
        {
            return -1;
        }
        std::cout << ("\e[36m"
                      "______  _______   __                                    "
                      "          "
                      " \n"
                      "| ___ \\|___  / | / /                                   "
                      "          "
                      "  \n"
                      "| |_/ /   / /| |/ /                                     "
                      "          "
                      " \n"
                      "| ___ \\  / / |    \\                                   "
                      "          "
                      "   "
                      "\n"
                      "| |_/ /./ /  | |\\  \\                                  "
                      "          "
                      "   "
                      "\n"
                      "\\____/ \\_/   \\_| \\_/                                "
                      "          "
                      "\e[0m"
                      "\n\n");

        auto mapper = std::make_unique<file_mapper>(argv[1]);
        auto mapped_file = mapper->map();

        auto ip = std::make_unique<interpreter>();
        ip->run(mapped_file);

        return 0;
    }
}
