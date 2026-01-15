module c_interop


// Declarations for interoperating with C.
[[extern("C")]] {

[[noreturn]]
func exit(t_status: int) -> void
}