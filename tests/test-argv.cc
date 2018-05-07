#include <cppunit/extensions/HelperMacros.h>

#include <argvcc.h>
#include <sstream>

namespace unittests {
namespace argv {

class test : public CppUnit::TestCase {
public:
	test();
	void setUp();
	void tearDown();

private:
	void test_empty();
	void test_one_element();
	void test_two_elements();
	void test_push_back();
	void test_nullptr();
	void test_stdstring();
	void test_iterators();
	void test_stdostream();
	void test_append();

	CPPUNIT_TEST_SUITE(test);
	CPPUNIT_TEST(test_empty);
	CPPUNIT_TEST(test_one_element);
	CPPUNIT_TEST(test_two_elements);
	CPPUNIT_TEST(test_push_back);
	CPPUNIT_TEST(test_nullptr);
	CPPUNIT_TEST(test_stdstring);
	CPPUNIT_TEST(test_iterators);
	CPPUNIT_TEST(test_stdostream);
	CPPUNIT_TEST(test_append);
	CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION(test);

test::test()
{ }

void test::setUp()
{ }

void test::tearDown()
{ }

void test::test_empty()
{
	auto a = argvcc::Argv();
	CPPUNIT_ASSERT(a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), a.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[0]);

	auto b = a;
	CPPUNIT_ASSERT(b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), b.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[0]);

	auto c = std::move(b);
	CPPUNIT_ASSERT(c.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), c.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), c[0]);

	b = argvcc::Argv();
	CPPUNIT_ASSERT(b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), b.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[0]);

	auto d = argvcc::Argv{"foo"};
	CPPUNIT_ASSERT_EQUAL(size_t(1), d.size());
	CPPUNIT_ASSERT(d[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(d[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), d[1]);

	d = a;
	CPPUNIT_ASSERT(d.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), d.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), d[0]);

	auto e = argvcc::Argv{"foo"};
	CPPUNIT_ASSERT_EQUAL(size_t(1), e.size());
	CPPUNIT_ASSERT(e[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(e[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), e[1]);

	e = std::move(a);
	CPPUNIT_ASSERT(e.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), e.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), e[0]);

	a = argvcc::Argv();
	CPPUNIT_ASSERT(a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), a.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[0]);
}

void test::test_one_element()
{
	auto a = argvcc::Argv{"foo"};
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[1]);

	auto b = a;
	CPPUNIT_ASSERT(!b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), b.size());
	CPPUNIT_ASSERT(b[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(b[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[1]);

	auto c = std::move(b);
	CPPUNIT_ASSERT(!c.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), c.size());
	CPPUNIT_ASSERT(c[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(c[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), c[1]);

	b = argvcc::Argv();
	CPPUNIT_ASSERT(b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), b.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[0]);

	auto d = argvcc::Argv{"bar"};
	CPPUNIT_ASSERT(!d.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), d.size());
	CPPUNIT_ASSERT(d[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(d[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), d[1]);

	d = a;
	CPPUNIT_ASSERT(!d.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), d.size());
	CPPUNIT_ASSERT(d[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(d[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), d[1]);

	auto e = argvcc::Argv{"bar"};
	CPPUNIT_ASSERT(!e.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), e.size());
	CPPUNIT_ASSERT(e[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(e[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), e[1]);

	e = std::move(a);
	CPPUNIT_ASSERT(!e.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), e.size());
	CPPUNIT_ASSERT(e[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(e[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), e[1]);

	a = argvcc::Argv();
	CPPUNIT_ASSERT(a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), a.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[0]);
}

void test::test_two_elements()
{
	auto a = argvcc::Argv{"foo", "bar"};
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[2]);

	auto b = a;
	CPPUNIT_ASSERT(!b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), b.size());
	CPPUNIT_ASSERT(b[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(b[0]));
	CPPUNIT_ASSERT(b[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(b[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[2]);

	auto c = std::move(b);
	CPPUNIT_ASSERT(!c.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), c.size());
	CPPUNIT_ASSERT(c[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(c[0]));
	CPPUNIT_ASSERT(c[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(c[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), c[2]);

	b = argvcc::Argv();
	CPPUNIT_ASSERT(b.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), b.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), b[0]);
}

void test::test_push_back()
{
	auto a = argvcc::Argv();
	CPPUNIT_ASSERT(a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(), a.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[0]);

	a.push_back("foo");
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(1), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[1]);

	a.push_back("bar");
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[2]);
}

void test::test_nullptr()
{
	auto throws = []() { return argvcc::Argv{"foo", nullptr, "bar"}; };
	CPPUNIT_ASSERT_THROW(throws(), std::bad_alloc);

	auto a = argvcc::Argv{"foo", "bar"};
	CPPUNIT_ASSERT_THROW(a.push_back(nullptr), std::bad_alloc);
}

void test::test_stdstring()
{
	auto a = argvcc::Argv{std::string("foo"), std::string("bar")};
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[2]);

	a.push_back(std::string("baz"));
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(3), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT(a[2] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("baz"), std::string(a[2]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[3]);
}

void test::test_iterators()
{
	auto a = argvcc::Argv();
	for (auto s: a) {
		CPPUNIT_ASSERT(false && s); // LCOV_EXCL_LINE
	}

	a = argvcc::Argv{"foo", "bar", "baz"};
	std::vector<std::string> v;
	copy(std::begin(a), std::end(a), back_inserter(v));
	CPPUNIT_ASSERT_EQUAL(size_t(3), v.size());
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), v[0]);
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), v[1]);
	CPPUNIT_ASSERT_EQUAL(std::string("baz"), v[2]);
}

void test::test_stdostream()
{
	auto ss = std::ostringstream();
	ss << argvcc::Argv{"foo", "bar", "baz"};
	CPPUNIT_ASSERT_EQUAL(std::string("foo bar baz"), ss.str());
}

void test::test_append()
{
	auto a = argvcc::Argv{};
	a.append(argvcc::Argv());
	CPPUNIT_ASSERT(a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(0), a.size());
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[0]);

	a.append(argvcc::Argv{"foo", "bar"});
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[2]);

	a.append(argvcc::Argv());
	CPPUNIT_ASSERT(!a.empty());
	CPPUNIT_ASSERT_EQUAL(size_t(2), a.size());
	CPPUNIT_ASSERT(a[0] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("foo"), std::string(a[0]));
	CPPUNIT_ASSERT(a[1] != static_cast<char *>(0));
	CPPUNIT_ASSERT_EQUAL(std::string("bar"), std::string(a[1]));
	CPPUNIT_ASSERT_EQUAL(static_cast<char *>(0), a[2]);
}

}}
