#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<cstdio>
#include<conio.h>
#include<windows.h>
#include<limits.h>
#define NO_OF_CHARS 256
#define ALPHA 26
#define INDEX(c) ((int)c - (int)'a')
using namespace std;
FILE *fp;

//Trie Module

int search_node(char w[]);

struct trie_node
{
    int value;
    trie_node *children[ALPHA];
};

trie_node *create_node()
{
    trie_node *p;
    p=new trie_node;
    if(p)
    {
        p->value=0;
        for(int i=0;i<ALPHA;++i)
        {
            p->children[i]=NULL;
        }
    }
    return p;
}

trie_node *trie_root = create_node();
int count=0;

void insert_node(char word[])
{
    int length=strlen(word);
    int index;
    trie_node *a;

    count++;
    a=trie_root;

    for(int i=0 ; i<length ; ++i)
    {
        index = INDEX(word[i]);
        if(!a->children[index])
        {
            a->children[index]=create_node();
        }
        a=a->children[index];
    }
    a->value=count;
}

void copystr(char b[], char a[])
{
    int i;
    for(i=1;i<strlen(a);++i)
    {
        b[i-1]=a[i];
    }
    b[i-1]='\0';
}


//Word Modification Module


static int flag=0;

int fail_search(trie_node *x,char word[])
{
    if(strlen(word)<2)
        return 0;
    char w[20];
    w[0]=NULL;
    strcpy(w,word);
    trie_node *t;
    t=x;
    int i;

    char p[][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
        for(i=0; i<ALPHA; ++i)
        {
            if(t->children[i]!=NULL)
            {
                flag=1;
                strcat(w,p[i]);
                if(search_node(w))
               {
                   cout<<endl<<w;
                   break;
                   return 1;
               }
                fail_search(t->children[i],w);
                w[0]='\0';
                strcpy(w,word);
            }
        }
}

int search_node(char word[])
{
    int length=strlen(word);
    int index,t=0;
    char w[20],z;
    w[0]='\0';
    trie_node *a;
    char p[][2]={"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};
    a=trie_root;
    for(int i=0 ; i<length ; i++)
    {
        t++;
        index=INDEX(word[i]);
        if(!a->children[index])
        {
            if(t>=3)
            {
                flag=1;
                int h = fail_search(a,w);
                if(h)
                cout<<"\n\nTry searching your word again if you found the correct spelling\n";
                return 2;
            }
            else

            {
                return 0;
            }
        }
        a=a->children[index];
        if(a==NULL)
        {
            return 0;
        }
        strcat(w,p[index]);
    }
    return(0!=a &&  a->value);
}

void fail_handle(char word[])
{
        trie_node *tp;
        tp=trie_root;
        int k=0,i;
        for(i=0; i<strlen(word); ++i)
        {

            k=int(word[i])-97;
            if(tp->children[k]==NULL)
                return ;
            else
            tp=tp->children[k];
        }

            fail_search(tp,word);
            return ;
}
void fail_control(char p[])
{
    char s[20];
    int h;
    ifstream file;
    file.open("OfficialWordlist.txt",ios::in);
    while(file)
    {
        file.getline(s,20);
        insert_node(s);
    }
    h = search_node(p);
    if(!h && h!=2)
        {
            fail_handle(p);
            cout<<"\nTry searching your word again if you found the correct spelling\n";
        }
}



//Boyer-Moore Horspool Algorithm
int max(int a, int b)
{
    return (a > b) ? a : b;
}

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

void searchw(char *txt, char *pat)
{
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            cout<<txt<<endl;

            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;

        }

        else
            s += max(1, j - badchar[txt[s + j]]);
    }
}


// For presentation

void gotoxy(int x,int y)
 {
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
 void spiral(int a, int b)
 {
     system("cls");
     int i,x1=0,x2=a,y1=0,y2=b;
    while(x1<x2 && y1<y2)
    {
        for(i=x1;i<x2;++i)
     {
         gotoxy(y1*1,i*1);
         cout<<".";
         Sleep(0.9);
     }
     y1++;

     for(i=y1;i<y2;++i)
     {
         gotoxy(i*1,(x2-1)*1);
         cout<<".";
         Sleep(0.9);
     }
     x2--;
    if(y1<y2)
     for(i=x2-1;i>=x1;--i)
     {
         gotoxy((y2-1)*1,i*1);
         cout<<".";
         Sleep(0.9);
     }
     y2--;
    if(x1<x2)
     for(i=y2-1;i>=y1;--i)
     {
         gotoxy(i*1,x1*1);
         cout<<".";
         Sleep(0.95);
     }
     x1++;
    }
    system("cls");
 }


 //BinarySearchTree Module



class node
{
    public:
    string a;
    string b;
    node *right, *left;

    node(){a='\0';}
}*root;

void file_rep()
{
    remove("OfficialDictionary.txt");
    rename("newfile2.txt","OfficialDictionary.txt");
    getch();
}


void make_tree(string x,string y)
{
    node *temp;
    temp=new node;
    if(temp==NULL)
        cout<<"Not enough memory";

   else
   {
        temp->a=x;
        temp->b=y;
        temp->left=NULL;
        temp->right=NULL;
        if(root==NULL)
    {
        root = temp;
    }
        else
    {
        node *p,*q;
        p=root;
        while(p!=NULL && p->a!=x)
        {
            q=p;
            if(p->a > x)
                {
                    p=p->left;
                }
            else if(p->a < x)
                {
                    p=p->right;
                }
        }
        if(p!=NULL);
        else if(x < q->a)
            q->left=temp;
        else
            q->right=temp;

   }
   }
}

void format(char s[],char w[], char m[])
{
    int i,j;
    for(i=0;s[i]!=' ';i++)
    w[i]=s[i];
    w[i++]=NULL;
    for(j=0;s[i]!='\0';i++,j++)
    {
        m[j]=s[i];
    }
    m[j]=NULL;
}


int check=0;
void show_word(node *n, string x)
{
    if(n==NULL)
        return;
    if(n->a==x)
    {
        cout<<endl<<"\t"<<n->a<<": "<<n->b<<endl;
        check = 1;
        return ;
    }
    else if(x < n->a)
    show_word(n->left,x);
    else
    show_word(n->right,x);
}

node* delete_tree(node* r)
{

    if(r!=NULL)
    {
        delete_tree(r->left);
        delete_tree(r->right);
        delete r;
        r=NULL;
        return r;
    }
}




// Word Modification Module

void delete_word()
{
    int x=0,i;
    char word[20],s[200],w[20];
    cout<<"\nEnter the word you want to delete\n";
    cin>>word;
    ofstream fo;
    fo.open("adv.txt",ios::out | ios::app);
    fo<<"DELETED: "<<word<<endl;
    fo.close();
    ifstream fin;
    fin.open("OfficialDictionary.txt",ios::in);
    ofstream fout;
    fout.open("newfile2.txt",ios::out);
    while(!fin.eof())
    {
        fin.getline(s,200);
        for(i=0;s[i]!=' ';++i)
        {
            w[i]=s[i];
        }
        while(i<20)
        {
            w[i]='\0';
            i++;
        }
        if(!strcmp(word,w))
            x=1;
            if(strcmp(word,w))
            {
                fout<<s<<endl;
            }
    }
    fin.close();
    fout.close();
    if(x==1)
        cout<<"The word successfully deleted";
    else
        cout<<"The word was not found in the dictionary";
    getch();
}


void edit_word()
{
    ofstream fo;
    fo.open("adv.txt",ios::out | ios::app);
    int x=0,i,j;
    char word[20],s[200],w[20],m[200];
    cout<<"\nEnter the word you want to edit\n";
    cin>>word;
    fo<<"EDITED: "<<word<<endl;
    fo.close();
    ifstream fin;
    fin.open("OfficialDictionary.txt",ios::in);
    ofstream fout;
    fout.open("newfile2.txt",ios::out);
    while(!fin.eof())
    {
        fin.getline(s,200);
        for(i=0;s[i]!=' ';++i)
        {
            w[i]=s[i];
        }
        j=i;
        while(i<20)
        {
            w[i]='\0';
            i++;
        }
        if(strcmp(w,word))
        {
            fout<<s<<endl;
        }
        else
        {
            x=1;
            for(i=0;s[i]!=' ';++i)
                fout<<s[i];
                i++;fout<<" ";
            for(;s[i]!=' ';++i)
                fout<<s[i];
                fout<<" ";
            cout<<"Enter the edited meaning\n";
            char ch;cin.get(ch);
            cin.getline(m,200);
            fout<<m<<endl;
        }
    }
    fout.close();
    fin.close();
    if(x==1)
    {
        cout<<"\nThe word successfully edited\n";
    }
    else
    {
        cout<<"\nThe word was not founded\n";
    }
    char *a;
    fp=fopen("newfile2.txt","r");
    while(!feof(fp))
    {
        a=fgets(s,200,fp);
        format(s,w,m);
        make_tree(w,m);
    }
    fclose(fp);
    getch();
}

int check_word(char o[])
{
    for(int i=0;i<strlen(o);++i)
    {
        if(o[i]==' ')
            {
                cout<<"\nEnter word without spaces\n";
                return 1;
            }
            else return 0;
    }
}

void add_new_words()
{
    char w[20],m[100],s[200],word[100];
    cout<<"\nEnter the word you want to add to the Dictionary\n";
    cin>>w;
    check=0;
    show_word(root,w);
    if(check!=0)
    {
        cout<<"\nThis word is already present in the dictionary\n";
    }
    else if(check==0)
   {
       ofstream fo;
        fo.open("adv.txt",ios::out | ios::app);
        fo<<"ADDED: "<<w<<endl;
        fo.close();
        fo.open("OfficialWordlist.txt", ios::out | ios::app);
        fo<<w<<endl;
        fo.close();
        ofstream fout;
        fout.open("OfficialDictionary.txt",ios::out | ios::app);
        cout<<"\nEnter the meaning of the word\n";
        char f;
        cin.get(f);
        cin.getline(m,100);
        char n[10];
        cout<<"Enter whether its a verb(v) or noun(n) or adjective(adj)\n";
        cin>>n;
        fout<<endl<<w<<" "<<n<<". "<<m;
        cout<<"\nThe word is successfully added to the dictionary\n";
        fp=fopen("OfficialDictionary.txt","r");
        int t=0;
        while(!feof(fp) && t<100)
    {

        char *a;
        a=fgets(s,200,fp);
        format(s,word,m);
        if(!strcmp(w,word))
        cout<<word<<endl;
        make_tree(w,m);
    }
    fclose(fp);
        return;

   }
    check = 0;
}

void correct_spelling()
{
    char w[20],f[20];
    cout<<"Enter the part of the word you know\n\n";
    cin>>w;
    if(strlen(w)<2)
        return;
    ifstream fin;
    fin.open("OfficialWordlist.txt",ios::in);
    while(fin)
    {
        fin.getline(f,20);
        searchw(f,w);
    }
    fail_control(w);
    fin.close();
}



//Main Module


void head()
{
    char *a,s[200],word[20],meaning[180],h[20],z,ch;
    int choice,ichoice,k;
    string enter_pw;
    ifstream fi,foi;
    fstream fo;
    fo.open("history.txt",ios::in | ios::out|ios::app);
    fp=fopen("OfficialDictionary.txt","r");
    while(!feof(fp))
    {
        a=fgets(s,200,fp);
        format(s,word,meaning);
        make_tree(word,meaning);
    }
    fclose(fp);
    here:
        system("cls");
    cout<<"\n\n\t\t\tWELCOME TO iDictionary  ^_^\n";
    cout<<"\n\n\t1.Look Up\n\t2.Advanced Options\n\t3.Prediction\n\t4.History\n\t5.Log Out\n\n";
    cin>>choice;
    if(!cin.fail())
    switch(choice)
    {
        system("cls");
        case 1: cout<<"\nEnter the word you want to search\n";
                cin>>word;
                fo<<word<<endl;
                for(int i=0;i<strlen(word);i++)
                {
                    if(isalpha(word[i]))
                    word[i]=tolower(word[i]);
                }
                check=0;
                system("cls");
                show_word(root,word);
                if(check==0)
                {
                    cout<<"\nSorry \""<<word<<"\" is not present in the dictionary\n";
                    cout<<"\nDo you want to use auto-prediction feature now\nY - Yes\nN - No\n";
                    char ch;cin.get(ch);
                    cin.get(z);
                    if(z=='y' || z=='Y')
                    {
                        cout<<"\nFor \""<<word<<"\" auto-prediction suggests\n";
                        fail_control(word);
                    }
                }
                getch();
                break;
        case 2: cout<<"\nEnter the administrator password to enter the advanced mode\n";
                cout<<"\n(no backspace allowed)\n\n";
                enter_pw="";
                ch=getch();
                while(ch!=13)
                {
                    enter_pw.push_back(ch);
                    cout<<"*";
                    ch=getch();
                }
                if(enter_pw=="high")
                {
                    ihere:
                    system("cls");
                    cout<<"\n\n\t\t\tWelcome to advanced section";
                    cout<<"\n1.Add a word\n2.Delete a word\n3.Edit a word\n4.Exit Advanced Mode\n\n(the application must be restarted to make the changes)\n\n";
                    cin>>ichoice;
                    switch(ichoice)
                    {

                    case 1: cout<<"\nAdd a new word in the dictionary\n";
                            add_new_words();
                            getch();
                            break;
                    case 2: cout<<"\nDelete a word in the dictionary\n";
                            delete_word();
                            file_rep();
                            break;
                    case 3: cout<<"\nEdit the meaning of a word in the dictionary\n";
                            edit_word();
                            file_rep();
                            break;
                    case 4: goto there;
                    default: cout<<"\n\nInvalid Input";
                             getch();
                             goto ihere;
                    }
                    cout<<"\n\nDo you want to restart now(press y)\n\n";
                    cin>>z;
                    if(z=='y'||z=='Y')
                        return;
                    goto ihere;
                }
                else
                    {
                        cout<<"\n\nWrong password :(\n\n";
                        getch();
                        goto here;
                    }
                    there:
                    fi.open("adv.txt",ios::in);
                    cout<<"The advanced actions taken so far\n";
                    while(fi)
                    {
                        fi.getline(s,200);
                        cout<<s<<endl;
                    }
                    getch();
                    goto here;
        case 3: cout<<"\nUse this feature to search the correct spelling of a word when you're not sure\n";
                correct_spelling();
                getch();
                goto here;
        case 4: foi.open("history.txt",ios::in);
            while(foi)
            {
                foi.getline(h,20);
                cout<<h<<endl;
            }
            getch();
            foi.close();
            goto here;
        case 5: system("cls");
                cout<<"Logging Out...";Sleep(1000);
                return;
        default: cout<<"\n\nERROR";
                 getch();
                 goto here;
    }
    else
    {
        cout<<"Invalid Input\n";
        getch();
        return ;
    }
    goto here;
}




// User Handling Module



class user
{
    char name[20];
    char password[20];
    int id;
    int state;
    int ti;
public:
    user()
    {
        state=0;
        ti=0;
    }
    void setname(char n[])
    {
        strcpy(name,n);
    }
    void setpassword(char p[])
    {
        strcpy(password,p);
    }
    int getreg()
    {
        return ti;
    }
    void reg()
    {
        char ch;
        cin.get(ch);
        cout<<"\n\n\t\tWelcome to iDictionary\n \nEnter your name\n";
        cin.getline(name,20);
        cout<<"Enter your password  (DONT FORGET IT)\n";
        cin.getline(password,20);
        cout<<"\nYour id is "<<id;
        ti=1;
        cout<<"\nCongratulation! Successfully registered\n \n";
        char aa;
        cin.get(aa);
        ofstream fout("userdata.txt");
        fout<<name<<" "<<password<<endl;
    }
    int getstate()
    {
        return state;
    }
    void getname()
    {
        cout<<name;
    }
    void setid(int x)
    {
        id=x;
    }
    int getid()
    {
        return id;
    }
    int login()
    {
        system("cls");
        char enter_us[20];
        cout<<"Enter the user name\n";
        cin.getline(enter_us,20);
        cout<<"Enter the password (Enter carefully-no backspace allowed\n";
        string enter_pw;
        char ch;
        ch=getch();
        while(ch!=13)
        {
            enter_pw.push_back(ch);
            cout<<"*";
            ch=getch();
        }
        if(enter_pw==password)
            {
            cout << "\nAccess granted \n";
            Sleep(800);
            system("cls");
            cout<<"\t\tSuccesfully Logged in !!";
            cout<<"\t\t\t\t\tWelcome "<<name<<endl;
            Sleep(1000);
            state=1;
            return state;
            }
        else
            {
                cout << "\nAccess aborted...\n";
                return 0;
            }

    }
    void logout()
    {
        state=0;
    }
};


// End of User Handling Module

int main()
{
    spiral(50,110);
    system("cls");
    user x[100];
    int b,r=0;
    char s[40],n[20],p[20];
    ifstream fin;
    fin.open("userdata.txt");
    while(fin)
    {
        fin.getline(s,40);
        format(s,n,p);
        x[r].setid(r);
        x[r].setname(n);
        x[r].setpassword(p);
        r++;
    }
    mp:
    system("cls");
    cout<<"\t\t\tDICTIONARY:)\n\n1.Sign Up\n2.Log In\n3.List of Users\n4.EXIT APP\n";
    while (!(cin >> b))
        {
            std::cin.clear();
            std::cin.ignore();
        }
    switch(b)
    {
    case 1:
        {
            r++;
            x[r].setid(r);
            x[r].reg();
            if(x[r].getreg()!=1)
                 {
                     cout<<"failed";
                     char aa;
                     cin.get(aa);
                 }
            goto mp;

        }
    case 2:
        {
            int i;
            cout<<"Enter the user id\n";
            while (!(cin >> i))
            {
                std::cin.clear();
                std::cin.ignore();
            }
            char a;cin.get(a);
            if(x[i].login())
            {
               head();
               x[i].logout();
               goto mp;
            }
            else
            {
                system("cls");
            }
        }
    case 3:
        {
            for(int i=1;i<=r;++i)
            {
                if(x[i].getreg())
                {
                    x[i].getname();
                    cout<<endl;
                }
            }
            char aa,bb;
            cin.get(aa);
            cin.get(bb);
            goto mp;
        }
    case 4:
        exit(0);
    default:
        {
            system("cls");
            cout<<"\nInvalid Input :(";
            cout<<"\nTry again :)\n";
            getch();
            goto mp;
        }

    }
    return 0;
}
