#pragma once

namespace Ng {

    //////////////////////////////////////////////////////////////////////////////
    /// Header
    //////////////////////////////////////////////////////////////////////////////
    template <typename T>
    class RedBlackTree {
    public:
        class Node {
        public:
            enum class Color : int { Red = 0, Black };

            Node();
            explicit Node(const T& value,
                          const Color& color = Color::Black,
                          Node* parent = nullptr,
                          Node* left = nullptr,
                          Node* right = nullptr);
            virtual ~Node();

            [[nodiscard]] inline const T& GetValue() const { return m_Value; }
            [[nodiscard]] inline const Color& GetColor() const { return m_Color; }
            [[nodiscard]] inline const Node* GetParent() const { return m_Parent; }
            [[nodiscard]] inline const Node* GetLeft() const { return m_Left; }
            [[nodiscard]] inline const Node* GetRight() const { return m_Right; }

            friend class RedBlackTree;

        private:
            T     m_Value;
            Color m_Color;
            Node* m_Parent;
            Node* m_Left;
            Node* m_Right;

        }; // class Node

        explicit RedBlackTree(const T& value);
        explicit RedBlackTree(Node* root = nullptr);
        virtual ~RedBlackTree();

        [[nodiscard]] inline Node* GetRoot() { return m_Root; }
        [[nodiscard]] inline const Node* GetRoot() const { return m_Root; }
        [[nodiscard]] inline int GetNodes() const { return m_Nodes; }

        [[nodiscard]] bool IsExists(const T& value) const;

        Node* PushNode(const T& value);
        void PopNode(const T& value);

    private:
        void RotateLeft(Node* node);
        void RotateRight(Node* node);

        Node* m_Root;
        int   m_Nodes;

    }; // class RedBlackTree

    //////////////////////////////////////////////////////////////////////////////
    /// Source
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
    RedBlackTree<T>::Node::Node(const T& value, const Color& color, Node* parent, Node* left, Node* right) :
        m_Value(value),
        m_Color(color),
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

        while (node && value != node->Value) {
            if (value < node->Value)
                node = node->Left;
            else
                node = node->Right;
        }

        return node;
    }

    template <typename T>
    typename RedBlackTree<T>::Node* RedBlackTree<T>::PushNode(const T& value) {
        Node* node = new Node(value);

        if (!m_Root)
            return m_Root = node;
    }

    template <typename T>
    void RedBlackTree<T>::PopNode(const T& value) {

    }

    template <typename T>
    void RedBlackTree<T>::RotateLeft(Node* node) {

    }

    template <typename T>
    void RedBlackTree<T>::RotateRight(Node* node) {

    }

} // namespace Ng