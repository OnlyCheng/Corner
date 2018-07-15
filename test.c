//#include <iostream>
//using namespace std;
//#include <vector>
//
//int main()
//{
//	//vector<int> v1;
//	////v1[0] = 1;  //还没有分配空间，直接赋值会导致程序崩溃
//	//v1.push_back(1);
//	//v1.insert(v1.begin()+1,2);
//	//v1.resize(3); //使用resize函数为v1分配了存放3个元素大小的空间
//	//v1[2] = 3;	  //有了空间，可以直接赋值了
//
//	//vector<int> v2(5);
//	//vector<int> v3(5, -1);
//
//	//int arr[5] = { 1, 2, 3, 4, 5 };
//	//vector<int> v4(arr,arr+5);
//	//vector<int> v5(v4.begin(), v4.end() - 1);
//	//vector<int> v6(v5);
//	//vector<int> v7 = v6;
//	//for (int i = 0; i < v6.size(); i++)
//	//	cout << v6[i] << " ";
//	//cout << endl;
//	//cout << &v5 << "  " << &v6 <<"  "<<&v7<<endl;
//
//	/*vector<int> v;
//	for (int i = 0; i < 5; i++)
//		v.push_back(i);
//	vector<int>::iterator it = v.begin();
//	while (it != v.end())
//	{
//		cout << *it << "  ";
//		it++;
//	}
//	cout << endl;
//	vector<int>::reverse_iterator rit;
//	for (rit = v.rbegin(); rit < v.rend(); rit++)
//		cout << *rit << "  ";
//	cout << endl;*/
//
//	vector<int> v;
//	for (int i = 0; i<10; i++) 
//		v.push_back(i);
//
//	for (int i = 0; i < v.size(); i++)
//	{
//		cout << v[i] << " ";
//		cout << v.at(i) << " ";
//	}
//	cout << endl;
//	cout << v.front() << endl;
//	cout << v.back() << endl;
//
//	/*cout << "size: " << myvector.size() << "\n";
//	cout << "capacity: " << myvector.capacity() << "\n";
//	cout << "max_size: " << myvector.max_size() << "\n";
//
//	myvector.reserve(20);
//	cout << "size: " << myvector.size() << "\n";
//	cout << "capacity: " << myvector.capacity() << "\n";
//	cout << "max_size: " << myvector.max_size() << "\n";*/
//
//
//
//	return 0;
//}
