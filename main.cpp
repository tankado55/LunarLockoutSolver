#include <iostream>
#include <vector>
#include <set>

struct Move
{
	int x0, y0, x1, y1;
	void printf()
	{
		//std::cout << x0 << "," << x1 << 
	}
};

struct Board;
bool isSeen(const Board& b);
void see(const Board& b);


struct Board
{
	int grid[5][5];

	std::vector<Move> enumerateMoves() const
	{
		std::vector<Move> move;
		for (int x = 0; x < 5; x++)
		{
			int lastFull = -1;
			for (int y = 0; y < 5; y++)
			{
				if (grid[x][y] != 0)
				{
					if (lastFull != -1 && y > lastFull + 1)
					{
						move.push_back(Move{ x,y,          x,lastFull + 1 });
						move.push_back(Move{ x,lastFull,   x,y - 1 });
					}
					lastFull = y;
				}
			}
		}

		for (int y = 0; y < 5; y++)
		{
			int lastFull = -1;
			for (int x = 0; x < 5; x++)
			{
				if (grid[x][y] != 0)
				{
					if (lastFull != -1 && x > lastFull + 1)
					{
						move.push_back(Move{ x,y,          lastFull + 1,y });
						move.push_back(Move{ lastFull,y,   x-1,y  });
					}
					lastFull = x;
				}
			}
		}
		return move;
	}

	bool operator<(const Board& b) const
	{
		for (int y = 0; y < 5; y++)
			for (int x = 0; x < 5; x++)
			{
				if (grid[x][y] < b.grid[x][y]) return true;
				if (grid[x][y] > b.grid[x][y]) return false;
			}
		return false;
	}

	void printf() const
	{
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
				std::cout << grid[x][y] << " ";

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	int nextMove()
	{

		if (grid[2][2] == 2) return +1;
	}

	void clearBoard()
	{
		for (int x = 0; x < 5; x++)
			for (int y = 0; y < 5; y++)
				grid[x][y] = 0;
	}

	bool won() const
	{
		return grid[2][2] == 2;
	}

	void playMove(Move m)
	{
		std::swap(grid[m.x0][m.y0], grid[m.x1][m.y1]);
	}

	bool solve() {
		if (won()) return true;
		
		std::vector<Move> moves = enumerateMoves();;
		for (Move m : moves)
		{
			Board n = *this;
			n.playMove(m);
			if (isSeen(n)) continue;
			see(n);
			if (n.solve()) {
				n.printf();
				return true;
			}

		}
		return false;
	}
};

std::set<Board> seen;

bool isSeen(const Board& b)
{
	return (seen.find(b) != seen.end());
}

void see(const Board& b)
{
	seen.insert(b);
}

Board n;
int main()
{
	n.clearBoard();
	n.grid[0][0] = 1;
	n.grid[4][0] = 1;
	n.grid[1][1] = 2;
	n.grid[2][4] = 1;
	n.grid[4][4] = 1;

	n.enumerateMoves();

	//std::cout << n.move.size() << std::endl;

	bool res = n.solve();
	n.printf();

	std::cout << res << std::endl;
}