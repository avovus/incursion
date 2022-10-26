#include <iostream>
#include <vector>

#include "lib/TicTacToe.cpp"

using namespace std;

int main() {
	vector<int> vec1{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0 };
	
	auto p1 = selectMove(vec1, true);
	cout << "test1: ( " << p1.first << ", " << p1.second << " )"  << endl;
	
	vector<int> vec2{
		1, -1, 1,
		0, -1, 0,
		0, 0, 1 };
	
	auto p2 = selectMove(vec2, false);
	cout << "test2: ( " << p2.first << ", " << p2.second << " )"  << endl;
	
	vector<int> vec3{
		1, -1, -1,
		0, 1, 0,
		0, 0, 0 };
	
	auto p3 = selectMove(vec3, true);
	cout << "test3: ( " << p3.first << ", " << p3.second << " )"  << endl;
}
