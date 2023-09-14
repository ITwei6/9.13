#include "RB_tree.h"


void test()
{
	RBTRree<int, int> avt ;
	avt.Insert(make_pair(1,1));

	avt.Insert(make_pair(2, 2));
	avt.Insert(make_pair(3, 3));


}
int main()
{
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	RBTRree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
		cout << "Insert:" << e << "->" << t.IsBalance() << endl;
	}

	return 0;
}
