#pragma once

#include <optional>

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
            void Print() const;

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

        [[nodiscard]] inline const Node* GetRoot() const { return m_Root; }
        [[nodiscard]] inline int GetNodes() const { return m_Nodes; }

        [[nodiscard]] int GetHeight() const;
        [[nodiscard]] bool IsExists(const T& value) const;
        [[nodiscard]] std::optional<T> GetMin() const;
        [[nodiscard]] std::optional<T> GetMax() const;

        Node* Push(const T& value);
        void Pop(const T& value);

        void Print() const;

    private:
        [[nodiscard]] int GetHeight(Node* node) const;

        [[nodiscard]] std::optional<T> GetMin(Node* node) const;
        [[nodiscard]] std::optional<T> GetMax(Node* node) const;

        [[nodiscard]] Node* GetMinNode(Node* node) const;
        [[nodiscard]] Node* GetMaxNode(Node* node) const;

        [[nodiscard]] Node* GetSuccessor(Node* node) const;

        void RotateLeft(Node* node);
        void RotateRight(Node* node);

        void PushFix(Node* node);
        void PopFix(Node* child, Node* parent);

        void Transplant(Node* first, Node* second);
        void Print(const Node* node, const int& level, const char* caption) const;

        Node* m_Root;
        int   m_Nodes;

    }; // class RedBlackTree

#include "RedBlackTree.inl"

} // namespace Ng