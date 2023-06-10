#ifndef FLAG_H
#define FLAG_H

struct Flag {
    bool flag = false;
    bool check();
    void set();
    void unset();
};


#endif //FLAG_H
