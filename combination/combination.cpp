// combination.cpp : メイン プロジェクト ファイルです。

#include "stdafx.h"

#ifndef _GLIBCXX_NO_ASSERT
#include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#if __cplusplus >= 201103L
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdalign>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif

//#include <bits/stdc++.h>
using namespace std;

class combination
{
public:

	//Nの最大値がわかれば代入する
	combination( long long int combinationThreshold = 1e7 ) {
		(*this).combinationThreshold = combinationThreshold;
	}

	//a^p % mod
	long long int powmod( long long int a, long long int p, long long int mod = LLONG_MAX ) {
		long long int ans = 1;
		long long int mul = a;
		for( ; p > 0; p >>= 1, mul = (mul*mul) % mod ) {
			if( (p & 1) == 1 ) ans = (ans*mul) % mod;
		}
		return ans;
	}

	//nCk mod m
	long long int cb( long long int N, long long int K, long long int M = LLONG_MAX ) {
		if( N < combinationThreshold ) {// 事前計算O(N)、答えるのはO(1)
			if( inv.size() == 0 ) {
				inv = vector<long long int>( combinationThreshold );
				inv[1] = 1;
				for( long long int i = 2; i < combinationThreshold; i++ ) {
					inv[i] = M - (M / i)*inv[M%i] % M;
				}
				fact = vector<long long int>( combinationThreshold );
				fact[0] = 1;
				revFact = vector<long long int>( combinationThreshold );
				revFact[0] = 1;
				for( long long int i = 1; i < combinationThreshold; i++ ) {
					fact[i] = (fact[i - 1] * i) % M;
					revFact[i] = (revFact[i - 1] * inv[i]) % M;
				}
			}
			return (((fact[N] * revFact[K]) % M)*revFact[N - K]) % M;
		} else {
			return cbOnce( N, K, M );
		}
	}

	//一回だけなら最速 O(K + log(M))
	long long int cbOnce( long long int N, long long int K, long long int M = LLONG_MAX ) {
		if( K > N / 2 ) return cb( N, N - K, M );
		long long int ans = 1;
		long long int div = 1;
		for( long long int i = 0; i < K; i++ ) {
			ans *= N - i;
			ans %= M;
			div *= i + 1;
			div %= M;
		}
		ans *= powmod( div, M - 2, M );
		return ans%M;
	}

private:
	vector<vector<long long int>>C;//3000以下の答え
	vector<long long int>fact;//階乗
	vector<long long int>revFact;//階乗の逆元
	vector<long long int>inv;//mod pでの逆元

	long long int combinationThreshold;//Nの最大値がわかれば入れる。
};

int main() {
	long long int W, H;
	cin >> W >> H;
	combination cb( W + H - 2 );
	cout << cb.cb( W + H - 2, H - 1, 1000000007LL ) << endl;
}
