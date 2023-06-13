#ifndef FLAG_H
#define FLAG_H

struct Flag {
    bool flag = false;
    virtual bool check();
    void set();
    void unset();
};

struct DoubleFlag : Flag {
    Flag &a;
    Flag &b;
    DoubleFlag(Flag &a, Flag &b): a(a), b(b) {};
    bool check() override;
};

#endif //FLAG_H
