class foo {
	public:
		// imagine constructor and destructor here ...
		void bar() {
			impl->bar();
		}
	private:
		class fooImpl; // forward declaration
		fooImpl *impl; // pointer to implementation
}
