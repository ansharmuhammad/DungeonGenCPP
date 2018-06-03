/**
 * @brief merupakan objek untuk menggenerate duneon dalam bentuk martriks char
 * 
 * @file dungeon.h
 * @author Muhammad Anshar
 * @date 2018-06-02
 */

#ifndef _DUNGEON_H
#define _DUNGEON_H

#pragma once
#include<cstdlib>		// random
#include<time.h>		// time
#include<vector>		// vector list
#include"rectangle.h"	// rectangle
#include"cell.h"		// cell
#include"gridm.h"		// gridm
#include"BSPTree.h"		// tree bsp
#include"labyrinth.h"	// labyrinth
#include<string>		// string

/**
* @mainpage dungeon generator (BSP Tree & recursive backtracking)
*
* Class untuk membuat dungeon secara otomatis
*
* dungeon yang di desain otomatis menggunakan penggabungan algoritma BSP Tree dan Recursive Backtracker.
* yang dimana BSP Tree berfungsi untuk membuat ruangan dalam dungeon (ruangan juga dapat dibuat secara manual)
* .dan Recursive Backtracker (atau juga dikenal sebagai Deep First Search) untuk membuat labirin nya.
*/

/**
 * @brief merupakan satu satunya objek yang di #include untuk membuat dungeon menggunakan fungsi dan mengatur attributnya.
 * 
 */
class dungeon
{
private:

	/**
	 * @brief struc yang menyimpan informasi suatu cell yang bisa digunakan sebagai penghubung
	 * 
	 */
	struct cellConnector {
		cell Cell;
		// 1 or 2 cell
		int step;
		// "u"p , "d"own, "l"eft, "r"ight
		char direction;
	};

	/**
	* @brief fungsi untuk mendapatkan angka secara acak
	*
	* @param start nilai minimum angka acak
	* @param size_index panjang jangkauan nilai acak
	* @return int nilai acak antara start hingga start + size_index
	*/
	int randomRange(int start, int size_index);

	/**
	* @brief fungsi untuk membuat ruangan dengan bsp tree
	*
	* @param peta [gridm] grid map untuk membuat ruangan
	* @param proses [bool] true untuk melihat proses pembuatan
	* @param minW [int] lebar minimal
	* @param minH [int] panjang minimal
	* @param maxW [int] lebar maksimal
	* @param maxH [int] panjang maksimal
	* @return gridm
	*/
	gridm executeBsp(gridm peta, bool proses, int minW, int minH, int maxW, int maxH);

	/**
	* @brief fungsi untuk membuat ruangan secara manual
	*
	* @param peta
	* @param listRoom
	* @return gridm
	*/
	gridm executeManual(gridm peta, vector<rectangle> listRoom);

	/**
	* @brief fungsi untuk membuat maze
	*
	* @param peta
	* @param proses
	* @return gridm
	*/
	gridm executeMaze(gridm peta, bool proses);

	/**
	* @brief fungsi untuk mendapat daftar cellyang bisa dijadikan connector
	*
	* @param map
	* @return vector<cellConnector>
	*/
	vector<cellConnector> candidateConnector(gridm map);

	/**
	* @brief fungsi untuk membuat connector yang dipilih dari calon connector
	*
	* @param peta
	* @param proses
	* @return gridm
	*/
	gridm executeConnector(gridm peta, bool proses);

	/**
	* @brief fungsi untuk membuat jalan masuk dan keluar
	*
	* @param peta
	* @param proses
	* @return gridm
	*/
	gridm executeInOut(gridm peta, bool proses);
	
	/**
	 * @brief merupakan atribut untuk menyimpan data dungeon
	 * 
	 */
	gridm peta;

public:

	/**
	 * @brief Construct a new dungeon object
	 * 
	 */
	dungeon();

	/**
	 * @brief Destroy the dungeon object
	 * 
	 */
	virtual ~dungeon();

	/**
	 * @brief fungsi untuk menapilkan hasil dungeon yang dibuat
	 * 
	 */
	void show();

	/**
	 * @brief mfungsi untuk men generate ulang dungeon dengan nilai attribut yang telah dirubah
	 * 
	 */
	void execute();

	/**
	 * @brief fungsi untuk menyimpandungeon ke dalam file .txt
	 * 
	 * @param name : nama file yang diinginkan
	 */
	void save(string name);

	//attribut sebagai parameter
	bool proses;		///< true untuk melihat proses pembuatan
	int lebar , panjang;///< lebar dan panjang dungeon 
	bool bsptree;		///< true jika ingin membuat ruangan dengan algoritma BSPTree
	int minLebar , minPanjang , maxLebar , maxPanjang ; ///< parameter yang digunakan oleh algoritma BSPTree
	vector<rectangle> listRuanganManual; ///< list yang berisikan definisi ruangan yang di inisiasi secara manual
	bool inOut;			///< bernilai true jika menginginkan dungeon dengan jalan masuk dan keluar
};

#endif // DUNGEON_H