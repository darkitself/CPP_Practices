#include <iostream>
#include <ctime>
#include "SLList.h"

using namespace std;

void printSLList(const SLList* list)
{
    while (list->hasNext())
    {
        cout << list->getData() << " -> ";
        list = list->next();
    }
    cout << list->getData() << endl;
}

void deleteDuplicates(SLList* list)
{
    SLList* node_to_compare = list;
    while (node_to_compare != nullptr && node_to_compare->hasNext())
    {
        SLList* curr_node = node_to_compare;
        while (curr_node->hasNext())
        {
            if (curr_node->next()->getData() == node_to_compare->getData())
                curr_node->removeNext();
            else
                curr_node = curr_node->next();
        }
        node_to_compare = node_to_compare->next();
    }
}

SLList* findByIndex(const SLList* list, int k)
{
    const SLList* t = list;
    for (int i = 0; i < k && list != nullptr; i++)
        list = list->next();
    if (list == nullptr)
        return nullptr;
    while (list->next() != nullptr)
    {
        t = t->next();
        list = list->next();
    }
    return (SLList*)t;
}

int main()
{
    srand(time(nullptr));
    SLList* list = SLList::beginList(rand() % 6);
    for (int i = 0; i < 9; i++)
        list->addElement(rand() % 6);
    cout << "Source list is: " << endl;
    printSLList(list);
    cout << "6 element from the end is: " << findByIndex(list, 6)->getData() << endl;
    deleteDuplicates(list);
    cout << "List without duplicates is: " << endl;
    printSLList(list);
    delete list;
    return 0;
}
