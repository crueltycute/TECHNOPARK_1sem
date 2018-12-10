#include <iostream>
#include <stack>

template <class T>
class AVLTree {
 public:
  AVLTree();
  AVLTree& operator=(const AVLTree& other) = delete;
  AVLTree(const AVLTree& other) = delete;
  AVLTree& operator=(AVLTree&& other);
  AVLTree(AVLTree&& other);

  ~AVLTree();

  void add(T data);
  void remove(T data);

  template <class Function>
  bool inOrder(Function function);

  T kStatistics(size_t index);
 private:
  struct Node {
    T key;
    unsigned char height;
    Node* left;
    Node* right;

    Node(T newKey) {
      key = newKey;
      left = right = nullptr;
      height = 1;
    }
  };

  Node* root_;

  unsigned char height(Node* node);
  int balanceFactor(Node* node);
  void fixHeight(Node* node);
  Node* rotateRight(Node* node);
  Node* rotateLeft(Node* node);
  Node* balance(Node* node);
  Node* add(Node* node, const T& key);

  Node* findMin(Node* node);
  Node* removeMin(Node* node);
  Node* remove(Node* node, T key);

  size_t getSize(Node* node);
};

template <class T>
AVLTree<T>::AVLTree() : root_(nullptr) {}

template <class T>
AVLTree<T>& AVLTree<T>::operator=(AVLTree &&other) {
  root_ = std::move(other.root_);
  return *this;
}

template <class T>
AVLTree<T>::AVLTree(AVLTree&& other) {
  root_ = std::move(other.root_);
}

template <class T>
AVLTree<T>::~AVLTree() {
  inOrder([](const Node* node) {
    delete node;
  });
}

template <class T>
unsigned char AVLTree<T>::height(AVLTree::Node *node) {
  return node ? node->height : (unsigned char)0;
}

template <class T>
int AVLTree<T>::balanceFactor(AVLTree::Node *node) {
  return height(node->right) - height(node->left);
}

template <class T>
void AVLTree<T>::fixHeight(AVLTree::Node *node) {
  unsigned char heightLeft = height(node->left), heightRight = height(node->right);
  node->height = ((heightLeft > heightRight) ? heightLeft : heightRight) + (unsigned char)1;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::rotateRight(AVLTree<T>::Node *node) {
  Node* rotated = node->left;
  node->left = rotated->right;
  rotated->right = node;
  fixHeight(node);
  fixHeight(rotated);
  return rotated;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::rotateLeft(Node* node) {
  Node* rotated = node->right;
  node->right = rotated->left;
  rotated->left = node;
  fixHeight(node);
  fixHeight(rotated);
  return rotated;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::balance(AVLTree<T>::Node *node) {
  fixHeight(node);
  if (balanceFactor(node) == 2) {
    if (balanceFactor(node->right) < 0)
      node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  if (balanceFactor(node) == -2) {
    if (balanceFactor(node->left) > 0)
      node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  return node;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::add(AVLTree<T>::Node *node, const T &key) {
  if (!node)
    return new Node(key);

  if (node->key > key) {
    node->left = add(node->left, key);
  } else {
    node->right = add(node->right, key);
  }
  return balance(node);
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::findMin(AVLTree<T>::Node *node) {
  return node->left ? findMin(node->left) : node;
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::removeMin(AVLTree<T>::Node *node) {
  if (!node->left)
    return node->right;

  node->left = removeMin(node->left);
  return balance(node);
}

template <class T>
typename AVLTree<T>::Node* AVLTree<T>::remove(Node* node, T key) {
  if (!node)
    return 0;

  if (node->key > key)
    node->left = remove(node->left, key);
  else if (node->key < key)
    node->right = remove(node->right, key);
  else {
    Node* currentLeft = node->left;
    Node* currentRight = node->right;
    delete node;

    if (!currentRight)
      return currentLeft;

    Node* min = findMin(currentRight);
    min->right = removeMin(currentRight);
    min->left = currentLeft;
    return balance(min);
  }
  return balance(node);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
void AVLTree<T>::add(T data) {
  root_ = add(root_, data);
}

template <class T>
void AVLTree<T>::remove(T data) {
  root_ = remove(root_, data);
}

template <class T>
size_t AVLTree<T>::getSize(AVLTree<T>::Node* node) {
  return 1 + (node->left ? getSize(node->left) : 0) + (node->right ? getSize(node->right) : 0);
}

template <class T>
template <class Function>
bool AVLTree<T>::inOrder(Function function) {
  if (!root_)
    return false;

  std::stack<Node*> nodes;
  Node* current = root_;
  nodes.push(current);

  size_t i = 0;

  size_t size = getSize(root_);

  while ((!nodes.empty() || current) && i < size) {
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
T AVLTree<T>::kStatistics(size_t index) {
  if (root_) {
    size_t height = 0;
    Node* currentNode = root_;

    while (currentNode) {
      size_t currentIndex = height + (currentNode->left ? getSize(currentNode->left) : 0);

      if (currentIndex == index)
        return currentNode->key;

      if (currentNode->left && currentIndex > index) {
        currentNode = currentNode->left;
      } else {
        height = currentIndex + 1;
        currentNode = currentNode->right;
      }
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  size_t N;
  std::cin >> N;

  AVLTree<int> tree;
  int tempData, tempIndex;

  for (int i = 0; i < N; ++i) {
    std::cin >> tempData >> tempIndex;
    if (tempData > 0)
      tree.add(tempData);

    if (tempData < 0)
      tree.remove(tempData * (-1));

    std::cout << tree.kStatistics(tempIndex) << ' ';
  }
  return 0;
}