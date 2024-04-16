#include <iostream>
using namespace std;

struct Node {
	int info;
	Node* left;
	Node* right;
};
typedef Node* NodePtr;

#pragma region Chèn nút
NodePtr makeNode(int value)
{
	NodePtr newNode = new Node;
	if (newNode == NULL) return NULL;
	newNode->info = value;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

void insert(NodePtr& root, int value)
{
	if (root == NULL) root = makeNode(value);

	else if (value == root->info) 
		cout << "\n Node da ton tai";
	else if (value < root->info) 
		insert(root->left, value);
	else 
		insert(root->right, value);
}
#pragma endregion

#pragma region Tìm nút
NodePtr findNode(NodePtr root, int value)
{
	if (root == NULL || root->info == value) 
		return root;
	else if (value < root->info) 
		return findNode(root->left, value);
	else 
		return findNode(root->right, value);
}
#pragma endregion

#pragma region Xóa nút
void deleteNode(NodePtr& root, int value)
{
	if(root == NULL) return;
	if(root->info == value)
	{
		if(root->left == NULL)
		{
			NodePtr temp = root;
			root = root->right;
			delete(temp);
		}
		else if (root->right == NULL)
		{
			NodePtr temp = root;
			root = root->left;
			delete(temp);
		}
		else
		{
			NodePtr maxRightOfLeftSubTree = root->left;
			while (maxRightOfLeftSubTree->right != NULL)
			{
				maxRightOfLeftSubTree = maxRightOfLeftSubTree->right;
			}
			root->info = maxRightOfLeftSubTree->info;
			deleteNode(root->left, maxRightOfLeftSubTree->info);
		}
	}
	else if(value < root->info)
		deleteNode(root->left, value);
	else
		deleteNode(root->right, value);
}
#pragma endregion

#pragma region Xuất các loại
void preOrder(NodePtr root)
{
	if (root)
	{
		cout << root->info << " ";
		preOrder(root->left);
		preOrder(root->right);
	}
}
void inOrder(NodePtr root)
{
	if (root)
	{
		inOrder(root->left);
		cout << root->info << " ";
		inOrder(root->right);
	}
}
void postOrder(NodePtr root)
{
	if (root)
	{
		postOrder(root->left);
		postOrder(root->right);
		cout << root->info << " ";
	}
}
void LNR(NodePtr root)
{
	if (root)
	{
		LNR(root->left);
		cout << root->info << " ";
		LNR(root->right);
	}
}
#pragma endregion

#pragma region Tổng số Node
int totalNode(NodePtr root) 
{
	if (!root) return 0; //Có thể ghi là (root == NULL)
	return 1 + totalNode(root->left) + totalNode(root->right);
}
#pragma endregion

#pragma region Tổng giá trị các trong Node
int tongGiaTri(NodePtr root)
{
	if (!root) return 0; //Có thể ghi là (root == NULL)
	return root->info + tongGiaTri(root->left) + tongGiaTri(root->right);
}
#pragma endregion //Thay 1 thành root->info để chuyển từ ĐẾM SỐ LƯỢNG sang TÍNH TỔNG GIÁ TRỊ (Những cái sau cũng thế y chang)

#pragma region Tổng số Node lá
int totalLeafNode(NodePtr root) 
{
	if (root == NULL) return 0; 
	if (root->left == NULL && root->right == NULL) //Có thể ghi là (!root->left && !root->right)
		return 1 /*+ totalLeafNode(root->left) + totalLeafNode(root->right)*/;
	return totalLeafNode(root->left) + totalLeafNode(root->right);
}
#pragma endregion

#pragma region Tổng số Node có 2 cây con
int tongNodeCo2CayCon(NodePtr root)
{
	if (root == NULL) return 0; 
	if (root->left != NULL && root->right != NULL) //Có thể ghi là (root->left && root->right)
		return 1 + tongNodeCo2CayCon(root->left) + tongNodeCo2CayCon(root->right);
	return tongNodeCo2CayCon(root->left) + tongNodeCo2CayCon(root->right);
}
#pragma endregion

#pragma region Tổng số Node có 1 cây con
int tongNodeCo1CayCon(NodePtr root)
{
	if (root == NULL) return 0;
	if (root->left != NULL && root->right == NULL || root->left == NULL && root->right != NULL) 
		//Có thể ghi là (root->left && !root->right || !root->left && root->right)
		return 1 + tongNodeCo1CayCon(root->left) + tongNodeCo1CayCon(root->right);
	return tongNodeCo1CayCon(root->left) + tongNodeCo1CayCon(root->right);
}
#pragma endregion

#pragma region Tính chiều cao cây
int height(NodePtr root)
{
	if (!root) return 0;
	int l = height(root->left);
	int r = height(root->right);
	if (l > r) return l + 1; // Có thể thay thế cụm điều kiện và trả về thành: 
	else return r + 1;		 // return max(left, right) + 1;
}
#pragma endregion

#pragma region Độ cao nút X
void heightOfXNode(NodePtr root, int x)
{
	if (root == NULL) cout << "\nCay rong";
	else
	{
		NodePtr temp = findNode(root, x);
		if (temp == NULL)
			cout << "\nNut khong ton tai trong cay => Khong tim duoc do cao";
		else
			cout << "\nDo cao cua nut " << x << ": " << height(temp);
	}
}
#pragma endregion

#pragma region Mức của nút X
void mucCuaNodeX(NodePtr root, int x)
{
	if (root == NULL) cout << "\nCay rong";
	else
	{
		int count = 0;
		while (root != NULL)
		{
			if (root->info == x) break;
			count++;
			if (x < root->info)
				root = root->left;
			else
				root = root->right;
		}
		if (root == NULL)
			cout << "\nNut khong ton tai => Khong tim duoc muc";
		else
			cout << "\nMuc cua nut " << x << ": " << count;
	}
}
#pragma endregion

#pragma region Xuất các giá trị tại mức X
void level(NodePtr root, int x)
{
	if (!root) return;
	if (x == 0)
		cout << root->info << " ";
	else
	{
		level(root->left, x - 1);
		level(root->right, x - 1);
	}
}
#pragma endregion

#pragma region Xuất các giá trị tại tất cả các mức
void printAllLevel(NodePtr root)
{
	int h = height(root);
	for (int i = 0; i < h; i++)
	{
		cout << endl;
		level(root, i);
	}
}
#pragma endregion





int main() 
{
	NodePtr root = NULL;
	int value;

	//Tự tạo cây, khỏi tốn sức nhập
	const int MAX = 10;
	int array[] = { 20,15,56,8,19,48,63,5,7,51 };
	for (int i = 0; i < MAX; i++)
	{
		insert(root, array[i]);
	}

#pragma region Chèn, Xuất, Tìm, Xóa
	////Chèn 
	//while (true)
	//{
	//	cout << "\nNhap gia tri (Nhap -99 de dung): "; 
	//	cin >> value;
	//	if (value == -99) break;
	//	insert(root, value);
	//}

	////Xuất
	//cout << "\n\nXuat cay vua nhap:";
	//cout << "\nPreOrder: ";
	//preOrder(root);
	//cout << "\nInOrder: ";
	//inOrder(root);
	//cout << "\nPostOrder: ";
	//postOrder(root);
	//cout << "\nTang Dan: ";
	//LNR(root);

	////Tìm
	//cout << "\n\nNhap so can tim: ";
	//cin >> value;
	//cout << "\nVi tri can tim: " << findNode(root, value);

	////Xóa
	//cout << "\n\nNhap so can xoa: ";
	//cin >> value;
	//deleteNode(root, value);
#pragma endregion


	//Xuất
	cout << "\n\nXuat cay sau khi xoa:";
	cout << "\nPreOrder: ";
	preOrder(root);
	cout << "\nInOrder: ";
	inOrder(root);
	cout << "\nPostOrder: ";
	postOrder(root);
	cout << "\nTang Dan: ";
	LNR(root);

	//Tổng số Node, Tổng giá trị các Node, Tổng số Node lá, Tổng số Node có 2 cây con, Tổng số Node có 1 cây con
	cout << endl;
	cout << "\nTong so Node: " << totalNode(root);
	cout << "\nTong gia tri cac Node: " << tongGiaTri(root);
	cout << "\nTong so Node la: " << totalLeafNode(root);
	cout << "\nTong so Node co 2 cay con: " << tongNodeCo2CayCon(root);
	cout << "\nTong so Node co 1 cay con: " << tongNodeCo1CayCon(root);
	
	//Chiều cao cây
	cout << "\n\nChieu cao cay: " << height(root);

	////Chiều cao cây và mức của nút nhập từ bàn phím
	//cout << "\n\nNhap nut can tim do cao va muc: "; cin >> value;
	//heightOfXNode(root, value);
	//mucCuaNodeX(root, value);

	//Xuất các giá trị tại từng mức của cây (mức còn gọi là tầng của cây)
	cout << endl;
	level(root, 0);
	cout << endl;
	level(root, 1);
	cout << endl;
	level(root, 2);
	cout << endl;
	level(root, 3);
	cout << endl;
	level(root, 4);

	//Xuất các giá trị tại mức value tự chọn
	cout << "\n\nNhap muc muon chon: "; cin >> value;
	level(root, value);

	//Xuất các giá trị tại tất cả các mức
	cout << endl;
	printAllLevel(root);





	cout << endl << endl << "\n\n";
	return 0;
}