#ifndef __MODEL_CONTROLLER_H__
#define __MODEL_CONTROLLER_H__

#include "Thread.h"
#include "MessageQueue.h"
#include "EntityManager.h"

class ModelController : public Thread {
    private:
        EntityManager &entityManager;
        MessageQueue &msgQueue;
        void handle(std::vector<uint32_t> &event);
        
    public:
        ModelController(EntityManager &anEntityManager, MessageQueue &aMsgQueue);
        ~ModelController();

        ModelController(const ModelController& copy) = delete;
        
        void run();
};

#endif
