/**
* @brief merupakan objek berbentuk binary tree
*  yang dimana nilai child-nya adalah hasil pembagian dari nilai parent-nya
*
* @file BST.h
* @author Muhammad Anshar
* @date 2018-05-07
*/

#ifndef _BST_H
#define _BST_H

#pragma once
#include<iostream>
#include"rectangle.h"
#include<cstdlib>
#include<vector>
#include <time.h>

using namespace std;

/*
* 
* bentuk dari  pohon bst yang dibagi (bsp tree)
* 		  *root 20
* 	*kiri 8		*kanan 12	8+12 = 20
*
*/

/**
 * @brief merupakan objek berbentuk binary tree
 *  yang dimana nilai child-nya adalah hasil pembagian dari nilai parent-nya
 * 
 */
class BSPTree
{
private:
	//struct

	/**
	* @struct node
	* @brief struc node merupakan struktur data tree yang menyimpan data berupa rectangle
	*
	*/
	struct node
	{
		rectangle area;	///< data
		node* left;		///< anak kiri
		node* right;	///< anak kanan
	};

	//instance attribut
	node* root;						///< var. untuk menyimpan pohon
	vector<rectangle> listOrder;	///< var. list(daftar) menyimpan data tree secara preorder

	//function

	/**
	* @brief fungsi membuat daun baru
	*
	* @param area
	* @return BST::node*
	*/
	node* createLeaf(rectangle area);

	/**
	* @brief fungsi untuk mendapatkan angka secara acak
	*
	* @param start nilai minimum angka acak
	* @param size_index panjang jangkauan nilai acak
	* @return int nilai acak antara start hingga start + size_index
	*/
	int randomRange(int start, int size_index);

	//procedur

	/**
	* @brief untuk menghapus tree secara keseluruhan dari memori
	*
	* @param ptr pointer tree
	*/
	void removeSubTree(node* ptr); ///< post order
	
	/**
	* @brief fungsi untu membagi(memecah) data pohon menjadi daun baru
	*
	* @param ptr pohon yang akan di bagi
	* @param minWidth [int] lebar minimal
	* @param minHeight [int] panjang minimal
	* @param maxWidth [int] lebar maksimal
	* @param maxHeight [int] panjang maksimal
	*/
	void splitPrivate(node* ptr, int minWidth, int minHeight, int maxWidth, int maxHeight);

	/**
	* @brief memasukkan data pohon secara preorder
	* kedalam var. listOrder
	*
	* @param ptr pohon yang ingin didapatkan nnilai secara preorder
	*/
	void getListOrderPrivate(node* ptr);

	/**
	* @brief fungsi untuk memasukkan nilai data daung terbawah dari pohon ke dalam var. listOrder
	*
	* @param ptr
	*/
	void getListLeafPrivate(node* ptr);

	/**
	* @brief prosedur untuk mencetak data secara preorder
	*
	* @param ptr pohon yang ingin dicetak
	*/
	void preOrderPrivate(node* ptr);

	/**
	* @brief prosedur untuk mencetak data secara inOrder
	*
	* @param ptr pohon yang ingin dicetak
	*/
	void printInOrderPrivate(node* ptr);

public:
	//constructor

	/**
	* @brief Construct a new BST::BST object
	*
	*/
	BSPTree();
	
	//desttructor

	/**
	* @brief Destroy the BST::BST object
	* @see removeSubTree()
	*/
	virtual ~BSPTree();

	//setter

	/**
	* @brief prosedur emembuat daun baru dengan memanggil createLeaf
	*
	* @param area data rectangle yang akan disimpan di simpul pohon(daun)
	* @see createLeaf()
	*
	*/
	void addLeaf(rectangle area);

	/**
	* @brief prosedur membagi data dari tree menggunakan fungsi splitPrivate
	* dengan ketentuan jika melebihi ukuran max nya maka dibagi
	* dan hanya area yang di atas ukuran minimalnya yang akan di jadikan ruangan
	*
	* @param minWidth [int] lebar minimal
	* @param minHeight [int] panjang minimal
	* @param maxWidth [int] lebar maksimal
	* @param maxHeight [int] panjang maksimal
	*
	* @see splitPrivate()
	*
	*/
	void split(int minWidth, int minHeight, int maxWidth, int maxHeight);

	//getter

	/**
	* @brief mendapatkan nilai data pohon secara preorder
	* dengan memanggil fungsi getListOrder()
	*
	* @return vector<rectangle>
	* @see getListOrder()
	*/
	vector<rectangle> getListOrderValue();

	/**
	* @brief fungsi untuk mendapatkan nilai data dari daun terbawah dari pohon
	*
	* @return vector<rectangle>
	* @see getListLeaf()
	*/
	vector<rectangle> getListLeafValue();

	//behaviour


	/**
	* @brief memasukkan data pohon secara preorder
	* dengan memanggil fungsi getListOrderPrivate()
	* kedalam var. listOrder
	*
	* @see getListOrderPrivate()
	*/
	void getListOrder();

	/**
	* @brief fungsi untuk memuat data daun terbawah dari pohon
	* dengan memanggil fungsi getListLeaf()
	*
	* @see getListLeafPrivate()
	*/
	void getListLeaf();

	/**
	* @brief prosedur untuk mencetak data secara pre order dengan memanggil preOrderPrivate
	* @see preOrderPrivate()
	*/
	void preOrder();	 ///< pre order untuk keperluan debug
	
	/**
	* @brief prosedur untuk mencetak data secara inOrder dengan memanggil printInOrderPrivate()
	* @see printInOrderPrivate()
	*/
	void printInOrder(); //in order untuk keperluan debug

};

#endif // BST_H