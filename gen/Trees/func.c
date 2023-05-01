#include <stdio.h>
#include <stdlib.h>
#include "head.h"

tree *init_root(tree *root, int field) // Выделение памяти под корень дереваnode
{
    tree *tmp = malloc(sizeof(tree)); // Присваивание значения ключу
    tmp -> field = field;// Присваивание указателю на родителя значения NULL
    tmp -> parent = NULL; // Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> left = tmp -> right = NULL;
    root = tmp;
    return root;
}

tree *add_node(tree *root, int field)
{
    tree *root2 = root, *root3 = NULL; // Выделение памяти под узел дерева
    tree *tmp = malloc(sizeof(tree)); // Присваивание значения ключу
    tmp -> field = field; 
    while (root2 != NULL)
    {
        root3 = root2;
        if (field < root2 -> field)
            root2 = root2 -> left;
        else
            root2 = root2 -> right;
    }
    tmp -> parent = root3; // Присваивание указателю на левое и правое поддерево значения NULL
    tmp -> left = NULL;
    tmp -> right = NULL;
    if (field < root3 -> field) root3 -> left = tmp;
    else root3 -> right = tmp;
    return root;
}

tree *find_node(tree * root, int field) // Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
{
    if ((root == NULL) || (root -> field == field))
        return root; // Поиск нужного узла
    if (field < root -> field)
        return find_node(root -> left, field);
    else return find_node(root -> right, field);
}

// Минимальный элемент дерева
tree *minim(tree *root)
{
    tree *lef = root;
    while (lef -> left != NULL)
        lef = lef -> left;
    return lef;
}

// Максимальный элемент дерева
tree *maxim(tree *root)
{
    tree *rig = root;
    while (rig -> right != NULL)
        rig = rig -> right;
    return rig;
}

tree *findForDel(tree *root)
{
    tree *p = root, *lef = NULL; // Если есть правое поддерево, то ищем минимальный элемент в этом поддереве
    if (p -> right != NULL)
        return minim(p -> right);
    lef = p -> parent;
    while ((lef != NULL) && (p == lef -> right))
    {
        p = lef;
        lef = lef -> parent;
    }
    return lef;
}

tree *del_node(tree *root, int field)
{
// Поиск удаляемого узла по ключу
    tree *p = root, *lef = NULL, *tmp = NULL;
    lef = find_node(root, field);
// 1 случай: у узла нет потомков
    if ((lef -> left == NULL) && (lef -> right == NULL))
    {
        tmp = lef -> parent;
        if (lef == tmp -> right) tmp -> right = NULL;
        else tmp -> left = NULL;
        free(lef);
    }
// 2 случай: потомок один - поддерево справа
    if ((lef -> left == NULL) && (lef -> right != NULL))
    {
        tmp = lef -> parent;
        if (lef == tmp -> right) tmp -> right = lef -> right;
        else tmp -> left = lef -> right;
        free(lef);
    }
// 2 случай: потомок один - поддерево слева
    if ((lef -> left != NULL) && (lef -> right == NULL))
    {
        tmp = lef -> parent;
        if (lef == tmp -> right) tmp -> right = lef -> left;
        else tmp -> left = lef -> left;
        free(lef);
    }
// 3 случай: оба потомка
    if ((lef -> left != NULL) && (lef -> right != NULL))
    {
        tmp = findForDel(lef);
        lef -> field = tmp -> field;
        if (tmp -> right == NULL)
            tmp -> parent -> left = NULL;
        else tmp -> parent -> left = tmp -> right;
        free(tmp);
    }
    return root;
}

void print_tree(tree *root)
{
    if (root == NULL)
        return;
    if (root -> field)
        printf("%d ", root -> field);
    print_tree(root -> left);
    print_tree(root -> right);
}