#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class KNIGHT
{
public:
  int stips,              // how many stips from the source
      row, col;           // location
  KNIGHT *previous;       // Where did I come from?
  vector<KNIGHT *> moves; // nodes where is possible to move
  bool checked;           // if its checked already

public:
  KNIGHT(int i, int j)
  { // constuctor
    row = i;
    col = j;
    previous = nullptr;
    checked = false;
  }
  // to fill the moves liste with the possible moves khnight can do
  void nextMoves(vector<vector<KNIGHT *>> &grid)
  {
    if (col < 6)
    {
      if (row < 7)
      {
        // 1 down -- 2 rigth
        moves.push_back(grid[row + 1][col + 2]);
      }
      if (row > 0)
      {
        // 1 up -- 2 right
        moves.push_back(grid[row - 1][col + 2]);
      }
    }

    if (col < 7)
    {
      if (row < 6)
      {
        // 2 down -- 1 right
        moves.push_back(grid[row + 2][col + 1]);
      }
      if (row > 1)
      {
        // 2 up -- 1 right
        moves.push_back(grid[row - 2][col + 1]);
      }
    }

    if (col > 0)
    {
      if (row > 1)
      {
        moves.push_back(grid[row - 2][col - 1]);
      }
      if (row < 6)
      {
        moves.push_back(grid[row + 2][col - 1]);
      }
    }

    if (col > 1)
    {
      if (row > 0)
      {
        moves.push_back(grid[row - 1][col - 2]);
      }
      if (row < 7)
      {
        moves.push_back(grid[row + 1][col - 2]);
      }
    }
  }

  // void aff() {
  //     cout << "(" << row << " , "<< col << ")  stips = "<< stips << endl;
  // }
};

// search for knight in the queue
bool include(vector<KNIGHT *> &queue, KNIGHT *move, const int &debut)
{
  for (int i = debut; i < queue.size(); i++)
  {
    if (move == queue[i])
    {
      return true;
    }
  }
  return false;
}

// get the position on the grid from given string input
KNIGHT *decode(string start, vector<vector<KNIGHT *>> &grid)
{

  reverse(start.begin(), start.end());
  int row = 8 - stoi(start);
  char alpha[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  int col;
  for (int i = 0; i < 8; i++)
  {
    if (start[1] == alpha[i])
    {
      col = i;
    }
  }
  return grid[row][col];
}

// the main function
int knight(std::string start, std::string finish)
{

  // setup the chess grid
  vector<vector<KNIGHT *>> grid(8, vector<KNIGHT *>(8));
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      grid[i][j] = new KNIGHT(i, j);
      // grid[i][j]->aff();
    }
  }

  // get the finish position
  KNIGHT *end = decode(finish, grid);
  // initialise the queue
  vector<KNIGHT *> queue = {decode(start, grid)};

  KNIGHT *current;
  // debut is the position of front item in the queue
  // fin is the position to enqueue(add) the new item
  int debut = 0, fin = 1;
  while (debut < fin)
  {
    current = queue[debut];
    debut++;

    if (current == end)
    {
      break;
    }
    current->checked = true;
    current->nextMoves(grid); // fill moves liste of the current

    for (int i = 0; i < current->moves.size(); i++)
    {

      if (!current->moves[i]->checked && !include(queue, current->moves[i], debut))
      {
        current->moves[i]->previous = current;
        current->moves[i]->stips = current->stips + 1;
        queue.push_back(current->moves[i]);
        fin++;
      }
    }
  }

  return end->stips;
}

int main()
{

  cout << knight("a1", "f7");
}
