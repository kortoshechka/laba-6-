#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <locale>
#include <numeric> 

// ========== Task 1: ќднонаправленный список ==========
class SinglyLinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    void add(int value) {
        Node* newNode = new Node(value);
        if (!head || head->data > value) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data < value) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    void remove(int value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        while (current->next && current->next->data != value) {
            current = current->next;
        }
        if (current->next) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    }

    void merge(const SinglyLinkedList& other) {
        Node* current = other.head;
        while (current) {
            add(current->data);
            current = current->next;
        }
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ========== Task 2: ƒвунаправленный список ==========
class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void add(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }

    void remove(int value) {
        Node* current = head;
        while (current && current->data != value) {
            current = current->next;
        }
        if (!current) return;
        if (current == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        }
        else if (current == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }
        delete current;
    }

    int countEqualNeighbors() const {
        if (!head || !head->next) return 0;
        int count = 0;
        Node* current = head->next;
        while (current && current->next) {
            if (current->prev->data == current->next->data) {
                ++count;
            }
            current = current->next;
        }
        return count;
    }

    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// ========== Task 3: ”никальные элементы ==========
class UniqueList {
private:
    std::set<std::string> elements;

public:
    void add(const std::string& value) {
        elements.insert(value);
    }

    void remove(const std::string& value) {
        elements.erase(value);
    }

    UniqueList Union(const UniqueList& other) const {
        UniqueList result;
        result.elements = elements;
        result.elements.insert(other.elements.begin(), other.elements.end());
        return result;
    }

    UniqueList Intersect(const UniqueList& other) const {
        UniqueList result;
        for (const auto& elem : elements) {
            if (other.elements.count(elem)) {
                result.add(elem);
            }
        }
        return result;
    }

    UniqueList Except(const UniqueList& other) const {
        UniqueList result;
        for (const auto& elem : elements) {
            if (!other.elements.count(elem)) {
                result.add(elem);
            }
        }
        return result;
    }

    bool Contains(const std::string& value) const {
        return elements.count(value);
    }

    static UniqueList OrderedByAll(const std::vector<UniqueList>& allOrders) {
        if (allOrders.empty()) return UniqueList();

        UniqueList result = allOrders[0];
        for (size_t i = 1; i < allOrders.size(); ++i) {
            result = result.Intersect(allOrders[i]);
        }
        return result;
    }

    void print() const {
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
};

// ========== Task 4: —огласные буквы в одном слове ==========
class ConsonantAnalyzer {
private:
    static bool isConsonant(char c) {
        static const std::string vowels = "аеЄиоуыэю€ј≈®»ќ”џЁёя";
        return std::isalpha(c, std::locale("")) && vowels.find(c) == std::string::npos;
    }

public:
    static std::set<char> findUniqueConsonants(const std::string& text) {
        std::map<char, int> consonantCount;
        std::istringstream stream(text);
        std::string word;

        while (stream >> word) {
            std::set<char> wordConsonants;
            for (char c : word) {
                if (isConsonant(c)) {
                    wordConsonants.insert(c);
                }
            }
            for (char c : wordConsonants) {
                consonantCount[c]++;
            }
        }

        std::set<char> result;
        for (const auto& pair : consonantCount) {
            char c = pair.first;
            int count = pair.second;
            if (count == 1) {
                result.insert(c);
            }
        }
        return result;
    }
};
class AthleteResults {
private:
    struct Athlete {
        std::string surname;
        std::string name;
        int totalScore;

        bool operator<(const Athlete& other) const {
            return totalScore > other.totalScore;
        }
    };

    std::vector<Athlete> athletes;

public:
    void add(const std::string& surname, const std::string& name, const std::vector<int>& scores) {
        int total = std::accumulate(scores.begin(), scores.end(), 0); // std::accumulate now available
        athletes.push_back({ surname, name, total });
    }

    void printTopThree() const {
        std::vector<Athlete> sortedAthletes = athletes;
        std::sort(sortedAthletes.begin(), sortedAthletes.end());

        int rank = 0;
        for (const auto& athlete : sortedAthletes) {
            if (rank >= 3) break;
            std::cout << athlete.surname << " " << athlete.name << " " << athlete.totalScore << std::endl;
            rank++;
        }
    }
};


// ========== Main Function for Testing ==========
int main() {
    setlocale(LC_ALL, "Russian");
    SinglyLinkedList list1;
    SinglyLinkedList list2;

    list1.add(1);
    list1.add(3);
    list1.add(5);

    list2.add(2);
    list2.add(4);
    list2.add(6);

    std::cout << "List 1: ";
    list1.print();

    std::cout << "List 2: ";
    list2.print();

    list1.merge(list2);
    std::cout << "Merged List: ";
    list1.print();

    // Testing DoublyLinkedList
    DoublyLinkedList dlist;
    dlist.add(1);
    dlist.add(2);
    dlist.add(2);
    dlist.add(1);

    std::cout << "Doubly Linked List: ";
    dlist.print();
    std::cout << "Count of nodes with equal neighbors: " << dlist.countEqualNeighbors() << std::endl;

    // Testing UniqueList
    UniqueList dishes;
    dishes.add("Pizza");
    dishes.add("Pasta");
    dishes.add("Burger");
    dishes.add("Burgernyaaaaaaaa");

    UniqueList orders1;
    orders1.add("Pizza");
    orders1.add("Burgers");

    UniqueList orders2;
    orders2.add("Pizza");
    orders2.add("Pasta");

    UniqueList orders3;
    orders3.add("Pizza");

    std::vector<UniqueList> allOrders = { orders1, orders2, orders3 };

    std::cout << "All dishes: ";
    dishes.print();
    std::cout << "Ordered dishes by some: ";
    UniqueList common = dishes.Intersect(orders1.Union(orders2).Union(orders3));
    common.print();

    UniqueList notOrdered = dishes.Except(orders1.Union(orders2).Union(orders3));
    std::cout << "Dishes not ordered: ";
    notOrdered.print();

    UniqueList dishesOrderedByAll = UniqueList::OrderedByAll(allOrders);
    std::cout << "Dishes ordered by all visitors: ";
    dishesOrderedByAll.print();

    // Testing ConsonantAnalyzer
    std::string text = "ѕривет мир привет всем";
    std::set<char> uniqueConsonants = ConsonantAnalyzer::findUniqueConsonants(text);
    std::cout << "Unique consonants in one word: ";
    for (char c : uniqueConsonants) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    AthleteResults results;

    results.add("Ivanov", "Ivan", { 10, 20, 30 });
    results.add("Petrov", "Petr", { 15, 25, 35 });
    results.add("Sidorov", "Alex", { 10, 10, 10 });
    results.add("Smirnov", "Dmitry", { 40, 50, 60 });

    std::cout << "Top 3 Athletes:" << std::endl;
    results.printTopThree();

    return 0;
}