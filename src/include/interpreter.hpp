#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <array>
#include <stack>

namespace b7k
{
    class interpreter
    {
      public:
        interpreter() : data_pointer {}
        {
        }
        void run(const char *operation);

      private:
        const char *ip;

        std::array<uint8_t, 30000> data_region;
        uintmax_t data_pointer;

        std::stack<const char *> loop_stack;

        void decode(const char *opcodes);
        void execute(const char opcode);

        void increment_data_pointer();
        void decrement_data_pointer();
        void increment_data();
        void decrement_data();
        void read_data();
        void write_data();
        void start_loop();
        void end_loop();
    };
}

#endif
