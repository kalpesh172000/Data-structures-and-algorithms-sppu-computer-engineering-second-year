/*
data stucture and alogorithm lab asignment No. 5 :
Construct an expression tree from the given prefix expression eg . +--a*bc/def and 
traverse it using post order traversal non recursive and then delete the entire tree .
*/
#include<iostream>
#include<string>

using namespace std;

#define max 20

class node
{
    public:
    char data;
    node *left,*right;
};

//----start of stack implementation--------------------

class stack
{
    public:
    int top;
    node *st[max];
    int check[max];
    
    stack()
    {
        for(int i=0;i<max;i++)
        {
            st[i]=NULL;
            check[i]=1;
        }
        top=-1;
    }
    bool empty();
    void push(node*);
    node* pop();
    int gettop();

};

bool stack::empty()
{
    return (top==-1)?1:0;
}

void stack::push(node *curr)
{
    st[++top]=curr;
    check[top]=1;
}

node* stack:: pop()
{
    return st[top--];
}


int stack::gettop()
{
    return check[top];
}

//----end of stack implementation--------------------


class exptree
{
    node* root;
    void insert(string exp);
    node* create_node(char ch);
    void delete_tree();
    void postorder();

    //extra implementation
    void inorder();
    int evaluate(node*);    //only works when the expression has operands from 0-9
    
    public:
    void menu();
    exptree()
    {
        root=NULL;
    }
};


int exptree::evaluate(node* curr)
{
    if (!curr)
        return 0;
    if (!curr->left && !curr->right)
        return curr->data-48;
    
    int l_val = evaluate(curr->left);
 
    int r_val = evaluate(curr->right);

    if (curr->data=='+')
        return l_val+r_val;
 
    if (curr->data=='-')
        return l_val-r_val;
 
    if (curr->data=='*')
        return l_val*r_val;
 
    return l_val/r_val;
}


node* exptree::create_node(char ch)
{
    node *temp;
    
    temp=new node;
    if(temp==NULL)
    {
        cout<<"\nmemory not allocated";
        exit(1);
    }
    temp->data=ch;
    temp->left=temp->right=NULL;
    return temp;
}


void exptree::insert(string exp)
{
    node *curr,*curr1,*curr2;
    char ch;
    stack maketree;
    int len=exp.length();

    for(int i=len-1;i>=0;i--)
    {
        ch=exp[i];
        curr=create_node(ch);
        if( ((ch>=97)&&(ch<=122))||((ch>=65)&&(ch<=90))||((ch>=48)&&(ch<=57)))
        {
            maketree.push(curr);
        }
        else if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/'))
        {
            curr1 = maketree.pop();
            curr2 = maketree.pop(); //pop 2 and attach them to operator 
            curr->left=curr1;
            curr->right=curr2;
            maketree.push(curr);    //push the operator in stack with its 2 subtrees attached to it
        }
        else 
        {
            cout<<"\nyour expression contains a symbol that can't be processed";
            return;
        }
    }
    root=curr;
}


void exptree::delete_tree()
{
    stack del;
    node* curr=root,*temp;
    bool bracket=1;
    if(curr==NULL)
    {
        cout<<"\ntree doesn't exit yet";
        return;
    }
    while(true)
    {
        while(curr!=NULL)
        {
            del.push(curr);  
            curr=curr->left;
        }
        if(!del.empty())
        {
            curr=del.pop();
            temp=curr;
            curr=curr->right;
            delete temp;
        }
        else
        {
            root=NULL;
            cout<<"\ntree is deleted";
            return;
        }
            
    }
}


void exptree::postorder()
{
    node* curr=root;
    stack post;


    if(root==NULL)
    {
        cout<<"\ntree doesn't exit yet";
        return;
    }
    cout<<"\nPostorder: ";
    while(true)
    {
        while(curr!=NULL)
        {
            post.push(curr);    // you are going to left so make it 1 
            curr=curr->left;    // so when you go from left child to parent it wont show parent 
        }                       // cause it still needs to go to right child 
        while(post.gettop()==0) // 0 means its right child was visited 
        {                       // this is loop cause you can keep going from right child to parent 
            curr=post.pop();
            cout<<curr->data;
            if(post.empty())
                return;
        }
        curr=post.st[post.top]; // you dont pop parent cause we still haven't shown it 
        curr=curr->right;       // go to right child now 
        post.check[post.top]=0; // make it 0 , you are going to right so when you return it will check if its zero 
    }

}


void exptree::inorder()
{
    stack in_ord;
    node* curr=root;
    bool bracket=1;
    if(curr==NULL)
    {
        cout<<"\ntree doesn't exit yet";
        return;
    }
    cout<<"\nInorder: ";
    while(true)
    {
        while(curr!=NULL)
        {
            in_ord.push(curr); 
            curr=curr->left;
        }
        if(!in_ord.empty())
        {
            curr=in_ord.pop();
            cout<<curr->data;
            curr=curr->right;
        }
        else
            return;
    }
}


void exptree::menu()
{
    int ch;
	string exp;
	node* curr;
    insert("+--a*bc/def");  //default prefix expression
    while(true)
    {
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. Enter a new prefix expression";
		cout<<"\n2. Display expression in inorder";
		cout<<"\n3. Display expression in postorder";
        cout<<"\n4. evaluate expression (only if numbers are inputed as an operands)";
		cout<<"\n5. Delete the tree";
        cout<<"\n6. Exit";
		cout<<"\n\nEnter the choice: ";
		cin>>ch;
		
        switch(ch)
        {
            case 1:
				cout<<"\nEnter a new prefix expression: ";
                cin.ignore();
				cin>>exp;
            	insert(exp);
                break;
            case 2:
				inorder();
                break;
            case 3:
                postorder();
                break;
            case 4:
                if(root)
                    cout<<"\nevaluation of tree is :"<<evaluate(root);
                else
                    cout<<"\ntree is empty";
                break;
            case 5:
                delete_tree();
            	break;
            case 6:
                return;
            default:
                cout<<"\nenter the correct choice";
        }
    }
}


int main()
{
    exptree e;
    e.menu();
    return 0;
}
