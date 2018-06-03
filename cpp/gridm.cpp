#include"gridm.h"

gridm::gridm()
{
	map.clear();
	this->height = 1;
	this->width = 1;

	map.resize(this->height);
	for (int i = 0; i < this->height; ++i)
	{
		map[i].resize(this->width);
	}

}

gridm::gridm(int  width, int height)
{
	map.clear();
	this->height = height;
	this->width = width;
	map.resize(this->height);
	for (int i = 0; i < this->height; ++i)
	{
		map[i].resize(this->width);
	}
	clearing(0);
}

gridm::~gridm()
{
}


void gridm::clearing(int value)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			map[y][x].value = value;
			map[y][x].visited = true;//td
			map[y][x].display = "*";
			map[y][x].color = 14;
			map[y][x].x = x;
			map[y][x].y = y;
		}
	}
	for (int i = 3; i < height - 3; i++) {
		for (int j = 3; j < width - 3; j++) {
			map[i][j].visited = false;
			map[i][j].color = 10;
		}
	}
}


void gridm::setValue(int x, int y, int value)
{
	map[y][x].value = value;
}


void gridm::setColor(int x, int y, int color)
{
	map[y][x].color = color;
}


void gridm::setVisited(int x, int y, bool visited)
{
	map[y][x].visited = visited;
}


void gridm::set_region_visited(int x1, int y1, int x2, int y2, bool visited)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			setVisited(j, i, visited);
		}
	}
}


void gridm::set_region(int x1, int y1, int x2, int y2, int value)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			setValue(j, i, value);
		}
	}
}


void gridm::set_region_color(int x1, int y1, int x2, int y2, int color)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			setColor(j, i, color);
		}
	}
}


void gridm::setCell(int x, int y, cell Cell)
{
	map[y][x] = Cell;
}


void gridm::setDisplay(int x, int y, string value)
{
	map[y][x].display = value;
}


void gridm::set_region_display(int x1, int y1, int x2, int y2, string value)
{
	for (int i = y1; i <= y2; i++)
	{
		for (int j = x1; j <= x2; j++)
		{
			setDisplay(j, i, value);
		}
	}
}

void gridm::resize(int width, int height)
{
	this->height = height;
	this->width = width;
	map.resize(this->height);
	for (int i = 0; i < this->height; ++i)
	{
		map[i].resize(this->width);
	}
}

int gridm::get_width()
{
	return width;
}


int gridm::get_height()
{
	return height;
}


int gridm::getValue(int x, int y)
{
	return map[y][x].value;
}


int gridm::getColor(int x, int y)
{
	return map[y][x].color;
}


bool gridm::getVisited(int x, int y)
{
	return map[y][x].visited;
}


cell gridm::getCell(int x, int y)
{
	return map[y][x];
}


string gridm::getDisplay(int x, int y)
{
	return map[y][x].display;
}



void gridm::printing()
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			//mengubah warna
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), map[i][j].color);
			//mencetak cell
			cout << map[i][j].display << " ";
		}
		cout << endl;
	}cout << endl;
}


void gridm::save(string name)
{
	ofstream out(name + ".txt");
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			//mencetak cell
			out << map[i][j].display << " ";
		}
		out << "\n";
	}
	out.close();
}