#pragma once
using namespace std;

template <typename TKey, typename TData>
class TList;

template <typename TKey, typename TData>
class TNode
{
public:
	TKey key;
	TData* p_data;
	TNode* p_next;
	TNode();
	TNode(const TNode& _node);
	TNode(TKey _key, TData* _p_data, TNode* _p_next = nullptr);
	~TNode();
	
	friend ostream& operator<<(ostream& out, const TNode<TKey, TData>& _node)
	{
		if (_node.p_data == nullptr)
			out << "<no data in this node>";
		else
			out << "'" << _node.key << "' : '" << *(_node.p_data) << "'";
		return out;
	};
};

// constructors & destructors

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode()
{
	this->p_data = nullptr;
	this->p_next = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode& _node)
{
	this->key = _node.key;

	if (_node.p_data)
	{
		this->p_data = new TData;
		*(this->p_data) = *_node.p_data;
	}
	else this->p_data = nullptr;

	this->p_next = _node.p_next;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey _key, TData* _p_data, TNode* _p_next)
{
	this->key = _key;

	if (_p_data)
	{
		this->p_data = new TData;
		*(this->p_data) = *_p_data;
	}
	else this->p_data = nullptr;

	this->p_next = _p_next;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode()
{
	if (p_data)
		delete p_data;
	p_data = nullptr;
	p_next = nullptr;
}