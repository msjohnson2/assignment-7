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
template<typename Value>
struct BstNode
{

    Value Data;
    std::unique_ptr<BstNode<Value>> Left;
    std::unique_ptr<BstNode<Value>> Right;


    BstNode(Value val)
        : Data(val)
    {}
};

// insert
template<typename Value>
void insert(std::unique_ptr<BstNode<Value>> & head, const Value & item)
{
    auto p = head.get();

    if(!head)
    {
        head = std::move(std::make_unique<BstNode<Value>>(item));
    }
    else
    {
        while(p)
        {
            if(item < p->Data)
            {
                if(!p->Left)
                {
                    p->Left = std::move(std::make_unique<BstNode<Value>>(item));
                    return;
                }
                else
                {
                    p = p->Left.get();
                }
            }
            else
            {
                if(!p->Right)
                {
                    p->Right = std::move(std::make_unique<BstNode<Value>>(item));
                    return;
                }
                else
                {
                    p = p->Right.get();
                }
            }
        }
    }
}


// inOrderTraverse

template<typename Value, typename FDIter>
void inOrderTraverse(const std::unique_ptr<BstNode<Value>> & node, FDIter & iter)
{
    if(!node)
    {
        return;
    }

    inOrderTraverse(node->Left, iter);

    *iter++ = node->Data; // gotta love post increment

    inOrderTraverse(node->Right, iter);

}


// treesort
// Sort a given range using Treesort.
// Pre:
//     ???
// Exception safety guarantee:
//     ???
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Value is the type that FDIter points to
    using Value = typename std::iterator_traits<FDIter>::value_type;

    std::unique_ptr<BstNode<Value>> head;

    for(FDIter i = first; i != last; ++i)
    {
        insert(head, *i);
    }   

    inOrderTraverse(head, first);
}


#endif //#ifndef FILE_TSORT_HPP_INCLUDED

