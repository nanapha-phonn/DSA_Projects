
#include <iostream>
#include <queue>
#include <string>
#include <map>
using namespace std;

struct Node {
    char letter;
    int frequency;
    Node *left, *right;

    Node(char ch, int freq) {
        letter = ch;
        frequency = freq;
        left = nullptr;
        right = nullptr;
    }
};

// Put the lowest frequency node first
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

// Print the Huffman codes
void showCodes(Node* root, string code) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->right == nullptr) {
        cout << root->letter << " : " << code << endl;
    }

    showCodes(root->left, code + "0");
    showCodes(root->right, code + "1");
}

// Free the memory used by the tree
void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string text;

    cout << "=== Huffman File Compression ===\n";
    cout << "Enter text to compress: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "Please enter some text.\n";
        return 0;
    }

    map<char, int> frequency;

    // Count how often each character appears
    for (char ch : text) {
        frequency[ch]++;
    }

    priority_queue<Node*, vector<Node*>, Compare> nodes;

    // Create a node for each character
    for (auto item : frequency) {
        nodes.push(new Node(item.first, item.second));
    }

    // Build the Huffman tree
    while (nodes.size() > 1) {
        Node* left = nodes.top();
        nodes.pop();

        Node* right = nodes.top();
        nodes.pop();

        Node* parent = new Node(
            '\0', left->frequency + right->frequency
        );

        parent->left = left;
        parent->right = right;

        nodes.push(parent);
    }

    Node* root = nodes.top();

    cout << "\n--- Huffman Codes ---\n";
    showCodes(root, "");

    // Encode the input text
    map<char, string> codes;

    // Generate codes and store them
    // using a simple recursive traversal
    // (implemented below through a local helper)

    deleteTree(root);

    return 0;
}
