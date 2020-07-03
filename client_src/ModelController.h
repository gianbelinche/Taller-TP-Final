#ifndef __MODEL_CONTROLLER_H__
#define __MODEL_CONTROLLER_H__

#include "Thread.h"
#include "ProtMsgQueue.h"
#include "EntityManager.h"
#include "LayoutManager.h"
//#include "LoginScreen.h"
#include <atomic>

class ModelController {
    private:
        EntityManager &entityManager;
        ProtMsgQueue &msgQueue;
        LayoutManager &layoutManager;
        void handle(std::vector<uint32_t> &event);
        
    public:
        ModelController(EntityManager &anEntityManager, 
                        ProtMsgQueue &aMsgQueue,LayoutManager &layoutManager);
        ~ModelController();

        ModelController(const ModelController& copy) = delete;
        
        void closeQueue();
        void run(std::atomic<bool> &closed);
};

#endif
