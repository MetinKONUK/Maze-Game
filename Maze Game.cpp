#include<iostream>
#include<fstream>
#include<iomanip>
#include<cctype>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
using namespace std;
// Used G++ Compiler in VSCode while developing this game
int main(){

// print rules of the game and introduce the game
cout << "RULES OF THE MAZE GAME" << endl
     << "--------------- LEARN SYMBOLS OF THE MAZE ---------------" << endl
     << "0: INDICATES ROADS"<< endl
     << "You can walk through roads"<< endl
     << "1: INDICATES WALLS"<< endl
     << "Walls: If a wall exist at a point you cannot move to that point"<< endl
     << "2: INDICATES GOLDS"<< endl
     << "Golds: Golds are collactable. To collect a gold ;move to the point a gold exists"<< endl
     << "3: INDICATES MONSTERS"<< endl
     << "5: INDICATES POINT YOU ARE ON" << endl
     << "MONSTERS: Monsters kill you!. If you move to the point a monsters exists, you die."<< endl
     << "--------------- LEARN ACTIONS OF THE MAZE ---------------"<< endl
     << "MOVING: You are able to walk only 1 point for each move if that point is not a wall."<< endl
     << "USE ARROW KEYS FOR MOVING!"<< endl
     << "LOSING (DYING): If you get killed by monsters game restarts with the same maze"<< endl
     << "WINNING: If you can reach the last last line of the maze, you win"<< endl << endl;

// open outfile
ofstream outfile;
outfile.open("outputs.txt");

//take matrix size from the user
int n;
cout << "Please enter the size of the maze (in range 10 to 100 inclusive): ";
cin >> n;
while(n < 10 || n > 100){
        cout << "Warning! Please enter a valid size!"<< endl;
        cout << "Please enter the size of the maze (in range 10 to 100 inclusive): ";
        cin >> n;   
}

//create dynamic board matrix
int **board;
board = new int*[n];
for (int i = 0; i < n; ++i) {
  board[i] = new int[n];
}

//create dynamic copy_board matrix
int **copy_board;
copy_board = new int*[n];
for (int i = 0; i < n; ++i) {
  copy_board[i] = new int[n];
}

//set maze full of walls for beginning
for (int i = 0; i < n; ++i) {   
  for (int j = 0; j < n; ++j) {
    board[i][j] = 1;
  }
}


//create the way out
int i = 0, j = 0; //enterance point
while (j != n-1) {
    board[j][i] = 0;
    int random = static_cast<int>((rand() + time(NULL)));
    if(random % 2) {
        if (i == n-1 && j < n-1){
            j += 1;
        } else {
            if(i < n-1) {
                i += 1;
            }
        }
    } else if(random % 2 == 0 && j < n){
        if(j == n-1 && i < n-1) {
            i += 1;
        } else {
            if(j < n-1) {
            j +=1;
            }
        }
    }
}
    board[j][i] = 0; // exit point


// adding golds monsters walls and unneeded roads
int gold_count = n;
int monster_count = n;
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < n; ++j) {
      if (board[i][j]){
        int random = static_cast<int>((rand() + time(NULL)) % 10 + 1);
            if(random >= 0 && random < 3 && gold_count > 0) {
                board[i][j] = 2;
                gold_count -= 1;
            } else if(random >= 3 && random < 5 && monster_count > 0){
                board[i][j] = 3;
                monster_count -= 1;
            } else if(random >= 5 && random < 8) {
                board[i][j] = 0;
            }

      }

  }
}

// take a copy of the maze for restarting
for(int i = 0; i < n; i++) {
  for(int j = 0; j < n; j++) {
    copy_board[i][j] = board[i][j]; 
  }
}

// Introduce the moving way
cout << "USE ARROW KEYS FOR MOVING" << endl;
cout << "DIRECTONS YOU CAN MOVE: LEFT, UP, RIGHT, DOWN" << endl;


// take moves from player
int c, ex;
int y = 0;
int x = 0;
int golds = 0;
bool isStart = true;
bool isAlive = true;
outfile << "The Way Out of the Labyrinth\n";
outfile << "x y\n---\n";

while(true){
    outfile << x << " " << y << "\n";
    // print the maze with some visual structures
    if(isStart) {
    isStart = false;
    for (int i = 0; i < n; ++i) {  
      for(int x = 0; x < n*3;x++) {
          cout << "_";
      }
      cout << endl;
      for (int j = 0; j < n; ++j) {
        if(i == 0 && j == 0) {
          cout << "|" << 5 << "|";
          continue;
        }
        cout << "|" <<  board[i][j] << "|";
      }
      cout << endl;
    }
    cout << endl;
    }

    if(y == n-1) {
      isAlive = false;
      cout << "WIN THE GAME!" << endl;
      cout << "GOLDS COLLECTED: " << golds;
      break;
    }
    c = getch();
    if (c && c != 224){
        cout << endl << "Not arrow: " << (char) c << endl;
    }
    else{
        switch(ex = getch()){
            case KEY_UP     /* H */:
                if (y == 0){
                  cout << "Cannot move out of the maze!" << endl;
                  continue;
                } else if(board[y-1][x] == 1) {
                  cout << "Cannot move to walls!" << endl;
                  continue;
                }
                cout << "Moved Up " << endl;//key up
                if(board[y-1][x] == 2) {
                  board[y-1][x] = 0;
                  golds += 1;
                  cout << "Took the gold!" << endl;
                }
                if(board[y-1][x] == 3) {
                  cout << "You got killed by monsters!" << endl;
                  // retstart the board
                  for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                      board[i][j] = copy_board[i][j]; 
                    }
                  }
                  x = 0;
                  y = 0;
                  outfile.close();
                  outfile.open("outputs.txt");
                  outfile << "The Way Out of the Labyrinth\n";
                  outfile << "x y\n---\n";
                  isStart = true;
                  golds = 0;
                  cout << "Restarting the game!" << endl;
                  continue;
                }
                y -= 1;

                break;
            case KEY_DOWN   /* K */:
                if (y == n-1){
                  cout << "Cannot move out of the maze!" << endl;
                  continue;
                } else if(board[y+1][x] == 1) {
                  cout << "Cannot move to walls!" << endl;
                  continue;
                }
                cout << "Moved Down " << endl;   // key down
                if(board[y+1][x] == 2) {
                  golds += 1;
                  board[y+1][x] = 0;
                  cout << "Took the gold!" << endl;
                }
                if(board[y+1][x] == 3) {
                  cout << "You got killed by monsters!" << endl;
                  // retstart the board
                  for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                      board[i][j] = copy_board[i][j]; 
                    }
                  }
                  x = 0;
                  y = 0;
                  outfile.close();
                  outfile.open("outputs.txt");
                  outfile << "The Way Out of the Labyrinth\n";
                  outfile << "x y\n---\n";
                  isStart = true;
                  golds = 0;
                  cout << "Restarting the game!" << endl;
                  continue;
                }
                y += 1;
                break;
            case KEY_LEFT   /* M */:
                if (x == 0){
                  cout << "Cannot move out of the maze!" << endl;
                  continue;
                } else if(board[y][x-1] == 1) {
                  cout << "Cannot move to walls!" << endl;
                  continue;
                }
                cout << "Moved Left " << endl;  // key left
                if(board[y][x-1] == 2) {
                  golds += 1;
                  board[y][x-1] = 0;
                  cout << "Took the gold!" << endl;
                }
                if(board[y][x-1] == 3) {
                  cout << "You got killed by monsters!" << endl;
                  // retstart the board
                  for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                      board[i][j] = copy_board[i][j]; 
                    }
                  }
                  x = 0;
                  y = 0;
                  outfile.close();
                  outfile.open("outputs.txt");
                  outfile << "The Way Out of the Labyrinth\n";
                  outfile << "x y\n---\n";
                  isStart = true;
                  golds = 0;
                  cout << "Restarting the game!" << endl;
                  continue;
                }
                x -= 1;
                break;
            case KEY_RIGHT: /* P */
                if (x == n-1) {
                  cout << "Cannot move out of the maze!" << endl;
                  continue;
                } else if(board[y][x+1] == 1) {
                  cout << "Cannot move to walls!" << endl;
                  continue;
                }
                cout << "Moved Right " << endl;  // key right
                if(board[y][x+1] == 2) {
                  golds += 1;
                  board[y][x+1] = 0;
                  cout << "Took the gold!" << endl;
                }
                if(board[y][x+1] == 3) {
                  cout << "You got killed by monsters!" << endl;
                  // retstart the board
                  for(int i = 0; i < n; i++) {
                    for(int j = 0; j < n; j++) {
                      board[i][j] = copy_board[i][j]; 
                    }
                  }
                  x = 0;
                  y = 0;
                  outfile.close();
                  outfile.open("outputs.txt");
                  outfile << "The Way Out of the Labyrinth\n";
                  outfile << "x y\n---\n";
                  isStart = true;
                  golds = 0;
                  cout << "Restarting the game!" << endl;
                  continue;
                } 
                x += 1;
                break;
            default:
                cout << endl << "Invalid key! Please use Arrow Keys!" << endl;  // not arrow
                break;
        }
    // print the maze with some visual structures after the moves
    for (int i = 0; i < n; ++i) {  
      for(int x = 0; x < n*3;x++) {
          cout << "_";
      }
      cout << endl;
      for (int j = 0; j < n; ++j) {
        if(i == y && j == x) {
          cout << "|" << 5 << "|";
          continue;
        }
        cout << "|" <<  board[i][j] << "|";
      }
      cout << endl;
    }
    cout << endl;



    }
}



// close the file after everything is done
outfile.close();
cout << endl << endl;

system("pause");
return 0;
}





