#include <iostream>
#include <unordered_map>
#include <thread>

/*
	These two functions calculate the fibonacci number at a given index.
	The second one uses memoization and is hugely faster than the pure recursive version.

	Need to compile to c++20 because of the use of the contains() method on unordered_map.

	command line to compile code :
	g++ -std=c++20 -O3 fibo.cpp -o prog_fibo

	to run it:
	./prog_fibo (on mac)
	./prog_fibo.exe (on windows)

	The program runs 2 threads to compare speed.

	it becomes interesing to compare numbers arround 40 - 48.
*/


// Recursive naive version

int fibonacci(int n)
{
	// Returns number at given index

	// Base case
	if (n == 2 || n == 1)
		return 1;

	// Returns addition of two previous values, starts like : 0 1 1 2 3 5 8 13 21 ...
	return fibonacci(n-1) + fibonacci(n-2);
}


// Improve with memoization

std::unordered_map<int, int> memoVec = {{0, 0}, {1, 1}, {2, 1}};

int fibonacciMemo(int n, std::unordered_map<int, int> &map)
{
	// Uses memoization

	if (n < 2)
		return 1;

	// Here we skip the calculation and return directly instead of adding to the call stack
	if (map.contains(n))
	{
		return map[n];
	}

	int newFibValue = fibonacciMemo(n-1, map) + fibonacciMemo(n-2, map);

	// Updating memoVec object
	map[n] = newFibValue;

	return newFibValue;
}


int main()
{
	int myNumber;

	std::cout << "Let's find the fib value at index :  ";
	std::cin >> myNumber;

	std::thread t1([&](){
		std::cout << fibonacci(myNumber) << " : normal version finished" <<  std::endl;
	});

	std::thread t2([&](){
		std::cout << fibonacciMemo(myNumber, memoVec) << " : memo version finished" << std::endl;
	});

	t1.join();
	t2.join();

	return 0;
}