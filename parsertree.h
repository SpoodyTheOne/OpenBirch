#ifndef PARSERTREE_H
#define PARSERTREE_H

#include <string>
#include <unordered_map>

struct ParserTreeBranch {
    ParserTreeBranch *part0;
    ParserTreeBranch *part1;
};

class ParserTree
{
public:
    ParserTree();

    void splitString ( std::string input );

    ParserTreeBranch root;
};

#endif // PARSERTREE_H
