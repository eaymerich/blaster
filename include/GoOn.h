#ifndef __GOON_H__
#define __GOON_H__

class GoOn {
public:
    GoOn() = default;
    virtual ~GoOn() = default;

    GoOn& operator=(const bool& other) {
        mGoOn = other;
        return *this;
    }

    static void stop() {
        mGoOn = false;
    }

    explicit operator bool() const {
        return mGoOn;
    }

    bool operator!() const {
        return !mGoOn;
    }

private:
    static bool mGoOn;
};

#endif // __GOON_H__
