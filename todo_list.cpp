#include<iostream>
#include<cstdio>


using namespace std;

class todo
{
    string *work;
    bool *done;
    static int count ;
public:
    void inti();
    void add()
    {
        inti();
        string temp;
        
        cout << "Enter work : " ;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        getline(cin , temp);
        work[count] =temp;
        count++;
    }
    void display();
    void load();
    void store();
};

int todo::count = 0;
void todo::inti()
{
    if(count != 0)
    {
        string *tmp = new string[count];
        bool *tmp2 = new bool[count]{false};

        for(int i = 0; i < count; i++)
        {
            tmp[i] = work[i];
            tmp2[i] = done[i];
        }
        delete[] work;
        delete[] done;

        work = new string[count+1];
        done = new bool[count+1] {false};

        for(int i = 0; i < count; i++)
        {
            work[i] = tmp[i] ;
            done[i] = tmp2[i];
        }
        delete[] tmp;
        delete[] tmp2;
    }
    else
    {
        work = new string[1];
        done = new bool[1] {false};
    }

}
void todo::display()
{
    if(count == 0)
    {
        cout <<endl<< "NO DATA FOUND !" << endl;
        return ;
    }
    cout << endl ;
    for(int i = 0; i < count; i++)
    {
        cout << work[i] <<  " ( " << (done[i] ? "not complete )" : "complete )")<<endl;
    }
}

void todo::store()
{
    FILE *file = fopen("listData.txt", "w");

    if(file == nullptr)
    {
        cout << "ERROR IN OPENING FILE !" << endl;
        return ;
    }

    
    fprintf(file, "%d\n", count);

    for(int i = 0; i < count; i++)
    {

        fputs(work[i].c_str(), file);

        fputc(',',file);

    }

    fclose(file);
}
void todo::load()
{
    FILE *file = fopen("listData.txt", "r");

    if(file == nullptr)
    {
        cout << "ERROR IN OPENING FILE !" << endl;
        return ;
    }
    int currentLine = 0;
    int target = 2;
    
    
    if(fscanf(file , "%d" , &count) != 1)
    {
        cout << "ERROE READING FILE ! " << endl;
        fclose(file);
        return ;
    }    
    
    char b[256];
    
    work = new string[count];
    int j = 0;
    while(fgets(b, sizeof(b), file))
    {
        currentLine++;
        if(currentLine == target)
        {
            for(int i = 0; b[i] != '\0'; i++)
            {
                if(b[i] == ',')
                {
                    cout << endl;
                    j++;
                }
                else
                {
                    work[j] += b[i];
                }
            }
        }
    }
    fclose(file);

}
int main()
{
    todo list;
    int ch;

    cout << "\tTODO LIST APP" << endl<<endl;
    do {
        cout <<endl << "1 . See Work List" << endl;
        cout << "2 . Add new Work" << endl;
        cout << "3 . Store Data " << endl;
        cout << "4 . Load Data " << endl;
        cout << "5 . Mark Complete " << endl;
        cout << "0 . Exit" << endl;

        cout << "Enter your choice : " ;
        cin>>ch;

        switch(ch)
        {
        case 1 :
            list.display();
            break;
        case 2 :
            list.add();
            break;
        case 3 :
            list.store();
            break;
        case 4 :
            list.load();
            break;
        case 5 : 
                list.display();
                
        }
    } while(ch != 0);
    return 0;
}