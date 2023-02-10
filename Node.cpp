#include "Node.h"

//setup 2d puzzle
vector<vector<string>> puzzle;
//setup g(n), to calculate the cost to get the node
unsigned gn;
//setup h(n), to calculate the cost from the heuristic
unsigned hn;
//here is to find where is the zero in the puzzle
pair<int, int> zero;
	
//this function is to change 2d vector to string
string Node::twodtostring() {
	string tostring;
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle.at(i).size(); j++) {
			tostring = tostring + puzzle.at(i).at(j);
		}
	}
	return tostring;
}

//this function is to check the string is goal or not.
bool Node::goal() {
	return this->twodtostring() == "123456780";
}

//this function is to initialization the data
Node::Node() {
	//gn = 0;
	//hn = 0;
	zero = make_pair(0, 0);
}

Node::Node(vector<vector<string>> puzz) {
	//gn = 0;
	//hn = 0;
	puzzle = puzz;
	//here is to traverse the all vector to find the coordinates(x,y) about string 0, and store the (x,y)
	for (int i = 0; i < puzz.size(); i++) {
		for (int j = 0; j < puzz.at(i).size(); j++) {
			if (puzz.at(i).at(j) == "0") {
				zero = make_pair(i, j);
			}
		}
	}
}

//this function is to find the cost for the gn and hn
void Node::findgnandhncost(int algorithm_choice) {
	gn++;
	string goal = "123456780";
	int total=0;
	//if user choose Uniform Cost Search(ucs)
	if (algorithm_choice == 1) {
		//in ucs, hn is always equal to 0
		hn = 0;
	}
	//if user choose A* Misplaced Tile Heuristic
	if (algorithm_choice == 2) {

		//use string a to store the string
		string a = this->twodtostring();

		//to compare string a and string goal
		//to find the different between two string
		//if found, h(n)=h(n)+1
		for (int i = 0; i < a.size(); i++) {
			if(a.at(i)!=goal.at(i)){
				total = total + 1;
			}
		}
		hn = total;
	}
	//if user choose A* Eucledian Distance Heuristic
	if (algorithm_choice == 3) {

        //calculate the hn.
        int sum;
        //in 3*3 puzzle, the first space is 1
        //num is also need to calculate the distance for the different number
        int num = 1;
        //two for loop to traverse the whole String
        //to compare with string goal to check which number is difference
		for (int i = 0; i < puzzle.size(); i++) {
            for (int j = 0; j < puzzle.at(i).size(); j++){

                //num can't be 9 because the last space should be 0.
                //stoi is translated string to int.
                //get idea in this link: https://www.udacity.com/blog/2021/05/the-cpp-stoi-function-explained.html
                if (num != 9 && stoi(puzzle.at(i).at(j)) != num && stoi(puzzle.at(i).at(j)) !=0 ){
                        
                    //this function is to find the number in corresponding(x_axis) in 8 puzzle
                    int x_axis=stoi(puzzle.at(i).at(j))%3;
                        
                    // x  1   2   3
                    // --------------
                    // y_____________
                    // 0|_1_|_2_|_3_|
                    // 1|_4_|_5_|_6_|
                    // 2|_7_|_8_|___|
                    // this is the (x,y) corresponding in puzzle, according to find the y,
                    // we can find the relation between the x and y.
                    // 3y+x= num
                        
                    int y_axis=(stoi(puzzle.at(i).at(j))-x_axis)/3;
                    //x is not a index so it need to -1
                    sum=sum+abs(y_axis - i)+abs(x_axis - 1 - j);
                }
                //this function is to check (x,y) is zero or not
                if(stoi(puzzle.at(i).at(j)) == 0) {

                    //we already know zero is always in the last space(9)
                    //x-axis and y-axis is (3,3)
                    //because we start with zero, so it need to -1.
                    sum = sum + abs(this->zero.first-2)+abs(this->zero.second-2);
                }
                num=num + 1;
            }
        }
        hn=sum;
	}
}

//this function is to calculate the total cost
int Node::cost() const{
	int total = gn + hn;
	return total;
}

//this function is to sort queue from small to large
//I got idea on this link:https://web.stanford.edu/class/archive/cs/cs106l/cs106l.1176/lectures/lecture09/09_Functions.pdf
//also on this link:https://web.stanford.edu/class/archive/cs/cs106l/cs106l.1192/lectures/lecture10/10_Classes_and_Operators.pdf
bool Node::operator<(const Node& lhs)const {
	return !(this->cost() < lhs.cost());
}

//here is to print the 2d puzzle
void Node::printpuzzle() {
	for (int i = 0; i < puzzle.size(); i++) {
		for (int j = 0; j < puzzle.at(i).size(); j++) {
			cout << puzzle.at(i).at(j) << " ";
		}
        cout<<endl;
	}
}

