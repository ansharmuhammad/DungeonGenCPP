#pragma once
#include<iostream>
#include"dungeon.h"
#include"rectangle.h"

using namespace std;

int main()
{
	//membuat objek  dungeon
	dungeon level;

	//menampilkan dungeon dengan parameter default
	level.show();

	//menyimpan dungeon menjadi file berekstensi .txt
	level.save("dungeon");
	cout << "dungeon tersimpan. silahan periksa file di dalam direktori" << endl << endl;

	///////////////////////////////////////////////////////////
	/// dungeon yang menggunakan BSPTree
	///////////////////////////////////////////////////////////
	//inisiasi
	level.proses = false;
	level.lebar = 45;
	level.panjang = 45;
	level.bsptree = true;
	level.minLebar = 10; level.minPanjang = 10; level.maxLebar = 12; level.maxPanjang = 12;
	level.inOut = false;
	//end of inisiasi

	//build ulang dungeon
	level.execute();
	level.show();

	///////////////////////////////////////////////////////////
	/// dungeon yang menggunakan deinisi ruangan secara manual
	///////////////////////////////////////////////////////////
	//inisiasi
	level.proses = false;
	level.lebar = 20;
	level.panjang = 20;
	level.bsptree = false; //jika ruangan di inisiasi secara manual, maka bsptree harus bernilai false
	level.listRuanganManual.clear(); //list nya harus di kosongkan dulu
	//inisiasi ruangan secara manual
	rectangle ruangan;
	ruangan.reDefine(0, 0, 5, 5); level.listRuanganManual.push_back(ruangan);
	ruangan.reDefine(14, 0, 5, 5); level.listRuanganManual.push_back(ruangan);
	ruangan.reDefine(0, 14, 5, 5); level.listRuanganManual.push_back(ruangan);
	ruangan.reDefine(14, 14, 5, 5); level.listRuanganManual.push_back(ruangan);
	ruangan.reDefine(7, 7, 5, 5); level.listRuanganManual.push_back(ruangan);
	level.inOut = false;
	//end of inisiasi

	//build ulang dungeon
	level.execute();
	level.show();

	system("pause");
	return 0;
}