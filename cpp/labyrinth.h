/**
* @brief
* merupaan objek maze(labirin) yang dibuat di dalam grid map dengan menggunakan algoritma deep first search
*
* @file labirinth.h
* @author Muhammad Anshar
* @date 2018-05-07
*/

#ifndef _LABYRINTH_H
#define _LABYRINTH_H

#pragma once
#include<string>
#include<stack>
#include<queue>
#include<vector>
#include<time.h>
#include"gridm.h"
#include"cell.h"

using namespace std;

//mendefinisikan konstanta arah
#define up 0
#define down 1
#define left 2
#define right 3

/**
 * @brief 
 * merupaan objek maze(labirin) yang dibuat di dalam grid map dengan menggunakan algoritma deep first search
 * 
 */
class labyrinth
{
private:
	stack<cell> tracker;	///< data berbentuk stack(tumpukan) untuk menyimpan langkah pembuatan maze
	vector<int> neighbour;	///< list(daftar) tetangga suatu cell yang belum di kunjungi
	gridm graph;			///< merupakan grid map yang akan dibuat maze di dalamnya


	/**
	* @brief fungsi untuk mendapatkan angka secara acak
	*
	* @param start nilai minimum angka acak
	* @param size_index panjang jangkauan nilai acak
	* @return int nilai acak antara start hingga start + size_index
	*/
	int randomRange(int start, int size_index);

	/**
	* @brief prosedur untuk membuat map di mulai pada titik (xstart,ystart)
	*
	* @param xStart nilai titik x awal untuk maze
	* @param yStart nilai titik y awal untuk maze
	* @param value  id maze (nilai yang diberikan pada cell yang dilalui maze)
	* @param progress true jika ingin melihat proses pembuatan maze
	*
	* @see cekNeighbour()
	* @see carving()
	*/
	void generate(int xStart, int yStart, int value, bool progress);

	/**
	* @brief
	* prosedur untuk memeriksa cell tetangga di sekitar cell yang ada pada top stack tracker apakah cell tersebut dapat dibuat jalur(unvisited) maze atau tidak
	* jika dapat dibuat jalur, maka cell tersebut disimpan di dalam variable neighbour
	*
	* @param x [int] posisi x cell yang diperiksa
	* @param y [int] posisi y cell yang diperiksa
	*/
	void cekNeighbour(int x, int y);

	/**
	* @brief merupakan prosedur untuk membuat jalur maze dari cell yang terpilih dalam list(daftar) var. neighbour
	*
	* @param value
	* @param progress untuk melihat proses
	*/
	void carving(int value, bool progress);

	/**
	* @brief merupakan prosedur untuk memeriksa suatu cell dapat dijadikan titik awal untuk membuat maze
	* dengan memeriksa cell di sekitarnya
	*
	* @param x [int] posisi x cell yang di periksa
	* @param y [int] posisi y cell yang di periksa
	* @return true jika cell disekitarnya unvisited
	* @return false jika cell disekitarnya ada visited
	*/
	bool cekAround(int x, int y);

public:

	/**
	* @brief Construct a new labirinth::labirinth object
	* membuat maze pada grid map dengan memanggil fungsi generate
	*
	* @param graph grid map tujuan yang akan di buat maze di dalamnya
	* @param progress true jika ingin melihat proses pembuatan maze
	*
	* @see generate()
	*/
	labyrinth(gridm graph, bool progress);

	/**
	* @brief Destroy the labirinth::labirinth object
	*
	*/
	virtual ~labyrinth();

	/**
	* @brief merpukan getter untuk mendapatkan grid map yang terdapat maze di dalamnya
	*
	* @return gridm
	*/
	gridm getMaze();		///< variable yang mengembalikan hasil labyrinth
};

#endif // LABYRINTH_H