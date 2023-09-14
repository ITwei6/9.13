#pragma once
#include <iostream>
using namespace std;

//����������Ǻ�ɫ���Ǻ�ɫ
enum Color
{
	RED,
    BLACK
};
template <class K, class V>
//�ȶ�����
struct RBtreeNode
{
	RBtreeNode<K, V>* _left;
	RBtreeNode<K, V>* _right;
	RBtreeNode<K, V>* _parent;
	Color _col;
	pair<K, V> _kv;
	RBtreeNode(const pair<K,V> kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_col(RED)//������Ǻ�ɫ,�������Ԫ���Ǻ�ɫ��
		,_kv(kv)
	{}

};


template <class K, class V>
class RBTRree
{
	typedef RBtreeNode<K, V> Node;

public:
	bool CheckColour(Node* root, int blacknum, int benchmark)
	{
		if (root == nullptr)
		{
			if (blacknum != benchmark)
				return false;

			return true;
		}

		if (root->_col == BLACK)
		{
			++blacknum;
		}

		if (root->_col == RED && root->_parent && root->_parent->_col == RED)
		{
			cout << root->_kv.first << "����������ɫ�ڵ�" << endl;
			return false;
		}

		return CheckColour(root->_left, blacknum, benchmark)
			&& CheckColour(root->_right, blacknum, benchmark);
	}

	bool IsBalance()
	{
		return IsBalance(_root);
	}

	bool IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		if (root->_col != BLACK)
		{
			return false;
		}

		// ��׼ֵ
		int benchmark = 0;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK)
				++benchmark;

			cur = cur->_left;
		}

		return CheckColour(root, 0, benchmark);
	}

	void RotateL(Node* parent)//����
	{

		Node* cur = parent->_right;

		Node* curleft = cur->_left;
		parent->_right = curleft;
		if (curleft)
		{
			curleft->_parent = parent;
		}
		cur->_left = parent;
		Node* pp = parent->_parent;
		parent->_parent = cur;



		if (parent == _root)
		{
			//��ô����cur���Ǹ������
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (pp->_left == parent)
			{
				pp->_left = cur;
			}
			else
			{
				pp->_right = cur;
			}

			cur->_parent = pp;
			//��ת��cur��parent bf��Ϊ0?
		}
		
	}
	void RotateR(Node* parent)//�ҵ���
	{
		Node* cur = parent->_left;

		Node* curright = cur->_right;

		parent->_left = curright;
		if (curright)
		{
			curright->_parent = parent;
		}
		Node* ppnode = parent->_parent;
		cur->_right = parent;
		parent->_parent = cur;

		if (ppnode == nullptr)
		{
			//˵��cur�ͱ�ɸ��ڵ���
			_root = cur;
			cur->_parent = nullptr;
		}
		else
		{
			if (ppnode->_left == parent)
			{
				ppnode->_left = cur;
			}
			else
			{
				ppnode->_right = cur;
			}
			cur->_parent = ppnode;
		}
		
	}
	//��������������һ�µ�
	bool Insert(const pair<K, V>& kv)
	{
		//������Ĳ�������������Ĳ���
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		//˵���ö��������ǿ�������ô�ͽ��бȽ��ҵ�λ��
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				//��¼����λ��
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		//�ߵ��������curΪ���ˣ�����λ���Ѿ��ҵ���
		cur = new Node(kv);
		cur->_col = RED;
		//�������Ǻ�ɫ��
		if (kv.first > parent->_kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		//ע�����������������Ҫע�⸸ָ��
		cur->_parent = parent;
	    

		//�������Ǻ�ɫ�ģ�Ȼ��������ڵ��Ǻ�ɫ����ô��û���£���������ڵ��Ǻ�ɫ��ô����Ҫ���ۣ�
		//����parent������
		while (parent && parent->_col == RED)
		{
			Node* grandfather = parent->_parent;
			//�ȼ�¼���游λ��
			
			if (parent==grandfather->_left)
			{
				//˵���������ұ�
				Node* uncle = grandfather->_right;
				//uncle������Ϊ��ɫ
				if(uncle && uncle->_col == RED)
				{
					//�����������ɫ+���ϵ���
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;


				}
				else//uncle�����ڻ���uncle����Ϊ��ɫ   �����������ת+��ɫ   ��ת�����Ϊ��������Ҫ���ɫ
				{
					if (cur == parent->_left)
					{
						//����
						RotateR(grandfather);
						//��ɫ
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//˫��
						//������
						RotateL(parent);
						RotateR(grandfather);

						//��ɫ
						cur->_col = BLACK;
						grandfather->_col = RED;

					}
					break;
				}
			}
			else//parent==grandfather->_right
			{
				Node* uncle = grandfather->_left;

				//uncle������Ϊ��ɫ
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle�����ڻ��ߴ�����Ϊ��ɫ
				{
					if (cur == parent->_right)
					{
						//����
						RotateL(grandfather);
						//��ɫ
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else
					{
						//������������
						RotateR(parent);
						RotateL(grandfather);
						//��ɫ
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;

				}
			}

		}
		//�������������ڵ�ʱ�����ڵ㲻���ڣ������ʱ�����Ҫ�Ǻ�ɫ����ô����Ҫ��ɫ��ɫ
		_root->_col = BLACK;
		return true;
	}
	private:
		Node* _root=nullptr;
		
	};