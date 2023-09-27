; ModuleID = 'Module'
source_filename = "Module"
target triple = "x86_64-pc-linux-gnu"

define i32 @main() {
entry:
  br i1 false, label %then, label %alt

then:                                             ; preds = %entry
  ret i32 100

alt:                                              ; preds = %entry
  ret i32 1
  ret i32 0
}
