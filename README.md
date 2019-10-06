# fixed-size-alloc
fixed size alloc

# Example

```cpp
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

```

# Result
```
//Some cases 20 times faster than malloc
fixed_size_alloc cost 115497us
malloc cost 3371072us
```

