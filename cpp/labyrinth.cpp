#include"labyrinth.h"

labyrinth::labyrinth(gridm graph, bool progress)
{
	this->graph = graph;

	int mazeValue = 0;
	int widthMaze = graph.get_width() / 2;
	int heightMaze = graph.get_height() / 2;
	// menelusuri grid map untuk mencari ruang di titik(x,y) mana saja bisa dibuat maze
	for (int i = 0; i < heightMaze; i++)
	{
		for (int j = 0; j < widthMaze; j++)
		{
			if (!graph.getVisited(j * 2, i * 2) && cekAround(j * 2, i * 2) == false)
			{
				mazeValue -= 1;
				//membuat maze pada titk(x,y) yang punya ruang untuk di buat maze
				generate(j * 2, i * 2, mazeValue, progress);
			}
		}
	}

}

labyrinth::~labyrinth()
{
}

int labyrinth::randomRange(int start, int size_index)
{

	return start + (rand() % size_index);
}

void labyrinth::generate(int xStart, int yStart, int value, bool progress)
{
	//memeriksa apakah punya tetangga di titik start
	cekNeighbour(xStart, yStart);
	if (!graph.getVisited(xStart, yStart) && !neighbour.empty())
	{

		neighbour.clear();//inisiasi var. neighbour

						  //menandai cell start sudah dikunjungi(visited)
		graph.setVisited(xStart, yStart, true);
		graph.setValue(xStart, yStart, value);
		graph.setDisplay(xStart, yStart, " ");

		//menambahkan cell tersebut kedalam var. tracker
		tracker.push(graph.getCell(xStart, yStart));

		//selama var. tracker tidak kosong
		while (!tracker.empty())
		{
			cekNeighbour(tracker.top().x, tracker.top().y); //jika cell mempunyai neighbour(tetangga)
			if (!neighbour.empty())
			{
				carving(value, progress);// membuat jalur dan mem push jalur baru ke var. tracker
			}
			else
			{
				tracker.pop();// mem pop cell dari var. tracker
			}
		}
	}
}

void labyrinth::cekNeighbour(int x, int y)
{
	neighbour.clear();///< inisiasi variable neighbour
					  //cek tetangga

					  //cek cell atas
	if
		(
		(!graph.getVisited(x - 1, y - 1)) &&
			(!graph.getVisited(x + 1, y - 1)) &&
			(!graph.getVisited(x, y - 1)) &&
			(!graph.getVisited(x - 1, y - 2)) &&
			(!graph.getVisited(x + 1, y - 2)) &&
			(!graph.getVisited(x, y - 2)) &&
			(!graph.getVisited(x - 1, y - 3)) &&
			(!graph.getVisited(x + 1, y - 3)) &&
			(!graph.getVisited(x, y - 3))
			)
	{
		//jika cell yang dicek dapat di buat jalur(unvisited)
		//maka masukkan cell tersebut kedalam var. neighbour
		neighbour.push_back(up);
	}

	//cek cell bawah
	if
		(
		(!graph.getVisited(x - 1, y + 1)) &&
			(!graph.getVisited(x + 1, y + 1)) &&
			(!graph.getVisited(x, y + 1)) &&
			(!graph.getVisited(x - 1, y + 2)) &&
			(!graph.getVisited(x + 1, y + 2)) &&
			(!graph.getVisited(x, y + 2)) &&
			(!graph.getVisited(x - 1, y + 3)) &&
			(!graph.getVisited(x + 1, y + 3)) &&
			(!graph.getVisited(x, y + 3))
			)
	{
		//jika cell yang dicek dapat di buat jalur(unvisited)
		//maka masukkan cell tersebut kedalam var. neighbour
		neighbour.push_back(down);
	}

	//cek cell kiri
	if
		(
		(!graph.getVisited(x - 1, y - 1)) &&
			(!graph.getVisited(x - 1, y + 1)) &&
			(!graph.getVisited(x - 1, y)) &&
			(!graph.getVisited(x - 2, y - 1)) &&
			(!graph.getVisited(x - 2, y + 1)) &&
			(!graph.getVisited(x - 2, y)) &&
			(!graph.getVisited(x - 3, y - 1)) &&
			(!graph.getVisited(x - 3, y + 1)) &&
			(!graph.getVisited(x - 3, y))
			)
	{
		//jika cell yang dicek dapat di buat jalur(unvisited)
		//maka masukkan cell tersebut kedalam var. neighbour
		neighbour.push_back(left);
	}

	//cek cell kanan
	if
		(
		(!graph.getVisited(x + 1, y - 1)) &&
			(!graph.getVisited(x + 1, y + 1)) &&
			(!graph.getVisited(x + 1, y)) &&
			(!graph.getVisited(x + 2, y - 1)) &&
			(!graph.getVisited(x + 2, y + 1)) &&
			(!graph.getVisited(x + 2, y)) &&
			(!graph.getVisited(x + 3, y - 1)) &&
			(!graph.getVisited(x + 3, y + 1)) &&
			(!graph.getVisited(x + 3, y))
			)
	{
		//jika cell yang dicek dapat di buat jalur(unvisited)
		//maka masukkan cell tersebut kedalam var. neighbour
		neighbour.push_back(right);
	}

}

void labyrinth::carving(int value, bool progress)
{
	//randomize();
	int xcarv = tracker.top().x;
	int ycarv = tracker.top().y;

	//memilih cell secara acak dari var. neihgbour
	int randomIndex = rand() % neighbour.size();
	switch (neighbour[randomIndex])
	{
	case up: //jika terpilih atas
	{
		//ubah nilai cell yang ada di atasnya
		graph.setVisited(xcarv, ycarv - 1, true);
		graph.setValue(xcarv, ycarv - 1, value);
		graph.setDisplay(xcarv, ycarv - 1, " ");
		graph.setVisited(xcarv, ycarv - 2, true);
		graph.setValue(xcarv, ycarv - 2, value);
		graph.setDisplay(xcarv, ycarv - 2, " ");
		//push bakc cell yang di atas ke dalam var. tracker
		tracker.push(graph.getCell(xcarv, ycarv - 2));

		break;
	}
	case down://jika terpilih bawah
	{
		//ubah nilai cell yang ada di bawahnya
		graph.setVisited(xcarv, ycarv + 1, true);
		graph.setValue(xcarv, ycarv + 1, value);
		graph.setDisplay(xcarv, ycarv + 1, " ");
		graph.setVisited(xcarv, ycarv + 2, true);
		graph.setValue(xcarv, ycarv + 2, value);
		graph.setDisplay(xcarv, ycarv + 2, " ");
		//push bakc cell yang di bawah ke dalam var. tracker
		tracker.push(graph.getCell(xcarv, ycarv + 2));

		break;
	}
	case left://jika terpilih kiri
	{
		//ubah nilai cell yang ada di kirinya
		graph.setVisited(xcarv - 1, ycarv, true);
		graph.setValue(xcarv - 1, ycarv, value);
		graph.setDisplay(xcarv - 1, ycarv, " ");
		graph.setVisited(xcarv - 2, ycarv, true);
		graph.setValue(xcarv - 2, ycarv, value);
		graph.setDisplay(xcarv - 2, ycarv, " ");
		//push bakc cell yang di kiri ke dalam var. tracker
		tracker.push(graph.getCell(xcarv - 2, ycarv));

		break;
	}
	case right://jika terpilih kana
	{
		//ubah nilai cell yang ada di kanannya
		graph.setVisited(xcarv + 1, ycarv, true);
		graph.setValue(xcarv + 1, ycarv, value);
		graph.setDisplay(xcarv + 1, ycarv, " ");
		graph.setVisited(xcarv + 2, ycarv, true);
		graph.setValue(xcarv + 2, ycarv, value);
		graph.setDisplay(xcarv + 2, ycarv, " ");
		//push bakc cell yang di kanan ke dalam var. tracker
		tracker.push(graph.getCell(xcarv + 2, ycarv));

		break;
	}
	}
	if (progress) { system("cls");graph.printing(); }//untuk melihat proses
}

bool labyrinth::cekAround(int x, int y)
{
	if (
		graph.getVisited(x, y) ||
		graph.getVisited(x - 1, y) || graph.getVisited(x + 1, y) ||
		graph.getVisited(x, y - 1) || graph.getVisited(x, y + 1) ||
		graph.getVisited(x - 1, y - 1) || graph.getVisited(x + 1, y - 1) ||
		graph.getVisited(x - 1, y + 1) || graph.getVisited(x + 1, y + 1)
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}

gridm labyrinth::getMaze()
{
	return graph;
}