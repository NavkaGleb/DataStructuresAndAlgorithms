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

        private:
            T     m_Value;
            Color m_Color;
            Node* m_Parent;
            Node* m_Left;
            Node* m_Right;

        }; // class Node

        explicit RedBlackTree(Node* root = nullptr);
        virtual ~RedBlackTree();

        [[nodiscard]] inline Node* GetRoot() { return m_Root; }
        [[nodiscard]] inline const Node* GetRoot() const { return m_Root; }

        Node* PushNode(const T& value);
        void PopNode(const T& value);

    private:
        

        Node* m_Root;

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
    RedBlackTree<T>::RedBlackTree(Node* root) :
        m_Root(root) { }

    template <typename T>
    RedBlackTree<T>::~RedBlackTree() {
        delete m_Root;
    }

    template <typename T>
    Node* RedBlackTree<T>::PushNode(const T& value) {

    }

} // namespace Ng