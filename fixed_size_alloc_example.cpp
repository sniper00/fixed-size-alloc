#include <chrono>
#include <iostream>
#include "fixed_size_alloc.hpp"

static int64_t microsecond()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

inline void not_null(void* p)
{
    if(nullptr == p)
    {
        abort();
    }
}

int main()
{
     int times = 10000000;
    {
        fixed_size_alloc<64, 4192> fsa;
        auto start = microsecond();
        for (int i = 0; i < times; ++i)
        {
            void* buf1 = fsa.alloc(16);
            void* buf2 = fsa.alloc(16);
            void* buf3 = fsa.alloc(32);
            void* buf4 = fsa.alloc(32);
            void* buf5 = fsa.alloc(64);
            not_null(buf1);
            not_null(buf2);
            not_null(buf3);
            not_null(buf4);
            not_null(buf5);
            memcpy(buf1, &i, sizeof(i));
            memcpy(buf2, &i, sizeof(i));
            memcpy(buf3, &i, sizeof(i));
            memcpy(buf4, &i, sizeof(i));
            memcpy(buf5, &i, sizeof(i));
            fsa.free(buf1);
            fsa.free(buf2);
            fsa.free(buf3);
            fsa.free(buf4);
            fsa.free(buf5);
        }

        std::cout << "fixed_size_alloc cost " << microsecond() - start << "us" << std::endl;
    }

    {
        auto start = microsecond();
        for (int i = 0; i < times; ++i)
        {
            void* buf1 = ::malloc(16);
            void* buf2 = ::malloc(16);
            void* buf3 = ::malloc(32);
            void* buf4 = ::malloc(32);
            void* buf5 = ::malloc(64);
            not_null(buf1);
            not_null(buf2);
            not_null(buf3);
            not_null(buf4);
            not_null(buf5);
            memcpy(buf1, &i, sizeof(i));
            memcpy(buf2, &i, sizeof(i));
            memcpy(buf3, &i, sizeof(i));
            memcpy(buf4, &i, sizeof(i));
            memcpy(buf5, &i, sizeof(i));
            ::free(buf1);
            ::free(buf2);
            ::free(buf3);
            ::free(buf4);
            ::free(buf5);
        }
        std::cout << "malloc cost " << microsecond() - start << "us" << std::endl;
    }
    return 0;
}