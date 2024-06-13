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
        std::unordered_map<std::string, int> counts;
        for (auto &F : M) {
            for (BasicBlock &BB : F) {
                for (Instruction &I : BB) {
                    std::string opcode(I.getOpcodeName());
                    auto it = counts.find(opcode);
                    if (it != counts.end()) {
                        counts[opcode]++;
                    }
                    else {
                        counts.insert(std::make_pair(opcode, 1));
                    }
                }
            }
        }

        for (const auto& pair : counts) {
                errs() << pair.first << "   " << pair.second << '\n';
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
