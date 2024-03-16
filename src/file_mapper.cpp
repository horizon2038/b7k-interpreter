#include <file_mapper.hpp>

#include <stdexcept>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

namespace b7k
{
    file_mapper::file_mapper(const char *file_path)
    {
        fd = open(file_path, O_RDONLY);

        if (fd < 0)
        {
            std::runtime_error("error : can't open file\n");
        }

        auto map_size = calculate_map_size();

        mapped_file = static_cast<char *>(
            mmap(NULL, map_size, PROT_READ, MAP_SHARED, fd, 0)
        );
    }

    const char *file_mapper::map()
    {
        return mapped_file;
    }

    file_mapper::~file_mapper()
    {
        close(fd);
        munmap(mapped_file, calculate_map_size());
    }
}
