/*
 * Object Pool
 * ===========
 * Intent:
 * 1, Object pooling can offer a significant performance boost; 
 * 2, it is most effective in situations where the cost of initializing a class instance is high, 
 * the rate of instantiation of a class is high, and the number of instantiations in use at any one time is low.
 *
 * Structure:
 * The general idea for the Connection Pool pattern is that if instances of a class can be reused, 
 * you avoid creating instances of the class by reusing them.
 * */

#include<iostream>
#include<vector>
#include<string>

template<typename T>
class Object
{
public:
	Object(){};
	~Object(){};
	T opA()
	{
		return obj;
	}
	void opB(T t)
	{
		obj = t;
	}
private:
	T obj;
};

template<typename T>
class ObjectPool
{
public:
	ObjectPool(size_t size)
	{
		for(size_t i=0; i< size; i++){
			pool.push_back(new Object<T>());
		}
		maxsize_ = size;
	}
	~ObjectPool()
	{
		for(size_t i=0; i< pool.size(); i++)
		{
			Object<T>* obj = pool.back();
			pool.pop_back();
			delete obj;
		}
	}
	Object<T>* acquire()
	{
		if(pool.size()<=0)
			return new Object<T>();
		else{
			Object<T>* obj = pool.back();	
			pool.pop_back();
			return obj;
		}
	}

	void release(Object<T>* obj)
	{
		if(pool.size()>=maxsize_)
			return;
		pool.push_back(obj);
	}

private:
	std::vector<Object<T>*> pool;
	size_t maxsize_;
};

int main()
{
	ObjectPool<std::string> pool(10);
	Object<std::string>* a = pool.acquire();
	a->opB("A");
	std::string tmp = a->opA();
	std::cout << "Hello from " << tmp << std::endl; 
	pool.release(a);
	return 0;
}


