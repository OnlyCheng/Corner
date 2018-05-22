#pragma once
#include <new>

#define THROW_BAD_ALLOC throw bad_alloc

template <int inst>
class Alloc_malloc_template
{
public:
	static void* Allocate(size_t n)
	{
		void* result = malloc(n);
		//申请失败，使用oom_malloc()重新尝试申请
		if(result == NULL)
			Oom_malloc(n);
		return result;
	}

	static void* Deallocate(void* p,size_t /* size*/)
	{
		free(p);
	}

	static void* Reallocate(void* p, size_t size)
	{
		void* result = realloc(p,size);
		//申请失败，使用oom_realloc()尝试申请
		if(result == NULL)
			Oom_realloc(p,size);
		return result;
	}

	static void (* Set_malloc_handler (void (*f)())) ()
	{
		void (*old)() = _Malloc_alloc_oom_handler;
		_Malloc_alloc_oom_handler = f;
		return (old);
	}

private:
	static void* Oom_malloc(size_t size)
	{
		void* result;
		void (*My_malloc_handler) ();
		for(;;)
		{
			My_malloc_handler = _Malloc_alloc_oom_handler;
			if(0 == my_malloc_handler)
				THROW_BAD_ALLOC;
			result = malloc(size);
			if(result)
				return result;
		}
	}

	static void* Oom_realloc(void* p,size_t size)
	{
		void* result;
		void (*my_malloc_handler) ();
		for(;;)
		{
			my_malloc_handler = _Malloc_alloc_oom_handler;
			if(0 == My_malloc_handler)
				THROW_BAD_ALLOC;
			result = realloc(p,size);
			if(result)
				return result;
		}
		
	}

private:
	static void (*_Malloc_alloc_oom_handler);
};

//类外初始化静态成员变量 _malloc_alloc_oom_handler
void (* Malloc_alloc_template<inst>::_Malloc_alloc_oom_handler)() = 0;

void test()
{
	Alloc_malloc_template<0> alloc;
	int* p = (int*)alloc.Allocate(3*sizeof(int));
	p[0] = 0;
	p[1] = 1;
	p[2] = 2;
	p = (int*)alloc.Reallocate(p,5*sizeof(int));
	p[3] = 3;
	p[4] = 4;
	
	for(int i = 0; i<5; i++)
	{
		cout<<p[i]<<" ";
	}
	cout<<endl;
}
