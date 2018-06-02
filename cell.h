/**
* @brief
* merupakan objek berupa cell(layaknya ruang di lemari) yang menyimpan beberapa attribut
*
* @file cell.h
* @author Muhammad Anshar
* @date 2018-05-06
*/

#ifndef _CELL_H
#define _CELL_H

#pragma once
#include<string> // string

using namespace std; // standard

/*
*
* bentuk dari objek cell
*  x________________
* y|nilai			|
*  |display(warna)	|
*  |dikunjungi?		|
*  ----------------
*/

/**
 * @brief merupakan objek berupa cell(layaknya ruang di lemari) yang menyimpan beberapa attribut
 *
 */
class cell
{
public:
	//constructore & destructor

	/**
	* @brief Construct a new cell::cell object
	*
	*/
	cell();

	/**
	* @brief Destroy the cell::cell object
	*
	*/
	virtual ~cell();

	//instance attribute
	int x;			///< koordinat x objek cell
	int y;			///< koordinat y objek cell
	int  value;		///< nilai yang disimpan objek cell
	bool visited;	///< menyatakan apakah cell sudah di kunjungi atau belum

	string display;	///< nilai yang dimunculkan cell di output (std::cout)
	int  color;		///< warna tampilan dari variable display
};

#endif // CELL_H