#include <iostream>
#include <stack>

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

  struct Node {
    T data;

    Node* left;
    Node* right;

    Node(T data) : data(data) {
      left = right = nullptr;
    }
  };

  template <class Function>
  bool inOrder(Function function);

  void add(T data);

  void print();
 private:
  size_t size_;
  Node* root_;

  bool empty();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
Tree<T>::Tree(size_t size) : size_(size), root_(nullptr) {}

template <class T>
Tree<T>::~Tree() {
  inOrder([](const Node* node) {
    delete node;
  });
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

  std::stack<Node*> nodes;
  Node* current = root_;
  nodes.push(current);

  size_t i = 0;

  while ((!nodes.empty() || current) && (i < size_)) {
    if (current) {
      nodes.push(current);
      current = current->left;
    } else {
      Node* node = nodes.top();
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
    root_ = new Node(data);
    // return;
  } else {
    Node* current = root_;
    while (true) {
      if (current->data > data) {
        if (!current->left) {
          current->left = new Node(data);
          break;
        } else {
          current = current->left;
        }
      } else {
        if (!current->right) {
          current->right = new Node(data);
          break;
        } else {
          current = current->right;
        }
      }
    }
  }
}

template <class T>
void Tree<T>::print() {
  inOrder([](const Node* node) {
    std::cout << node->data << ' ';
  });
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t N;
  std::cin >> N;

  Tree<int> tree(N);

  int root;
  std::cin >> root;

  tree.add(root);

  int tempElement;
  for (int i = 0; i < N - 1; ++i) {
    std::cin >> tempElement;
    tree.add(tempElement);
  }

  tree.print();

  return 0;
}