// This is adapated from `gcc.gnu.org/wiki/Visibility`
#if defined WIN32 || defined __CYGWIN__
  #define YENAH_EXPORT __declspec(dllexport)
  #define YENAH_LOCAL
#elif __GNUC__
  #define YENAH_EXPORT __attribute__ ((visibility ("default")))
  #define YENAH_LOCAL __attribute__ ((visibility ("hidden")))
#else
  #define YENAH_EXPORT
  #define YENAH_LOCAL
#endif

#define FFI_EXPORT extern "C" YENAH_EXPORT

// A basic demontration class for testing
class Test
{
public:
	int x;
	Test(int x_) {x = x_;}
	int getX(void) {return x;}
	void setX(int x_) {x = x_;}
};

FFI_EXPORT Test* Test_new(int x_)
{
	return new Test(x_);
}

FFI_EXPORT void Test_delete(Test* __this)
{
	delete __this;
}

FFI_EXPORT int Test_getX(const Test* __this)
{
	return __this->x;
}

FFI_EXPORT void Test_setX(Test* __this, int x_)
{
	__this->x = x_;
}
