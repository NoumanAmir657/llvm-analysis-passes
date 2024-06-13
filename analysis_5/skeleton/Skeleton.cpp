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
            for (BasicBlock &BB : F) {
                DataLayout DL = F.getParent()->getDataLayout();
                for (Instruction &I : BB) {
                    if (AllocaInst *AI = dyn_cast<AllocaInst>(&I)) {
                        Type *AllocatedType = AI->getAllocatedType();
                        uint64_t SizeInBytes = DL.getTypeAllocSize(AllocatedType);
                        errs() << "Allocas " << *AI << "\n";
                        errs() << "Size: " << SizeInBytes << " bytes\n";
                    }
                }
            }
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
