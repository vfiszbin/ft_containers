#include <iostream>
#include <cassert>
#include <deque>

#if NAMESPACE==1
	#include <map>
	#include <stack>
	#include <vector>
	#define NS std
#else
	#include "map.hpp"
	#include "stack.hpp"
	#include "vector.hpp"
	#define NS ft
#endif

void stack_tests()
{
	//constructor with container
	std::deque<int> deq(3, 5);
	NS::stack<int,std::deque<int> > stack1(deq);
	assert(stack1.size() == deq.size());

	//copy constructor
	NS::stack<std::string> stack2;
	stack2.push("4");
	stack2.push("5");
	NS::stack<std::string> stack3(stack2);
	assert(stack3.size() == stack2.size());

	//assisgnment operator
	NS::stack<int> s4;
	s4.push(1);
	s4.push(2);
	NS::stack<int> s5;
	s5 = s4;
	assert(s5.size() == s4.size());
	assert(s5 == s4);

	NS::stack<int> s6;
	s6.push(1);
	s6.push(2);
	NS::stack<int> s7;
	s7.push(3);
	s7.push(4);
	s7 = s6;
	assert(s7.size() == s6.size());
	assert(s7 == s6);

	NS::stack<int> s8;
	s8.push(1);
	s8.push(2);
	s8 = s8;
	assert(s8.size() == 2);

	//push
	NS::stack<int> myStack;
	myStack.push(5);
	myStack.push(10);
	assert(myStack.size() == 2);
	assert(myStack.top() == 10);

	//pop
	myStack.pop();
	assert(myStack.size() == 1);
	assert(myStack.top() == 5);

	//empty
	myStack = NS::stack<int>();
	assert(myStack.empty() == true);
	myStack.push(5);
	assert(myStack.empty() == false);

	//relational operators
	NS::stack<int> s1;
	NS::stack<int> s2;

	s1.push(1);
	s1.push(2);
	s1.push(3);

	s2.push(1);
	s2.push(2);
	s2.push(3);

	assert(s1 == s2);

	s1.pop();
	s1.push(4);

	assert(s1 != s2);

	s2.pop();
	s2.push(4);

	assert(s1 == s2);

	s1 = NS::stack<int>();
	s1.push(1);
	s1.push(2);

	s2 = NS::stack<int>();
	s2.push(1);
	s2.push(2);

	NS::stack<int> s3;
	s3.push(3);
	s3.push(4);

	assert(s1 < s3);
	assert(s1 <= s2);
	assert(s3 > s1); 
	assert(s3 >= s1); 
}

void vector_tests()
{
	//default constructor
	NS::vector<int> v1;
	assert(v1.empty() == true);

	//constructor with size
	NS::vector<int> v2(5);
	assert(v2.size() == 5);

	//constructor with size and value
	NS::vector<int> v3(5, 10);
	assert(v3.size() == 5);
	assert(v3[0] == 10 && v3[4] == 10);

	//constructor with first and last iterators
	int arr[] = {1, 2, 3, 4, 5, 6};
	NS::vector<int> v4(arr, arr + 5);
	assert(v4.size() == 5);
	assert(v4[0] == 1 && v4[4] == 5);

	//copy constructor
	NS::vector<int> v5(v4);
	assert(v5.size() == 5);
	assert(v5[0] == 1 && v5[4] == 5);

	//assigment operator
	v1 = NS::vector<int>(arr, arr+3);
	v2 = NS::vector<int>();

	v2 = v1;
	assert(v2 == v1);

	v3 = NS::vector<int>(arr+3, arr+6);
	v2 = v3;
	assert(v2 == v3);

	//begin
	NS::vector<int> v(arr, arr+3);
	NS::vector<int>::iterator it = v.begin();
	assert(*it == 1);
	assert(*(++it) == 2);

	//end
	it = v.end();
	it--;
	assert(*it == 3);

	//rbegin
	NS::vector<int>::reverse_iterator rit = v.rbegin();
	assert(*rit == 3);

	//rend
	rit = v.rend();
	rit--;
	assert(*rit == 1);

	//push_back
	v.push_back(4);
	assert(v.size() == 4);
	assert(v[3] == 4);

	//pop_back
	v.pop_back();
	assert(v.size() == 3);

	//at
	assert(v.at(1) == 2);

	//front
	assert(v.front() == 1);

	//back
	assert(v.back() == 3);

	//clear
	v.clear();
	assert(v.size() == 0);

	//resize
	v.resize(5);
	assert(v.size() == 5);

	//reserve
	v.reserve(10);
	assert(v.capacity() >= 10);

	//assign
	v = NS::vector<int>(arr, arr+3);
	v2.assign(v.begin(), v.end());
	assert(v == v2);

	//insert
	it = v.begin();
	it++;
	v.insert(it, 4);
	assert(v[1] == 4);

	//erase
	v = NS::vector<int>(arr, arr+3);
	it = v.begin();
	it++;
	v.erase(it);
	assert(v[1] == 3);

	//swap
	v1 = NS::vector<int>(arr, arr+3);
	v2 = NS::vector<int>(arr+3, arr+6);
	v1.swap(v2);
	assert(v1[0] == 4);
	assert(v1[1] == 5);
	assert(v1[2] == 6);
	assert(v2[0] == 1);
	assert(v2[1] == 2);
	assert(v2[2] == 3);

	//clear
	v.clear();
	assert(v.size() == 0);

	//relational operators
	v1 = NS::vector<int>(arr, arr+3);
	v2 = NS::vector<int>(arr, arr+3);
	assert(v1 == v2);

	v2 = NS::vector<int>(arr+3, arr+6);
	assert(v1 != v2);

	v2 = NS::vector<int>(arr, arr+2);	
	v2.push_back(4);
	assert(v1 < v2);

	assert(v2 > v1);

	v1 = NS::vector<int>(arr, arr+3);
	v2 = NS::vector<int>(arr, arr+3);
	assert(v1 <= v2);
	assert(v1 >= v2);

}

int main() 
{
	stack_tests();
	vector_tests();
	return (0);
}
