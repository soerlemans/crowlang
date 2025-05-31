CrowLang Intermediate Representation (CLIR)
===========================================
This is a medium level IR for the crow compiler.
The IR is Static Single Assignment (SSA) and structured.
The reason that it is structured is because the unstructuring/desugaring.
Should happen when we convert from this mid level IR to LLVM IR.
