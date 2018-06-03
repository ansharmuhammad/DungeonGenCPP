# Dungeon Generator (BSP Tree & Recursive Backtracking)

Class c++ untuk membuat _dungeon_ secara otomatis. _Dungeon_ yang di desain otomatis menggunakan penggabungan algoritma [_BSP Tree_](http://physicsforanimators.com/what-is-a-bsp-tree/) dan [_Recursive Backtracker_](https://www.hackerearth.com/practice/basic-programming/recursion/recursion-and-backtracking/tutorial/). yang dimana _BSP Tree_ berfungsi untuk membuat ruangan dalam _dungeon_ (ruangan juga dapat dibuat secara manual) dan _Recursive Backtracker_ (atau juga dikenal sebagai Deep First Search) untuk membuat labirin nya.

### Bagaimana Program Ini Bekerja
program ini akan membuat dungeon secara otomatis dengan beberapa tahapan
1. membuat ruangan pada _dungeon_ dengan [_BSP Tree_](http://www.roguebasin.com/index.php?title=Basic_BSP_Dungeon_generation). _klik link untuk melihat cara pembuatan_
2. kemudian membuat jalur pada _dungeon_ dengan [_recursive backtracking_](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking). _klik link untuk melihat cara pembuatan_
3. lalu [menghubungkan](http://journal.stuffwithstuff.com/2014/12/21/rooms-and-mazes/) ruangan dengan jalur yang telah dibuat. _klik link untuk melihat cara pembuatan_
4. membuat jalur masuk dan keluar _dungeon_.

### Kebutuhan
- compiler c++

### Instalasi
1. masukkan seluruh file di folder (file .cpp dan .h) kecuali `example.cpp` ke dalam project anda

| Nama | Keterangan |
| --- | --- |
| `rectangle` | struktur data yang merepresentasikan kotak pada program |
| `cell` | struktur data yang merepresentasikan cell yang dapat menyimpan kotak |
| `gridm` | objek grid map yaitu struktur data yang menyimpan kumpulan cell pada titik x,y |
| `BSPTree` | struktur data [pohon(tree)](http://physicsforanimators.com/what-is-a-bsp-tree/) yang dimana simpul child menyimpan data pecahan dari data parentnya |
| `labyrinth` | objek untuk men generate maze pada grid map dengan metode [recursive bactracking](http://weblog.jamisbuck.org/2010/12/27/maze-generation-recursive-backtracking)|
| `dungeon` | objek untuk men generate _dungeon_ dengan menggabungkan `BSPTree` dan `labyrinth`|
2. include file `dungeon.h` pada program anda
```c++
#include"dungeon.h"
```
### Daftar Fungsi
berikut daftar fungsi dan kegunaan `dungeon.h` :

| fungsi | kegunaan |
| --- | --- |
| `execute`| generate ulang _dungeon_ dengan attribut baru |
| `show` | menampilkan _dungeon_ pada console|
| `save(string nama_file)` | menyimpan _dungeon_ dalam file .txt |

### Daftar Attribute
berikut daftar attribut dan keterangan `dungeon.h` :

| fungsi | tipe data | keterangan | default |
| --- | --- | --- | --- |
| proses | bool | true untuk melihat proses pembuatan | false |
| lebar, panjang | int | lebar dan panjang dungeon | 40, 40 |
|	bsptree | bool | true jika ingin membuat ruangan dengan algoritma BSPTree | true |
|	minLebar, minPanjang, maxLebar, maxPanjang | int | parameter yang digunakan oleh algoritma BSPTree | 8,8,15,15 |
|	listRuanganManual | vector<rectangle> | list yang berisikan definisi ruangan yang di inisiasi secara manual | empty |
|	inOut | bool | bernilai true jika menginginkan dungeon dengan jalan masuk dan keluar | true |

lihat [`dungeon.h`](https://github.com/ansharmuhammad/DungeonGenCPP/blob/master/cpp/dungeon.h) dan [`dungeon.cpp`](https://github.com/ansharmuhammad/DungeonGenCPP/blob/master/cpp/dungeon.cpp) untuk rincian

### Pemakaian
berikut beberapa cara untuk membuat _dungeon_ menggunakan framework ini :

#### Membuat Dungeon Dengan Nilai Default
```c++
#include<iostream>
#include"dungeon.h"
using namespace std;
int main(){
  //membuat objek  dungeon
  dungeon level;
  //menampilkan dungeon dengan parameter default
  level.show();
  //menyimpan dungeon menjadi file berekstensi .txt
  level.save("dungeon");
  cout << "dungeon tersimpan. silahan periksa file di dalam direktori" << endl << endl;
  system("pause");
  return 0;
}
```

#### Membuat Dungeon Dengan BSP Tree
```c++
#include<iostream>
#include"dungeon.h"
using namespace std;
int main(){
  //membuat objek  dungeon
  dungeon level;
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
  system("pause");
  return 0;
}
```

#### Membuat Dungeon Dengan inisiasi Ruangan Secara Manual 
```c++
#include<iostream>
#include"dungeon.h"
using namespace std;
int main(){
  //membuat objek  dungeon
  dungeon level;
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
```

untuk lebih rinci silahkan lihat file [`example.cpp`](https://github.com/ansharmuhammad/DungeonGenCPP/blob/master/cpp/example.cpp)

### Dibuat Menggunakan
- [visual studio community](https://www.visualstudio.com/vs/community/) - IDE yang digunakan
- [doxygen](http://www.stack.nl/~dimitri/doxygen/) - generator untuk dokumentasi code

### Authors
- Muhammad Anshar [`facebook`](https://www.facebook.com/anshar.ancay) , [`instagram`](https://www.instagram.com/_anshar_muhammad/), [`twitter`](https://twitter.com/swer_anshar?lang=id)

### Lisensi
project ini menggunakan lisensi MIT License - lihat file [LICENSE.md](https://github.com/ansharmuhammad/DungeonGenCPP/blob/master/LICENSE.md) untuk rincian
