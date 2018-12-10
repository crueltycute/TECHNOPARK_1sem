#include <iostream>
#include <stack>
#include <queue>

template <class T>
struct Node {
  T data;
  size_t priority;

  Node* left;
  Node* right;

  Node(T data) : data(data) {
      left = right = nullptr;
    }

  Node(T data, size_t priority) : data(data), priority(priority) {
    left = right = nullptr;
  }
};

template <class T>
class Tree {
 public:
  Tree() = delete;
  Tree(size_t size);

  Tree& operator=(const Tree& other) = delete;
  Tree& operator=(Tree&& other) = delete;
  Tree(const Tree& other) = delete;
  Tree(Tree&& other) = delete;

  ~Tree();

  Node<T>* getRoot();

  template <class Function>
  bool inOrder(Function function);

  void add(T data);
 private:
  size_t size_;
  Node<T>* root_;

  bool empty();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Tree<T>::Tree(size_t size) : size_(size), root_(nullptr) {}

template <class T>
Tree<T>::~Tree() {
  inOrder([](const Node<T>* node) {
    delete node;
  });
}

template <class T>
Node<T>* Tree<T>::getRoot() {
  return root_;
}

template <class T>
bool Tree<T>::empty() {
  return root_ == nullptr;
}

template <class T>
template <class Function>
bool Tree<T>::inOrder(Function function) {
  if (empty())
    return false;

  std::stack<Node<T>*> nodes;
  Node<T>* current = root_;
  nodes.push(current);

  size_t i = 0;

  while ((!nodes.empty() || current) && (i < size_)) {
    if (current) {
      nodes.push(current);
      current = current->left;
    } else {
      Node<T>* node = nodes.top();
      nodes.pop();
      function(node);
      current = node->right;
      i++;
    }
  }
  return true;
}

template <class T>
void Tree<T>::add(T data) {
  if (empty()) {
    root_ = new Node<T>(data);
    // return;
  } else {
    Node<T>* current = root_;
    while (true) {
      if (current->data > data) {
        if (!current->left) {
          current->left = new Node<T>(data);
          break;
        } else {
          current = current->left;
        }
      } else {
        if (!current->right) {
          current->right = new Node<T>(data);
          break;
        } else {
          current = current->right;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Treap {
 public:
  Treap() = delete;
  Treap(size_t size);

  Treap& operator=(const Treap& other) = delete;
  Treap& operator=(Treap&& other) = delete;
  Treap(const Treap& other) = delete;
  Treap(Treap&& other) = delete;

  ~Treap();

  template <class Function>
  bool inOrder(Function function);

  void add(T data, size_t newPriority);

  Node<T>* getRoot();
 private:
  size_t size_;
  Node<T>* root_;

  bool empty();

  void split(Node<T>* currentNode, T data, Node<T>*& left, Node<T>*& right);
};

template <class T>
Treap<T>::Treap(size_t size) : size_(size), root_(nullptr) {}

template <class T>
Treap<T>::~Treap() {
  inOrder([](const Node<T>* node) {
    delete[] node;
  });
}

template <class T>
Node<T>* Treap<T>::getRoot() {
  return root_;
}

template <class T>
bool Treap<T>::empty() {
  return root_ == nullptr;
}

template <class T>
template <class Function>
bool Treap<T>::inOrder(Function function) {
  if (empty())
    return false;

  std::stack<Node<T>*> nodes;
  Node<T>* current = root_;
  nodes.push(current);

  size_t i = 0;

  while ((!nodes.empty() || current) && (i < size_)) {
    if (current) {
      nodes.push(current);
      current = current->left;
    } else {
      Node<T>* node = nodes.top();
      nodes.pop();
      function(node);
      current = node->right;
      i++;
    }
  }
}

template <class T>
void Treap<T>::split(Node<T>* currentNode, T data,
                     Node<T>*& left, Node<T>*& right) {
  if (!currentNode) {
    left = right = nullptr;
  } else if (currentNode->data > data) {
    split(currentNode->left, data, left, currentNode->left);
    right = currentNode;
  } else {
    split(currentNode->right, data, currentNode->right, right);
    left = currentNode;
  }
}

template <class T>
void Treap<T>::add(T data, size_t newPriority) {
  if (empty()) {
    root_ = new Node<T>(data, newPriority);
    root_->left = root_->right = nullptr;
  } else {
    Node<T>* tempNode = new Node<T>(data, newPriority);
    Node<T>* previousNode = root_, *currentNode = root_;

    while (currentNode && currentNode->priority > newPriority) {
      previousNode = currentNode;
      currentNode = (currentNode->data > data) ? currentNode->left : currentNode->right;
    }

    split(currentNode, data, tempNode->left, tempNode->right);

    if (currentNode == root_) {
      root_ = tempNode;
    } else {
      (previousNode->data > data) ? (previousNode->left = tempNode) : (previousNode->right = tempNode);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
int getMaxWidth(Node<T>* root) {
  if (!root)
    return 0;

  int maxWidth = 0;

  std::queue<Node<T>*> nodesOnLevel;
  nodesOnLevel.push(root);

  while (!nodesOnLevel.empty()) {
    if (nodesOnLevel.size() > maxWidth) {
      maxWidth = nodesOnLevel.size();
    }

    size_t currentWidth = nodesOnLevel.size();
    for (int i = 0; i < currentWidth; ++i) {
      Node<T>* currentNode = nodesOnLevel.front();
      nodesOnLevel.pop();

      if (currentNode->left)
        nodesOnLevel.push(currentNode->left);

      if (currentNode->right)
        nodesOnLevel.push(currentNode->right);
    }
  }
  return maxWidth;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t N;
  std::cin >> N;

  Tree<int> tree(N);
  Treap<int> treap(N);

  int tempElement, tempPriority;

  for (int i = 0; i < N; ++i) {
    std::cin >> tempElement >> tempPriority;
    tree.add(tempElement);
    treap.add(tempElement, tempPriority);
  }

  std::cout << getMaxWidth(treap.getRoot()) - getMaxWidth(tree.getRoot()) << std::endl;
  return 0;
}