#include<stdio.h>
#include<stdlib.h>
struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};


struct TreeNode* newTreeNode(int data)
{
    struct TreeNode* newNode = (struct TreeNode* )malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/*understand this algo as a story.....*/

/**
Method 1: First Approach
Time Complexity: O(n)
*/
//do a normal inorder traversal and count the nodes
struct TreeNode* getKthSmallestElement(struct TreeNode* root, int k)
{
    static int count = 0;
    //relevant base case
    if(!root || count >= k)
    {
        return root;
    }

    //go to the extreme left node
    struct TreeNode* left = getKthSmallestElement(root->left, k);//root is asking its Left subtree to get kth smallest elem

    //if left subtree gets the elem, then that is the elem and will pass this news to its own ancestor(if it has one)
    if(left)
    {
        printf("\nOyee node %d-- %d is the kth smallest elem from your left subtree, dont search anymore",root->data, left->data);
        return left;
    }

    //if you still not got that elem just print yourself
    //printf("%d\n ", root->data);

    //and now keep the count on;
    count++;

    //as the count reaches k, desired elem found
    if(count == k)
    {
        return root;//returns the desired elem wherever
    }
    printf("%d says that it is still %dth smallest elem, so search in its right subtree\n", root->data,count);

    //root also asks its right subtree for the kth smallest elem,

    struct TreeNode* right = getKthSmallestElement(root->right, k);

    //if right subtree gets the elem, return the elem to the calling parent, telling that i found the desired elem, no need to search anymore
    //just keep telling your ancestor
    if(right)
    {
        printf("\n__________\nOyee node %d-- %d is the kth smallest elem from your right subtree, dont search anymore",root->data, right->data);
        return right;
    }

    printf("Oyee %d, i did not get kth smallest from your right subtree either, go back to my parent\n", root->data);
    return NULL;
}


struct TreeNode* getKthSmallestElement_2(struct TreeNode* root, int k)
{
    static int count = 0;
    if(!root)
        return root;

    struct TreeNode* kthSmallestnode = getKthSmallestElement_2(root->left, k);

    if(count != k)//as you see a node check whether it is the kth smallest, if it is not
    {
        count++;//then increment
        kthSmallestnode = root;//and assign it to a variable
    }

    if(count == k)
        return kthSmallestnode;
    else
        return getKthSmallestElement_2(root->right, k);
}

struct TreeNode* getKthSmallestElement_3(struct TreeNode* root, int k)
{
    static int count = 0;
    //relevant base case
    if(!root || count >= k)
    {
        return root;
    }

    //go to the extreme left node
    struct TreeNode* left = getKthSmallestElement_3(root->left, k);//root is asking its Left subtree to get kth smallest elem

    //if left subtree gets the elem, then that is the elem and will pass this news to its own ancestor(if it has one)
    if(left)
    {
        printf("\nOyee node %d-- %d is the kth smallest elem from your left subtree, dont search anymore",root->data, left->data);
        return left;
    }

    //if you still not got that elem just print yourself
    //printf("%d\n ", root->data);

    //and now keep the count on;
    count++;

    //as the count reaches k, desired elem found
    if(count == k)
    {
        return root;//returns the desired elem wherever
    }
    //root also asks its right subtree for the kth smallest elem,

    else
    {
        printf("%d says that it is still %dth smallest elem, so search in its right subtree\n", root->data,count);
        return getKthSmallestElement_3(root->right, k);
    }
}


/**
Above three approaches are the same
Time Complexity: O(n)
Space Complexity: O(n)
*/


/**
Method 2: a variant of method 1 doing inorder using morris rule and finding kth smallest element
Time complexity: O(n)
Space Complexity: O(1)*/
struct TreeNode* kthSmallest_morris_inorder(struct TreeNode* root, int k)
{
    struct TreeNode* curr = root;
    int count = 0;
    struct TreeNode* kthSmallestNode;
    while(curr != NULL)
    {
        if(curr->left == NULL)
        {
            count++;
            if(count == k)
            {
                kthSmallestNode = curr;//if left subtree is null then may be root itself can be kthsmallest
            }
            curr = curr->right;
        }
        else
        {
            //find the inorder predecessor to curr
            struct TreeNode* pre_curr = curr->left;
            while(pre_curr->right != NULL & pre_curr->right != curr)
                pre_curr = pre_curr->right;

            //make child right pointers to its inorder successor
            if(pre_curr->right == NULL)
            {
                pre_curr->right = curr;
                curr = curr->left;
            }
            else
            {
                pre_curr->right == NULL;
                count++;
                if(count == k)
                {
                    kthSmallestNode = curr;
                }
                curr = curr->right;
            }
        }
    }
    return kthSmallestNode;
}

/**
Method 3:

Time complexity: O(n * logn) , since not using order statistics tree, if using then O(logn)
*/
struct TreeNode* getKthSmallest_5(struct TreeNode* root, int k)
{
    if(!root)
        return root;
    int childCount = getChildCount(root->left);//get count of the left subtree of root
    printf("root = %d, k = %d , childCount+1 = %d, ", root->data , k, childCount+1);

    if(k == childCount+1){
        printf("got the element\n");
        return root;
    }
    else if(k < childCount+1){
        printf("k < childCount+1\n");
        return getKthSmallest_5(root->left, k);
    }
    else{
        printf("k > childCount+1\n");
        return getKthSmallest_5(root->right, k - (childCount+1));
    }
}

/**
Using order-statistics tree, method 3, is done in a different example using iteration
*/

int getChildCount(struct TreeNode* root)
{
    if(root== NULL)
        return 0;
    int left = getChildCount(root->left);
    int right = getChildCount(root->right);
    return 1+left+right;
}

void main()
{
    struct TreeNode* root = newTreeNode(44);
    root->left = newTreeNode(22);
    //root->left->right = newTreeNode(33);
    root->right = newTreeNode(66);
    root->left->left = newTreeNode(10);
    root->left->left->left = newTreeNode(1);
    root->left->left->right = newTreeNode(20);
    root->right->left = newTreeNode(55);
    root->right->right = newTreeNode(70);
    root->right->left->left = newTreeNode(50);
    root->left->left->left = newTreeNode(8);
    root->right->left->left->right = newTreeNode(53);
    printf("\n\nchildCount: %d\n",getChildCount(root->left));
    printf("\n\n%dth smallest element in BST is: %d", 3, getKthSmallest_5(root, 3)->data);
}
