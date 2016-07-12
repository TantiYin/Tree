#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>

using namespace std;
/*trie树，又称字典树
有以下性质：
1.根节点不包含字符，除根节点外每一个节点都只包含一个字符
2.从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串
3.每个节点的所有子节点包含的字符都不相同*/
struct Node
{
	Node() {}
	Node(char c1, int f = 0): c(c1), occurTimes(f) {}
	int occurTimes = 0;
	char c = '\0';
	unordered_map<char, Node*> children;
};

class Trie
{
public:
	Trie() {root = new Node();}
	Node * Root() {return root;}
	void Insert(string s)
	{
		Node *p = root;
		int i = 0;
		while (i < s.length())
		{
			if (p->children.find(s[i]) == p->children.end())
			{				
				Node *tmp = new Node(s[i]);
				p->children[s[i]] = tmp;
			}
			p = p->children[s[i]];
			++i;
		}
		p->occurTimes += 1;
	}
	bool Search(string s)
	{
		Node *p = root;
		int i = 0;
		while (i < s.length())
		{
			if (p->children.find(s[i]) == p->children.end()) return false;
			p = p->children[s[i]];
			++i;
		}
		if (p->occurTimes) return true;
	}
	void display(Node *p)
	{
		cout << string(count++, '-');
		cout << p->c << ":" << p->occurTimes << endl;
		for (const auto &n: p->children)
		{
			display(n.second);
		}
		--count;
	}
	void Display()
	{
		display(root);
	}
	void bfs()
	{
		queue<Node*> q;
		q.push(root);
		while (!q.empty())
		{
			cout << q.front()->c << " ";
			for (const auto &n: q.front()->children)
			{
				q.push(n.second);
			}
			q.pop();
		}
		cout << endl;
	}

private:
	Node *root = nullptr;
	int count = 0;
};
vector<vector<bool>> paths;
string tmp;

void generateString(Trie &trie, vector<vector<char>> &board, int r, int c)
{
	if (paths[r][c] == true) return;
	tmp += board[r][c];
	trie.Insert(tmp);
	paths[r][c] = true;
	if ((r + 1) < board.size()) generateString(trie, board, r + 1, c);
	if ((c + 1) < board[0].size()) generateString(trie, board, r, c + 1);
	if ((r - 1) >= 0) generateString(trie, board, r - 1, c);
	if ((c - 1) >= 0) generateString(trie, board, r, c - 1);
	paths[r][c] = false;
	tmp = tmp.substr(0, tmp.length() - 1);
}

void search(vector<string> &res, Node* root, vector<vector<char>> &board, int r, int c)
{
	if (board[r][c] == '\0') return;
	if (root->children.find(board[r][c]) != root->children.end())
	{
		char ch = board[r][c];
		board[r][c] = '\0';
		tmp += ch;
		if (root->children[ch]->occurTimes)
		{
			root->children[ch]->occurTimes = 0;
			res.push_back(tmp);
		}
		if ((r + 1) < board.size()) search(res, root->children[ch], board, r + 1, c);
		if ((c + 1) < board[0].size()) search(res, root->children[ch], board, r, c + 1);
		if (r - 1 >= 0) search(res, root->children[ch], board, r - 1, c);
		if (c - 1 >= 0) search(res, root->children[ch], board, r, c - 1);
		board[r][c] = ch;
		tmp = tmp.substr(0, tmp.length() - 1);
	}
}

vector<string> findword(vector<vector<char>> &board, vector<string> strs)
{
	/*Trie trie;
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[0].size(); ++j)
		{
			paths = vector<vector<bool>>(board.size(), vector<bool>(board[0].size(), false));
			tmp = "";
			generateString(trie, board, i, j);
		}
	}
	vector<string> res;
	for (int i = 0; i < strs.size(); ++i)
	{
		if (trie.Search(strs[i])) res.push_back(strs[i]);
	}
	return res;*/
	Trie trie;
	for (int i = 0; i < strs.size(); ++i)
	{
		trie.Insert(strs[i]);
	}
	trie.Display();
	cout << "display finished" << endl;
	trie.bfs();
	cout << "bfs fin" << endl;
	vector<string> res;
	for (int i = 0; i < board.size(); ++i)
	{
		for (int j = 0; j < board[0].size(); ++j)
		{
			tmp = "";
			search(res, trie.Root(), board, i, j);
		}
	}
	return res;
}

int main()
{
	vector<string> strs = {
		"oath",
		"pea",
		"eat",
		"rain",
		"abc"
	};
	/*string s1 = "abc", s2 = "jira";
	Trie trie;
	for (int i = 0; i < strs.size(); ++i)
	{
		trie.Insert(strs[i]);
	}
	cout << (trie.Search(s1)? "yes": "no") << endl;
	cout << (trie.Search(s2)? "yes": "no") << endl;*/
	vector<vector<char>> board = {
		{'o', 'a', 'a', 'n'},
		{'e', 't', 'a', 'e'},
		{'i', 'h', 'k', 'r'},
		{'i', 'f', 'l', 'v'}
	};
	vector<vector<char>> board2 = {
		{'a', 'b'}
	};
	vector<string> sea = {"ba"};
	vector<string> res = findword(board2, sea);
	for (const auto &s: res)
	{
		cout << s << endl;
	}
	return 0;
}
