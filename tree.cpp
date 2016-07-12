#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*树分为二叉树，多叉树
二叉树分为：二叉搜索树，平衡二叉树
二叉搜索树(binary search tree)：它或者是一棵空树，或者是具有下列性质的二叉树，
若它的左子树不空，则左子树上所有节点的值均小于他的根节点的值；若右子树不空，
则右子树上所有节点的值大于他的根节点的值；他的左右子树也分别为二叉搜索树

平衡二叉树(AVL树)：它或者是一棵空树，或者是具有以下性质的二叉树，它的左右子树
都是平衡二叉树，且左子树和右子树的高度之差绝对值不超过1

红黑树：它是一种自平衡二叉查找树*/
struct Node
{
	Node(int v, Node *pr = nullptr): val(v), parent(pr) {children = vector<Node*>(2, nullptr);}
	int val;
	int deltaHgt = 0;
	Node *parent = nullptr;
	vector<Node*> children;
};
class Tree
{
public:
	Tree() {}
	Tree(Node *r): root(r) {}
	Node * Root() {return root;}
	void Insert(int v)
	{
		Node **p = &root;
		Node *entry = nullptr;
		while (*p != nullptr)
		{
			entry = *p;
			if (v > entry->val)
			{
				p = &(entry->children[1]);
			}
			else if (v < entry->val)
			{
				p = &(entry->children[0]);
			}
			else return;
		}
		*p = new Node(v, entry);
	}

	void InsertAvl(int v)
	{

	}
	bool Search(int v)
	{
		Node **p = &root;
		while (*p != nullptr)
		{
			if (v == (*p)->val)
			{
				return true;
			}
			else if (v < (*p)->val)
			{
				p = &((*p)->children[0]);
			}
			else p = &((*p)->children[1]);
		}
		return false;
	}
	void display(Node *p)
	{
		cout << string(count++, '-') << p->val << endl;
		for (const auto &n: p->children)
		{
			if (n != nullptr)
			{
				display(n);
			}
		}
		--count;
	}

private:
	Node *root = nullptr;
	int count = 0;
};
int main()
{
	vector<int> n = {50, 78, 60, 3, 6, 9, 99, 54, 78};
	Tree tree;
	for (const auto &i: n)
	{
		tree.Insert(i);
	}
	tree.display(tree.Root());
	cout << "display fin" << endl;
	cout << (tree.Search(9)? "yes": "no") << endl;
	return 0;
}
