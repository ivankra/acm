#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

// Treap node.
// All functions accept this==NULL, which represents empty tree.
class Node {
    int auxiliaryKey;       // auxiliary random key; tree is a min-heap w.r.t. auxiliaryKey
    int size;               // number of nodes in this subtree
    char character;
    Node *left, *right;
   
    void updateSize() {
        size = 1 + left->getSize() + right->getSize();
    }

    void toStringHelper(std::string &out) const {
        if (this) {
            left->toStringHelper(out);
            out += character;
            right->toStringHelper(out);
        }
    }

  public:
    Node(char character)
        : auxiliaryKey(rand()), size(1), character(character), left(NULL), right(NULL) {}

    int getSize() const {
        return this ? this->size : 0;
    }

    // Joins this with other tree. Returns a tree, representing concatenation
    // this's and other's sequence of characters.
    Node *join(Node *other) {
        if (this == NULL)
            return other;
        if (other == NULL)
            return this;

        if (this->auxiliaryKey < other->auxiliaryKey) {
            this->right = this->right->join(other);
            this->updateSize();
            return this;
        } else {
            other->left = this->join(other->left);
            other->updateSize();
            return other;
        }
    }

    // Splits a tree into a tree, representing its first leftCount elements, and a tree
    // representing all other elements.
    void split(int leftCount, Node **outLeft, Node **outRight) {
        assert(0 <= leftCount && leftCount <= getSize());

        if (this == NULL) {
            *outLeft = NULL;
            *outRight = NULL;
            return;
        }

        if (leftCount <= left->getSize()) {
            // left subtree needs to be split
            left->split(leftCount, outLeft, &left);
            updateSize();
            *outRight = this;
        } else {
            // right subtree needs to be split
            right->split(leftCount - 1 - left->getSize(), &right, outRight);
            updateSize();
            *outLeft = this;
        }
    }

    std::string toString() {
        std::string str;
        this->toStringHelper(str);
        return str;
    }
};

struct Transform {
    int start, end, shift;
};

std::istream &operator >>(std::istream &in, std::vector<Transform> &out)
{
    int size;
    in >> size;
    out.resize(size);
    for (int i = 0; i < size; i++)
        in >> out[i].start >> out[i].end >> out[i].shift;
    return in;
}

std::string solve(const std::string &str, const std::vector<Transform> &transforms)
{
    Node *root = NULL;
    for (size_t i = 0; i < str.size(); i++)
        root = root->join(new Node(str[i]));
		
	for (std::vector<Transform>::const_reverse_iterator it = transforms.rbegin(); it != transforms.rend(); ++it) {
        const Transform &transform = *it;
        int intervalSize = transform.end - transform.start + 1;
    
        // decompose tree to extract the interval which was rotated
        Node *before, *interval, *after;
        root->split(transform.start - 1, &before, &after);
        after->split(intervalSize, &interval, &after);

        // undo circular rotation of this interval
        Node *intervalBegin, *intervalEnd;
        interval->split(transform.shift % intervalSize, &intervalBegin, &intervalEnd);
        interval = intervalEnd->join(intervalBegin);

        // reassemble tree
        root = before->join(interval)->join(after);
    }

    return root->toString();
}

int main()
{
    std::string stroka;
    std::vector<Transform> transforms;

    std::cin >> stroka >> transforms;
    std::cout << solve(stroka, transforms) << std::endl;

    return 0;
}
