#include<iostream>
#include<cstring>
#include<stdlib.h>
using namespace std;
struct node
{ 
    char word[10];
    string meaning;
    struct node* left;
    struct node* right;
};
struct node* root=NULL;
void adWord()
{
    struct node* temp=new node;
    cout<<"\nENTER WORD: ";
    cin>>temp->word;
    cout<<"\nENTER MEANING: ";
    cin.get();
    getline(cin,temp->meaning);
    temp->left=NULL;
    temp->right=NULL;
    if(root==NULL)
    {
        root=temp;
    }
    else
    {
        struct node* p=root;
        struct node* q;
        while(p!=NULL)
        {
            q=p;
            if(strcmp(temp->word,p->word)<0)
            {
                p=p->left;
            }
            else
            {
                p=p->right;
            }
        }
        if(strcmp(temp->word,q->word)<0)
        {
            q->left=temp;
        }
        else
        {
            q->right=temp;
        }
    }
}
void displayWord(struct node*p)
{
    if(p->left!=NULL)
    {
        displayWord(p->left);
    }
    cout<<"\nWORD: "<<p->word<<" "<<"MEANING: "<<p->meaning;
    if(p->right!=NULL)
    {
        displayWord(p->right);
    }
}
void searchAndUpdate(struct node* p,char word[10])
{
    string newMeaning;
    if(strcmp(word,p->word)<0)
    {
        searchAndUpdate(p->left,word);
    }
    if(strcmp(word,p->word)>0)
    {
        searchAndUpdate(p->right,word);
    }
    if(strcmp(word,p->word)==0)
    {
        cout<<"\nENTER NEW MEANING OF THE WORD: ";
        cin.get();
        getline(cin,newMeaning);
        p->meaning=newMeaning;
    }
}
int count=0;
void noOfComparisons(struct node*p,char word[])
{
    count++;
        if(strcmp(word,p->word)==0)
        {
            cout<<"\nTOTAL COMPARISONS: "<<count;
            count=0;
        }
        if(strcmp(word,p->word)<0)
        {
          noOfComparisons(p->left,word);  
        }
        if(strcmp(word,p->word)>0)
        {
            noOfComparisons(p->right,word);
        }
}
void deleteNode(struct node* p,char word[10])
{
    struct node* q;
    struct node* r;
    while(p!=NULL)
    {
        q=p;
            if(strcmp(word,p->word)<0)
            {
                p=p->left;
            }
            if(strcmp(word,p->word)>0)
            {
                p=p->right;
            }
            if(strcmp(word,p->word)==0)
            {
                break;
            }
    }
    while(1)
    {
        if(p==q && p->left==NULL && p->right==NULL)
        {
            root=NULL;
            delete p;
            break;
        }
        if(p==q && p->right==NULL && p->left!=NULL)
        {
            strcpy(p->word,p->left->word);
            p->meaning=p->left->meaning;
            p->left=NULL;
            struct node* r=p->left;
            delete r;
            break;
        }
        if(p==q && p->left==NULL && p->right!=NULL)
        {
            strcpy(p->word,p->right->word);
            p->meaning=p->right->meaning;
            p->right=NULL;
            struct node* r=p->right;
            delete r;
            break;
        }
        if(p!=q && p->left==NULL && p->right==NULL)
        {
            if(q->right==p)
            {
                q->right=NULL;
                delete p;
                break;
            }
            if(q->left==p)
            {
                q->left=NULL;
                delete p;
                break;
            }
        }
        if(p->right!=NULL && p->left==NULL)
        {
            if(q->right==p)
            {
                q->right=p->right;
                p->right=NULL;
                delete p;
                break;
            }
            if(q->left==p)
            {
                q->left=p->right;
                p->right=NULL;
                delete p;
                break;
            }
        }
        if(p->right==NULL && p->left!= NULL)
        {
            if(q->right==p)
            {
                q->right=p->left;
                p->left=NULL;
                delete p;
                break;
            }
            if(q->left==p)
            {
                q->left=p->left;
                p->left=NULL;
                delete p;
                break;
            }
        }
        if(p->right!=NULL && p->left!=NULL)
        {
            /*if(p->right->right==NULL &&
            p->right->left==NULL &&
            P->left->left==NULL &&
            p->left->right==NULL)
            {
                p->data=p->right->data;
                p->right=NULL;
                delete p->right;
            }*/
            struct node* t=p;
            struct node* r;
            p=p->right;
            char min[10];
            strcpy(min,p->word);
            while(p!=NULL)
            {
                if(p->word<min)
                {
                    strcpy(min,p->word);
                    r=p;
                }
                p=p->left;
                }deleteNode(root,min);
                strcpy(t->word,min);
                break;
        }
    }
}
int main()
{
    int ch,word;
    char newWord[10];
    for(char y='y';y=='1'||y=='y';)
    {
        cout<<"1.Insert the Data: "<<endl;
        cout<<"2.Display the Data "<<endl;
        cout<<"3. Search and Update "<<endl;
        cout<<"4. Find the No of Comparisons "<<endl;
        cout<<"5. Delete the Node"<<endl;
        cout<<"Enter the Choice:"<<endl;
        cin>>ch;
        switch(ch)
        {
            case 1:cout<<"|nHow many word you want to add: ";
                cin>>word;
                for(int i=1;i<=word;i++)
                {
                    adWord();
                }
                break;
            case 2:displayWord(root);
                break;
            case 3: cout<<"\nEnter word to search and update: ";
                cin>>newWord;
                searchAndUpdate(root,newWord);
                break;
            case 4:cout<<"\nEnter the wowrd to check no of comparisons: ";
                cin>>newWord;
                noOfComparisons(root,newWord);
                break;
            case 5:cout<<"\nEnter word to delete: ";
                cin>>newWord;
                deleteNode(root,newWord);
        }
        cout<<"\nPRESS 1 TO CONTINUE: ";
        cin>>y;
    }
    return 0;   
}

