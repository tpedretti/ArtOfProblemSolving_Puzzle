#include <iostream>
#include <fstream> 
#include <string>
#include <sstream> 
#include <list>
#include <stack>

using namespace std;

struct TreeNode
{
    int _data;
    TreeNode* left;
    TreeNode* right;

	TreeNode() {}
	TreeNode(int data)
	{
		_data = data;
		left = nullptr;
		right = nullptr;
	}
};

//Read in input file info
TreeNode* readInFile(int& target);

//Write outcome to file
void writeToFile(stack<char> &path);

//Process Tree to find if any paths lead to our given target
bool hasPathDiv(TreeNode* node, int target, stack<char> &path);

int main()
{
	int target = 0;
	stack<char> path;
	TreeNode *root = readInFile(target);

	hasPathDiv(root, target, path);
	writeToFile(path);

	return 0;
}

TreeNode* readInFile(int& target)
{
    ifstream inFile("pyramid_sample_input.txt");

	if (inFile.is_open())
	{
		string curLine;
		getline(inFile, curLine); //Get the first line for our target number

		target = stoi(curLine.substr(curLine.find(" ")));

		//Get root node from file
		getline(inFile, curLine);
		TreeNode* root = new TreeNode(stoi(curLine));

		//Hold onto the previous nodes the line before
		list<TreeNode*> previousNodes;

		while (getline(inFile, curLine))
		{			
			//stringstream used to make it easier to parse input file
			stringstream ss(curLine); 
			//curLine input stored in a list of TreeNodes
			list<TreeNode*> curInput; 
			//Used to temporarily curInput to then replace all in previousNodes
			list<TreeNode*> tmpHold; 

			//Process the curLine from line and split it at each comma
			for (int i; ss >> i;)
			{
				TreeNode* tmp = new TreeNode(i);
				curInput.push_back(tmp);

				if (ss.peek() == ',')
					ss.ignore();
			}

			//Process the second line from the line
			if (previousNodes.size() == 0) 
			{
				root->left = new TreeNode(*curInput.front());
				root->right = new TreeNode(*curInput.back());

				previousNodes.push_back(root->left);
				previousNodes.push_back(root->right);
			}
			//Process everything from 3rd line and lower
			else 
			{
				//Assign all curNodes to the previous nodes before it
				for (TreeNode* pN : previousNodes) 
				{
					pN->left = curInput.front();
					tmpHold.push_back(curInput.front());
					curInput.pop_front();
					pN->right = curInput.front();
				}

				//Clear all last previousNode list
				previousNodes.clear(); 
				//Push the last curInput node onto the tmp holding
				tmpHold.push_back(curInput.front()); 
				//All nodes in tmpHold which are curInput to previousNodes
				previousNodes = tmpHold; 
				//Clear curInput
				curInput.clear(); 
				//Clear tmp holding
				tmpHold.clear(); 
			}
		}

		inFile.close();
		return root;
	}
	else
	{
		cout << "Failed to open in file!" << endl;
	}

	inFile.close();
	return nullptr;
}

void writeToFile(stack<char> &path)
{
	ofstream outFile("pyramid_sample_output.txt");

	if (outFile.is_open())
	{
		while (!path.empty())
		{
			outFile << path.top();
			path.pop();
		}
	}
	else
	{
		cout << "Failed to write to file!" << endl;
	}

	outFile.close();
}

bool hasPathDiv(TreeNode* node, int target, stack<char> &path)
{
	//Check to main see if root is null
	if (node == nullptr) 
	{
		return (target == 0);
	}
	else
	{
		bool ans = false;
		//Keep track of the recursion sum while processing
		float subSum = target / node->_data; 

		//If our subSum is 0 and doesn't have nodes on the left or right then valid path
		if (subSum == 0 && node->left == nullptr && node->right == nullptr) 
			return true;

		//Go down left side of node
		if (node->left) 
		{
			//If we haven't found a the end of the path and if it isn't valid 
			if (ans == false) 
			{
				path.push('L');
				ans = hasPathDiv(node->left, subSum, path);
			}

			//If we have a valid path dont pop the path off the stack
			if(ans == false) 
				path.pop();
		}

		//Go down right side of node
		if (node->right) 
		{
			//If we haven't found a the end of the path and if it isn't valid
			if (ans == false)  
			{
				path.push('R');
				ans = hasPathDiv(node->right, subSum, path);
			}

			//If we have a valid path dont pop the path off the stack
			if (ans == false) 
				path.pop();
		}
		
		return ans;
	}
}