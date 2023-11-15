// tsort.hpp
// Matthew Johnson
// 2023-11-14
//
// For CS 311 Fall 2023
// Header for function template treesort
// There is no associated source file.

#ifndef FILE_TSORT_HPP_INCLUDED
#define FILE_TSORT_HPP_INCLUDED

#include <iterator>
// For std::iterator_traits

#include <memory>
// For std::unique_ptr
// For std::make_unique

#include <algorithm>
// For std::move

// BstNode
// is a node of a binary search tree that contains data and a pointer to rigth and left branches
// Invarients:
//      Value must have copy ctor and < operator
template<typename Value>
struct BstNode
{

    Value Data; // data stored at node
    std::unique_ptr<BstNode<Value>> Left; // points to left child
    std::unique_ptr<BstNode<Value>> Right; // points to right child

    // constructor with 1 parameter
    // makes a BstNode with data set to val
    // Pre:
    //      none
    // No-Throw Guarentee
    BstNode(const Value & val) noexcept
        : Data(val)
    {}
};

// insert
// insert given values into a binary search tree
// Pre:
//      Value must have < comparison operator
//      Value must have a copy ctor 
// No-Throw Guarentee
template<typename Value>
void insert(std::unique_ptr<BstNode<Value>> & head, const Value & item)
{
    auto p = head.get();

    if(!head) // if head is nullptr, it is set to a BstNode with data member equal to item
    {
        head = std::move(std::make_unique<BstNode<Value>>(item));
    }
    else
    {
        while(true)// keeps looping until item is placed
        {
            if(item < p->Data) // goes down left tree
            {
                if(!p->Left) // if left node is null, it is set to a BstNode wit data meber item
                {
                    p->Left = std::move(std::make_unique<BstNode<Value>>(item));
                    return;
                }
                else // if left node already has data, it moves to the next left node
                {
                    p = p->Left.get();
                }
            }
            else // goes down right tree
            {
                if(!p->Right) // if right node is null, it is set to a BstNode wit data meber item
                {
                    p->Right = std::move(std::make_unique<BstNode<Value>>(item));
                    return;
                }
                else // if left node already has data, it moves to the next left node
                {
                    p = p->Right.get();
                }
            }
        }
    }
}


// inOrderTraverse
// preforms an in order traversal of a binary search tree
// Pre:
//      iter must point to head of array on first call
//      Value must have a copy ctor 
// No-Throw Gaurentee
template<typename Value, typename FDIter>
void inOrderTraverse(const std::unique_ptr<BstNode<Value>> & node, FDIter & iter)
{
    if(!node)
    {
        return;
    }

    inOrderTraverse(node->Left, iter); // goes down left untill it hits the end


    *iter++ = node->Data; // sets data at iter to node->Data

    inOrderTraverse(node->Right, iter); // goes down right branch if it is there

}


// treesort
// Sort a given range using Treesort.
// Pre:
//      Value must have < comparison operator
//      Value must have a copy ctor 
//      first and last must point to a range on a sequence
// Exception safety guarantee:
//      No-Throw Guarentee
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Value is the type that FDIter points to
    using Value = typename std::iterator_traits<FDIter>::value_type;

    std::unique_ptr<BstNode<Value>> head; // makes a nullptr to BstNode<Value>

    for(FDIter i = first; i != last; ++i) // inserts sequence into a Binary search tree with pointer head
    {
        insert(head, *i);
    }   

    inOrderTraverse(head, first); // traverses the search tree and copys values back into original sequence
}


#endif //#ifndef FILE_TSORT_HPP_INCLUDED

