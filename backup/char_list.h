#ifndef CHAR_LIST_H_INCLUDED
#define CHAR_LIST_H_INCLUDED

#include <cstring>
class char_list
{
    class ListItem {
        friend class char_list;
        ListItem(char * _value) {
            value = new char [strlen(_value)+1];
            strcpy(value, _value);
        }

        ~ListItem() {
            if (value)
                delete [] value;
            value = 0;
        }

        ListItem() {
            value = 0;
        }
        char * value;
        ListItem * next;
        ListItem * prev;
    };

    ListItem * head;

 public:
    class Iterator {
        ListItem * i;
        friend class char_list;

    public:
        Iterator(ListItem * _i) : i(_i) {}
        Iterator() {}
        //Iterator() : i(head->next) {}

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

        char* operator * () {
            return i->value;
        }

        void operator = (Iterator other)
        {
            i = other.i;
        }
    };

    char_list() {
        head = new ListItem();
        head->next = head;
        head->prev = head;
    }

    ~char_list() {
        ListItem * current = head->next;
        while (current != head) {
            current = current->next;
            delete current->prev;
        }

        delete head;
    }

    Iterator insert(char * new_value) {
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

    Iterator begin() const{
        return Iterator(head->next);
    }

    Iterator end() const{
        return Iterator(head);
    }
};

#endif // CHAR_LIST_H_INCLUDED
