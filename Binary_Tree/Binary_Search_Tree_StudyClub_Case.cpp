#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Node {
	
	int key;
	Node *left, *right;
	
} *root;


void search (struct Node* curr, int find){
	
	if (curr == NULL) {
		printf ("%d is not found\n", find);
		return;
	}
	
	if (find == curr->key) {
		printf ("%d is found\n", find);
		return;
	}
	
	if (find < curr->key) return search (curr->left, find);
	
	return search (curr->right, find);
	
}


void insert (struct Node* curr, int val){
	
	struct Node *newNode = (Node*) malloc (sizeof(Node));
	
	newNode->key = val;
	newNode->left = newNode->right = NULL;
	
	if (root == NULL){
		root = newNode;
	}
	
	else if (val != curr->key){
		if (val < curr->key && curr->left == NULL){
			curr->left = newNode;
		}
		else if (val > curr->key && curr->right == NULL){
			curr->right = newNode;
		}
		else if (val < curr->key && curr->left != NULL){
			insert (curr->left, val);
		}
		else if (val > curr->key && curr->left != NULL){
			insert (curr->right, val);
		}
	}
	
}


void inOrderTraversal (struct Node* curr){
	
	if (curr == NULL) return;
	
	inOrderTraversal (curr->left);
	printf ("%d ", curr->key);
	inOrderTraversal (curr->right);
	
}


void preOrderTraversal (struct Node* curr){
	
	if (curr == NULL) return;
	
	printf ("%d ", curr->key);
	
	preOrderTraversal (curr->left);
	preOrderTraversal (curr->right);
	
}


void postOrderTraversal (struct Node* curr){
	
	if (curr == NULL) return;
	
	postOrderTraversal (curr->left);
	postOrderTraversal (curr->right);
	
	printf ("%d ", curr->key);
	
}

// Delete using successor

void executeDeleteNode2 (struct Node* parent, struct Node* curr){
	
	// Case 1: Node to be deleted has no children (is a leaf node)
	
    if (curr->left == NULL && curr->right == NULL) {
    	
        if (parent->left == curr) {
            parent->left = NULL;
        } 
		
		else {
            parent->right = NULL;
        }
        
        free(curr);
    }
    
    // Case 2: Node to be deleted has one child
    
    else if (curr->left == NULL || curr->right == NULL) {
    	
        struct Node* child = (curr->left != NULL) ? curr->left : curr->right;
        
        if (parent->left == curr) {
            parent->left = child;
        } 
		
		else {
            parent->right = child;
        }
        
        free(curr);
    }
    
    // Case 3: Node to be deleted has two children
    
    else {
    	
        struct Node* successorParent = curr;
        struct Node* successor = curr->right;

        // Find the leftmost child of the right subtree
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        // Copy the successor's value to the current node
        curr->key = successor->key;

        // Delete the successor node (which is guaranteed to have 0 or 1 child)
        if (successorParent->left == successor) {
            successorParent->left = (successor->right != NULL) ? successor->right : NULL;
        } 
		
		else {
            successorParent->right = (successor->right != NULL) ? successor->right : NULL;
        }
        
        free(successor);
        
    }
	
}

// Delete using predecessor

void executeDeleteNode(struct Node* parent, struct Node* curr) {
	
    // Case 1: Node to be deleted has no children (is a leaf node)
    
    if (curr->left == NULL && curr->right == NULL) {
        if (parent->left == curr) {
            parent->left = NULL;
        } 
		
		else {
            parent->right = NULL;
        }
        free(curr);
    }
    
    // Case 2: Node to be deleted has one child
    
    else if (curr->left == NULL || curr->right == NULL) {
        struct Node* child = (curr->left != NULL) ? curr->left : curr->right;
        if (parent->left == curr) {
            parent->left = child;
        } 
		
		else {
            parent->right = child;
        }
        free(curr);
    }
    
    // Case 3: Node to be deleted has two children
    
    else {
    	
        // Find the predecessor node (largest node in the left subtree)
        
        struct Node* predecessorParent = curr;
        struct Node* predecessor = curr->left;

        while (predecessor->right != NULL) {
            predecessorParent = predecessor;
            predecessor = predecessor->right;
        }

        // Copy the predecessor's value to the current node
        curr->key = predecessor->key;

        // Delete the predecessor node (which is guaranteed to have 0 or 1 child)
        if (predecessorParent->left == predecessor) {
            predecessorParent->left = (predecessor->left != NULL) ? predecessor->left : NULL;
        } 
		
		else {
            predecessorParent->right = (predecessor->left != NULL) ? predecessor->left : NULL;
        }

        free(predecessor);
        
    }
}


void deleteNode (struct Node* curr, int find){
	
	struct Node* parent = curr;
	
	while (curr && curr->key != find){
		if (find < curr->key){
			parent = curr;
			curr = curr->left;
		}
		else if  (find > curr->key){
			parent = curr;
			curr = curr->right;
		}
	}
	
	if (!curr){
		printf ("%d is not found");
	}
	
	else if (curr->key == find){
		executeDeleteNode (parent, curr);
	}
	
}


int minValue (struct Node* node){
	
	// Base Case
	
	if (node == NULL) return NULL;
	if (node->left == NULL) return node->key;
	
	return minValue (node->left);
	
}


int maxValue (struct Node* node){
	
	// Base Case
	
	if (node == NULL) return NULL;
	if (node->right == NULL) return node->key;
	
	return maxValue (node->right);
	
}


int count (struct Node* node){
	
	if (!node) return 0;
	
	return (1 + count(node->left) + count (node->right));
	
}


int height (struct Node* node){
	
	if (node == NULL) {
        return 0;
    }

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
	
}


int main(){
	
	root = NULL;
	
	insert (root, 54);
	insert (root, 81);
	insert (root, 16);
	insert (root, 27);
	insert (root, 9);
	insert (root, 36);
	insert (root, 63);
	insert (root, 72);
	
	printf ("Total Node in BST: %d\n", count(root));
	
	printf ("Height of Binary Tree: %d\n", height(root));
	
	printf ("\nInorder: "); inOrderTraversal (root); puts ("");
	printf ("\Preorder: "); preOrderTraversal (root); puts ("");
	printf ("\Postorder: "); postOrderTraversal (root); puts ("");
	
	puts ("");
	
	deleteNode (root, 54);
	
	printf ("\nPreorder (after del 54): "); preOrderTraversal (root); puts ("");
	
	deleteNode (root, 9);
	
	printf ("\Postorder (after del 9): "); postOrderTraversal (root); puts ("");
	
	deleteNode (root, 81);
	
	printf ("\Inorder (after del 81): "); inOrderTraversal (root); puts ("");
	
	puts ("");
	
	printf ("Min Value: %d\n", minValue(root));
	printf ("Max Value: %d\n", maxValue(root));
	
	puts ("");
	
	search (root, 72);
	search (root, 8);
	
	return 0;
	
}

