#include"rectangle.h"

rectangle::rectangle()
{
	this->x = 0;
	this->y = 0;
	this->width = 1;
	this->height = 1;
	this->large = width * height;
	this->color = randomRange(0, 256);
}

rectangle::rectangle(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->large = width * height;
	this->color = randomRange(0, 256);  // memberikan nilai warna pada kotak secara random 
}

rectangle::~rectangle()
{
}

int rectangle::midX()
{
	return (this->x + (this->x + this->width - 1)) / 2;
}

int rectangle::midY()
{
	return (this->y + (this->y + this->height - 1)) / 2;
}

int rectangle::randomRange(int start, int size_index)
{
	return start + (rand() % size_index);
}

void rectangle::reDefine(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->large = width * height;
	this->color = randomRange(0, 256);  // memberikan nilai warna pada kotak secara random 
}