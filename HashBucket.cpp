#pragma once
#include <iostream>
using namespace std;
#include <vector>

//2完成开散列
//>> 哈希桶中的元素既可以重复，也可以是唯一的
//>> 考虑如何增容
//>> 任意类型的关键字都可以处理
//>> 除留余数法模素数
//>> 尝试着自己增加迭代器----参考unordered_map

const int _PrimeSize = 28;
static const unsigned long _PrimeList[_PrimeSize] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

//定义一个模板类来将插入的元素转换成整型
template <class K>
struct KeyToInt
{
	size_t operator()(const K& key)
	{
		return key;
	}
};

//利用类模板的特化实现用哈希表存储字符串
template <>
struct KeyToInt<string>
{
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}

private:
	//将字符串转换成一个整型
	static size_t BKDRHash(const char* str)
	{
		unsigned int seed = 131;//31131131313131131313
		unsigned int hash = 0;
		while (*str)
		{
			hash = hash*seed + (*str++);
		}
		return(hash & 0x7FFFFFFF);
	}
};

template <class K,class V>
struct HashTableNode
{
	HashTableNode* _pNext;
	K _key;
	V _value;

	HashTableNode(const K& key, const K& value)
		: _pNext(NULL)
		, _key(key)
		, _value(value)
	{}
};

// 
template<class K, class V, class KeyToInt = KeyToInt<K>>
class HashBucket
{
	typedef HashTableNode<K,V> Node;
	typedef Node* PNode;

public:
	HashBucket(size_t capacity = 10)
		:_capacity(capacity)
		, _size(0)
	{
		_HashBucket.resize(capacity);
	}

	// 重复 
	bool InsertEqual(const K& key, const V& value)
	{
		CheckCapacity();
		return _Insert(key, value);
	}

	// 元素不能重复 
	bool InsertUnique(const K& key, const V& value)
	{
		int addr = Find(key);
		if (addr >= 0)
			return false;
		else
		{
			CheckCapacity();
			return _Insert(key, value);
		}
	}

	bool DeleteEqual(const K& key)
	{
		size_t addr = Find(key);
		if (addr < 0)
			return false;
		else
		{
			PNode pCur = _HashBucket[addr];
			PNode pPre = NULL;
			size_t oldsize = _size;
			while (pCur)
			{
				if (pCur->_key == key)
				{
					if (pCur == _HashBucket[addr])//为该位置的第一个元素
					{
						_HashBucket[addr] = pCur->_pNext;
						delete pCur;
						pCur = _HashBucket[addr];
					}
					else
					{
						pPre->_pNext = pCur->_pNext;
						delete pCur;
						pCur = pPre->_pNext;
					}
					_size--;
				}
				else
				{
					pPre = pCur;
					pCur = pCur->_pNext;
				}
			}
			if (oldsize == _size)
				return false;
			else
				return true;
		}
	}

	bool DeleteUnique(const K& key)
	{
		size_t addr = Find(key);
		if (addr < 0)
			return false;
		else
		{
			PNode pCur = _HashBucket[addr];
			PNode pPre = NULL;
			while (pCur)
			{
				if (pCur->_key == key)
				{
					if (pCur == _HashBucket[addr])//为该位置的第一个元素
						_HashBucket[addr] = pCur->_pNext;
					else
						pPre->_pNext = pCur->_pNext;

					delete pCur;
					_size--;
					return true;
				}
				pPre = pCur; 
				pCur = pCur->_pNext;
			}
		}
		return true;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	size_t Size()const
	{
		return _size;
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	void Swap(HashBucket& ht)
	{
		if (this != &ht)
		{
			swap(ht._HashBucket, _HashBucket);
			swap(ht._capacity, _capacity);
			swap(ht._size, _size);
		}
	}

	// 清空hashTable中的所有元素 
	void Clear()
	{
		for (size_t i = 0; i < _capacity; i++)
		{
			PNode pCur = _HashBucket[i];
			while (_HashBucket[i])
			{
				_HashBucket[i] = pCur->_pNext;
				delete pCur;
				pCur = _HashBucket[i];
			}
		}
	}

	~HashBucket()
	{
		Clear();
	}

private:
	int Find(const K& key)
	{
		size_t addr = HashFunc(key);
		PNode pCur = _HashBucket[addr];

		while (pCur)
		{
			if (pCur->_key == key)
				return addr;
			pCur = pCur->_pNext;
		}
		return -1;
	}

	bool _Insert(const K& key, const V& value)
	{
		size_t addr = HashFunc(key);
		PNode newNode = new Node(key,value);

		newNode->_pNext = _HashBucket[addr];
		_HashBucket[addr] = newNode;
		_size++;

		return true;
	}

	size_t FindNextPrime(size_t addr)
	{
		int i = 0;
		for (; i < 28; i++)
		{
			if (_PrimeList[i]>addr)
				break;
		}
		return _PrimeList[i];
	}

private:
	size_t HashFunc(const K& key)
	{
		return KeyToInt()(key) % _HashBucket.capacity();
		//return (key) % _HashBucket.capacity();
	}

	void CheckCapacity()
	{
		if (_size * 10 / _capacity < 7)
			return;
		else
		{
			unsigned long newCapacity = FindNextPrime(_capacity);
			size_t size = _size;
			_HashBucket.resize(newCapacity);
		
			_size = size;
			_capacity = newCapacity;
		}
	}
private:
	vector<PNode> _HashBucket;
	size_t _size;
	size_t _capacity;
};

void TestHashBucket1()
{
	HashBucket<int, int> hb;
	hb.InsertEqual(1, 1);
	hb.InsertEqual(2, 2);
	hb.InsertEqual(3, 3);
	hb.InsertEqual(4, 4);
	hb.InsertEqual(5, 5);
	hb.InsertEqual(5, 5);
	hb.InsertEqual(6, 6);
	hb.InsertEqual(6, 6);
	hb.InsertEqual(15, 15);
	hb.InsertEqual(12, 12);
	hb.InsertEqual(23, 23);

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;

	hb.DeleteEqual(5);

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;
}

void TestHashBucket2()
{
	HashBucket<int, int> hb;
	hb.InsertUnique(1, 1);
	hb.InsertUnique(2, 2);
	hb.InsertUnique(3, 3);
	hb.InsertUnique(4, 4);
	hb.InsertUnique(5, 5);
	hb.InsertUnique(6, 6);
	hb.InsertUnique(6, 6);

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;

	hb.DeleteUnique(6);

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;
}

void TestHashBucket3()
{
	HashBucket<string,string> hb;
	hb.InsertEqual("abcd", "abcd");
	hb.InsertEqual("abcd", "abcd");
	hb.InsertEqual("dgjkldg", "dgjkldg");
	hb.InsertUnique("saslkd", "saslkd");
	hb.InsertUnique("saslkd", "saslkd");
	hb.InsertUnique("dkgkld", "dkgkld");

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;

	hb.DeleteEqual("abcd");

	cout << "size:" << hb.Size() << endl;
	cout << "capacity:" << hb.Capacity() << endl;
}

