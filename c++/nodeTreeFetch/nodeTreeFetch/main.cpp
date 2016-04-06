#include <iostream>
#include <random>
#include <cassert>

using namespace std;

class Node {
public:
    explicit Node(const string& name) : _name(name) {}

    void addChild(Node* node) {
        _childs.push_back(node);
    }
    
    void fetch(const function<void(Node*)> proc) {
        proc(this);
        for (auto child : _childs) {
            child->fetch(proc);
        }
    }
    
    const string& getName() const {
        return _name;
    }
    
private:
    string _name;
    vector<Node*> _childs;
};

int randNumber(int maxValue) {
    assert(maxValue != 0);
    return (rand() % maxValue) + 1;
}

//  テスト用に適当なツリー構造のノードを生成。
Node* createTestTreeNodes() {
    auto parentNode = new Node("parentNode");

    auto imax = randNumber(10);
    for( int i = 0 ; i < imax ; ++i ){
        auto jmax = randNumber(10);
        auto childNode = new Node("|_ childNode:" + to_string(i));
        for( int j = 0 ; j < jmax ; ++j ){
            auto kmax = randNumber(10);
            auto grandChildNode = new Node("|  |_ grandchildNode:" + to_string(j));
            for( int k = 0 ; k < kmax ; ++k ){
                grandChildNode->addChild(new Node("|  |  |_ great-grandchild:" + to_string(k)));
            }
            childNode->addChild(grandChildNode);
        }
        parentNode->addChild(childNode);
    }
    
    return parentNode;
}

int main(int argc, const char * argv[]) {
    srand(static_cast<uint32_t>(time(nullptr)));

    auto parentNode = createTestTreeNodes();
    parentNode->fetch([](Node* n) {
        cout << n->getName() << endl;
    });
    
    return 0;
}