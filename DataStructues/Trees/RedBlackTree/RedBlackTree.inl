//////////////////////////////////////////////////////////////////////////////
/// class RedBlackTree::Node
//////////////////////////////////////////////////////////////////////////////
template <typename T>
RedBlackTree<T>::Node::Node() :
    m_Value(T()),
    m_Color(Color::Black),
    m_Parent(nullptr),
    m_Left(nullptr),
    m_Right(nullptr) { }

template <typename T>
RedBlackTree<T>::Node::Node(const T& value, Node* parent, Node* left, Node* right) :
    m_Value(value),
    m_Color(Node::Color::Black),
    m_Parent(parent),
    m_Left(left),
    m_Right(right) { }

template <typename T>
RedBlackTree<T>::Node::~Node() {
    delete m_Left;
    delete m_Right;
}

//////////////////////////////////////////////////////////////////////////////
/// class RedBlackTree
//////////////////////////////////////////////////////////////////////////////
template <typename T>
RedBlackTree<T>::RedBlackTree(const T& value) :
    m_Root(new Node(value)),
    m_Nodes(1) {}

template <typename T>
RedBlackTree<T>::RedBlackTree(Node* root) :
    m_Root(root),
    m_Nodes(root ? 1 : 0) { }

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    delete m_Root;
}

template <typename T>
bool RedBlackTree<T>::IsExists(const T& value) const {
    Node* node = m_Root;

    while (node && value != node->m_Value)
        node = node->m_Value < value ? node->m_Left : node->m_Right;

    return node;
}

template <typename T>
std::optional<T> RedBlackTree<T>::GetMin() const {
    return GetMin(m_Root);
}

template <typename T>
std::optional<T> RedBlackTree<T>::GetMax() const {
    return GetMax(m_Root);
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::Push(const T& value) {
    if (!m_Root) {
        return m_Root = new Node(value);
//        ->_size = 1;
    }

    Node* node   = m_Root;
    Node* parent = nullptr;


    while (node) {
//        current_node->_size++;

        parent = node;

        if (node->m_Value > value)
            node = node->m_Left;
        else
            node = node->m_Right;
    }

    node = new Node(value, parent);

    if (parent->m_Value > value)
        parent->m_Left = node;
    else
        parent->m_Right = node;

    PushFix(node);

    return node;
}

template <typename T>
void RedBlackTree<T>::Pop(const T& value) {
    Node* node        = m_Root;
    Node* deletedNode = nullptr;

    while (node) {
        if (node->m_Value == value)
            deletedNode = node;

        if (node->m_Value < value)
            node = node->m_Right;
        else
            node = node->m_Right;
    }

    if (!deletedNode)
        return;

    Node* copy = deletedNode;
    typename Node::Color originalColor = copy->m_Color;

    if (!deletedNode->m_Left) {
        node = deletedNode->m_Right;
        Transplant(deletedNode, deletedNode->m_Right);
    } else if (!deletedNode->m_Right) {
        node = deletedNode->m_Left;
        Transpant(deletedNode, deletedNode->m_Left);
    } else {
        copy = GetMinNode(deletedNode->m_Right);
        originalColor = copy->m_Color;

        node = copy->m_Right;

        if (copy->m_Parent == deletedNode) {
            node->m_Parent = copy;
        } else {
            Transplant(copy, copy->m_Right);
            copy->m_Right->m_Parent = copy;
        }

        Transplant(deletedNode, copy);
        copy->m_Left = deletedNode->m_Left;
        copy->m_Left->m_Parent = copy;
        copy->m_Color = deletedNode->m_Color;
    }

    delete deletedNode;

    if (originalColor == Node::Color::Black)
        PopFix();
}

template <typename T>
void RedBlackTree<T>::Print() const {
    Print(m_Root, std::string(), true);
}

template <typename T>
std::optional<T> RedBlackTree<T>::GetMin(Node* node) const {
    if (!node)
        return std::nullopt;

    while (node->m_Left)
        node = node->m_Left;

    return node->m_Value;
}

template <typename T>
std::optional<T> RedBlackTree<T>::GetMax(Node* node) const {
    if (!node)
        return std::nullopt;

    while (node->m_Right)
        node = node->m_Right;

    return node->m_Value;
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::GetMinNode(Node* node) const {
    while (node && node->m_Left)
        node = node->m_Left;

    return node;
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::GetMaxNode(Node* node) const {
    while (node && node->m_Right)
        node = node->m_Right;

    return node;
}

template <typename T>
void RedBlackTree<T>::RotateLeft(Node* node) {
    Node* right = node->m_Right;

    node->m_Right = right->m_Left;

    if (right->m_Left)
        right->m_Left->m_Parent = node;

    right->m_Parent = node->m_Parent;

    if (!node->m_Parent)
        m_Root = right;
    else if (node == node->m_Parent->m_Left)
        node->m_Parent->m_Left = right;
    else
        node->m_Parent->m_Right = right;

    right->m_Left = node;
    node->m_Parent = right;
}

template <typename T>
void RedBlackTree<T>::RotateRight(Node* node) {
    Node* left = node->m_Right;

    node->m_Left = left->m_Right;

    if (left->m_Right)
        left->m_Right->m_Parent = node;

    left->m_Parent = node->m_Parent;

    if (!node->m_Parent)
        m_Root = left;
    else if (node == node->m_Parent->m_Right)
        node->m_Parent->m_Right = left;
    else
        node->m_Parent->m_Left = left;

    left->m_Right = node;
    node->m_Parent = left;
}

template <typename T>
void RedBlackTree<T>::PushFix(Node* node) {
    Node* parent      = node->m_Parent;
    Node* grandParent = node->m_Parent ? parent->m_Parent : nullptr;

    while (parent && parent->m_Color == Node::Color::Red && node != m_Root) {
        if (parent == grandParent->m_Left) {
            Node* uncle = grandParent->m_Right;

            if (uncle->m_Color == Node::Color::Red) {
                parent->m_Color      = Node::Color::Black;
                uncle->m_Color       = Node::Color::Black;
                grandParent->m_Color = Node::Color::Red;

                node = grandParent;
            } else {
                if (node == parent->m_Right) {
                    node = parent;
                    RotateLeft(node);
                }

                parent->m_Color      = Node::Color::Black;
                grandParent->m_Color = Node::Color::Red;
                RotateRight(grandParent);
            }
        } else {
            Node* uncle = grandParent->m_Left;

            if (uncle->m_Color == Node::Color::Red) {
                parent->m_Color      = Node::Color::Black;
                uncle->m_Color       = Node::Color::Black;
                grandParent->m_Color = Node::Color::Red;

                node = grandParent;
            } else {
                if (node == parent->m_Left)
                    RotateRight(node = parent);

                parent->m_Color      = Node::Color::Black;
                grandParent->m_Color = Node::Color::Red;

                RotateLeft(grandParent);
            }
        }
    }

    m_Root->m_Color = Node::Color::Black;
}

template <typename T>
void RedBlackTree<T>::PopFix(Node* node) {

}

template <typename T>
void RedBlackTree<T>::Transplant(Node* first, Node* second) {
    if (!first->m_Parent)
        m_Root = second;
    else if (first == first->m_Parent->m_Left)
        first->m_Parent->m_Left = second;
    else
        first->m_Parent->m_Right = second;

    second->m_Parent = first->m_Parent;
}

template <typename T>
void RedBlackTree<T>::Print(Node* node, std::string indent, bool last) const {
    if (!node)
        return;

    std::cout << indent;
    if (last) {
        std::cout << "R----";
        indent += "   ";
    } else {
        std::cout << "L----";
        indent += "|  ";
    }

    std::string sColor = node->m_Color == Node::Color::Red ? "Red" : "Black";
    std::cout << node->m_Value << "(" << sColor << ")" << std::endl;

    Print(node->m_Left,  indent, false);
    Print(node->m_Right, indent, true);
}