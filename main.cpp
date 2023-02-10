#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <sstream>
using namespace std;

#include "Node.h"


//move the zero up
Node movezeroup(Node puzz) {
	//get the idea from this link:https://www.geeksforgeeks.org/pair-in-cpp-stl/
	//use longlong because int has 4 bits, but here is 8 bits.
	// long long x = puzz.zero.first;
	// long long y = puzz.zero.second;
	//here is to check the (x,y) y is 0 or not
	if (puzz.zero.second != 0) {
		//here is to switch the zero with the number above the zero in the vector
		//switch the position
		swap(puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second-1), puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second));
		//update the position about zero.
		puzz.zero.second = puzz.zero.second - 1;
	}
	return puzz;
}

//move the zero dowm
Node movezerodown(Node puzz) {
	// long long x = puzz.zero.first;
	// long long y = puzz.zero.second;
	//because puzzle size is 3, we count 0,1,2
	if (puzz.zero.second != 2) {
		//here is to switch the zero with the number below the zero in the vector
		//switch the position
		swap(puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second + 1), puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second));
		//update the position about zero.
		puzz.zero.second = puzz.zero.second + 1;
	}
	return puzz;
}

//move the zero left
Node movezeroleft(Node puzz) {
	// long long x = puzz.zero.first;
	// long long y = puzz.zero.second;
	//here is to check the (x,y) x is 0 or not
	if (puzz.zero.first != 0) {
		//here is to switch the zero with the number on the left of the zero in the vector
		//switch the position
		swap(puzz.puzzle.at(puzz.zero.first-1).at(puzz.zero.second), puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second));
		//update the position about zero.
		puzz.zero.first = puzz.zero.first - 1;
	}
	return puzz;
}

//move the zero right
Node movezeroright(Node puzz) {
	// long long x = puzz.zero.first;
	// long long y = puzz.zero.second;
	//because puzzle size is 3, we count 0,1,2
	if (puzz.zero.first != 2) {
		//here is to switch the zero with the number on the right of the zero in the vector
		//switch the position
		swap(puzz.puzzle.at(puzz.zero.first + 1).at(puzz.zero.second), puzz.puzzle.at(puzz.zero.first).at(puzz.zero.second));
		//update the position about zero.
		puzz.zero.first = puzz.zero.first + 1;
	}
	return puzz;
}


//this function is to expand the nodes
//map of string and bool. get idea in this link:https://thispointer.com/c-map-insert-example/
//rightnow mean the current node.
void nodeexpand(Node rightnow, map < string, bool >& marknodes, priority_queue<Node>& nodes, int algorithm_choice ) {
	
	//this function is to mark the current node
	//to make sure this node is already explored in map
	marknodes[rightnow.twodtostring()] = true;
	
	//the follow four function is to check with the map
	//to check the node is mark or not
	//if the node is not mark, it will return false
	//also, they will calculate the gn and hn cost.
	Node zeroup = movezeroup(rightnow);
	if (marknodes[zeroup.twodtostring()] == false) {
		zeroup.findgnandhncost(algorithm_choice);
		nodes.push(zeroup);
	}
	Node zerodown = movezerodown(rightnow);
	if (marknodes[zerodown.twodtostring()] == false) {
		zerodown.findgnandhncost(algorithm_choice);
		nodes.push(zerodown);
	}
	Node zeroleft = movezeroleft(rightnow);
	if (marknodes[zeroleft.twodtostring()] == false) {
		zeroleft.findgnandhncost(algorithm_choice);
		nodes.push(zeroleft);
	}
	Node zeroright = movezeroright(rightnow);
	if (marknodes[zeroright.twodtostring()] == false) {
		zeroright.findgnandhncost(algorithm_choice);
		nodes.push(zeroright);
	}
}

//here is the 2d default puzzle
vector<vector<string>> getdepuzzle() {
	vector<vector<string>> depuzzle = { {"1", "2", "3"},
 										{"4", "8", "0"},
 										{"7", "6", "5"} };

	/*
	this is the test puzzle.
	vector<vector<string>> depuzzle = { {"1", "2", "3"},
 										{"4", "5", "6"},
 										{"7", "8", "0"} };
	
	vector<vector<string>> depuzzle = { {"1", "2", "3"},
 										{"4", "5", "6"},
 										{"7", "0", "8"} };

	vector<vector<string>> depuzzle = { {"1", "2", "0"},
 										{"4", "5", "3"},
 										{"7", "8", "6"} };

	vector<vector<string>> depuzzle = { {"0", "1", "2"},
 										{"4", "5", "3"},
 										{"7", "8", "6"} };

	vector<vector<string>> depuzzle = { {"8", "7", "1"},
 										{"6", "0", "2"},
 										{"5", "4", "3"} };	

	vector<vector<string>> depuzzle = { {"1", "2", "3"},
 										{"4", "5", "6"},
 										{"8", "7", "0"} };								 
	*/
 	return depuzzle;
}

int main() {
	int userchoice;
	vector<vector<string>> puzzle;
	// string userpuzzle;
	int algorithm_choice;
	// string userput;

	//start the menu
	cout << "Welcome to 862215973's 8 puzzle solver." << endl;
	cout << "Type '1' to use a default puzzle, or '2' to enter your own puzzle." << endl;

	//let user input the choice
	cin >> userchoice;

    //ignore is used to ignore the char before.
    //if I don't have ignore, when system print the first and second row, it will print in one line.
	//I also check this problem for a long time, then I found the link below to get idea.
	//https://stackoverflow.com/questions/6649852/getline-not-working-properly-what-could-be-the-reasons#:~:text=A%20common%20problem%20while%20using,How%20to%20resolve%20it%3F&text=%2B1%20for%20psychic%20debugging.
    cin.ignore(10, '\n');

	//check the user input 1 or 2
	if (userchoice == 1) {
		//if user input 1, get the default puzzle
		cout << "You have selected the default puzzle." << endl;
        puzzle= getdepuzzle();;

	}
	if (userchoice == 2) {
        string userput;
        string userpuzzle;
		//if user input 2, let user input the puzzle
		cout << "Enter your puzzle, use a zero to represent the blank" << endl;
		cout << "Enter the first row, use space or tabs between numbers:\t\t";
		//get user input puzzle then store them in string userput
		getline(cin, userpuzzle);
		userput = userput + userpuzzle + " ";
		cout << "Enter the second row, use space or tabs between numbers:\t";
		getline(cin, userpuzzle);
		userput = userput + userpuzzle + " ";
		cout << "Enter the third row, use space or tabs between numbers:\t\t";
		getline(cin, userpuzzle);
		userput = userput + userpuzzle + " ";

		//we need to store string into 2d vector
		//2d vector={{a},{a},{a}}
		vector<string>a;
		//b is position, just use one time in here.
		int b=0;
		for (int i = 0; i < 3; i++) {
			puzzle.push_back(a); //this puzzle is the vector in main() function puzzle
			for (int j = 0; j < 3; j++) {
				puzzle.at(i).push_back(userput.substr(b, 1));
				b = b + 2;
			}
		}
	}

	//user choose what algorithm to solve
	cout << endl;
	cout << "Enter your choice of algorithm" << endl;
	cout << "1. Uniform Cost Search" << endl;
	cout << "2. A* with the Misplaced Tile Heuristic." << endl;
	cout << "3. A* with the Eucledian Distance Heuristic." << endl;

    // userchoice=-1;
	cout << endl;
	cin >> algorithm_choice;
	cout << endl;
	cout << "Expanding state" << endl;

	//this function is to print the user input puzzle
	// for (int i = 0; i < 9; i++) {
	// 	if (i != 0 && i % 3 == 0) {
	// 		cout << endl;
	// 	}
	// 	cout << userput[i] << " ";
	// }
	// cout << endl;

	//this function is to set up the initial puzzle
	Node initial(puzzle);
	
	//this function is to store the nodes that need to be explored
	priority_queue<Node> nodes;

	//this function is to mark the node is already explored
	//if the node is explored, mark it true
	map<string, bool> marknodes;

	//this function is to push nodes into queue.
	nodes.push(initial);

	//this function is to calculate the max # of nodes in the queue
	//at the beginning is should be 1 because node always has min size 1.
	int nodesmaxsize = nodes.size();

	//this funtion is to calculate the search algorithm total expanded
	int totalnodes = 0;
	
	//use while loop to search the soluction
	//to find the goal string
	while (algorithm_choice==1||algorithm_choice==2||algorithm_choice==3) {
		
		
		//this function is to find the current max nodes sizes in queue
		if (nodesmaxsize < nodes.size()) {
			nodesmaxsize = nodes.size();
		}

		//this function is to find the best node making explore
		Node rightnow = nodes.top();
		//this function is to pop the best node from the queue
		nodes.pop();

		//this function is to print every step of the puzzle move and find the every step of gn and hn cost.
		if (rightnow.puzzle != initial.puzzle) {
			cout << "The best state to expand with g(n) = " << rightnow.gn << " and h(n) = " << rightnow.hn << " is..." << endl;
			rightnow.printpuzzle();
			cout << "Expanding this node..." << endl;
            cout << endl;
		}
        else {
            //this function is to print the user input puzzle
            rightnow.printpuzzle();
            cout << endl;
        }

		//this function is to check the string is equal to goal or not
		//if equal, print the following
		if (rightnow.goal()) {
            cout << endl;
			cout << "Goal!!!" << endl;
			cout << endl;
			cout << "To solve this problem the search algorithm expanded a total of " << totalnodes << " nodes." << endl;
			cout << "The maximum number of nodes in the queue at any ont time: " << nodesmaxsize << endl;
			cout << "The depth of the goal node was " << rightnow.gn << endl;
            break;
		}

		nodeexpand(rightnow, marknodes, nodes, algorithm_choice);

		//this function is to calculate the depth of node
		//when while loop doing one time, total +1
        totalnodes = totalnodes + 1;
	}
}
