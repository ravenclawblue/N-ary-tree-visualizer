#include<graphics.h>
#include<bits/stdc++.h>
using namespace std;
class TreeNode
{
	public:

	int val;
	vector<TreeNode*> children;

	TreeNode(int n)
	{
		this -> val = n;
	}
};

class Node{
	public:
	int xmin,xmax;
	TreeNode* node;
	Node(int xmin,int xmax,TreeNode* curr){
		this->xmin=xmin;
		this->xmax=xmax;
		this->node=curr;
	}
};

void createTree(TreeNode *root)
{
	queue<TreeNode*> q;
	q.push(root);

	while(!q.empty())
	{
		TreeNode* curr = q.front();
		q.pop();

		cout << "Enter children of " << curr -> val << ", Press 'q' to exit: ";
		string ch = "a";
		while(ch != "q")
		{
			cin >> ch;
			if(ch == "q") break;

			TreeNode *child = new TreeNode(stoi(ch));
			curr -> children.push_back(child);
			q.push(child);
		}
	}
}

double convert(float deg){
	return deg*3.14159/180;
}

int y = 200;

void display(TreeNode* root){
	 queue<Node> pq;
	 setcolor(BLUE);
	 Node rand(0,1600,root);
	 pq.push(rand);
	 circle(800,100,20);

	 int r=20;
	 outtextxy(800-7,100-7,&(to_string(root->val))[0]);
	 while(!pq.empty()){
	 	int size=pq.size();
	 	while(size--){
	 		auto q=pq.front();
	 		pq.pop();
	 		TreeNode* curr = q.node;
		    int total_width = q.xmax-q.xmin;
			int xmax = q.xmax;
			int xmin = q.xmin;
			int x1 = (xmax + xmin)/2;
			int y1 = y-100;
			if(curr -> children.size() > 0)
			{
				int gap = total_width / curr->children.size();
				double angle=135;
				for(int i = 0 ; i < curr -> children.size(); i++)
				{
					circle(xmin + (i * gap) + gap/2, y, 20);
				   floodfill(xmin + (i * gap) + gap/2,y, BLUE);
				   outtextxy(xmin + (i * gap) + gap/2 - 7, y - 7, &(to_string(curr->children[i]->val))[0]);
				   int x2=xmin+(i*gap)+gap/2,y2=y;
				   line(x1+r*cos(convert(angle)),y1 + r*sin(convert(angle)),x2 + r*cos(convert(-90)),y2+r*sin(convert(-90)));
				   Node n(xmin + i * gap, xmin + (i + 1)*gap, curr -> children[i]);
				   pq.push(n);
				   angle -= 45;
				}
			}
		 }
		 y += 100;
	 }
}

void preOrder(TreeNode* root, string &pre)
{
    if(root == NULL) return;

    pre += to_string(root -> val ) + " ";
    for(auto &x : root -> children)
        preOrder(x, pre);
}

void postOrder(TreeNode* root, string &post)
{
    if(root == NULL) return;

    for(auto &x : root -> children)
        postOrder(x, post);
    post += to_string(root -> val ) + " ";
}

void levelOrder(TreeNode *root, string &level)
{
	queue<TreeNode*> q;
	q.push(root);

	while(!q.empty())
	{
		int s = q.size();
		while(s--)
		{
			TreeNode* curr = q.front();
			q.pop();
			level += to_string(curr -> val) + " ";

			for(int i = 0; i < curr -> children.size(); i++)
				q.push(curr -> children[i]);
		}
	}
}

void DFS(TreeNode* root, string &ans, int goal, bool &found)
{
	if(root == NULL) return;
	ans += to_string(root -> val) + " ";
	if(root -> val == goal) found = true;

	for(auto &x : root -> children) 
	{
		if(!found)
			DFS(x, ans, goal, found);
	}
}

void DLS(TreeNode* root, string &ans, int goal, bool &found, int currHeight, int height)
{
	if(root == NULL || currHeight > height) return;
	ans += to_string(root -> val) + " ";
	if(root -> val == goal) found = true;

	for(auto &x : root -> children) 
	{
		if(!found)
			DLS(x, ans, goal, found, currHeight + 1, height);
	}
}

bool DLS(TreeNode* root, int goal, int limit, string &ans)
{
	if (limit < 0) return false;
	
	ans += to_string(root -> val) + " ";
    if (root -> val == goal) return true;
   
    // Recur for all the vertices adjacent to source vertex
    for (auto &x : root -> children)
       if (DLS(x, goal, limit - 1, ans) == true)
          return true;
   
     return false;
}
 
bool IDDFS(TreeNode* root, int goal, int max_depth)
{
	int y1 = y;
	string display = "Depth                      Iterative Deepening Depth First Search";
	outtextxy(400, y1, &display[0]);

	
    for (int i = 0; i <= max_depth; i++)
    {
    	string s = to_string(i);
    	y1 += 50;
    	outtextxy(400, y1, &s[0]);
    	
    	string ans = "";
    	bool found = DLS(root, goal, i, ans);
    	outtextxy(500, y1, &ans[0]);
	    if (found) return true;
    }
   
    return false;
}

bool IBBFS(TreeNode *root, int goal, int max_depth, int curr)
{
	queue<TreeNode*> q;
	q.push(root);
	
	int y1 = y;
	string ans = "";
	string s = to_string(curr);
	y1 += 50;

	while(!q.empty() && curr--)
	{
		int si = q.size();
		outtextxy(400, y1, &s[0]);
		string ans = "";
		
		while(si--)
		{
			TreeNode* curr = q.front();
			q.pop();
			
			ans += to_string(root -> val) + " ";
			if(curr -> val == goal)
			{
				return true;	
			}
			
			for(auto &x : curr -> children) q.push(x);		
		}
		outtextxy(500, y1, &ans[0]);
	}

	return false;
}


int main()
{
	initwindow(1600,800);
	setbkcolor(15);
	cleardevice();
	int n;
	cout << "\nEnter root data: ";
	cin >> n;
	TreeNode* root = new TreeNode(n);
	createTree(root);
	display(root);

	start:
	int x;
	cout << "\n----------------------------Menu Options for Searching Goal Node and Printing Path--------------------------" << endl;
	cout << "\n\t 1. Using BFS\n\t 2. Using DFS(Root-Left-Right)\n\t 3. Using DLS(Depth Limited Search)\n\t 4. Using IDS(Iterative Deepening Search)\n\t 5. Using IBS(Iterative Broadening Search) \n\t 6. Exit" << endl;
	cin >> x;

	switch(x)
	{
		case 1:
		{
			int goal;
			bool found = false;
			cout << "Enter the goal node's value : ";
			cin >> 	goal;

			queue<TreeNode*> q;
			q.push(root);
			string ans = "BFS Order for finding " + to_string(goal) + " : ";
			y -= 100;

			while(!q.empty() && !found)
			{
				int s = q.size();
				while(s-- && !found)
				{
					TreeNode* curr = q.front();
					q.pop();

					ans += to_string(curr -> val) + " ";

					if(curr -> val == goal)
					{
						found = true;
						continue;
					}

					for(auto &y : curr -> children)
						q.push(y);
				}
			}
			
			for(int i = 0; i < 30; i++) ans += " ";


			if(found)
			{
				setcolor(BLUE);
				outtextxy(400, y, &ans[0]);
			}
			else cout << "The Goal node " << goal << " is not present in the tree." << endl;
			goto start;
		}

		case 2:
		{
			int goal;
			cout << "Enter the goal node's value : ";
			cin >> goal;

			string ans = "DFS Order for finding " + to_string(goal) + " : ";
			bool found = false;
			DFS(root, ans, goal, found);
			for(int i = 0; i < 30; i++) ans += " ";
			
			if(found)
			{
				setcolor(BLUE);
				outtextxy(400, y, &ans[0]);
			}
			else cout << "The Goal node " << goal << " is not present in the tree." << endl;
			goto start;
		}
		
		case 3:
		{
			int h, goal;
			cout << "\nEnter the height you want to search: ";
			cin >> h;
			cout << "\nEnter the goal node: ";
			cin >> goal;
			
			string ans = "DLS Order for finding " + to_string(goal) + " : ";
			bool found = false;
			DLS(root, ans, goal, found, 0, h);
			for(int i = 0; i < 30; i++) ans += " ";
			
			if(found)
			{
				setcolor(BLUE);
				outtextxy(400, y, &ans[0]);
			}
			else cout << "The Goal node " << goal << " is not present in the tree within given height." << endl;
			goto start;
		}
		
		case 4:
		{
			int h, goal;
			cout << "\nEnter the height you want to search: ";
			cin >> h;
			cout << "\nEnter the goal node: ";
			cin >> goal;
			
			string ans = "IDS Order for finding " + to_string(goal) + " : ";
			bool found = IDDFS(root, goal, h);
			for(int i = 0; i < 30; i++) ans += " ";
			
			if(found)
			{
				setcolor(BLUE);
//				outtextxy(400, y, &ans[0]);
			}
			else cout << "The Goal node " << goal << " is not present in the tree within given height." << endl;
			goto start;
		}
		
		case 5:
		{
			int h, goal;
			cout << "\nEnter the height you want to search: ";
			cin >> h;
			cout << "\nEnter the goal node: ";
			cin >> goal;
			
			string ans = "IBS Order for finding " + to_string(goal) + " : ";
			
			bool found = false;
			found = IBBFS(root, goal, h, h);
			if(found) break;
			else cout << "The Goal node " << goal << " is not present in the tree within given height." << endl;
			
//			for(int i = 0; i < h; i++)
//			{
//			}
			goto start;
		}

		case 6: break;
	}


//	y -= 100;
//	setcolor(BLUE);
//	string pre = "Pre-Order Traversal: ";
//	preOrder(root, pre);
//	outtextxy(400, y, &pre[0]);
//
//	string post = "Post-Order Traversal: ";
//	postOrder(root, post);
//	outtextxy(400, y + 50, &post[0]);
//
//	string level = "Level-Order Traversal: ";
//	levelOrder(root, level);
//	outtextxy(400, y + 100, &level[0]);

	system("pause");
	closegraph();
	return 0;
}
