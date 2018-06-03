#include"BSPTree.h"

BSPTree::BSPTree()
{
	root = NULL;
}

BSPTree::~BSPTree()
{
	removeSubTree(root);// menghapus seluruh tree dari memori mdengan memanggil prosedur removesubtree()
}

void BSPTree::removeSubTree(node* ptr)
{
	//penelusuran secara post order
	if (ptr != NULL)
	{
		if (ptr->left != NULL)
		{
			//hapus tree dari memori
			removeSubTree(ptr->left);
		}
		if (ptr->right != NULL)
		{
			//hapus tree dari memori
			removeSubTree(ptr->right);
		}
		delete ptr;
	}
}

void BSPTree::addLeaf(rectangle area)
{
	root = createLeaf(area);
}

BSPTree::node* BSPTree::createLeaf(rectangle area)
{
	node* leaf = new node;
	leaf->area = area;
	leaf->left = NULL;
	leaf->right = NULL;

	return leaf;
}

int BSPTree::randomRange(int start, int size_index)
{
	return start + (rand() % size_index);
}

void BSPTree::split(int minWidth, int minHeight, int maxWidth, int maxHeight)
{
	splitPrivate(root, minWidth, minHeight, maxWidth, maxHeight);
}

void BSPTree::splitPrivate(node* ptr, int minWidth, int minHeight, int maxWidth, int maxHeight)
{
	if (ptr->area.width > maxWidth || ptr->area.height > maxHeight)
	{
		//menentukan dibagi secara horizontal atau vertikal
		bool splitHorizontal;
		if (ptr->area.height != ptr->area.width)
		{
			splitHorizontal = (ptr->area.height > ptr->area.width) ? true : false;
		}
		else
		{
			splitHorizontal = (randomRange(0, 2)) ? true : false;
		}

		//menentukan apakah pohon masih bisa dibagi(dipecah)
		bool canSplit = (ptr->area.width > minWidth && ptr->area.height > minHeight) ? true : false;

		if (splitHorizontal && canSplit) //membagi secara horizontal
		{
			//membagi panjang dengan ukuran random
			int newHeight = minHeight + randomRange(0, ptr->area.height - minHeight);
			//randomRange(0, ptr->area.height);
			//randomRange(maxHeight, ptr->area.height - maxHeight);
			//minHeight + randomRange(0, ptr->area.height-minHeight*2);

			//rectangle setelah dibagi
			rectangle leftArea(ptr->area.x, ptr->area.y, ptr->area.width, newHeight);
			rectangle rightArea(ptr->area.x, ptr->area.y + newHeight, ptr->area.width, ptr->area.height - newHeight);

			//membuat daun baru hasil rectangle setelah dibagi
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->left = createLeaf(leftArea);
			ptr->right = createLeaf(rightArea);

			//bagi lagi daun yang baru dibuat
			splitPrivate(ptr->left, minWidth, minHeight, maxWidth, maxHeight);
			splitPrivate(ptr->right, minWidth, minHeight, maxWidth, maxHeight);

		}
		else if (canSplit) //membagi secara vertikal
		{
			//membagi panjang dengan ukuran random
			int newWidth = minWidth + randomRange(0, ptr->area.height - minWidth);
			//randomRange(0, ptr->area.width);
			//randomRange(maxWidth,ptr->area.width-maxWidth);
			//minWidth + randomRange(0, ptr->area.height-minWidth*2);

			//rectangle setelah dibagi
			rectangle leftArea(ptr->area.x, ptr->area.y, newWidth, ptr->area.height);
			rectangle rightArea(ptr->area.x + newWidth, ptr->area.y, ptr->area.width - newWidth, ptr->area.height);

			//membuat daun baru hasil rectangle setelah dibagi
			ptr->left = NULL;
			ptr->right = NULL;
			ptr->left = createLeaf(leftArea);
			ptr->right = createLeaf(rightArea);

			//bagi lagi daun yang baru dibuat
			splitPrivate(ptr->left, minWidth, minHeight, maxWidth, maxHeight);
			splitPrivate(ptr->right, minWidth, minHeight, maxWidth, maxHeight);

		}
	}
}

vector<rectangle> BSPTree::getListOrderValue()
{
	getListOrder();
	return listOrder;
}

void BSPTree::getListOrder()
{
	listOrder.clear();
	getListOrderPrivate(root);
}

void BSPTree::getListOrderPrivate(node* ptr)
{
	if (ptr == NULL)
		return;

	//dapatkan data parent
	listOrder.push_back(ptr->area);

	//dapatkan data kiri
	getListOrderPrivate(ptr->left);

	//dapatkan data kanan
	getListOrderPrivate(ptr->right);
}

vector<rectangle> BSPTree::getListLeafValue()
{
	getListLeaf();
	return listOrder;
}

void BSPTree::getListLeaf()
{
	listOrder.clear();
	getListLeafPrivate(root);
}

void BSPTree::getListLeafPrivate(node* ptr)
{
	if (ptr == NULL)
		return;

	//jika merupakan daun
	if (ptr->left == NULL && ptr->right == NULL)
	{
		listOrder.push_back(ptr->area);
	}

	//cek kiri
	getListLeafPrivate(ptr->left);

	//cek kanan
	getListLeafPrivate(ptr->right);
}

void BSPTree::preOrder()
{
	preOrderPrivate(root);
	cout << endl;
}

void BSPTree::preOrderPrivate(node* ptr)
{
	if (ptr == NULL)
		return;

	//dapatkan data parent
	cout << ptr->area.width << "x" << ptr->area.height << " ";

	//dapatkan data kiri
	preOrderPrivate(ptr->left);

	//dapatkan data kanan
	preOrderPrivate(ptr->right);
}

void BSPTree::printInOrder()
{
	printInOrderPrivate(root);
}

void BSPTree::printInOrderPrivate(node* ptr)
{
	if (root != NULL)
	{
		if (ptr->left != NULL)
		{
			printInOrderPrivate(ptr->left);
		}

		cout << ptr->area.color << " " << endl;

		if (ptr->right != NULL)
		{
			printInOrderPrivate(ptr->right);
		}
	}
	else
	{
		cout << " kosong " << endl;
	}
}