#ifndef FILE_MAPPER_HPP
#define FILE_MAPPER_HPP

#include <stdint.h>

namespace b7k
{
    inline constexpr auto PAGE_SIZE = 4096;
    inline constexpr auto FILE_SIZE = 1024;

    inline constexpr uintmax_t calculate_map_size()
    {
        return (FILE_SIZE / PAGE_SIZE + 1) * PAGE_SIZE;
    }

    class file_mapper
    {
      public:
        file_mapper(const char *file_path);
        ~file_mapper();
        const char *map();

      private:
        int fd;
        char *mapped_file;
    };
}

#endif
