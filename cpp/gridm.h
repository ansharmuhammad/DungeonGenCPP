/**
* @brief
* merupakan objek grid map. yaitu objek yang menampung sekumpulan objek cell pada koordinat x,y
* seperti cell pada micrososft excell
*
* @file gridm.h
* @author Muhammad Anshar
* @date 2018-05-07
*/

#ifndef _GRIDM_H
#define _GRIDM_H

#pragma once
#include<vector>	// list
#include<cstdlib>	// random
#include<Windows.h>	// warna
#include<string>	// string
#include<iostream>  // io
#include<fstream>	// file
#include"cell.h"	// cell

using namespace std; // standard

/*
*
* bentuk dari objek grid map
*  x
* y[cell(x,y)]			[cell(1,0)]			...[cell(lebar-1,0)]
*  [cell(0,1)]			[cell(1,1)]			...[cell(lebar-1,1)]
* 		*					*						*
*  [cell(0,panjang-1)]	[cell(1,panjang-1)]	...[cell(lebar-1,panjang-1)]
*
*/

/**
 * @brief
 * merupakan objek grid map. yaitu objek yang menampung sekumpulan objek cell pada koordinat x,y
 * seperti cell pada micrososft excell
 */
class gridm
{
private:
	//instance attribute
	int width; 	///< lebar grid map
	int height;	///< panjang grid map

public:
	//constructore & destructor

	/**
	* @brief Construct a new gridm::gridm object
	*
	*/
	gridm();

	/**
	* @brief Construct a new gridm::gridm object
	* membuat gridmap berisikan cell.
	* sebanyak lebar * panjang = banyaknya cell
	*
	* @param width [int] lebar map
	* @param height [int] panjang map
	*/
	gridm(int width, int height);

	/**
	* @brief Destroy the gridm::gridm object
	*
	*/
	virtual ~gridm();

	//instance attribute
	vector<vector<cell>> map; ///< list 2 dimensi yang berisikan cell

	//setter
	/**
	* @brief menginisiasi nilai setiap cell pada grid map
	*
	* @param value [int] nilai inisiasi untuk setiap cell
	*/
	void clearing(int value);

	/**
	* @brief setter : untuk menentukan value(nilai) cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @param value [int] nilai yang dierikan pada cell
	*/
	void setValue(int x, int y, int value);

	/**
	* @brief setter : untuk menentukan color(warna) cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @param color [int] kode warna yang dierikan pada cell
	*/
	void setColor(int x, int y, int color);

	/**
	* @brief setter : untuk menentukan apakah suatu cell sudah dikunjungi pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @param visited [bool] boolean yang diberikan pada variable visited di cell x,y
	*/
	void setVisited(int x, int y, bool visited);

	/**
	* @brief setter : untuk menentukan sekumpulan cell sudah dikunjungi atau belum pada koordinat x,y awal hingga x,y akhir
	*
	* @param x1 [int] koordinat x awal
	* @param y1 [int] koordinat y awal
	* @param x2 [int] koordinat x akhir
	* @param y2 [int] koordinat y akhir
	* @param visited [bool]  boolean yang diberikan pada variable visited di cell x,y
	*/
	void set_region_visited(int x1, int y1, int x2, int y2, bool value);

	/**
	* @brief setter : untuk menentukan value(nilai) sekumpulan cell pada koordinat x,y awal hingga x,y akhir
	*
	* @param x1 [int] koordinat x awal
	* @param y1 [int] koordinat y awal
	* @param x2 [int] koordinat x akhir
	* @param y2 [int] koordinat y akhir
	* @param value [int] nilai yang dierikan pada cell
	*/
	void set_region(int x1, int y1, int x2, int y2, int value);

	/**
	* @brief setter : untuk menentukan color(warna) sekumpulan cell pada koordinat x,y awal hingga x,y akhir
	*
	* @param x1 [int] koordinat x awal
	* @param y1 [int] koordinat y awal
	* @param x2 [int] koordinat x akhir
	* @param y2 [int] koordinat y akhir
	* @param color [int] kode warna yang dierikan pada cell
	*/
	void set_region_color(int x1, int y1, int x2, int y2, int color);

	/**
	* @brief setter : untuk menentukan objek cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @param Cell [cell] cell yang diberikan untuk koordinat x,y
	*/
	void setCell(int x, int y, cell Cell);

	/**
	* @brief setter : untuk menentukan display(string yang ditampilkan) cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @param value [string] string yang diberikan untuk cell pada koordinat x,y
	*/
	void setDisplay(int x, int y, string value);

	/**
	* @brief setter : untuk menentukan display(string yang ditampilkan) cell pada koordinat x,y awal hingga x,y akhir
	*
	* @param x1 [int] koordinat x awal
	* @param y1 [int] koordinat y awal
	* @param x2 [int] koordinat x akhir
	* @param y2 [int] koordinat y akhir
	* @param value [string] string yang diberikan untuk cell pada koordinat x,y
	*/
	void set_region_display(int x1, int y1, int x2, int y2, string value);

	/**
	* @brief prosedur untuk mengubah panjang dan lebar grid map
	*
	* @param width [int] lebar grid map yang baru
	* @param height [int] panjang grid map yang baru
	*/
	void resize(int height, int width);

	//getter

	/**
	* @brief getter : untuk mendapatkan nilai width(lebar) grid map
	*
	* @return int
	*/
	int get_width();

	/**
	* @brief getter : untuk mendapatkan nilai height(panjang) grid map
	*
	* @return int
	*/
	int get_height();

	/**
	* @brief getter : untuk mendapatkan nilai cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @return int
	*/
	int getValue(int x, int y);

	/**
	* @brief getter : untuk mendapatkan color(warna) cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @return int
	*/
	int getColor(int x, int y);

	/**
	* @brief getter : untuk mengetahui apakah cell pada koordinat x,y sudah dikunjungi
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @return true jika sudah dikunjungi
	* @return false jika belum dikunjungi
	*/
	bool getVisited(int x, int y);

	/**
	* @brief getter : untuk mendapatkan cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @return cell
	*/
	cell getCell(int x, int y);

	/**
	* @brief getter : untuk mendapatkan display(string yang ditampilkan) cell pada koordinat x,y
	*
	* @param x [int] koordinat x
	* @param y [int] koordinat y
	* @return string
	*/
	string getDisplay(int x, int y);

	//behaviour

	/**
	* @brief
	* untuk mencetak(menampilkan) seluruh cell pada grid map
	*
	*/
	void printing();

	/**
	* @brief
	* untuk menyimpan seluruh cell pada grid map
	*
	*/
	void save(string name);
};

#endif // GRIDM_H