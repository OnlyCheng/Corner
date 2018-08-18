#include <iostream>
#include <vector>
#include <algorithm>

int count_cost(std::vector<int>& v, int size)
{
	sort(v.begin(), v.end());
    int count = 0;
    for(int i = 1; i < size; ++i)
        count += v[i];
    return count;
}

int main()
{
    int N = 0;
    std::cin >> N;
    std::vector<int> A(N, 0);
    for(int i = 0; i < N; ++i)
        std::cin >> A[i];
    int ret = count_cost(A, N);
    std::cout << ret << std::endl;
    
	return 0;
}
