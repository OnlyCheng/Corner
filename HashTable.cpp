#pragma once
#include <iostream>
using namespace std;

//完成闭散列要求：
//>> 插入元素唯一
//>> 写成动态的考虑如何增容？
//>> 哈希函数用出留余数法，考虑余数每次模素数 增容尽量增加到原空间的两倍
//>> 哈希表中任意类型都可以存储

//近似于二倍增长的素数表
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

//用于标记哈希表元素的状态
enum State{EMPTY,FILLED,DELETED};

//哈希表元素结点
template<class K>
struct HashTableElem
{
	K _key;
	State _state;

	HashTableElem(K key = K())
		:_key(key)
		, _state(EMPTY)
	{}
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

//哈希表的主体
template<class K, bool IsLine = true, class KeyToInt = KeyToInt<K>>
class HashTable
{
	typedef HashTableElem<K> Elem;
public:
	HashTable(size_t capacity = 10)
		:_size(0)
		, _capacity(capacity)
	{
		_hashTable = new Elem[capacity];
	}

	bool Insert(const K& key)
	{
		if (Find(key) > 0)//已经存在
			return false;

		CheckCapacity();
		return _Insert(key);
	}

	int Find(const K& key)
	{
		size_t addr = HashFunc(key);
		if (EMPTY == _hashTable[addr]._state)//不在哈希表中
			return -1;

		if (key == _hashTable[addr]._key && _hashTable[addr]._state == FILLED)//找到了
			return addr;
		else//由于哈希冲突，使得原本的位置被别的元素占用
		{
			size_t oldAddr = addr;
			while (addr + 1 != oldAddr)
			{
				if (key == _hashTable[addr]._key && _hashTable[addr]._state == FILLED)
					return addr;

				addr++;
				if (addr == _capacity)
					addr = 0;
			}
			return -1;
		}
	}

	//删除哈希表中的关键字key
	bool Delete(const K& key)
	{
		int addr = Find(key);
		if (addr < 0)
			return false;
		else
		{
			_hashTable[addr]._state = DELETED;
			_size--;
			return true;
		}

	}
	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	~HashTable()
	{
		if (_size != 0)
		{
			for (size_t i = 0; i < _capacity; i++)
			{
				if (_hashTable[i]._state == FILLED)
				{
					_hashTable[i]._state = DELETED;
					_size--;
				}
			}
		}
	}

private:
	bool _Insert(const K& key)
	{
		size_t hashNo = HashFunc(key);
		if (_hashTable[hashNo]._state != EMPTY)
		{
			if (IsLine)
				LineCheck(hashNo);
			else
			{
				int i = 0;
				SecondCheck(hashNo, i);
			}
		}

		_hashTable[hashNo]._key = key;
		_hashTable[hashNo]._state = FILLED;
		_size++;
		return true;
	}

private:
	size_t HashFunc(const K& key)
	{
		return KeyToInt()(key) % _capacity;
		//return key%_capacity;
	}

	// 线性探测 
	void LineCheck(size_t& hashAddr)
	{
		while (_hashTable[hashAddr]._state != EMPTY)
		{
			hashAddr++;
			if (hashAddr == _capacity)
				hashAddr = 0;
		}
	}

	// 二次探测 
	void SecondCheck(size_t hashAddr, size_t i)
	{
		while (_hashTable[hashAddr]._state != EMPTY)
		{
			hashAddr = (hashAddr + i ^ 2) % _capacity;
			i++;
		}
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

	void Swap(HashTable& ht)
	{
		if (&ht != this)
		{
			swap(ht._hashTable, _hashTable);
			swap(ht._capacity, _capacity);
			swap(ht._size, _size);
		}
	}

	void CheckCapacity()
	{
		if (_size * 10 / _capacity < 7)
			return;

		size_t newCapacity = FindNextPrime(_capacity);
		HashTable ht(newCapacity);

		//将旧空间的元素以插入的方式搬移到新空间
		for (size_t i = 0; i < _capacity; i++)
		{
			if (_hashTable[i]._state == FILLED)
				ht.Insert(_hashTable[i]._key);
		}
		Swap(ht);
	}

private:
	Elem* _hashTable;
	size_t _size;
	size_t _capacity;
};

void TestHashTable1()
{
	HashTable<int> ht;

	ht.Insert(3);
	ht.Insert(5);
	ht.Insert(5);
	ht.Insert(7);
	ht.Insert(11);
	ht.Insert(8);
	ht.Insert(10);
	ht.Insert(9);
	ht.Insert(18);

	int addr = ht.Find(18);
	cout << "capacity is: " << ht.Capacity() << endl;
	cout << "size is: " << ht.Size() << endl;
	cout << "18's addr is: " << addr << endl;
}

void TestHashTable2()
{
	HashTable<string,false> ht;

	ht.Insert("abcde");
	ht.Insert("asdfg");
	ht.Insert("asdfg");
	ht.Insert("siadnvkj");
	ht.Insert("durhiej");
	ht.Insert("dhidsn");
	ht.Insert("erion");
	ht.Insert("fiskwewjf");
	ht.Insert("rueif");

	int addr = ht.Find("erion");
	cout << "capacity is: " << ht.Capacity() << endl;
	cout << "size is: " << ht.Size() << endl;
	cout << "abcde's addr is: " << addr << endl;
}
