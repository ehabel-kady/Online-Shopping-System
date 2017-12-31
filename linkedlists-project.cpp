#include <iostream>
#include <string>

using namespace std;

class ItemNode {
public:
	string brand;
	string model;
	double price;
  ItemNode *next; // pointer to next node

  ItemNode(string br, string md, double pr, ItemNode *ptr = 0) {
		brand = br;
		model = md;
		price = pr;
    next = ptr;
  }
};

class ItemList {
private:
  ItemNode *head, *tail;

public:
  ItemList() {
		head = tail = 0;
	}

  int isEmpty() {
		return head == 0;
	}

  void addToHead(string br, string md, double pr) {
    head = new ItemNode(br, md, pr, head);
    if (tail == 0)
      tail = head;
  }

  void addToTail(string br, string md, double pr) {
    if (tail == 0)
      head = tail = new ItemNode(br, md, pr);
    else {
      tail->next = new ItemNode(br, md, pr);
      tail = tail->next;
    }
  }

  void deleteFromHead() {
    ItemNode *tmp = head;
    if (head == tail)
      head = tail = 0;
    else
      head = head->next;
    delete tmp;
  }

  void deleteFromTail() {
    if (head == tail) {
      delete head;
      head = tail = 0;
    } else {
      ItemNode *tmp;
      for (tmp = head; tmp->next != tail; tmp = tmp->next)
        ;

      delete tail;
      tail = tmp;
      tail->next = 0;
    }
  }

  void deleteNode(string br, string md, double pr) {
    if (head != 0) {
      if (head == tail && ( br == head->brand && md == head->model && pr == head->price ) ) {
        delete head;
        head = tail = 0;
      } else if (br == head->brand && md == head->model && pr == head->price) {
        // deleteFromHead();
        ItemNode *tmp = head;
        head = head->next;
        delete tmp;
      } else {
        ItemNode *p, *tmp;
        for (p = head, tmp = head->next; (tmp != 0 && tmp->brand != br && tmp->model != md && tmp->price != pr);
             p = p->next, tmp = tmp->next)
          ;

        if (tmp != 0) {
          p->next = tmp->next;
          if (tmp == tail)
            tail = p;
          delete tmp;
        }
      }
    }
  }

  bool isInList(string br, string md, double pr) const { // can't change any member state
    ItemNode *tmp;
    for (tmp = head; tmp != 0 && tmp->brand != br && tmp->model != md && tmp->price != pr; tmp = tmp->next)
      ;
    return tmp != 0;
  }

  void printAll() const {
    ItemNode *p;
    for (p = head; p != 0; p = p->next) {
      cout << p->brand << "," << p->model << "," << p->price << endl;
    }
  }

  ~ItemList() {
    for (ItemNode *p; !isEmpty();) {
      p = head->next;
      delete head;
      head = p;
    }
  }
};

int main() {
  ItemList *headPhones = new ItemList();

  headPhones->addToTail("ilov","3x01",120.99);
	headPhones->printAll();

  return 0;
}