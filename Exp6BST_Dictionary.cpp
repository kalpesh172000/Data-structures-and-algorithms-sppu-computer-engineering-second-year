/*
data stucture and alogorithm lab asignment No. 6 :
A Dictionary stores keywords and its meanings .
Provide facility for -
1. adding new keywords
2. deleting keywords
3. updating values of any entry
4. Provide a facility to display whole data sorted in ascending / Descending order
5. Also find how many maximum comparisons may require for finding any keyword
Use Binary Search Tree for Implementation .
*/


#include<iostream>
#include<string>

using namespace std;


struct entry
{
    string word,meaning;
    entry *lchild,*rchild;
};


class dictionary
{
    entry *root;
    int height,count;

    void insert(string ,string);
    void update(string ,string);
    void search(entry*&,string);

    void max_comparisions(entry*); 
    void display_asc(entry*);
    void display_dec(entry*);

    void del_word(entry*&,string);
    void getparent(entry*&,string,entry*&);
    entry* successor(entry*);

    public:
    void menu();
    dictionary()
    {
        root=NULL;
        height=0;
		count=0;
    }
};


void dictionary::insert(string word,string meaning)
{
    entry *current,*temp;

    temp=new entry;
    if(temp==NULL)
    {
        cout<<"\nmemory not allocated";
        return;
    }
    temp->word=word;
    temp->meaning=meaning;
    temp->lchild=temp->rchild=NULL;

    if(root==NULL)
    {
        root=temp;
        cout<<"\n\'"<<word<<"\' was inserted in the dictionary";
        return;
    }

    current=root;
    while(1)
    {
    	if(current->word>word)
    	{
    		if(current->lchild==NULL)
    		{
    			current->lchild=temp;
    			cout<<"\n\'"<<word<<"\' was inserted in the dictionary";
		    	return;
    		}
    		else
    			current=current->lchild;
    	}
    	else if(current->word<word)
    	{
    		if(current->rchild==NULL)
    		{
    			current->rchild=temp;
    			cout<<"\n\'"<<word<<"\' was inserted in the dictionary";
		    	return;
    		}
    		else
    			current=current->rchild;
    	}
    	else
    	{
    		cout<<"\n"<<word<<" already exits in the dictionary";
		    return;
    	}
    }
}


void dictionary::update(string word,string meaning)
{
    entry* current=root;

    search(current,word);

    if(current==NULL)
    {
        cout<<"\nWord doesn't exist in the dicitonary";
        return;
    }
    current->meaning=meaning;
    cout<<"\nmeaning for word \'"<<word<<"\' was changed";
}


void dictionary::del_word(entry *&root,string word)
//this needs to be *& to change rchild in previous call
{
    entry *current=root;
    entry *parent=NULL;
    entry *temp;
    getparent(current,word,parent);
    //'current' and 'parent' passed by refference

    temp=current;

    if(current==NULL)
    {
        cout<<"\n\'"<<word<<"\' doesn't exist in the dictionary";
        return;
    }

    if(current->lchild==NULL && current->rchild==NULL)
    {
        if(current!=root)
        {
            if(parent->lchild==current)
                parent->lchild=NULL;
            else
                parent->rchild=NULL;
        }
        else
            root=NULL;
        delete current;
        cout<<"\n\'"<<word<<"\' was deleted from the dictionary";
    }
    else if(current->lchild!=NULL && current->rchild!=NULL)
    {
        entry* succ=successor(current->rchild);
        string temp1,temp2;

        temp1=succ->word;
        temp2=succ->meaning;

        succ->word=current->word;
        succ->meaning=current->meaning;

        current->word=temp1;
        current->meaning=temp2;

        del_word(current->rchild,succ->word);
        //passed as refference in case it gets NULLed then current in this fuction
        //will be parent and it's rchild field will get NULLed
    }
    else
    {
        temp=(current->lchild)?current->lchild:current->rchild;
        if(current!=root)
        {
            if(parent->lchild==current)
                parent->lchild=temp;
            else
                parent->rchild=temp;
        }
        else
            root=temp;
        delete current;
        cout<<"\n\'"<<word<<"\' was deleted from the dictionary";
    }
}


void dictionary::getparent(entry *&current,string word,entry *&parent)
{
    if(current==NULL)
        return;
	else if(word < current->word)
	{
		parent = current;
		current = current->lchild;
		getparent(current,word,parent);
	}
	else if(word > current->word)
	{
		parent = current;
		current = current->rchild;
		getparent(current,word,parent);
	}
	else
        return;

}


entry* dictionary::successor(entry *current)
{
    while (current->lchild!=NULL)
        current=current->lchild;
    return current;
}


void dictionary::search(entry *&current,string word)
{
    while (1)
    {
        if(current==NULL)
            return;
        else if(word < current->word)
        {
            current=current->lchild;
        }

        else if(word > current->word)
        {
            current=current->rchild;
        }

        else
            return;
    }
}


void dictionary::max_comparisions(entry* current)
{
    if(height < count)
		height=count;//change only if it encounters larger hieght
	if(current!=NULL)
	{
		count++;//going down from parent to childres so ++
		cout<<current->word<<"-"<<count<<" ";
		max_comparisions(current->lchild);
		max_comparisions(current->rchild);
        count--;//after checking both lchild and rchild it would go back to its parent so --
	}
}


void dictionary::display_asc(entry* current)
{
    if(current!=NULL)
    {
        display_asc(current->lchild);
        cout<<"\n"<<current->word<<"\t\t\t\t"<<current->meaning;
        display_asc(current->rchild);
    }
}


void dictionary::display_dec(entry* current)
{
    if(current!=NULL)
    {
        display_dec(current->rchild);
        cout<<"\n"<<current->word<<"\t\t\t\t"<<current->meaning;
        display_dec(current->lchild);
    }
}


void dictionary::menu()
{
    int choice;
    string word,meaning;
    entry* current;

    insert("goat","four leges creature that eats paper");
    insert("boat","vehicle that travels on water");
    insert("fan","macjine that blows air");
    insert("atom","smallest part of molecule");
    insert("camera","device that takes photographs");
    insert("eat","verb representing action of consuming food");
    insert("beach","sandy edge of sea");

    while(true)
    {
		cout<<"\n\n\n------------------------------------\nMENU";
		cout<<"\n1. Insert new word in dictionary";
		cout<<"\n2. Update meaning of word in dictionary";
		cout<<"\n3. Search for a word in dictionary";
		cout<<"\n4. Delete the word form the dictionary";
		cout<<"\n5. Maximum comparisons needed to search a word";
		cout<<"\n6. display all words in ascending order";
		cout<<"\n7. display all words in decending order";
		cout<<"\n8. exit";
		cout<<"\n\nEnter the choice: ";

		cin>>choice;

        switch(choice)
        {
            case 1:
                cout<<"\nEnter the word: ";
                cin>>word;

                cout<<"\nEnter the meaning of the word: ";
                cin.ignore();
                getline(cin, meaning);
            	insert(word,meaning);
                break;
            case 2:
                if(root==NULL)
                {
                    cout<<"\ndictionary is empty";
                    break;
                }
                cout<<"\nEnter the word you want to update: ";
                cin>>word;
                cout<<"\nEnter the meaning of the word: ";
                cin.ignore();
                getline(cin, meaning);
				update(word,meaning);
                break;
            case 3:
                if(root==NULL)
                {
                    cout<<"\ndictionary is empty";
                    break;
                }
                cout<<"\nEnter the word you want to search: ";
                cin>>word;
                current=root;
				search(current,word);//'current' is pass by refference
                if(current!=NULL)
                {
                    cout<<"\n________________________________________________________________________";
                    cout<<"\nword\t\t\t\tmeaning";
                    cout<<"\n________________________________________________________________________";
                    cout<<"\n"<<current->word<<"\t\t\t\t"<<current->meaning;
                    cout<<"\n________________________________________________________________________";
                }
                else
                    cout<<"\nword doesn't exit in the dictionary";
                break;
            case 4:
                if(root==NULL)
                {
                    cout<<"\ndictionary is empty";
                    break;
                }
                cout<<"\nEnter the word you want to delete: ";
                cin>>word;
            	del_word(root,word);
                break;
			case 5:

                height=0;
				max_comparisions(root);
                cout<<"\nmaximum comparisons required for finding any keywords is "<<height;
                if(root==NULL)
                    cout<<"\nThat is due to dictionary is empty";
                break;
            case 6:
                if(root==NULL)
                {
                    cout<<"\ndictionary is empty";
                    break;
                }
                cout<<"\n________________________________________________________________________";
                cout<<"\nword\t\t\t\tmeaning";
                cout<<"\n________________________________________________________________________";
				display_asc(root);
                cout<<"\n________________________________________________________________________";
				break;
			case 7:
                if(root==NULL)
                {
                    cout<<"\ndictionary is empty";
                    break;
                }
                cout<<"\n________________________________________________________________________";
                cout<<"\nword\t\t\t\tmeaning";
                cout<<"\n________________________________________________________________________";
				display_dec(root);
                cout<<"\n________________________________________________________________________";
                break;
			case 8:
				return;
            default:
                cout<<"\nenter the correct choice";
        }
    }
}


int main()
{
    dictionary dict;
    dict.menu();
    return 0;
}
