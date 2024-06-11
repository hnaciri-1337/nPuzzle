#include "Tools.hpp"

class Node {
public:
	vector<vector<short>> state;
	Node* parent;
	int g;
	float h;
	int	algo;

	Node(vector<vector<short>> _state, Node* _parent, int _g, float _h, int _algo) {
		state = _state;
		parent = _parent;
		g = _g;
		h = _h;
		algo = _algo;
	}
};

class CompareNodes {
public:
	bool operator()(Node* a, Node* b) {
		if (a->algo == 1)
			return (a->g + a->h) >= (b->g + b->h);
		else if (a->algo == 2)
			return a->h >= b->h;
		return a->g >= b->g;
	}
};
