#pragma once

#include <iostream>
#include <string>
#include "Nodes.h"
#include "Session.h"
#include "Types.h"
class Connection;
class SessionContext;

class Terminal {
 public:
  Terminal();
  ~Terminal();

 public:
  enum Option : uint32_t {
    kEnableEcho = 0x01,
    kQuietMode = 0x02,  //! 安静模式，不主动打印提示信息
  };
  SessionToken newSession(Connection *wp_conn);
  bool deleteSession(const SessionToken &st);

  uint32_t getOptions(const SessionToken &st) const;
  void setOptions(const SessionToken &st, uint32_t options);

  bool onBegin(const SessionToken &st);
  bool onExit(const SessionToken &st);

  bool onRecvString(const SessionToken &st, const std::string &str);
  bool onRecvWindowSize(const SessionToken &st, uint16_t w, uint16_t h);

 public:
  NodeToken createFuncNode(const Func &func, const std::string &help);
  NodeToken createDirNode(const std::string &help);
  NodeToken rootNode() const;
  NodeToken findNode(const std::string &path) const;
  bool  mountNode(const NodeToken &parent, const NodeToken &child,
                 const std::string &name);

 protected:
  void onChar(SessionContext *s, char ch);
  void onEnterKey(SessionContext *s);
  void onBackspaceKey(SessionContext *s);
  void onDeleteKey(SessionContext *s);
  void onTabKey(SessionContext *s);
  void onMoveUpKey(SessionContext *s);
  void onMoveDownKey(SessionContext *s);
  void onMoveLeftKey(SessionContext *s);
  void onMoveRightKey(SessionContext *s);
  void onHomeKey(SessionContext *s);
  void onEndKey(SessionContext *s);

  void printPrompt(SessionContext *s);
  void printHelp(SessionContext *s);

  bool execute(SessionContext *s);
  bool executeCmd(SessionContext *s, const std::string &cmdline);

  void executeCdCmd(SessionContext *s, const Args &args);
  void executeHelpCmd(SessionContext *s, const Args &args);
  void executeLsCmd(SessionContext *s, const Args &args);
  void executeHistoryCmd(SessionContext *s, const Args &args);
  void executeExitCmd(SessionContext *s, const Args &args);
  void executeTreeCmd(SessionContext *s, const Args &args);
  void executePwdCmd(SessionContext *s, const Args &args);
  bool executeRunHistoryCmd(SessionContext *s, const Args &args);
  void executeUserCmd(SessionContext *s, const Args &args);

  bool findNode(const std::string &path, Path &node_path) const;

 private:
  Cabinet<SessionContext> sessions_;
  Cabinet<Node> nodes_;
  NodeToken root_token_;
};
