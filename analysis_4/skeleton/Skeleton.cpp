#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <unordered_map>
#include <set>

using namespace llvm;

namespace {

struct SkeletonPass : public PassInfoMixin<SkeletonPass> {
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
        for (auto &F : M) {
            std::set<std::string> allocas;
            errs() << "Function: " << F.getName() << '\n';
            for (BasicBlock &BB : F) {
                for (Instruction &I : BB) {
                    if (auto *allocaInst = dyn_cast<AllocaInst>(&I)) {
                        allocas.insert(std::string(allocaInst->getName()));
                    }
                    if (auto *gepInst = dyn_cast<GetElementPtrInst>(&I)) {
                        allocas.insert(std::string(gepInst->getName()));
                    }


                    if (auto *loadInst = dyn_cast<LoadInst>(&I)) {
                        auto it = allocas.find(std::string(loadInst->getPointerOperand()->getName()));
                        if (it != allocas.end()) {
                            errs() << I << '\n';
                        }
                    } else if (auto *storeInst = dyn_cast<StoreInst>(&I)) {
                        auto it = allocas.find(std::string(storeInst->getPointerOperand()->getName()));
                        if (it != allocas.end()) {
                            errs() << I << '\n';
                        }
                    }
                }
            }

            errs() << "Allocas: " << '\n';
            for (auto alloca: allocas) {
                errs() << alloca << '\n';
            }
            errs() << '\n';
        }
        return PreservedAnalyses::all();
    };
};

}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return {
        .APIVersion = LLVM_PLUGIN_API_VERSION,
        .PluginName = "Skeleton pass",
        .PluginVersion = "v0.1",
        .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
            PB.registerPipelineStartEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel Level) {
                    MPM.addPass(SkeletonPass());
                });
        }
    };
}
