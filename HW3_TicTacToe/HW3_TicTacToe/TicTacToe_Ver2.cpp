#include <iostream>
using namespace std;

class TicTacToe
{
public:
    //Tic Tac Toe Board
    //Empty by Default
    char board[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    enum Entry
    {
        EMPTY = ' ',
        PLAYER_ONE = 'x',
        PLAYER_TWO = 'o'
    };

    bool isFull()
    {
        bool result = true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Entry::EMPTY)
                    result = false;
            }
        }

        return result;
    }

    //Checks to see if either player has already won
    bool isVictory(Entry e)
    {

        // first col
        if (board[0][0] == (char)e && board[0][1] == (char)e && board[0][2] == (char)e)
        {
            return true;
        }

        // second col
        else if (board[1][0] == (char)e && board[1][1] == (char)e && board[1][2] == (char)e)
        {
            return true;
        }

        // third col
        else if (board[2][0] == (char)e && board[2][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // first row
        else if (board[0][0] == (char)e && board[1][0] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        // second row
        else if (board[0][1] == (char)e && board[1][1] == (char)e && board[2][1] == (char)e)
        {
            return true;
        }

        // third row
        else if (board[0][2] == (char)e && board[1][2] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 1
        else if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        else if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        return false;
    }

    //Returns the size of the board
    int getSize()
    {
        return 3;
    }

    //Prints the contents of the board to the console
    void dump()
    {
        cout << "----------------------------------------" << endl << endl;
        for (int i = 0; i < getSize(); i++)
        {
            for (int j = 0; j < getSize(); j++)
            {
                cout << " | " << board[i][j] << " | ";
            }

            cout << endl;
        }
        cout << "----------------------------------------" << endl << endl;
    }

};

static bool getHumanMove(int maxValue, TicTacToe::Entry human, TicTacToe& t)
{
    //Check if the player is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;

    do {

        do {

            cout << "Enter column number (x) : 0 ... 2 : ";
            cin >> colChoice;
            cout << endl;

        } while (colChoice > maxValue || colChoice < 0);

        do {

            cout << "Enter row number (y) : 0 ... 2 : ";
            cin >> rowChoice;
            cout << endl;

        } while (rowChoice > maxValue || rowChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)human;

            return false;
        }

        else
        {
            cout << "Not a valid option! Please try again..." << endl;
        }


    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    //The player has completed their move
    return false;
}

static bool getComputerMove(TicTacToe::Entry computer, TicTacToe::Entry human, TicTacToe& t)
{
    //Check if the computer is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;
    bool comHasChosen = false;

    //Check if the computer can win
    for (int row = 0; row <= 2; row++)
    {
        for (int col = 0; col <= 2; col++)
        {
            if (t.board[row][col] == t.EMPTY)
            {
                t.board[row][col] = (char)computer;
                if (t.isVictory(computer))
                {
                    comHasChosen = true;
                    break;
                }
                else
                {
                    t.board[row][col] = t.EMPTY;
                }
            }
        }
        if (comHasChosen)
        {
            break;
        }
    }

    //Check if the player can win
    if (!comHasChosen)
    {
        for (int row = 0; row <= 2; row++)
        {
            for (int col = 0; col <= 2; col++)
            {
                if (t.board[row][col] == t.EMPTY)
                {
                    t.board[row][col] = (char)human;
                    if (t.isVictory(human))
                    {
                        t.board[row][col] = (char)computer;
                        comHasChosen = true;
                        break;
                    }
                    else
                    {
                        t.board[row][col] = t.EMPTY;
                    }
                }
            }
            if (comHasChosen)
            {
                break;
            }
        }
    }

    //Check to see if the center space is available
    if (!comHasChosen
        && t.board[1][1] == t.EMPTY)
    {
        t.board[1][1] = (char)computer;
        comHasChosen = true;
    }

    //Check to see if any of the corners are available
    if (!comHasChosen
        && t.board[0][0] == t.EMPTY)
    {
        t.board[0][0] = (char)computer;
        comHasChosen = true;
    }
    if (!comHasChosen
        && t.board[0][2] == t.EMPTY)
    {
        t.board[0][2] = (char)computer;
        comHasChosen = true;
    }
    if (!comHasChosen
        && t.board[2][0] == t.EMPTY)
    {
        t.board[2][0] = (char)computer;
        comHasChosen = true;
    }
    if (!comHasChosen
        && t.board[2][2] == t.EMPTY)
    {
        t.board[2][2] = (char)computer;
        comHasChosen = true;
    }

    if (!comHasChosen)
    {
        do {

            //Chooses at random until an empty space is found
            do {

                rowChoice = rand() % ((t.getSize() - 0) + 1) + 0;

            } while (rowChoice > t.getSize() || rowChoice < 0);

            do {

                colChoice = rand() % ((t.getSize() - 0) + 1) + 0;

            } while (colChoice > t.getSize() || colChoice < 0);


            if (t.board[rowChoice][colChoice] == t.EMPTY)
            {
                t.board[rowChoice][colChoice] = (char)computer;
                break;
            }

        } while (t.board[rowChoice][colChoice] != t.EMPTY);
    }

    //The computer has completed their move
    return false;
}

// ----------------------------
// main
// ----------------------------

int main()
{
    TicTacToe t;
    TicTacToe::Entry human = TicTacToe::PLAYER_ONE;
    TicTacToe::Entry computer = TicTacToe::PLAYER_TWO;

    int maxValue = t.getSize();

    cout << "----------------------------------------" << endl;

    cout << "You are '" << (char)human << "', " <<
        "the computer is: '" << (char)computer << "'" << endl;

    cout << "----------------------------------------" << endl << endl;

    //Runs the game until either a victory or a full board
    do
    {
        t.dump(); //Prints the contents of the board to the console
    } while (!getHumanMove(maxValue, human, t) && !getComputerMove(computer, human, t));


    t.dump(); //Prints the contents of the board to the console

    if (t.isVictory(human))
        cout << "You Win" << endl;

    else if (t.isVictory(computer))
        cout << "You Lose" << endl;

    else if (t.isFull())
        cout << "It's a Tie" << endl;

    return(0);
}