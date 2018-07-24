#ifndef LIST_H
#define LIST_H

template <class T>
class list
{
    class ListItem {
        friend class list;
        ListItem(T _value) : value(_value) {}
        ListItem() {}
        T value;
        ListItem * next;
        ListItem * prev;
    };

    ListItem * head;

 public:
    class Iterator {
        ListItem * i;
        friend class list;

    public:
        Iterator(ListItem * _i) : i(_i) {}
        Iterator() {}

        Iterator & operator ++ () {
            i = i->next;
            return *this;
        }

        Iterator operator ++ (int) {
            Iterator ret = i;
            i = i->next;
            return ret;
        }

        Iterator & operator -- () {
            i = i->prev;
            return *this;
        }

        Iterator operator -- (int) {
            Iterator ret = i;
            i = i->prev;
            return ret;
        }

        bool operator != (Iterator other) {
            if (i != other.i)
                return true;
            else
                return false;
        }

        T & operator * () {
            return i->value;
        }

        void operator = (Iterator other)
        {
            i = other.i;
        }
    };

    list() {
        head = new ListItem();
        head->next = head;
        head->prev = head;
    }

    ~list() {
        ListItem * current = head->next;
        while (current != head) {
            current = current->next;
            delete current->prev;
        }

        delete head;
    }

    Iterator insert(T new_value) {
        ListItem * new_item = new ListItem(new_value);

        new_item->prev = head->prev;
        new_item->next = head;

        head->prev->next = new_item;
        head->prev = new_item;

        return Iterator(new_item);
    }

    void remove(Iterator i)
    {
        i.i->prev->next = i.i->next;
        i.i->next->prev = i.i->prev;

        delete i.i;
    }

    void edit(Iterator i, T newValue)
    {
        i.i->value = newValue;
    }

    Iterator begin() const{
        return Iterator(head->next);
    }

    Iterator end() const{
        return Iterator(head);
    }
};

#endif // LIST_H
