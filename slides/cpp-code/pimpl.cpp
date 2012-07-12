class fooImpl; // forward declaration
class foo {
	public:
		// imagine constructor and destructor here ...
		void bar() {
			impl->bar();
		}
	private:
		fooImpl *impl; // pointer to implementation
}
