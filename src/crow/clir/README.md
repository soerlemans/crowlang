CrowLang Intermediate Representation (CLIR)
===========================================
This is a medium level IR for the crow compiler.
The IR is Static Single Assignment (SSA) and unstructured.
The reason for the IR being unstructured is so that we have a desugared representation.
This way generating LLVM IR becomes a lot easier.
Not all backends should perform codegen using this mid level IR.
