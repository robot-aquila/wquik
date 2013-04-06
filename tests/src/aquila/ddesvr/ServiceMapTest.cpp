/**
 * ============================================================================
 * 2011/07/27
 * $Id: ServiceMapTest.cpp 101 2011-08-11 18:37:57Z whirlwind $ Juno
 * ============================================================================
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "aquila/ddesvr/ServiceMap.h"
#include "aquila/core/auto_drop.h"
#include "aquila/core/WinApi.h"
#include "aquila/core/CriticalSection.h"
#include "aquila/core/MockCriticalSection.h"
#include "aquila/dde/MockCallbackHandler.h"

using namespace testing;
using namespace aquila::core;

namespace aquila {
	namespace ddesvr {

class ServiceMapTest : public ::testing::Test {
public:

	ServiceMapTest()
	  : winApi(WinApi::getInstance()),
	    cs(new CriticalSection(winApi))
	{

	}

protected:
	auto_drop<IWinApi> winApi;
	auto_drop<CriticalSection> cs;
	MockCallbackHandler handler;
	MockCriticalSection mockCs;
};

TEST_F(ServiceMapTest, testConstructorIncrementsRefCount) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));

	ASSERT_EQ(2, cs->getRefCount());
}}

TEST_F(ServiceMapTest, testDestructorDecrementsRefCount) {{
	ServiceMap* map = new ServiceMap(cs);
	map->drop();

	ASSERT_EQ(1, cs->getRefCount());
}}

TEST_F(ServiceMapTest, testAccessors) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));

	ASSERT_EQ(cs.get(), map->getCriticalSection());
}}

TEST_F(ServiceMapTest, testAdd_Locking) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);
	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->add("foobar", &handler);
}}

TEST_F(ServiceMapTest, testHas_Locking_Str) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);
	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->has("foobar");
}}

TEST_F(ServiceMapTest, testHas_Locking_Id) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);
	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->has(12345);
}}

TEST_F(ServiceMapTest, testRemove_Locking_Str) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->add("foobar", &handler);
	map->remove("foobar");
}}

TEST_F(ServiceMapTest, testRemove_Locking_Id) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->remove(map->add("foobar", &handler));
}}

TEST_F(ServiceMapTest, testRemoveAll_Locking) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->removeAll();
}}

TEST_F(ServiceMapTest, testGetName_Locking) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->getName(map->add("foobar", &handler));
}}

TEST_F(ServiceMapTest, testGetId_Locking) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->add("foobar", &handler);
	map->getId("foobar");
}}

TEST_F(ServiceMapTest, testGet_Locking_Str) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->add("foobar", &handler);
	map->get("foobar");
}}

TEST_F(ServiceMapTest, testGet_Locking_Id) {{
	InSequence s;
	EXPECT_CALL(mockCs, enter()).Times(1); // блокировка в add
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1);
	EXPECT_CALL(mockCs, leave()).Times(1);
	EXPECT_CALL(mockCs, enter()).Times(1); //блокировка в деструкторе removeAll
	EXPECT_CALL(mockCs, leave()).Times(1);

	auto_drop<ServiceMap> map(new ServiceMap(&mockCs));
	map->get(map->add("foobar", &handler));
}}

TEST_F(ServiceMapTest, testMainOperations) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	long serviceId = map->add("foo", &handler);
	ASSERT_STREQ("foo", map->getName(serviceId).c_str());
	ASSERT_EQ(serviceId, map->getId("foo"));
	ASSERT_EQ(&handler, map->get(serviceId));
	ASSERT_EQ(&handler, map->get("foo"));
	ASSERT_TRUE(map->has("foo"));
	ASSERT_TRUE(map->has(serviceId));
	ASSERT_EQ(2, handler.getRefCount()); // увеличивает счетчик ссылок
}}

TEST_F(ServiceMapTest, testRemoveAll) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	long service1Id = map->add("foo", &handler);
	long service2Id = map->add("bar", &handler);
	map->removeAll();
	ASSERT_FALSE(map->has("foo"));
	ASSERT_FALSE(map->has(service1Id));
	ASSERT_THROW(map->get(service1Id), std::exception);
	ASSERT_THROW(map->get("foo"), std::exception);
	ASSERT_THROW(map->getId("foo"), std::exception);
	ASSERT_THROW(map->getName(service1Id), std::exception);

	ASSERT_FALSE(map->has("bar"));
	ASSERT_FALSE(map->has(service2Id));
	ASSERT_THROW(map->get(service2Id), std::exception);
	ASSERT_THROW(map->get("bar"), std::exception);
	ASSERT_THROW(map->getId("bar"), std::exception);
	ASSERT_THROW(map->getName(service2Id), std::exception);
}}

TEST_F(ServiceMapTest, testAdd_ThrowsIfAlreadyExists) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	map->add("foo", &handler);
	ASSERT_THROW(map->add("foo", &handler), std::exception);
}}

TEST_F(ServiceMapTest, testRemove_ThrowsIfNotExists_Str) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->remove("foo"), std::exception);
}}

TEST_F(ServiceMapTest, testRemove_ThrowsIfNotExists_Id) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->remove(321), std::exception);
}}

TEST_F(ServiceMapTest, testGetName_ThrowsIfNotExists) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->getName(321), std::exception);
}}

TEST_F(ServiceMapTest, testGetId_ThrowsIfNotExists) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->getId("foo"), std::exception);
}}

TEST_F(ServiceMapTest, testGet_ThrowsIfNotExists_Name) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->get("zulu"), std::exception);
}}

TEST_F(ServiceMapTest, testGet_ThrowsIfNotExists_Id) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	ASSERT_THROW(map->get(321), std::exception);
}}

TEST_F(ServiceMapTest, testDestructorDropAllHandlers) {{
	ServiceMap* map = new ServiceMap(cs);
	map->add("foo", &handler);
	map->add("bar", &handler);
	ASSERT_EQ(3, handler.getRefCount());
	delete map;
	ASSERT_EQ(1, handler.getRefCount());
}}

TEST_F(ServiceMapTest, testRemove_Str) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	long service1Id = map->add("foo", &handler);
	long service2Id = map->add("bar", &handler);
	map->remove("foo");
	ASSERT_FALSE(map->has("foo"));
	ASSERT_FALSE(map->has(service1Id));
	ASSERT_THROW(map->get(service1Id), std::exception);
	ASSERT_THROW(map->get("foo"), std::exception);
	ASSERT_THROW(map->getId("foo"), std::exception);
	ASSERT_THROW(map->getName(service1Id), std::exception);

	ASSERT_TRUE(map->has("bar"));
	ASSERT_TRUE(map->has(service2Id));
	ASSERT_EQ(&handler, map->get(service2Id));
	ASSERT_EQ(&handler, map->get("bar"));
	ASSERT_EQ(service2Id, map->getId("bar"));
	ASSERT_STREQ("bar", map->getName(service2Id).c_str());
}}

TEST_F(ServiceMapTest, testRemove_Id) {{
	auto_drop<ServiceMap> map(new ServiceMap(cs));
	long service1Id = map->add("foo", &handler);
	long service2Id = map->add("bar", &handler);
	map->remove(service2Id);

	ASSERT_TRUE(map->has("foo"));
	ASSERT_TRUE(map->has(service1Id));
	ASSERT_EQ(&handler, map->get(service1Id));
	ASSERT_EQ(&handler, map->get("foo"));
	ASSERT_EQ(service1Id, map->getId("foo"));
	ASSERT_STREQ("foo", map->getName(service1Id).c_str());

	ASSERT_FALSE(map->has("bar"));
	ASSERT_FALSE(map->has(service2Id));
	ASSERT_THROW(map->get(service2Id), std::exception);
	ASSERT_THROW(map->get("bar"), std::exception);
	ASSERT_THROW(map->getId("bar"), std::exception);
	ASSERT_THROW(map->getName(service2Id), std::exception);
}}

	} // end namespace ddesvr
} // end namespace aquila