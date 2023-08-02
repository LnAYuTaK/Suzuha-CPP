#include "Nodes.h"

bool DirNode::addChild(const NodeToken &nt, const std::string &child_name) {
  auto iter = children_.find(child_name);
  if (iter != children_.end()) return false;

  children_.insert(std::make_pair(child_name, nt));
  return true;
}

NodeToken DirNode::findChild(const std::string &child_name) const {
  auto iter = children_.find(child_name);
  if (iter == children_.end()) return NodeToken();
  return iter->second;
}

void DirNode::children(std::vector<NodeInfo> &vec) const {
  for (auto item : children_) {
    NodeInfo info{item.first, item.second};
    vec.push_back(info);
  }
}

FuncNode::FuncNode(const Func &func, const std::string &help)
    : Node(help), func_(func) {}

void FuncNode::execute(const Session &s, const Args &a) const {
  if (func_) func_(s, a);
}
