#pragma once
#include "TNode.h"
using namespace std;

template <typename TKey, typename TData>
class TList
{
private:
	TNode<TKey, TData>* p_first;
	TNode<TKey, TData>* p_previous;
	TNode<TKey, TData>* p_current;
	TNode<TKey, TData>* p_next;

public:
	// constructors & destructors
	TList();
	TList(const TList<TKey, TData>& _list);
	TList(const TNode<TKey, TData>* _node);
	~TList();

	// inserting methods
	void insert_to_start(TKey _key, TData* _data);
	void insert_to_end(TKey _key, TData* _data);
	void insert_before(TKey key_where, TKey _key, TData* _data);
	void insert_after(TKey key_where, TKey _key, TData* _data);

	// searching & deleting methods
	TNode<TKey, TData>* find_key(const TKey _key);
	void remove_head();
	void remove_current();
	void remove_key(TKey _key);

	// positions & borders
	void go_next();
	void reset();
	bool is_ended() const;
	bool is_empty() const;
	TKey get_first_key() const;
	TKey get_current_key() const;

	// output
	friend ostream& operator<<(ostream& out, const TList<TKey, TData>& list_to_show)
	{
		if (list_to_show.is_empty())
			out << "<empty list>";
		else
		{
			TNode<TKey, TData>* p_another_node = list_to_show.p_first;
			while (p_another_node != nullptr)
			{
				out << *(p_another_node);
				if (p_another_node->p_next != nullptr)
					out << " -> ";
				p_another_node = p_another_node->p_next;
			}
		}
		return out;
	}
};

// constructors & destructors

template<typename TKey, typename TData>
TList<TKey, TData>::TList()
{
	p_first = nullptr;
	p_current = nullptr;
	p_previous = nullptr;
	p_next = nullptr;
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& _list)
{
	p_previous = nullptr;
	p_next = nullptr;
	p_current = nullptr;
	if (_list.p_first == nullptr)
		p_first = nullptr;
	else
	{
		p_first = new TNode<TKey, TData>(*(_list.p_first));
		p_current = p_first;
		TNode<TKey, TData>* iter = _list.p_first;
		iter = iter->p_next;
		while (iter != nullptr)
		{
			p_current->p_next = new TNode<TKey, TData>(*iter);
			p_current = p_current->p_next;
			iter = iter->p_next;
		}
		reset();
	}
}

template<typename TKey, typename TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* _node)
{
	p_previous = nullptr;
	p_next = nullptr;

	if (_node == nullptr)
	{
		p_first = nullptr;
		p_current = nullptr;
	}
	else
	{
		p_first = new TNode<TKey, TData>(*(_node));
		p_current = p_first;
		TNode<TKey, TData>* iter = _node->p_next;
		while (iter != nullptr)
		{
			p_current->p_next = new TNode<TKey, TData>(*iter);
			go_next();
			iter = iter->p_next;
		}
		reset();
	}
}

template <typename TKey, typename TData>
TList<TKey, TData>::~TList()
{
	TNode<TKey, TData>* tmp = p_first;
	TNode<TKey, TData>* next;
	while (tmp != nullptr)
	{
		next = tmp->p_next;
		delete tmp;
		tmp = next;
	}
}

// inserting methods

template<typename TKey, typename TData>
void TList<TKey, TData>::insert_to_start(TKey _key, TData* _data)
{
	if (is_empty())
	{
		p_first = new TNode<TKey, TData>(_key, _data);
		p_current = p_first;
		return;
	};
	TNode<TKey, TData>* p_new_first = new TNode<TKey, TData>(_key, _data, p_first);
	if (p_current == p_first)
			p_previous = p_new_first;
	p_first = p_new_first;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insert_to_end(TKey _key, TData* _data)
{
	if (is_empty())
	{
		p_first = new TNode<TKey, TData>(_key, _data);
		p_current = p_first;
		return;
	}

	TNode<TKey, TData>* p_saved_prev = p_previous;
	TNode<TKey, TData>* p_saved_curr = p_current;
	TNode<TKey, TData>* p_saved_next = p_next;

	while (!is_ended())
		go_next();
	p_current = new TNode<TKey, TData>(_key, _data);
	if (p_previous)
		p_previous->p_next = p_current;
	// restore old navigator
	if (p_previous == p_saved_curr)
	{
		p_next = p_current;
	}
	else
	{
		p_next = p_saved_next;
	}
	p_current = p_saved_curr;
	p_previous = p_saved_prev;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insert_before(TKey key_where, TKey _key, TData* _data)
{
	if (is_empty())
		throw "error: list is empty";
	if (key_where == p_first->key)
		insert_to_start(_key, _data);
	else
	{
		TNode<TKey, TData>* p_saved_prev = p_previous;
		TNode<TKey, TData>* p_saved_curr = p_current;
		TNode<TKey, TData>* p_saved_next = p_next;
		reset();
		TNode<TKey, TData>* p_to_insert_before = find_key(key_where);
		if (!p_to_insert_before)
			throw "error: element to insert before not found";
		
		while (p_current != p_to_insert_before)
			go_next();
		TNode<TKey, TData>* p_new_node = new TNode<TKey, TData>(_key, _data, p_current);
		p_previous->p_next = p_new_node;
		// inserts near navigator
		if (p_to_insert_before == p_saved_curr)
			p_previous = p_new_node; // change
		else
			p_previous = p_saved_prev; // restore navigator

		if (p_to_insert_before == p_saved_next)
			p_next = p_new_node; // change
		else
			p_next = p_saved_next; // restore navigator
		// restore old current element
		p_current = p_saved_curr;
	}
}

template<typename TKey, typename TData>
void TList<TKey, TData>::insert_after(TKey key_where, TKey _key, TData* _data)
{
	if (is_empty())
		throw "error: list is empty";
	TNode<TKey, TData>* p_saved_prev = p_previous;
	TNode<TKey, TData>* p_saved_curr = p_current;
	TNode<TKey, TData>* p_saved_next = p_next;
	TNode<TKey, TData>* p_to_insert_after = find_key(key_where);
	if (!p_to_insert_after)
		throw "error: element to insert after not found";
	reset();
	while (p_current->key != p_to_insert_after->key)
		go_next();
	TNode<TKey, TData>* p_new_node = new TNode<TKey, TData>(_key, _data, p_next);
	p_current->p_next = p_new_node;
	// inserts near navigator
	if (p_to_insert_after == p_saved_curr)
		p_next = p_new_node; // change
	else
		p_next = p_saved_next; // restore navigator

	if (p_to_insert_after == p_saved_prev)
		p_previous = p_new_node; // change
	else
		p_previous = p_saved_prev; // restore navigator
	// restore old current element
	p_current = p_saved_curr;
	return;
}

// searching & deleting

template<typename TKey, typename TData>
TNode<TKey, TData>* TList<TKey, TData>::find_key(const TKey _key)
{
	if (is_empty())
		throw "error: list is empty";
	TNode<TKey, TData>* p_saved_prev = p_previous;
	TNode<TKey, TData>* p_saved_curr = p_current;
	TNode<TKey, TData>* p_saved_next = p_next;
	reset();
	TNode<TKey, TData>* p_found = nullptr;
	while (!is_ended())
	{
		if (p_current->key == _key)
		{
			p_found = p_current;
			p_previous = p_saved_prev;
			p_current = p_saved_curr;
			p_next = p_saved_next;
			return p_found;
		}
		else
			go_next();
	}
	p_previous = p_saved_prev;
	p_current = p_saved_curr;
	p_next = p_saved_next;
	return nullptr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove_head()
{
	if (p_first == p_current)
	{
		p_current = p_next;
		if (p_next)
			p_next = p_next->p_next;
		else
			p_next = nullptr;
		delete p_first;
		p_first = p_current;
		return;
	}
	if (p_first == p_previous)
	{
		p_previous = nullptr;
		delete p_first;
		p_first = p_current;
		return;
	}
	delete p_first;
	return;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove_key(TKey _key)
{
	// find
	if (is_empty())
		throw "error: list is empty";
	if (p_first->key == _key)
	{
		remove_head();
		return;
	}
	TNode<TKey, TData>* p_saved_prev = p_previous;
	TNode<TKey, TData>* p_saved_curr = p_current;
	TNode<TKey, TData>* p_saved_next = p_next;
	reset();
	TNode<TKey, TData>* p_victim = find_key(_key);
	if (!p_victim)
		throw "error: element to delete not found";
	
	while (p_current != p_victim)
		go_next();

	// deleting around the old navigator
	p_previous->p_next = p_next;
	if ((p_victim == p_saved_curr) || (p_victim == p_saved_prev))
	{
		p_current = p_next;
		p_next = p_current->p_next;
		delete p_victim;
		return;
	}
	if (p_victim == p_saved_next)
	{
		p_current = p_previous;
		p_previous = p_saved_prev;
		p_next = p_current->p_next;
		delete p_victim;
		return;
	}
	p_next = p_saved_next;
	p_current = p_saved_curr;
	p_previous = p_saved_prev;
	delete p_victim;
	return;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::remove_current()
{
	remove_key(p_current->key);
}

// position & borders

template<typename TKey, typename TData>
void TList<TKey, TData>::go_next()
{
	if (is_ended())
		throw "error: end of list reached";
	p_previous = p_current;
	p_current = p_next;
	if (p_next)
		p_next = p_next->p_next;
	else
		p_next = nullptr;
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::is_ended() const
{
	return p_current == nullptr;
}

template<typename TKey, typename TData>
bool TList<TKey, TData>::is_empty() const
{
	return p_first == nullptr;
}

template<typename TKey, typename TData>
void TList<TKey, TData>::reset()
{
	p_previous = nullptr;
	p_current = p_first;
	if (p_first != nullptr)
		p_next = p_current->p_next;
	else
		p_next = nullptr;
}

template<typename TKey, typename TData>
TKey TList<TKey, TData>::get_first_key() const
{
	if (is_empty())
		throw "error: no first key, list is empty";
	return p_first->key;
}

template<typename TKey, typename TData>
TKey TList<TKey, TData>::get_current_key() const
{
	if (is_empty())
		throw "error: no current key, list is empty";
	return p_current->key;
}