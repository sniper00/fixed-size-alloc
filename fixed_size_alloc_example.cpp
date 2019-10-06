#include <chrono>
#include <iostream>
#include "fixed_size_alloc.hpp"

static int64_t microsecond()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int main()
{
    int times = 10000000;
   {
        fixed_size_alloc<64, 4192> la;
        auto start = microsecond();

        for (int i = 0; i < times; ++i)
        {
            void* lbuf1 = la.alloc(16);
            void* lbuf2 = la.alloc(16);
            void* lbuf3 = la.alloc(32);
            void* lbuf4 = la.alloc(64);
            void* lbuf5 = la.alloc(64);
            la.free(lbuf1);
            la.free(lbuf2);
            la.free(lbuf3);
            la.free(lbuf4);
            la.free(lbuf5);
        }

        std::cout << "fixed_size_alloc cost " << microsecond() - start << "us" << std::endl;
    }

    {
        auto start = microsecond();
        for (int i = 0; i < times; ++i)
        {
            void* lbuf1 = malloc(16);
            void* lbuf2 = malloc(16);
            void* lbuf3 = malloc(32);
            void* lbuf4 = malloc(32);
            void* lbuf5 = malloc(64);
            ::free(lbuf1);
            ::free(lbuf2);
            ::free(lbuf3);
            ::free(lbuf4);
            ::free(lbuf5);
        }
        std::cout << "malloc cost" << microsecond() - start << "us" << std::endl;
    }
    return 0;
}