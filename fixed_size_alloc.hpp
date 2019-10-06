#pragma once
#include <cstring>
#include <cstdlib>

template<size_t chunk_size, size_t count>
class fixed_size_alloc
{
public:
    static constexpr size_t capacity = chunk_size * count;

    fixed_size_alloc()
    {
        begin_ = new char[capacity];
        for (size_t i = 0; i < count; ++i)
        {
            record_[i] = i;
        }
        end_ = begin_ + capacity;
    }

    ~fixed_size_alloc()
    {
        delete[] begin_;
    }

    void* realloc(void* p, size_t size) noexcept
    {
        if (nullptr == p)
        {
            return alloc(size);
        }
        else//realloc
        {
            if (p < begin_ || p > end_)
            {
                return ::realloc(p, size);
            }

            if (size > chunk_size)
            {
                //copy old data to new memory
                auto np = ::realloc(nullptr, size);
                memcpy(np, p, chunk_size);
                free(p);
                return np;
            }
            else
            {
                return p;
            }
        }
    }

    void* alloc(size_t size) noexcept
    {
        if (size > chunk_size || pos_<0)//use malloc
        {
            return ::malloc(size);
        }
        else
        {
            return begin_ + record_[pos_--] * chunk_size;
        }
    }

    void free(void* p) noexcept
    {
        if (p<begin_ || p > end_)
        {
            ::free(p);
            return;
        }
        auto pos = ((char*)p - begin_) / chunk_size;
        record_[++pos_] = pos;
    }
private:
    int32_t pos_ = count - 1;
    char* begin_ = nullptr;
    void* end_ = nullptr;
    size_t record_[count];
};
