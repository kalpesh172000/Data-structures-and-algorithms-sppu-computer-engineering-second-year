/*
data stucture and alogorithm lab asignment No.  :
Beginning with an empty binary search tree Construct a binary search tree by inserting the values in the order given . After constructing a binary tree -
i . 	Insert new node
ii .	Find number of nodes in longest path from root
iii . 	Minimum data value found in the tree
iv . 	Change a tree so that the roles of the left and right pointers are swapped at every node
v . 	Search a value
*/

#include<iostream>
#include<string.h>
#include<cstdlib>//for srand function which will generate random numbers;
#include<ctime>// to provide seed value for srand;
#pragma GCC diagnostic ignored "-Wreturn-type" // used this to avoid warning when i dont put return statement

using namespace std;


class node
{
    public:
    int data;
    node *left,*right;
};


class bst
{
	node *root;
	int height,count,minimum;

    //asked in the problem
	void insert(int data);
	void max_len(node*);
	int find_min();
	void swap(node*);
	node* search(node*,int data);


    //extra implemented for practice
    void insert_recurr(node*,node*);
	void inorder(node *root);
	void preorder(node *root);
	void postorder(node *root);

    //search_del, deletion, successor work together
	void search_del(node*&,int,node*&); //searches node and gives node to be deleted and its parent
	void deletion(node*&root,int );     //main deletion function that decides what kind of node is tobe deleted 
                                        //i.e with zero ,one or two childs and deletes it 
	node* successor(node* curr);        //searches for inorder successor

	int check(node* curr);//checks if its a binary trer or not.

	public:
	bst()
	{
		root=NULL;
		height=0;
		count=0;
		minimum=99999;
	}
	void menu();

};


void bst::search_del(node*& curr,int data,node*&parent) // used '*&' cause i wanted to pass the reference of pointer and not just the reference of variable
{
	if(curr==NULL)
		return;
	else if(curr->data>data)
	{
		parent=curr;
		curr=curr->left;
		search_del(curr,data,parent);
	}
	else if(curr->data<data)
	{
		parent=curr;
		curr=curr->right;
		search_del(curr,data,parent);
	}
	else
		return;	//this just stops the execution as changes made in this function also reflect in fuction that called this function
}


void bst::deletion(node*& root,int data)//this needs to be *& to change curr->right in function that called this 
{
	node* curr=root;
	node* parent=NULL;
	node* temp;

	search_del(curr,data,parent);
	temp=curr;
	if(curr==NULL)
	{
		cout<<"\nnumber doesn't exist in the tree";
		return;
	}
	if (curr->left==NULL && curr->right==NULL)
	{
		if(curr!=root)
		{
			if(parent->left==curr)
				parent->left=NULL;
			else
				parent->right=NULL;

		}
		else
			root=NULL;

		free(curr);
		cout<<"\n"<<data<<" is deleted from the tree";
	}
	else if(curr->left!=NULL && curr->right!=NULL)
	{
		node * succ=successor(curr->right);
		int val=succ->data;			//swap node to be deleted with the successor node
		succ->data=curr->data;
		curr->data=val;
		deletion(curr->right,succ->data);	//call the deletion of swaped node
	}
	else
	{
		temp=(curr->left)?curr->left:curr->right;
		if(curr!=root)
		{
			if(parent->left==curr)
				parent->left=temp;
			else
				parent->right=temp;
		}
		else
			root=temp;

		free(curr);
		cout<<"\n"<<data<<" is deleted from the tree";
	}
	return;

}


node* bst::successor(node* curr)
{
	while(curr->left!=NULL)
		curr=curr->left;
	return curr;
}


void bst::insert(int data)
{
	node *curr,*temp;
	temp=new node;
	if(temp==NULL)
    {
        cout<<"memory not allocated"<<endl;
        return;
    }

    temp->data=data;
    temp->left=temp->right=NULL;

    if(root==NULL)
    {
    	root=temp;
    	cout<<"\n"<<data<<" inserted in the bst";
    	return;
    }


    curr=root;

    while(1)
    {
    	if(curr->data>data)
    	{
    		if(curr->left==NULL)
    		{
    			curr->left=temp;
    			cout<<"\n"<<data<<" inserted in the bst";
		    	return;
    		}
    		else
    			curr=curr->left;
    	}
    	else if(curr->data<data)
    	{
    		if(curr->right==NULL)
    		{
    			curr->right=temp;
    			cout<<"\n"<<data<<" inserted in the bst";
		    	return;
    		}
    		else
    			curr=curr->right;
    	}
    	else
    	{
    		cout<<"\n"<<data<<" already exits in the bst";
		    return;
    	}
    }
}


void bst::insert_recurr(node* curr,node *temp)
{
	if(curr->data>temp->data)
	{
		if(curr->left==NULL)
		{
			curr->left=temp;
			cout<<"\n"<<temp->data<<" inserted in the bst";
			return;
		}
		else
			insert_recurr(curr->left,temp);
	}
	else if(curr->data<temp->data)
	{
		if(curr->right==NULL)
		{
			curr->right=temp;
			cout<<"\n"<<temp->data<<" inserted in the bst";
			return;
		}
		else
			insert_recurr(curr->right,temp);
	}
	else
	{
		cout<<"\n"<<temp->data<<" already exits in the bst";
		return;
	}
}


void bst::max_len(node *curr)
{
	if(height < count)
		height=count;
	if(curr!=NULL)
	{
		count++;
		cout<<curr->data<<"-"<<count<<" ";
		max_len(curr->left);
		max_len(curr->right);
        count--;
	}
}


int bst::find_min()
{
	node* curr;
	curr=root;
	while(curr->left!=NULL)
		curr=curr->left;
	return curr->data;
}


void bst::swap(node *curr)
{
	node *temp;
	if(curr!=NULL)
	{
		temp=curr->left;
		curr->left=curr->right;
		curr->right=temp;
		swap(curr->left);
		swap(curr->right);
	}
}


node* bst::search(node *curr,int data)
{
	if(curr==NULL)
		return NULL;
	if(data < curr->data)
		search(curr->left,data);
	else if(data > curr->data)
		search(curr->right,data);
	else
		return curr;
}


void bst::inorder(node *curr)
{
	if(curr!=NULL)
	{
		inorder(curr->left);
		cout<<curr->data<<" ";
		inorder(curr->right);
	}
}


void bst::preorder(node *curr)
{
	if(curr!=NULL)
	{
		cout<<curr->data<<" ";
		preorder(curr->left);
		preorder(curr->right);
	}
}


void bst::postorder(node *curr)
{
	if(curr!=NULL)
	{
		postorder(curr->left);
		postorder(curr->right);
		cout<<curr->data<<" ";
	}
}


int bst::check(node *curr)
{
	int flag=1;
	if(curr!=NULL)
	{
		if(curr->left!=NULL)
			if(curr->left->data>curr->data)
				return 0;
		if(curr->right!=NULL)
			if(curr->right->data<curr->data)
				return 0;
		flag = check(curr->left);
		if(flag==0)
			return 0;
		flag = check(curr->right);
	}
	return flag;
}


void bst::menu()
{
	int ch;
	int data,total,random;
	node* curr;
	// insert(15);//default tree
	// insert(10);
	// insert(20);
	// insert(11);
	// insert(5);
	// insert(23);
	// insert(30);

    while(true)
    {
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. insert";
		cout<<"\n2. Number of nodes in the longest path";
		cout<<"\n3. search minimun data value";
		cout<<"\n4. Swap tree order";
		cout<<"\n5. search in tree";
		cout<<"\n6. display inorder";
		cout<<"\n7. display preorder";
		cout<<"\n8. display postorder";
		cout<<"\n9. delete node";
		cout<<"\n10.check in its a binary tree";
		cout<<"\n11.insert recurcive";
		cout<<"\n12.insert random numbers";
		cout<<"\n13.exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;

        switch(ch)
        {
            case 1:
				cout<<"\nenter the number you want to insert: ";
				cin>>data;
            	insert(data);
                break;
            case 2:
				max_len(root);
				cout<<"\nnumber of nodes in longest path is: "<<height;
                break;
            case 3:
				minimum=root->data;
				cout<<"\nminimum number in the tree is: "<<find_min();
                break;
            case 4:
            	swap(root);
                break;
			case 5:
				cout<<"\nenter the number you want to search: ";
				cin>>data;
				if(search(root,data)!=NULL)
					cout<<"\nnumber is present in the tree";
				else
					cout<<"\nnumber is not present in tree";
				break;
            case 6:
				cout<<"\ninorder: ";
                inorder(root);
				break;
			case 7:
				cout<<"\npreorder: ";
				preorder(root);
                break;
			case 8:
				cout<<"\npostorder: ";
				postorder(root);
                break;
			case 9:
				cout<<"\nenter the number you want to delete: ";
				cin>>data;
				deletion(root,data);
                break;
			case 10:
                if(check(root))
					cout<<"\ngiven tree is binary tree";
				else
					cout<<"\ngiven tree is not a binary tree";
				break;
			case 11:
				node* temp;
				temp=new node;
				if(temp==NULL)
				{
					cout<<"\nmemory not allocated";
					return;
				}
				cout<<"\nenter the number you want to insert: ";
				cin>>data;
				temp->data=data;
    			temp->left=temp->right=NULL;
				insert_recurr(root,temp);
                break;
			case 12:
				cout<<"\nenter how many numbers you want to insert: ";
				cin>>total;
				srand((unsigned) time(NULL));
				for(int i=0;i<total;i++)
				{
					random=1+(rand()%100);
					insert(random);
				}
                break;
			case 13:
                return;
            default:
                cout<<"\nenter the correct choice";
        }
    }
}


int main()
{
	bst b;
	b.menu();
}
