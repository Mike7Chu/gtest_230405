// 4_스위트픽스쳐.cpp
#include <string>

class Terminal {
public:
    void Connect() { }
    void Disconnect() { }

    void Login(const std::string& id, const std::string& password) { }
    void Logout() { }

    bool IsLogin() const { return false; }
};

#include <gtest/gtest.h>