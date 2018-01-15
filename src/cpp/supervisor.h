#pragma once

#include "puct/node.h"
#include "puct/config.h"
#include "puct/evaluator.h"
#include "gdltransformer.h"

#include <statemachine/basestate.h>
#include <statemachine/jointmove.h>
#include <statemachine/statemachine.h>

#include <vector>

namespace GGPZero {

    // forwards
    class PuctEvaluator;
    class SelfPlay;
    class SelfPlayConfig;
    class SelfPlayManager;

    class Supervisor {
    public:
        Supervisor(GGPLib::StateMachineInterface* sm,
                   const GdlBasesTransformer* transformer,
                   int batch_size);
        ~Supervisor();

    public:
        void createInline(const SelfPlayConfig* config);

        // basically proxies to manager/workers
        std::vector <Sample*> getSamples();

        int poll(float* policies, float* final_scores, int pred_count);
        float* getBuf() const;

        void addUniqueState(const GGPLib::BaseState* bs);
        void clearUniqueStates();

    private:
        GGPLib::StateMachineInterface* sm;
        const GdlBasesTransformer* transformer;
        const int batch_size;

        SelfPlayManager* inline_sp_manager;

        // XXX worker thread

        std::vector <SelfPlayManager*> self_play_managers;
    };
}