#include <interpreter.hpp>

#include <iostream>

namespace b7k
{
    void interpreter::run(const char *operation)
    {
        decode(operation);
        std::cout << "\n\e[36msuccessfully finished.\e[0m" << std::endl;
    }

    void interpreter::decode(const char *opcodes)
    {
        ip = opcodes;

        while (*ip)
        {
            switch (*ip)
            {
                case '>' :
                    increment_data_pointer();
                    break;

                case '<' :
                    decrement_data_pointer();
                    break;

                case '+' :
                    increment_data();
                    break;

                case '-' :
                    decrement_data();
                    break;

                case ',' :
                    read_data();
                    break;

                case '.' :
                    write_data();
                    break;

                case '[' :
                    start_loop();
                    break;

                case ']' :
                    end_loop();
                    break;

                default :
                    ip++;
                    continue;
            }
            ip++;
        }
    }

    void interpreter::increment_data_pointer()
    {
        data_pointer++;
    }

    void interpreter::decrement_data_pointer()
    {
        if (data_pointer == 0)
        {
            return;
        }

        data_pointer--;
    }

    void interpreter::increment_data()
    {
        data_region[data_pointer]++;
    }

    void interpreter::decrement_data()
    {
        data_region[data_pointer]--;
    }

    void interpreter::read_data()
    {
        uint8_t data = 0;
        std::cin >> data;
        data_region[data_pointer] = data;
    }

    void interpreter::write_data()
    {
        std::cout << static_cast<char>(data_region[data_pointer]);
    }

    void interpreter::start_loop()
    {
        if (data_region[data_pointer] != 0)
        {
            return;
        }

        auto depth = 1;
        while (depth > 0)
        {
            ip++;
            if (*ip == '[')
            {
                depth++;
            }
            if (*ip == ']')
            {
                depth--;
            }
        }
    }

    void interpreter::end_loop()
    {
        if (data_region[data_pointer] == 0)
        {
            return;
        }

        auto depth = 1;
        while (depth > 0)
        {
            ip--;
            if (*ip == '[')
            {
                depth--;
            }
            else if (*ip == ']')
            {
                depth++;
            }
        }
    }
}
