//
// Created by rex on 2020/1/28.
//

#include <queue>

#include "ASTUtility.h"
#include "ASTFetchSubnode.h"

namespace opene {
    void ASTUtility::FixNodeParent(Node *root) {
        std::queue<std::pair<Node*, ASTFetchSubnode::ASTFetchResult>> workqueue;
        workqueue.push(std::pair(root, ASTFetchSubnode::ASTFetchResult()));
        while (workqueue.empty() == false) {
            std::pair<Node*, ASTFetchSubnode::ASTFetchResult> work = workqueue.front();
            workqueue.pop();
            if (ASTFetchSubnode::FetchSubNode(work.first, work.second) == false) {
                continue;
            }
            for (const Node * node : work.second) {
            }
        }
    }
}