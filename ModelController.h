#ifndef __MODEL_CONTROLLER_H__
#define __MODEL_CONTROLLER_H__

#include "Thread.h"

class ModelController : public Thread {
    private:
        
    public:
        ModelController(/* args */);
        ~ModelController();
        
        void run();
};

#endif
