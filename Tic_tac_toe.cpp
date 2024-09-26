#include<iostream>
#include<vector>
#include<climits>
#include<algorithm>

using namespace std;

char gameArr[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};

void board(char gameArr[9]  )
{
    int arrI[9] = {1,1,1, 5,5,5,9,9,9};
    int arrJ[9] = {1,5,9,1,5,9,1,5,9};
    int index = 0;

    cout << endl << endl;
    for(int i = 0; i < 11; i++)
    {
        cout << "\t" ;
        for(int j = 0; j < 11; j++)
        {
            if(j == 3 || j == 7)
                cout << "| ";
            else if(i == 3 || i == 7)
                cout << "- ";
            else if(arrI[index] == i && arrJ[index] == j)
            {
                if(gameArr[index] != ' ')
                    cout << gameArr[index] << " ";
                else
                    cout << index << " ";
                index++;
            }
            else
                cout << "  ";
        }
        cout << endl;
    }
    cout << endl << endl;
    index = 0;
}

int checkWin(char gameArr[9])
{
    int winPos[8][3] = {
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6},
    };

    for(int i = 0; i<8; i++)
    {
        int a,b, c ;

        a = winPos[i][0];
        b = winPos[i][1];
        c = winPos[i][2];

        if(gameArr[a] != ' ' && gameArr[a] == gameArr[b] && gameArr[a] == gameArr[c])
        {
            if(gameArr[a] == 'x' || gameArr[a] == 'X')
                return 1;
            else
                return 2;
        }
    }

    for(int i = 0; i < 9; i++)
    {
        if(gameArr[i] == ' ' )
            return 0;
    }
    return 3;
}

int gameResult(bool &getData, bool &isGameContinue)
{
    int result = checkWin(gameArr);

    if(result)
    {
        board(gameArr);
        if(result == 3)
        {
            cout<<endl << "\tGAME TIE" << endl;
        }
        else
        {
            cout <<endl<< "\t"<<(result == 1 ? "X" : "O" ) << " WIN THE GAME !"<< endl<<endl;
        }
        int choice ;
        cout << "Do you want to play again " << endl;
        do {
            cout << "1. Yes ( Press 1 ) " << endl;
            cout << "2. No ( Press 2 )  " << endl;
            cout << "Enter your choice : " ;
            cin>>choice ;

            if(choice != 1 && choice != 2)
            {
                cout <<endl<< "INVALID CHOICE !" << endl<<endl;
            }
        } while(choice != 1 && choice != 2);

        if(choice == 1)
        {
            for(int i = 0; i < 9; i++)
            {
                gameArr[i] = ' ';
            }
            getData = true;
        }
        else
        {
            cout<<endl<<endl << "\tTHANK YOU FOR PLAYING" << endl;
            isGameContinue = false;
        }
    }
    
    return result ;
}

vector<int>minimax(bool maxi , int alpha ,int beta)
{
    int result = checkWin(gameArr);
    if(result)
    {
        int val[4] = {0,-1,1,0};
        
        vector<int> ans ;
        ans.push_back(val[result]);
        ans.push_back(-1);
        
        
        return ans;
    }
    
    vector<int> best ;
    best.push_back((maxi ? INT_MIN : INT_MAX));
    best.push_back(-1);
    
    for(int i = 0; i < 9; i++)
    {
        if(gameArr[i] == ' ')
        {
            gameArr[i] = (maxi ? 'o' : 'x');
            vector<int>re = minimax(!maxi , alpha, beta);
            gameArr[i] = ' ';
            
            if(maxi)
            {
                alpha = max(alpha , re[0]);
                if(re[0] > best[0])
                {
                    best[0] = re[0];
                    best[1]  = i;
                }
                
                if(beta <= alpha )
                    break;
            }
            else
            {
                beta = min(beta , re[0]);
                if(re[0] < best[0])
                {
                    best[0] = re[0];
                    best[1]  = i;
                }
                if(beta <= alpha )
                    break;
            }
        }
    }
    
    return best;
}


int main()
{

    bool isGameContinue = true;
    bool getData = true;
    bool isXTurn = true;
    bool isCpuGame = false;
    int pos;
    
    do {
        if(getData)
        {
            int ch ;
            do {

                cout <<endl<< "1. Play against player ( press 1 )" << endl;
                cout << "2. Play against cpu ( press 2 )" << endl;
                cout << "3. Exit ( press 3 )" << endl;
                cout << "Enter your choice : " ;
                cin>>ch;
            } while(ch != 1 && ch != 2 && ch != 3);
            
            if(ch == 3)
            {
                return 0;
            }
            isCpuGame = (ch == 1 ? false : true);
            getData = false;


            do {

                cout <<endl<< "1. Press 1 for \"x\" " << endl;
                cout << "2. Press 2 for \"o\" " << endl;
                cout << "Enter your choice : " ;
                cin>>ch;
            } while(ch != 1 && ch != 2);

            isXTurn = (ch == 2 ? false : true);
            
            getData = false;
        }

        if(isCpuGame)
        {
            board(gameArr);
            
            do {
                cout<<(isXTurn ? 'X' : 'O')<< " Turn to play "<<endl;
                cout << "Enter index to play " <<(isXTurn ? 'X' : 'O') << "(As above) : ";
                cin >>pos ;

                if(pos < 0 || pos > 9 || gameArr[pos] != ' ')
                    cout<<endl << "Invalid index !" << endl;
            } while(pos < 0 || pos > 9 || gameArr[pos] != ' ');
            
            gameArr[pos] = (isXTurn ? 'x' : 'o');;
            isXTurn = ! isXTurn;
            
            if(gameResult(getData , isGameContinue) == 0)
            {
                
                vector<int>bestMove = minimax(isXTurn ? false : true , INT_MIN , INT_MAX);
                gameArr[bestMove[1]] = (isXTurn ? 'x' : 'o'); ;
                board(gameArr);
                cout<<endl << "CPU Played On Index " << bestMove[1] <<endl<< endl;
                isXTurn = ! isXTurn;
                gameResult(getData , isGameContinue) ;
            }
        }
        else
        {
            board(gameArr);
            do {
                cout<<(isXTurn ? 'X' : 'O')<< " Turn to play "<<endl;
                cout << "Enter index to play " <<(isXTurn ? 'X' : 'O') << "(As above) : ";
                cin >>pos ;

                if(pos < 0 || pos > 9 || gameArr[pos] != ' ')
                    cout<<endl << "Invalid index !" << endl;
            } while(pos < 0 || pos > 9 || gameArr[pos] != ' ');

            gameArr[pos] = (isXTurn ? 'x' : 'o'); ;
            isXTurn = ! isXTurn;
            
            gameResult(getData , isGameContinue);
        }
    } while(isGameContinue == true);

    return 0;
}