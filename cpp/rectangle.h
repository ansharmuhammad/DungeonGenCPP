/**
* @brief
* merupakan objek berbentuk kotak
*
* @file rectangle.h
* @author Muhammad Anshar
* @date 2018-05-06
*/

#ifndef _RECTANGLE_H
#define _RECTANGLE_H

#pragma once
#include<stdlib.h> //random

/*
*
* bentuk objek rectangle yaitu kotak
*
*  		 		     x___ <-width(lebar)->
* 	|				y|  |
* panjang(height)	 |__| tampil seusai warna
*   |
*
*/

/**
 * @brief merupakan objek berbentuk kotak
 *
 */
class rectangle
{
public:
	//instance attribute
	int x;		///< koordinat x
	int y;		///< koordinat y
	int width;	///< lebar kotak
	int height;	///< tinggi kotak
	int color;	///< warna kotak
	int large;	///< luas kotak

	//constructor & destructor

	/**
	 * @brief Construct a new rectangle object
	 * 
	 */
	rectangle();

	/**
	* @brief Construct a new rectangle::rectangle object
	* membuat objek kotak
	* @param x [int] posisi x
	* @param y [int] posisi y
	* @param width [int] lebar
	* @param height [int] tinggi
	*/
	rectangle(int x, int y, int width, int height);

	/**
	* @brief Destroy the rectangle::rectangle object
	*
	*/
	virtual ~rectangle();

	//getter

	/**
	* @brief fungsi untuk mendapatkan posisi tengah horizontal
	*
	* @return int
	*/
	int midX();

	/**
	* @brief fungsi untuk mendapatan posisi tengah vertical
	*
	* @return int
	*/
	int midY();

	/**
	* @brief fungsi untuk mendapatkan angka secara acak
	*
	* @param start nilai minimum angka acak
	* @param size_index panjang jangkauan nilai acak
	* @return int nilai acak antara start hingga start + size_index
	*/
	int randomRange(int start, int size_index);

	//procedure

	/**
	 * @brief menginisiasi ulang objek
	 * 
	 * @param x [int] posisi x
	 * @param y [int] posisi y
	 * @param width [int] lebar
	 * @param height [int] tinggi
	 */
	void reDefine(int x, int y, int width, int height);
};

#endif // RECTANGLE_H