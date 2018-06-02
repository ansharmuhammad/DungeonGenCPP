#include"dungeon.h"

dungeon::dungeon()
{
	//untuk inisiasi nilai randomya
	srand(static_cast<int>(time(0)));

	//inisiasi default
	proses = false;
	lebar = 40;
	panjang = 40;
	peta.resize(lebar + 6, panjang + 6);
	bsptree = true;
	minLebar = 8, minPanjang = 8, maxLebar = 15, maxPanjang = 15;
	listRuanganManual.clear();
	inOut = true;
	execute();
}

dungeon::~dungeon()
{
}

int dungeon::randomRange(int start, int size_index)
{
	return start + (rand() % size_index);
}

gridm dungeon::executeBsp(gridm peta, bool proses, int minW, int minH, int maxW, int maxH)
{
	//change** to param
	rectangle kotak(3, 3, peta.get_width() - 6, peta.get_height() - 6); //bikin kotak besar (minimal 10)
																		//inisiasi  spesifikasi ruangan
																		/*in menu lebar & panjang minimal, lebar & panjang maximal*/
																		//change to param
	int minLebar = minW, minPanjang = minH, maxLebar = maxW, maxPanjang = maxH;

	BSPTree pohon; //bikin tree
	pohon.addLeaf(kotak); //inisiasi tree

	pohon.split(minLebar, minPanjang, maxLebar, maxPanjang); //bikin bsp tree

	vector<rectangle> wilayah = pohon.getListOrderValue(); //mendapatkan wilayah hasil split
	vector<rectangle> ruangan = pohon.getListLeafValue(); //mendapatkan daun pohon

														  //proses bsp tree
	int x1, y1, x2, y2;
	if (proses)
	{
		for (int l = 0; l < wilayah.size(); l++) //memasukkan data ke grid map
		{
			x1 = wilayah[l].x;
			y1 = wilayah[l].y;
			x2 = wilayah[l].x + wilayah[l].width - 1;
			y2 = wilayah[l].y + wilayah[l].height - 1;
			peta.set_region(x1, y1, x2, y2, l);
			peta.set_region_color(x1, y1, x2, y2, wilayah[l].color);

			//pohon.printInOrder(); //debugging
			system("cls");peta.printing();
		}
	}

	//proses bikin ruangan
	peta.clearing(0);
	int newLebar, newPanjang, newx1, newy1, newx2, newy2, roomCount = 0;
	for (int i = 0; i < ruangan.size(); i++)
	{
		//hanya area(wilayah) yang memenuhi kriteria yang dibuatkan ruangan
		if (ruangan[i].width >= minLebar && ruangan[i].height >= minPanjang)
		{
			//memasukkan data ke grid map
			roomCount += 1;
			newLebar = randomRange(2, ruangan[i].width - 2);
			newPanjang = randomRange(2, ruangan[i].height - 2);
			newx1 = ruangan[i].midX() - (newLebar / 2);
			newy1 = ruangan[i].midY() - (newPanjang / 2);
			newx2 = ruangan[i].midX() + (newLebar / 2);
			newy2 = ruangan[i].midY() + (newPanjang / 2);
			peta.set_region(newx1, newy1, newx2, newy2, i + 1);
			peta.set_region_color(newx1, newy1, newx2, newy2, ruangan[i].color);
			peta.set_region_display(newx1, newy1, newx2, newy2, " ");
			peta.set_region_visited(newx1, newy1, newx2, newy2, true);

			if (proses) { system("cls");peta.printing(); } //see progress
		}
	}
	return peta;
}

gridm dungeon::executeManual(gridm peta, vector<rectangle> listRoom)
{
	for (int i = 0; i < listRoom.size(); i++)
	{
		peta.set_region			(listRoom[i].x + 3, listRoom[i].y + 3, listRoom[i].x + 3 + listRoom[i].width, listRoom[i].y + 3 + listRoom[i].height, i + 1);
		peta.set_region_display	(listRoom[i].x + 3, listRoom[i].y + 3, listRoom[i].x + 3 + listRoom[i].width, listRoom[i].y + 3 + listRoom[i].height, " ");
		peta.set_region_visited	(listRoom[i].x + 3, listRoom[i].y + 3, listRoom[i].x + 3 + listRoom[i].width, listRoom[i].y + 3 + listRoom[i].height, true);
	}
	return peta;
}

gridm dungeon::executeMaze(gridm peta, bool proses)
{
	labyrinth maze(peta, proses);
	peta = maze.getMaze();
	if (proses) { system("cls");peta.printing(); }
	return peta;
}

vector<dungeon::cellConnector> dungeon::candidateConnector(gridm map)
{
	vector<cellConnector> listCC;
	listCC.clear();
	cellConnector cellCC;
	for (int y = 3; y < map.get_height() - 3; y++)
	{
		for (int x = 3; x < map.get_width() - 3; x++)
		{
			if (!map.getVisited(x, y))
			{
				//cek vertical {jika cell diatasnya nilainya berbeda dengan cell dibawahnya, dan jika cell yang dimaksud unvisited maka ditambahkan dalam opsi connector}
				if (map.getVisited(x, y - 1) && map.getValue(x, y - 1) != 0)
				{
					if (map.getVisited(x, y + 1) && map.getValue(x, y + 1) != 0 && map.getValue(x, y - 1) != map.getValue(x, y + 1))
					{
						cellCC.Cell = map.getCell(x, y);
						cellCC.step = 1;
						cellCC.direction = 'v';
						listCC.push_back(cellCC);
					}
					else if (map.getVisited(x, y + 2) && map.getValue(x, y + 2) != 0 && map.getValue(x, y - 1) != map.getValue(x, y + 2) && !map.getVisited(x, y + 1) && !map.getVisited(x + 1, y + 1) && !map.getVisited(x - 1, y + 1))
					{
						cellCC.Cell = map.getCell(x, y);
						cellCC.step = 2;
						cellCC.direction = 'v';
						listCC.push_back(cellCC);
					}
				}

				//cekhorizontal {jika cell dikirinya nilainya berbeda dengan cell dikanannya, dan jika cell yang dimaksud unvisited maka ditambahkan dalam opsi connector}
				if (map.getVisited(x - 1, y) && map.getValue(x - 1, y) != 0)
				{
					if (map.getVisited(x + 1, y) && map.getValue(x + 1, y) != 0 && map.getValue(x - 1, y) != map.getValue(x + 1, y))
					{
						cellCC.Cell = map.getCell(x, y);
						cellCC.step = 1;
						cellCC.direction = 'h';
						listCC.push_back(cellCC);
					}
					else if (map.getVisited(x + 2, y) && map.getValue(x + 2, y) != 0 && map.getValue(x - 1, y) != map.getValue(x + 2, y) && !map.getVisited(x + 1, y) && !map.getVisited(x + 1, y + 1) && !map.getVisited(x + 1, y - 1))
					{
						cellCC.Cell = map.getCell(x, y);
						cellCC.step = 2;
						cellCC.direction = 'h';
						listCC.push_back(cellCC);
					}
				}

			}
		}
	}
	return listCC;
}

gridm dungeon::executeConnector(gridm peta, bool proses)
{
	//membuat penghubung
	bool ulang = true;
	while (ulang)
	{
		vector<cellConnector> calonPenghubung;
		calonPenghubung.clear();

		//cek calon penghubung
		calonPenghubung = candidateConnector(peta);

		if (proses) { system("cls");peta.printing(); }

		//hubungkan	
		if (!calonPenghubung.empty())
		{
			int nilaiSumber, nilaiTarget;
			cellConnector penghubung;
			for (int re = 0; re < 2; re++)
			{
				//pilih penghubung
				int randomIndex = rand() % calonPenghubung.size();
				penghubung = calonPenghubung[randomIndex];

				//set penghubung
				switch (penghubung.direction)
				{
				case 'v'://untuk penghubung vertikal
					nilaiSumber = peta.getValue(penghubung.Cell.x, penghubung.Cell.y - 1);
					peta.setValue(penghubung.Cell.x, penghubung.Cell.y, nilaiSumber);peta.setDisplay(penghubung.Cell.x, penghubung.Cell.y, " ");
					if (penghubung.step == 2)
					{
						peta.setValue(penghubung.Cell.x, penghubung.Cell.y + 1, nilaiSumber); peta.setDisplay(penghubung.Cell.x, penghubung.Cell.y + 1, " ");
						nilaiTarget = peta.getValue(penghubung.Cell.x, penghubung.Cell.y + 2);
					}
					else { nilaiTarget = peta.getValue(penghubung.Cell.x, penghubung.Cell.y + 1); }

					break;

				case 'h'://untuk penghubung horizontal
					nilaiSumber = peta.getValue(penghubung.Cell.x - 1, penghubung.Cell.y);
					peta.setValue(penghubung.Cell.x, penghubung.Cell.y, nilaiSumber); peta.setDisplay(penghubung.Cell.x, penghubung.Cell.y, " ");
					if (penghubung.step == 2)
					{
						peta.setValue(penghubung.Cell.x + 1, penghubung.Cell.y, nilaiSumber); peta.setDisplay(penghubung.Cell.x + 1, penghubung.Cell.y, " ");
						nilaiTarget = peta.getValue(penghubung.Cell.x + 2, penghubung.Cell.y);
					}
					else { nilaiTarget = peta.getValue(penghubung.Cell.x + 1, penghubung.Cell.y); }
					break;

				}
			}
			//replace nilaiSumber dengan nilaiTarget. agar tidak masuk dalam opsi connector lagi 
			for (int y = 0; y < peta.get_height(); y++)
			{
				for (int x = 0; x < peta.get_width(); x++)
				{
					if (peta.getValue(x, y) == nilaiTarget)
					{
						peta.setValue(x, y, nilaiSumber);peta.setColor(x, y, penghubung.Cell.color);
					}
					//ganti warna sumber
					if (peta.getValue(x, y) == nilaiSumber)
					{
						peta.setColor(x, y, penghubung.Cell.color);
					}
				}
			}
		}
		else
		{
			ulang = false;
		}
	}
	if (proses) { system("cls");peta.printing(); }
	return peta;
}

gridm dungeon::executeInOut(gridm peta, bool proses)
{
	//membuat pintu masuk
	vector<cellConnector> calonPintu;
	cellConnector kandidatPintu;
	for (int x = 3; x < peta.get_width() - 3; x++)
	{
		//long 1
		if (peta.getDisplay(x, 4) == " " && peta.getDisplay(x, 3) != " " && peta.getDisplay(x - 1, 3) != " " && peta.getDisplay(x + 1, 3) != " ")
		{
			kandidatPintu.Cell = peta.getCell(x, 3);kandidatPintu.step = 1;
			calonPintu.push_back(kandidatPintu);
		}
		//long 2
		if (peta.getDisplay(x, 5) == " " && peta.getDisplay(x, 3) != " " && peta.getDisplay(x - 1, 3) != " " && peta.getDisplay(x + 1, 3) != " "  && peta.getDisplay(x, 4) != " " && peta.getDisplay(x - 1, 4) != " " && peta.getDisplay(x + 1, 4) != " ")
		{
			kandidatPintu.Cell = peta.getCell(x, 3);kandidatPintu.step = 2;
			calonPintu.push_back(kandidatPintu);
		}
	}

	//set pintu masuk
	int randomIndex = rand() % calonPintu.size();
	cellConnector penghubung = calonPintu[randomIndex];
	for (int y = 0; y <= 3; y++) { peta.setDisplay(penghubung.Cell.x, y, " "); }
	if (penghubung.step == 2) { peta.setDisplay(penghubung.Cell.x, 4, " "); }

	//membuat pintu keluar
	calonPintu.clear();

	for (int x = 3; x < peta.get_width() - 3; x++)
	{
		//long 1
		if (peta.getDisplay(x, peta.get_height() - 1 - 4) == " " &&
			peta.getDisplay(x, peta.get_height() - 1 - 3) != " " && peta.getDisplay(x - 1, peta.get_height() - 1 - 3) != " " && peta.getDisplay(x + 1, peta.get_height() - 1 - 3) != " ")
		{
			kandidatPintu.Cell = peta.getCell(x, peta.get_height() - 1 - 3);kandidatPintu.step = 1;
			calonPintu.push_back(kandidatPintu);
		}
		//long 2
		if (peta.getDisplay(x, peta.get_height() - 1 - 5) == " "
			&& peta.getDisplay(x, peta.get_height() - 1 - 3) != " " && peta.getDisplay(x - 1, peta.get_height() - 1 - 3) != " " && peta.getDisplay(x + 1, peta.get_height() - 1 - 3) != " "
			&& peta.getDisplay(x, peta.get_height() - 1 - 4) != " " && peta.getDisplay(x - 1, peta.get_height() - 1 - 4) != " " && peta.getDisplay(x + 1, peta.get_height() - 1 - 4) != " ")
		{
			kandidatPintu.Cell = peta.getCell(x, peta.get_height() - 1 - 3);kandidatPintu.step = 2;
			calonPintu.push_back(kandidatPintu);
		}
	}

	//set pintu masuk
	randomIndex = rand() % calonPintu.size();
	penghubung = calonPintu[randomIndex];
	for (int y = peta.get_height() - 1; y >= peta.get_height() - 1 - 3; y--) { peta.setDisplay(penghubung.Cell.x, y, " "); }
	if (penghubung.step == 2) { peta.setDisplay(penghubung.Cell.x, peta.get_height() - 1 - 4, " "); }
	if (proses) { system("cls");peta.printing(); }

	return peta;
}

void dungeon::show()
{
	peta.printing();cout << endl;
}

void dungeon::execute()
{
	peta.resize(lebar + 6, panjang + 6);
	peta.clearing(0); //inisiasi peta
	if (bsptree) { peta = executeBsp(peta, proses, minLebar, minPanjang, maxLebar, maxPanjang); }
	else { peta = executeManual(peta, listRuanganManual); }
	peta = executeMaze(peta, proses);
	peta = executeConnector(peta, proses);
	if (inOut) { peta = executeInOut(peta, proses); }
}

void dungeon::save(string name)
{
	peta.save(name);
}