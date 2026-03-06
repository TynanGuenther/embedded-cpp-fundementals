template<typename F>
class ScopeGuard {
    public:
	explicit ScopeGuard(F cleanup) : cleanup_(cleanup) {}
	~ScopeGuard() { cleanup_(); };

	ScopeGuard(const ScopeGuard&) = delete;
	ScopeGuard& operator=(const ScopeGuard&) = delete;
	ScopeGuard(ScopeGuard&&) = delete;
	ScopeGuard& operator=(ScopeGuard&&) = delete;

    private:
	F cleanup_;

};

