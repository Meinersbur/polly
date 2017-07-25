

#include <vector>
#include <cassert>

extern "C" {
	void isl_allocated(void *p, const char *ty);
	void isl_released(void *p);
}

struct Allocation {
	void *p;
	const char *ty;
	long id;

	Allocation(void *p, const char *ty, long id) : p(p), ty(ty), id(id) {}
};

static long NextId = 0;
static std::vector<Allocation> Allocations;

struct isl_map *a, *b;

void isl_allocated(void *p, const char *type) {
	for (auto It = Allocations.begin(); It != Allocations.end(); ++It) {
		assert(It->p != p && "Must not be already registered");
	}

	if (NextId == 9693) {
		a = (struct isl_map*)p;
	}
	if (NextId == 9695) {
		b = (struct isl_map*)p;
	}

	Allocations.emplace_back( p, type, NextId );
	NextId += 1;
}

void isl_released(void *p) {
	if (a == p) {
		int x = 0;
	}
	if (b == p) {
		int y = 0;
	}

	for (auto It = Allocations.begin(); It != Allocations.end(); ++It) {
		if (It->p == p) {
			Allocations.erase(It);
			return;
		}
	}
	assert(!"Allocation not found!");
}