#include <iostream>
#include <fstream> 
#include <string>
#include <sstream> 
#include <vector>
#include <list>
#include <stack>

using namespace std;

struct TreeNode
{
    int _data;
	int _level;
    TreeNode* left;
    TreeNode* right;
	TreeNode* previous;


	TreeNode() {}
	TreeNode(int data)
	{
		_data = data;
		left = nullptr;
		right = nullptr;
		previous = nullptr;
	}
	TreeNode(int data, int level)
	{
		_data = data;
		_level = level;
		left = nullptr;
		right = nullptr;
		previous = nullptr;
	}
};

//Read in input file info
TreeNode* readInFile(int& target);
void writeToFile(stack<char> path);

//Process Tree and find all paths that could be taken
void findPathes(TreeNode* root, int target, int curTotal);

void printPreorder(TreeNode* node, int& total);

bool hasPathDiv(TreeNode* node, int target, vector<char>& path);

int main()
{
	int target;
	int total = 1;
	vector<char> path;
	TreeNode *root = readInFile(target);
	hasPathDiv(root, target, path);
}

TreeNode* readInFile(int& target)
{
    ifstream inFile("pyramid_sample_input.txt");
	string curLine;
	getline(inFile, curLine); //Get the first line for our target number

	target = stoi(curLine.substr(curLine.find(" ")));

	//Get root node from file
	getline(inFile, curLine);
	TreeNode *root = new TreeNode(stoi(curLine), 1);	

	//Get all other values and assign to tree
	list<TreeNode*> previousNodes;
	int count = 2;

	while (getline(inFile, curLine))
	{
		stringstream ss(curLine);
		list<TreeNode*> curInput;
		list<TreeNode*> tmpHold;

		for (int i; ss >> i;)
		{
			TreeNode* tmp = new TreeNode(i, count);
			curInput.push_back(tmp);

			if (ss.peek() == ',')
				ss.ignore();
		}

		if (previousNodes.size() == 0) //On second line after the root
		{
			root->left = new TreeNode(*curInput.front());
			root->left->_level = count;
			root->right = new TreeNode(*curInput.back());
			root->right->_level = count;

			previousNodes.push_back(root->left);
			previousNodes.push_back(root->right);
		}
		else
		{
			for (TreeNode* pN : previousNodes)
			{
				pN->left = curInput.front();
				tmpHold.push_back(curInput.front());
				curInput.pop_front();
				pN->right = curInput.front();
			}

			previousNodes.clear();
			tmpHold.push_back(curInput.front());
			previousNodes = tmpHold;
			curInput.clear();
			tmpHold.clear();
		}

		count++;
	}

	return root;
}

void findPathes(TreeNode* root, int target, int curTotal)
{
	if (root == NULL)
	{
		return;
	}

	stack<TreeNode*> nodeStack;
	nodeStack.push(root);
	curTotal = root->_data;

	while (!nodeStack.empty())
	{
		TreeNode* node = nodeStack.top();
		cout << "{L: " << node->_level << ", D: " << node->_data << "}" << endl;

		nodeStack.pop();

		if (node->right)
			nodeStack.push(node->right);
		else
		{

		}


		if (node->left)
			nodeStack.push(node->left);
		else
		{

		}
	}
}

void printPreorder(TreeNode* node, int &total)
{
	if (node->left == NULL && node->right == NULL)
	{
		cout << node->_data << " ";
		return;
	}

	/* first print data of node */
	cout << node->_data << " ";

	/* then recur on left sutree */
	printPreorder(node->left, total);

	/* now recur on right subtree */
	printPreorder(node->right, total);
}

bool hasPathDiv(TreeNode* node, int target, vector<char>& path)
{
	if (node == nullptr)
	{
		return (target == 0);
	}
	else
	{
		bool ans = false;
		float subSum = target / node->_data;		

		if (subSum == 0 && node->left == nullptr && node->right == nullptr)
			return true;

		if (node->left)
		{
			ans = ans;
			path.push_back('L');			
			hasPathDiv(node->left, subSum, path);
			path.pop_back();
		}

		if (node->right)
		{
			ans = ans;
			path.push_back('R');			
			hasPathDiv(node->right, subSum, path);
			path.pop_back();
		}

		
		return ans;
	}
}

void writeToFile(stack<char> path)
{

}