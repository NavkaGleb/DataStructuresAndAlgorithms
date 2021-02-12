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
    m_Color(Node::Color::Red),
    m_Parent(parent),
    m_Left(left),
    m_Right(right) { }

template <typename T>
RedBlackTree<T>::Node::~Node() {
    delete m_Left;
    delete m_Right;
}

template <typename T>
void RedBlackTree<T>::Node::Print() const {
    std::cout << m_Value << " {C:";

    std::cout << (m_Color == Node::Color::Black ? "Black"                          : "Red" ) << ", L: ";
    std::cout << (m_Left                        ? std::to_string(m_Left->m_Value)  : "Null") << ", R: ";
    std::cout << (m_Right                       ? std::to_string(m_Right->m_Value) : "Null") << "}";
}

//////////////////////////////////////////////////////////////////////////////
/// class RedBlackTree
//////////////////////////////////////////////////////////////////////////////
template <typename T>
RedBlackTree<T>::RedBlackTree(const T& value) :
    m_Root(new Node(value)) { }

template <typename T>
RedBlackTree<T>::RedBlackTree(Node* root) :
    m_Root(root) { }

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
    delete m_Root;
}

template <typename T>
int RedBlackTree<T>::GetHeight() const {
    return GetHeight(m_Root);
}

template <typename T>
bool RedBlackTree<T>::IsExists(const T& value) const {
    Node* node = m_Root;

    while (node && value != node->m_Value)
        node = node->m_Value > value ? node->m_Left : node->m_Right;

    return node;
}

template <typename T>
typename RedBlackTree<T>::Node* RedBlackTree<T>::GetNode(const T& value) {
    Node* node = m_Root;

    while (node && value != node->m_Value)
        node = node->m_Value > value ? node->m_Left : node->m_Right;

    return node;
}

template <typename T>
const typename RedBlackTree<T>::Node* RedBlackTree<T>::GetNode(const T& value) const {
    Node* node = m_Root;

    while (node && value != node->m_Value)
        node = node->m_Value > value ? node->m_Left : node->m_Right;

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
T& RedBlackTree<T>::Push(const T& value) {
    if (!m_Root) {
        m_Root = new Node(value);
        m_Root->m_Color = Node::Color::Black;

        return m_Root->m_Value;
    }

    Node* node   = m_Root;
    Node* parent = nullptr;

    while (node) {
        if (node->m_Value == value)
            return node->m_Value;

        parent = node;
        node   = node->m_Value > value ? node->m_Left : node->m_Right;
    }

    ++m_Size;

    node = new Node(value, parent);

    if (parent->m_Value > value)
        parent->m_Left = node;
    else
        parent->m_Right = node;

    PushFix(node);

    return node->m_Value;
}

template <typename T>
void RedBlackTree<T>::Pop(const T& value) {
    Node* node = GetNode(value);

    if (!node)
        return;

    --m_Size;

    Node* parent = node->m_Parent;
    Node* child  = nullptr;

    if (node->m_Left && node->m_Right) {
        Node* successor = GetSuccessor(node);

        node->m_Value = successor->m_Value;
        parent        = successor->m_Parent;
        node          = successor;

        if (successor->m_Right)
            child = successor->m_Right;
    } else if (!node->m_Left && node->m_Right) {
        child = node->m_Right;
    } else if (node->m_Left && !node->m_Right) {
        child = node->m_Left;
    }

    if (parent) {
        if (parent->m_Left == node)
            parent->m_Left = child;
        else
            parent->m_Right = child;

        if (child)
            child->m_Parent = parent;
    } else {
        m_Root = child;

        if (m_Root)
            m_Root->m_Parent = nullptr;
    }

    if (node->m_Color == Node::Color::Black && child)
        PopFix(child);

    node->m_Left  = nullptr;
    node->m_Right = nullptr;

    delete node;
}

template <typename T>
void RedBlackTree<T>::Print() const {
    Print(m_Root, 1, "Root");
}

template <typename T>
int RedBlackTree<T>::GetHeight(Node* node) const {
    return node ? std::max(GetHeight(node->m_Left), GetHeight(node->m_Right)) + 1 : 0;
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
typename RedBlackTree<T>::Node* RedBlackTree<T>::GetSuccessor(Node* node) const {
    if (node->m_Right)
        return GetMinNode(node->m_Right);

    Node* successor = node->m_Parent;

    while (successor && successor->m_Right == node) {
        node      = successor;
        successor = successor->m_Parent;
    }

    return successor;
}

template <typename T>
void RedBlackTree<T>::RotateLeft(Node* node) {
    //   c      =>      s
    //  / \            / \
    // u   s    =>    c   r
    //    / \        / \
    //   l   r  =>  u   l

    Node* right     = node->m_Right;
    Node* rightLeft = right->m_Left;

    right->m_Parent   = node->m_Parent;

    if (!node->m_Parent)
        m_Root = right;
    else if (node == node->m_Parent->m_Left)
        node->m_Parent->m_Left = right;
    else
        node->m_Parent->m_Right = right;

    node->m_Parent = right;
    right->m_Left = node;
    node->m_Right = rightLeft;

    if (rightLeft)
        rightLeft->m_Parent = node;
}

template <typename T>
void RedBlackTree<T>::RotateRight(Node* node) {
    //     c    =>    u
    //    / \        / \
    //   u   s  =>  l   c
    //  / \            / \
    // l   r    =>    r   s

    Node* left      = node->m_Left;
    Node* leftRight = left->m_Right;

    left->m_Parent   = node->m_Parent;

    if (!node->m_Parent)
        m_Root = left;
    else if (node == node->m_Parent->m_Left)
        node->m_Parent->m_Left = left;
    else
        node->m_Parent->m_Right = left;

    node->m_Parent = left;
    left->m_Right  = node;
    node->m_Left   = leftRight;

    if (leftRight)
        leftRight->m_Parent = node;
}

template <typename T>
void RedBlackTree<T>::PushFix(Node* node) {
    while (node->m_Parent && node->m_Parent->m_Color == Node::Color::Red) {
        Node* parent = node->m_Parent;
        Node* uncle  = node->m_Parent->m_Parent && node->m_Parent->m_Parent->m_Left == node->m_Parent ?
                       node->m_Parent->m_Parent->m_Right :
                       node->m_Parent->m_Parent->m_Left;

        // uncle is leaf => color is black
        if (!uncle || uncle->m_Color == Node::Color::Black) {
            // if uncle is at right, parent at left.
            if (parent->m_Parent->m_Left == parent) {
                // from shape triangle to line
                if (parent->m_Left != node) {
                    RotateLeft(parent);

                    node = parent;
                    parent = node->m_Parent;
                }

                // grand parent rotation from line shape
                if (parent->m_Left == node) {
                    parent->m_Color           = Node::Color::Black;
                    parent->m_Parent->m_Color = Node::Color::Red;

                    RotateRight(parent->m_Parent);
                    // will break because parent color has changed to black.
                }
            } else {
                // from shape triangle to line
                if (parent->m_Right != node) {
                    RotateRight(parent);

                    node = parent;
                    parent = node->m_Parent;
                }

                // grand parent rotation from line shape
                if (parent->m_Right == node) {
                    parent->m_Color           = Node::Color::Black;
                    parent->m_Parent->m_Color = Node::Color::Red;

                    RotateLeft(parent->m_Parent);
                }
            }
        } else if (uncle->m_Color == Node::Color::Red) {
            parent->m_Color = Node::Color::Black;
            uncle->m_Color = Node::Color::Black;
            parent->m_Parent->m_Color = Node::Color::Red;

            node = parent->m_Parent;
        }

    }

    m_Root->m_Color = Node::Color::Black;
}

template <typename T>
void RedBlackTree<T>::PopFix(Node* node) {
    while (node != m_Root && node->m_Color == Node::Color::Black) {
        Node* parent = node->m_Parent;

        if (parent->m_Left == node) {
            Node* sibling = parent->m_Right;

            if (sibling->m_Color == Node::Color::Red) {
                sibling->m_Color = Node::Color::Black;
                parent->m_Color  = Node::Color::Red;

                RotateLeft(parent);
                sibling = parent->m_Right;
            }

            if ((!sibling->m_Left || sibling->m_Left->m_Color == Node::Color::Black) &&
                (!sibling->m_Right || sibling->m_Right->m_Color == Node::Color::Black)) {

                sibling->m_Color = Node::Color::Red;
                node             = parent;
                parent           = node->m_Parent;
            } else if (!sibling->m_Right || sibling->m_Right->m_Color == Node::Color::Black) {
                sibling->m_Color = Node::Color::Red;

                RotateRight(sibling);
                sibling = parent->m_Right;
            }

            if (parent) {
                sibling->m_Color = parent->m_Color;
                parent->m_Color  = Node::Color::Black;

                if (sibling->m_Right)
                    sibling->m_Right->m_Color = Node::Color::Black;

                RotateLeft(parent);
            }

            node = m_Root;
        } else {
            Node* sibling = parent->m_Left;

            if (sibling->m_Color == Node::Color::Red) {
                sibling->m_Color = Node::Color::Black;
                parent->m_Color  = Node::Color::Red;

                RotateRight(parent);
                sibling = parent->m_Left;
            }

            if ((!sibling->m_Left || sibling->m_Left->m_Color == Node::Color::Black) &&
                (!sibling->m_Right || sibling->m_Right->m_Color == Node::Color::Black)) {

                sibling->m_Color = Node::Color::Red;
                node             = parent;
                parent           = node->m_Parent;
            } else if (!sibling->m_Left || sibling->m_Left->m_Color == Node::Color::Black) {
                sibling->m_Color = Node::Color::Red;

                RotateLeft(sibling);
                sibling = parent->m_Left;
            }

            if (parent) {
                sibling->m_Color = parent->m_Color;
                parent->m_Color  = Node::Color::Black;

                if (sibling->m_Left)
                    sibling->m_Left->m_Color = Node::Color::Black;

                RotateRight(parent);
            }

            node = m_Root;
        }
    }

    node->m_Color = Node::Color::Black;
}

template <typename T>
void RedBlackTree<T>::Print(const Node* node, const int& level, const char* caption) const {
    if (!node) {
        std::cout << caption << ": Null" << std::endl;
        return;
    }

    std::cout << caption << ": ";
    node->Print();

    if (node->m_Left || node->m_Right) {
        std::cout << " (" << std::endl;

        for (int i = 0; i < level; i++)
            std::cout << "| ";
        Print(node->m_Left, level + 1, "Left");

        for (int i = 0; i < level; i++)
            std::cout << "| ";
        Print(node->m_Right, level + 1, "Right");

        for (int i = 0; i < level - 1; i++)
            std::cout << "| ";
        std::cout << ")";
    }

    std::cout << std::endl;
}