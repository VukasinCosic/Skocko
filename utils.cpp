typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;

#define global_variable static
#define internal static

#define SPECIAL 1
#define STAR 2
#define SPADE 3
#define CLUB 4
#define DIAMOND 5
#define HEART 6
#define ENTER 7
#define DELETE 8

inline int
clamp(int min, int val, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}