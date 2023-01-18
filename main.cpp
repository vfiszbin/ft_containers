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

void map_tests()
{
	//empty constructor
	NS::map<int, int> m;
	assert(m.empty());

	//constructor with comparison operator
	NS::map<int, int, std::greater<int> >m2;
	m2[1] = 2;
	m2[2] = 1;
	assert(m2.begin()->first == 2);

	//copy constructor
	NS::map<int, int> m3;
	m3[1] = 2;
	m3[2] = 1;
	NS::map<int, int> m4(m3);
	assert(m4.size() == 2);

	//range constructor
	NS::pair<int, int> arr[] = {NS::make_pair(1,2), NS::make_pair(2,3), NS::make_pair(3,4)};
	NS::map<int, int> m5(arr, arr + 3);
	assert(m5.size() == 3);
	assert(m5[2] == 3);

	//assignment operator
	NS::map<int, int> m6;
	m6[1] = 2;
	m6[2] = 1;
	NS::map<int, int> m7;
	m7 = m6;
	assert(m7.size() == m6.size());
	assert(m7[2] == m6[2]);

	NS::map<int, int> m8;
	m8[3] = 4;
	m8[4] = 3;
	m8 = m6;
	assert(m8.size() == m6.size());
	assert(m8[2] == m6[2]);

	m6 = m6;
	assert(m6.size() == 2);
	assert(m6[2] == m6[2]);

	//begin
	m[1] = 2;
	m[2] = 1;
	NS::map<int, int>::iterator it = m.begin();
	assert(it->first == 1);
	assert((++it)->first == 2);

	//end
	it = m.end();
	it--;
	assert(it->first == 2);

	//rbegin
	NS::map<int, int>::reverse_iterator rit = m.rbegin();
	assert(rit->first == 2);

	//rend
	rit = m.rend();
	rit--;
	assert(rit->first == 1);

	//at
	assert(m.at(1) == 2);
	m.at(1) = 3;
	assert(m.at(1) == 3);

	//insert
	m.insert(NS::make_pair(3, 4));
	assert(m.at(3) == 4);

	it = m.find(1);
	m.insert(it, NS::make_pair(4, 5));
	assert(m.at(4) == 5);

	m.clear();
	m.insert(arr, arr + 2);
	assert(m.size() == 2);

	//erase
	m.clear();
	m[1] = 2;
	m[2] = 1;
	m.erase(1);
	try {
		m.at(1);
		assert(false);
	} catch(const std::out_of_range& e) {
		assert(e.what() == std::string("map::at"));
	}

	it = m.find(2);
	m.erase(it);
	try {
		m.at(2);
		assert(false);
	} catch(const std::out_of_range& e) {
		assert(e.what() == std::string("map::at"));
	}

	m.clear();
	m[1] = 2;
	m[2] = 1;
	m[3] = 4;
	m[4] = 3;
	m[5] = 6;
	NS::map<int, int>::iterator it1 = m.find(2);
	NS::map<int, int>::iterator it2 = m.find(4);
	m.erase(it1, it2);
	assert(m.size() == 3);

	//swap
	NS::map<int, int> m1;
	m1[1] = 2;
	m1[2] = 1;
	m.clear();
	m[3] = 4;
	m[4] = 3;
	m1.swap(m);
	assert(m1.size() == 2);
	assert(m[1] == 2);
	assert(m[2] == 1);
	assert(m1[3] == 4);
	assert(m1[4] == 3);

	m.clear();
	m[1] = 2;
	m[2] = 1;
	m1.clear();
	m.swap(m1);
	assert(m.empty());

	//clear
	m[1] = 2;
	m[2] = 1;
	m.clear();
	assert(m.empty());

	//key_comp
	NS::map<int, int>::key_compare comp = m.key_comp();
	assert(comp(1, 2) == true);

	NS::map<std::string, int> m_s;
	NS::map<std::string, int>::key_compare comp2 = m_s.key_comp();
	assert(comp2("a", "b") == true);

	//value_comp
	NS::map<int, int>::value_compare comp3 = m.value_comp();
	assert(comp3(NS::make_pair(1,2), NS::make_pair(2,1)) == true);

	NS::map<std::string, int>::value_compare comp4 = m_s.value_comp();
	assert(comp4(NS::make_pair("a", 2), NS::make_pair("b", 1)) == true);

	//find
	m.clear();
	m[1] = 2;
	m[2] = 1;
	it = m.find(1);
	assert(it->first == 1);
	assert(it->second == 2);

	it = m.find(3);
	assert(it == m.end());

	//count	
	assert(m.count(1) == 1);
	assert(m.count(3) == 0);

	//lower_bound
	m[1] = 2;
	m[2] = 1;
	m[3] = 4;
	it = m.lower_bound(2);
	assert(it->first == 2);

	it = m.lower_bound(4);
	assert(it == m.end());

	//upper_bound
	it = m.upper_bound(2);
	assert(it->first == 3);

	it = m.upper_bound(4);
	assert(it == m.end());

	//equal_range
	m[1] = 2;
	m[2] = 1;
	m[3] = 4;
	m[4] = 3;
	m[5] = 6;
	NS::pair<NS::map<int, int>::iterator, NS::map<int, int>::iterator> range = m.equal_range(2);
	NS::map<int, int>::iterator lower = range.first;
	NS::map<int, int>::iterator upper = range.second;
	assert(lower->first == 2);
	assert(upper->first == 3);

	//relational operators
	m.clear();
	m[1] = 2;
	m[2] = 1;
	m1.clear();
	m1[3] = 4;
	m1[4] = 3;
	assert(m < m1);

	assert(m1 > m);

	assert(m <= m1);

	assert(m1 >= m);

	assert(m != m1);

	m1.clear();
	m1[1] = 2;
	m1[2] = 1;

	assert(m == m1);

}

int main() 
{
	stack_tests();
	vector_tests();
	map_tests();
	return 0;
}
