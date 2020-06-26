#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Thread.h"

class Renderer : public Thread {
    private:
        bool closed;

    public:
        Renderer();
        ~Renderer();

        void run();
        void close();
};

#endif
